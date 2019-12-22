/*
 * libgametasks.c
 *
 *  Created on: Dec. 19, 2019
 *      Author: takis
 */

#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

/*************************************************************************
 *
 * Private Functions (invite only)
 *
 *************************************************************************/
static void prvDeleteAllTasks(game_t game)
{
	go_t *pW = NULL;
	go_t *pTemp=NULL;

	/* eradicate aliens */
	pW = game.aliens;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext;
		vPortFree(pW);
		pW=pTemp;
	}
	/* eradicate poohs */
	pW = game.poohs;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext;
		vPortFree(pW);
		pW=pTemp;
	}
	/* eradicate babies */
	pW = game.babies;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext;
		vPortFree(pW);
		pW=pTemp;
	}
	/* eradicate kitties */
	pW = game.kitties;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext;
		vPortFree(pW);
		pW=pTemp;
	}
	/* eradicate expungers */
	pW = game.expungers;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext;
		vPortFree(pW);
		pW=pTemp;
	}


}

/*
 * function sets up very basic default settings for a newly created GO
 *
 * 	NB: presumes that passed in GO pointer already points to valid memory
 *
 */
go_t* getGODefaults(go_t *pRet, char taskstring[])
{
	/*
	 * GO IDs:
	 * 			0x0000 000q: players
	 * 			0x0000 00q0: aliens
	 * 			0x0000 0q00: poohs
	 * 			0x0000 q000: expungers
	 * 			0x000q 0000: babies
	 * 			0x00q0 0000: kitties
	 *
	 * 			where q \in {0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F}
	 *
	 */
	pRet->ID		= 0x00000000UL; /* to be defined by genesisGO */
	pRet->go_level	= 1;
	pRet->health 	= 256;
	pRet->alive 	= True;
	pRet->active	= True;
	pRet->on_screen	= True;
	pRet->gameover	= False;
	pRet->pos.X = 0; pRet->pos.Y = 0;
	pRet->vel.X = 0; pRet->vel.Y = 0;
	pRet->acc.X = 0; pRet->acc.Y = 0;
	pRet->move_left = False;
	pRet->move_right = False;
	pRet->crouch_or_extra = False;
	pRet->shoot_or_pooh = False;
	pRet->numlives = 1;
	pRet->interactions=NULL;
	pRet->task=NULL;
	pRet->taskText=taskstring;
	pRet->pNext=NULL;
	pRet->pPrev=NULL;

	return pRet;
}

/*
 * creates a basic GO node, with default information based on GO type
 */
go_t* createGONode(char GOtype[])
{
	go_t *pNew = (go_t *) pvPortMalloc(sizeof(go_t));

	if (strcmp(GOtype,"player")==0)
	{
		pNew = getGODefaults(pNew, "player task");
		return pNew;
	}
}

/*
 * creates a game object for the first time, adding it to the GO master list
 */
go_t*	genesisGO(go_t* pGOHead, char GOtype[], go_coord_t GOstartcoord, size_t ID)
{
	go_t* pW=pGOHead; /* working pointer */

	if (pW==NULL)
	{
		/* create the first instance of this GO */
		taskENTER_CRITICAL(); /* need to properly position and initialize an object before game play can resume */
			go_t *pNode =createGONode(GOtype); /* creates a GO node of desired type with generic, default settings */
			pNode->ID = ID;
			pNode->pos = GOstartcoord;
		taskEXIT_CRITICAL();
		return pNode;
	}
	else
	{
		/* find the next available opening in the list */
		while (pW->pNext != NULL)
		{
			pW = pW->pNext;
		}
		/* now add the GO there, with the proper settings */
		taskENTER_CRITICAL();
			pW->pNext = createGONode(GOtype); /* creates a GO node of desired type with generic, default settings */
			pW->pNext->ID = ID;
			pW->pNext->pos = GOstartcoord;
			pW->pNext->pPrev=pW;
		taskEXIT_CRITICAL();
	}
	return pGOHead;
}

/*
 *
 * High-level supervisory task for each game (one game for each human player)
 *
 */
void vRunGameTask(void *pvParams)
{
	go_t		*pW=NULL;
	xTaskHandle	pvImpactsTaskHandle;
	volatile 	game_t		*this_game;
	size_t 		player = *((size_t *) pvParams); /* human player number, up to a maximum of MAX_NUMBER_OF_PLAYERS */

	/* new game parameters */
	this_game->score = 0;
	this_game->playerID="AAA";
	this_game->level = 1;
	/* initialize GO lists */
	this_game->aliens = NULL;
	this_game->poohs = NULL;
	this_game->expungers = NULL;
	this_game->babies = NULL;
	this_game->kitties = NULL;
	this_game->player = NULL;

	/* give birth to the player GO for this game (recall that one "game" is allocated to each human player) */
	go_coord_t player_start_posn = {XMIDDLE, YBOTTOM};
	this_game->player = genesisGO(this_game->player,"player",player_start_posn,0x00000001);
	this_game->player->numlives = 3; /* player starts with three lives */

	while (1)
	{
		xSemaphoreTake(xGameMutex, portMAX_DELAY);
		{
			go_t *pWplayer = this_game->player; /* point to this game's player */
			if (pWplayer->active)
			{
				prvResetBoard();
				prvGreetPlayer(player);
				/* create Impacts Task to run the show */
				xTaskCreate(vImpactsTask, "Impact-checking Task",
						2048, NULL, &pvImpactsTaskHandle, IMPACTS_TASK_PRIORITY);
				/* keep running until player loses life */
				while ((pWplayer->alive))
				{
					vTaskDelay(DELAY_RUN_GAME); /* relinquish control of game to tasks just created for a period of time */
				}
				/* player died, update status */
				if (  ( --(pWplayer->numlives) ) == 0  )
				{
					pWplayer->gameover=True;
					vTaskDeleta(pvImpactsTaskHandle);
					prvDeleteAllTasks(this_game);
					/* inform player */
					prvUARTSend("C:clc\n");
					prvSayGoodbye(pWplayer->ID); /* say goodbye to player, get their initials */
					vTaskDelay(configTICK_RATE_HZ*5);

				}
		}
		xSemaphoreGive(xGameMutex);
	} /* end while (1)*/
}

static void vImpactsTask(void *pvParams)
{
	/* aliens */
	// prvCreateTasks(this_game.aliens, vAliensTask);
	/* babies */
	prvCreateTasks(this_game.babies, vBabiesTask);
	/* kitties */
	// prvCreateTasks(this_game.kitties, vKittiesTask);

}
