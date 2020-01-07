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
#include "libgameds.h"

/*************************************************************************
 *
 * Private Functions (invite only)
 *
 *************************************************************************/
/*
 * function to initialize game at very beginning
 */
static void prvInitGame(game_t *this_game)
{
	/* initialize GO code books */
	for (size_t i = 0; i != MAX_GO_CODES; ++i)
	{
		 /* GO IDs:
		 * 			0x0000 000q: players
		 * 			0x0000 00q0: aliens
		 * 			0x0000 0q00: poohs
		 * 			0x0000 q000: expungers
		 * 			0x000q 0000: babies
		 * 			0x00q0 0000: kitties
		 */

		this_game->aliensID[i].code		= 0x00000000 + (i << 4);
		this_game->poohsID[i].code		= 0x00000000 + (i << 8);
		this_game->expungersID[i].code	= 0x00000000 + (i << 12);
		this_game->babiesID[i].code		= 0x00000000 + (i << 16);
		this_game->kittiesID[i].code	= 0x00000000 + (i << 20);

		this_game->aliensID[i].available	= True;
		this_game->poohsID[i].available		= True;
		this_game->expungersID[i].available	= True;
		this_game->babiesID[i].available	= True;
		this_game->kittiesID[i].available	= True;
	}

	this_game->number_of_aliens = 0;
	this_game->number_of_poohs = 0;
	this_game->number_of_expungers = 0;
	this_game->number_of_babies = 0;
	this_game->number_of_kitties = 0;

	return;
}
static bool_t prvGetGOIDCode(go_ID_t *book, uint32_t *code)
{
	bool_t code_found=False;

	/* find an available code */
	for (size_t i=0; i != MAX_GO_CODES; ++i)
	{
		if (book[i].available)
		{
			*code = book[i].code;
			code_found=True;
			book[i].available=False;
			break;
		}
	}
	return code_found;
}


static bool_t prvYesHappens(likely_t prob)
{
	int r = rand(); /* pull my finger */
	register int s = RAND_MAX;

	s=s << prob;
	if (r < s)
	{
		return True;
	}
	else
	{
		return False;
	}
}

/*
 * Uses addGONode() to create a GO list element, then applies xTaskCreate()
 * to generate the behaviour for that GO
 */
static go_t* spawnGONodeandTask(game_t *this_game, go_t *pGOHead,
								uint8_t GOtype, go_coord_t GOstartcoord,
								go_id_t *codebook, uint32_t GOIDcode)
{
	/* GOtype values (listed here for reference):
	 * 		0 -> player
	 * 		1 -> alien
	 * 		2 -> poohs
	 * 		3 -> expungers
	 * 		4 -> babies
	 * 		5 -> kitties
	 */
	/* initialize working pointer */
	if (!GOtype) // player
	{
		if (pGOHead==NULL) // list is empty, create the first player
		{
			taskENTER_CRITICAL();
			go_t *pW = addGONode(this_game, pGOHead, 0, GOstartcoord, GOIDcode);
			xTaskCreate(vPlayerTask, pW->taskText,
						256, (void *) this_game,
						&(pW->task), GO_TASK_PRIORITY);
			taskEXIT_CRITICAL();
			return pW;
		}
	}
	else // any other type of game object
	{
		if (pGOHead==NULL) // the list is empty
		{
			taskENTER_CRITICAL();
			go_t *pW = addGONode(pGOHead, GOType, GOstartcoord, GOIDCode);
								baby_start_posn_LEFT, GOIDcode);
			switch (GOType)
			{
				case 1:
					xTaskCreate(vAliensTask, pW->taskText,
								256, (void *) this_game,
								&(pW->task), GO_TASK_PRIORITY);
				case 2:
					xTaskCreate(vPoohsTask, pW->taskText,
								256, (void *) this_game,
								&(pW->task), GO_TASK_PRIORITY);
				case 3:
					xTaskCreate(vExpungersTask, pW->taskText,
								256, (void *) this_game,
								&(pW->task), GO_TASK_PRIORITY);
				case 4:
					xTaskCreate(vBabiesTask, pW->taskText,
								256, (void *) this_game,
								&(pW->task), GO_TASK_PRIORITY);
				case 5:
					xTaskCreate(vKittiesTask, pW->taskText,
								256, (void *) this_game,
								&(pW->task), GO_TASK_PRIORITY);
			}
			taskEXIT_CRITICAL();
			return pW;
		}
		else
		{
			/* there is already at least one element in the GO list,
			 * so find the next available spot... */
			go_t* pW = pGOHead;
			while (pW->pNext != NULL)
				pW = pW->pNext;
			taskENTER_CRITICAL();
			go_t* pNew = addGONode(pGOHead, GOType, GOstartcoord, GOIDCode);
			pW->pNext = pNew;
			switch (GOType)
			{
				case 1:
					xTaskCreate(vAliensTask, pNew->taskText, 256,
						(void *) this_game, &(pNew->task), GO_TASK_PRIORITY);
				case 2:
					xTaskCreate(vPoohsTask, pNew->taskText, 256,
						(void *) this_game, &(pNew->task), GO_TASK_PRIORITY);
				case 3:
					xTaskCreate(vExpungersTask, pNew->taskText, 256,
						(void *) this_game, &(pNew->task), GO_TASK_PRIORITY);
				case 4:
					xTaskCreate(vBabiesTask, pNew->taskText, 256,
						(void *) this_game, &(pNew->task), GO_TASK_PRIORITY);
				case 5:
					xTaskCreate(vKittiesTask, pNew->taskText, 256,
						(void *) this_game, &(pNew->task), GO_TASK_PRIORITY);
			}
			taskEXIT_CRITICAL();
		}
	}



	taskENTER_CRITICAL();
		if (prvGetGOIDCode(babiesID, &GOIDcode))
		{
			this_game->babies = addGONode(this_game->babies, "baby",
									baby_start_posn_LEFT, GOIDcode);
			this_game->babies->numlives=1; /* each baby has ... */
			xTaskCreate(vBabiesTask, this_game->babies->taskText,
						256, (void *) &this_game,
						&this_game->babies->task, GO_TASK_PRIORITY);
		}
		if (prvGetGOIDCode(babiesID, &GOIDcode))
		{
			this_game->babies = addGONode(this_game->babies, "baby",
										baby_start_posn_MID, GOIDcode);

			this_game->babies->pNext->numlives=1; /* only one life */
			xTaskCreate(vBabiesTask, this_game->babies->taskText,
						256, (void *) &this_game,
						&this_game->babies->pNext->task, GO_TASK_PRIORITY);
		}
	taskEXIT_CRITICAL();


}

