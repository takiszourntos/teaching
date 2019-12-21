/*
 * libgametasks.c
 *
 *  Created on: Dec. 19, 2019
 *      Author: takis
 */

#include <stdlib.h>
#include <string.h>

/*
 * function sets up very basic default settings for a newly created GO
 *
 * 	NB: presumes that passed in GO pointer already points to valid memory
 *
 */
go_t* getGODefaults(go_t *pRet, char taskstring[])
{
	pRet->ID		= 0x000000; /* to be defined by genesisGO */
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
	pRet->numlives = 3;
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
		{
			go_t *pNode =createGONode(GOtype);
			pNode->ID = ID;
			pNode->pos = GOstartcoord;
		}
		taskEXIT_CRITICAL();
		return pNode;
	}
	else
	{
		while (pW->pNext != NULL)
		{
			pW = pW->pNext;
		}
	}

	return pGOHead;
}

void vRunGameTask(void *pvParams)
{
	go_t		*pW=NULL;
	xTaskHandle	pvImpactsTaskHandle;
	volatile 	game_t		*this_game;
	size_t 		player = *((size_t *) pvParams); /* human player number, up to a maximum of MAX_NUMBER_OF_PLAYERS */

	/* new game parameters */
	this_game.score = 0;
	this_game.playerID="AAA";
	this_game.level = 1;
	/* allocate head for each GO list, one character each */
	this_game.aliens = NULL;
	this_game.poohs = NULL;
	this_game.expungers = NULL;
	this_game.babies = NULL;
	this_game.kitties = NULL;

	/* give birth to the player GO for this game (recall that one "game" is allocated to each human player) */
	go_coord_t player_start_posn = {XMIDDLE, YBOTTOM};
	this_game.player = genesisGO(this_game.player,"player",player_start_posn,0x000000);

	while (1)
	{
		xSemaphoreTake(xGameMutex, portMAX_DELAY);
		{
			go_t *pWplayer = this_game.player; /* point to this game's player */
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
					/* inform player */
					prvUARTSend("C:clc\n");
					prvSayGoodbye(pWplayer->ID);
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