static void prvDeleteAllTasks(game_t game)
{
	go_t *pW = NULL;
	go_t *pTemp=NULL;

	/* eradicate aliens */
	pW = game.aliens;
	while (pW != NULL)
	{
		vTaskDelete(pW->task);
		pTemp=pW->pNext; /* save the pointer to the next GO node */
		vPortFree(pW); /* delete current GO node */
		pW=pTemp; /* move on to the next one */
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
	/* free all codes from GO code book */
	for (size_t i = 0; i != MAX_GO_CODES; ++i)
	{
		 /* GO IDs:
		 * 			0x0000 000q: players
		 * 			0x0000 00q0: aliens
		 * 			0x0000 0q00: poohs
		 * 			0x0000 q000: expungers
		 * 			0x000q 0000: babies
		 * 			0x00q0 0000: kitties
		 */
		aliensID[i].available		= True;
		poohsID[i].available		= True;
		expungersID[i].available	= True;
		babiesID[i].available		= True;
		kittiesID[i].available		= True;
	}

}

void vPlayerTask(void *pvParams)
{
	//
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
	volatile 	game_t *this_game = (game_t *) pvPortMalloc(sizeof(game_t));
	size_t 		player = *((size_t *) pvParams); /* human player number, up to
													a maximum of
													MAX_NUMBER_OF_PLAYERS */
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
	/* initialize code books and record-keeping variables */
	prvInitGame(this_game);

	/* give birth to the player GO for this game (recall that one "game"
	 * 					is allocated to each human player) */

	go_coord_t player_start_posn = {XMIDDLE, YBOTTOM};
	this_game->player = spawnGONodeandTask(this_game, this_game->player, 0,
							player_start_posn, NULL, 0x00000001);

	while (1)
	{
		xSemaphoreTake(xGameMutex, portMAX_DELAY);
		{
			go_t *pWplayer = this_game->player; /* point to this
													game's player */
			if (pWplayer->active)
			{
				prvResetBoard();
				prvUARTSend("D: Player %zu",player); /* prompt the player */
				vTaskDelay(5*configTICK_RATE_HZ); /* wait 5 seconds */
				/* create Impacts Task (with lower priority than RunGameTask())
				 * to run the show */
				xTaskCreate(vImpactsTask, "Impact-checking Task",
						1024, (void *) &this_game,
						&pvImpactsTaskHandle, IMPACTS_TASK_PRIORITY);

				/* keep running until player loses life */
				while ((pWplayer->alive))
				{
					vTaskDelay(DELAY_RUN_GAME); /* relinquish control of game
													to tasks just created for a
														period of time */
				}
				/* player died, update status */
				if (  ( --(pWplayer->numlives) ) == 0  )
				{
					pWplayer->gameover=True;
					vTaskDelete(pvImpactsTaskHandle);
					prvDeleteAllTasks(this_game);
					/* inform player */
					prvUARTSend("C:clc\n");
					prvSayGoodbye(pWplayer->ID); /* say goodbye to player,
													get their initials */
					vTaskDelay(configTICK_RATE_HZ*5); /* wait 5 seconds */
				}
		}
		xSemaphoreGive(xGameMutex);
	} /* end while (1) */
}

static void vImpactsTask(void *pvParams)
{
	game_t *this_game = (game_t *) pvParams;
	uint32_t GOIDcode;

	/*
	 * to begin with, spawn off an alien and two babies...
	*/
	if (prvGetGOIDCode(this_game->aliensID, &GOIDcode))
	{
		go_coord_t alien_start_posn = {XMIDDLE, YMIDDLE};
		spawnGONodeandTask(this_game, this_game->aliens, alien,
							alien_start_posn, this_game->aliensID, GOIDcode);
	}
	if (prvGetGOIDCode(this_game->babiesID, &GOIDcode))
	{
		go_coord_t baby_start_posn_LEFT = {XLEFT, YBOTTOM};
		spawnGONodeandTask(this_game, this_game->babies, baby,
				baby_start_posn_LEFT, this_game->babiesID, GOIDcode);

	}
	if (prvGetGOIDCode(this_game->babiesID, &GOIDcode))
	{
		go_coord_t baby_start_posn_MID = {XMIDDLE, YBOTTOM};
		spawnGONodeandTask(this_game, this_game->babies, baby,
				baby_start_posn_MID, this_game->babiesID, GOIDcode);
	}

	/* main loop of Impacts Task */
	while (1)
	{
		/* simple way to set the game level */
		this_game->game_level = this_game->score / LEVELUP;

		/* is it time to spawn an alien? number of aliens
		 * should be (game_level + 1) */
		if ( number_of_aliens < (this_game->game_level+1) )
		{
			/* a high probability exists of an alien being created */
			if (prvYesHappens(QuiteLikely))
			{
				if (prvGetGOIDCode(aliensID, &GOIDcode))
				{
					/* spawn an alien */
					taskENTER_CRITICAL();
						go_coord_t alien_start_posn = {XMIDDLE, YMIDDLE};

						this_game->aliens = addGONode(this_game->aliens,"alien",
													alien_start_posn,GOIDcode);
						this_game->aliens->numlives = 1;
						this_game->aliens->health = 1024;
						xTaskCreate(vAliensTask, this_game->aliens->taskText,
									256, (void *) &this_game,
									&this_game->aliens->task, GO_TASK_PRIORITY);
					taskEXIT_CRITICAL();
				}
			}
		}

		/* is it time to spawn a kitty? The number of kitties should be
		 * 			(game_level + 1) */
		if ( number_of_kitties < (this_game->game_level+1) )
		{
			/* a some probability exists of a kitty showing up,
			 * in which case the alien's pooh may start dropping */
			if (prvYesHappens(Maybe))
			{
				if (prvGetGOIDCode(kittiesID, &GOIDcode)) // kitties available?
				{
					/* spawn a kitty */
					taskENTER_CRITICAL();
						go_coord_t kitties_start_posn = {XRIGHT, YBOTTOM};

						this_game->kitties = addGONode(this_game->kitties,
												"kitty", kitties_start_posn,
												GOIDcode);
						this_game->kitties->numlives = 1;
						this_game->kitties->health = 8192;
						xTaskCreate(vKittiesTask, this_game->kitties->taskText,
									256, (void *) &this_game,
									&this_game->kitties->task,
									GO_TASK_PRIORITY);
					taskEXIT_CRITICAL();
				}
			}
		}

		/* check alien proximity to kitties and expungers */
		pW = this_game->aliens;
		while (pW != NULL)
		{
			prvComputeProximities(pW, this_game->expungers);
			prvComputeProximities(pW, this_game->kitties);
			pW = pW->pNext;
		}
		/* check player proximity to poohs, kitties or babies */
		pW = this_game->player;
		while (pW != NULL)
		{
			prvComputeProximities(pW, this_game->poohs);
			prvComputeProximities(pW, this_game->kitties);
			prvComputeProximities(pW, this_game->babies);
			pW = pW->pNext;
		}
		/* check babies for proximities to poohs */

		// prvCreateTasks(this_game.aliens, vAliensTask);
		/* babies */
		prvCreateTasks(this_game.babies, vBabiesTask);
		/* kitties */
		// prvCreateTasks(this_game.kitties, vKittiesTask);
	}
}
