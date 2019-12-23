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
	volatile 	game_t		*this_game;
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

	/* give birth to the player GO for this game (recall that one "game" is allocated to each human player) */
	taskENTER_CRITICAL();
		go_coord_t player_start_posn = {XMIDDLE, YBOTTOM};
		this_game->player = genesisGO(this_game->player,"player",player_start_posn,0x00000001);
		//this_game->player->numlives = 3; /* player starts with three lives */
		xTaskCreate(vPlayerTask, this_game->player->taskText,
					256, NULL, &this_game->player->task, GO_TASK_PRIORITY);
	taskEXIT_CRITICAL();

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
						1024, NULL, &pvImpactsTaskHandle, IMPACTS_TASK_PRIORITY);
				/* keep running until player loses life */
				while ((pWplayer->alive))
				{
					vTaskDelay(DELAY_RUN_GAME); /* relinquish control of game to tasks just created for a period of time */
				}
				/* player died, update status */
				if (  ( --(pWplayer->numlives) ) == 0  )
				{
					pWplayer->gameover=True;
					vTaskDelete(pvImpactsTaskHandle);
					prvDeleteAllTasks(this_game);
					/* inform player */
					prvUARTSend("C:clc\n");
					prvSayGoodbye(pWplayer->ID); /* say goodbye to player, get their initials */
					vTaskDelay(configTICK_RATE_HZ*5);
				}
		}
		xSemaphoreGive(xGameMutex);
	} /* end while (1) */
}

static void vImpactsTask(void *pvParams)
{
	/* to begin with, spawn off an alien, two babies and a kitty, initially
	 *  off screen... */
	taskENTER_CRITICAL();
		go_coord_t alien_start_posn = {XMIDDLE, YMIDDLE};
		go_coord_t baby_start_posn = {XLEFT, YBOTTOM};
		go_coord_t kitty_start_posn = {XRIGHT, YBOTTOM};

		this_game->aliens = genesisGO(this_game->aliens,"alien",
										alien_start_posn,0x00000010);
		//this_game->player->numlives = 3; /* player starts with three lives */
		xTaskCreate(vAliensTask, this_game->aliens->taskText,
					256, NULL, &this_game->aliens->task, GO_TASK_PRIORITY);

	taskEXIT_CRITICAL();

	RAND_MAX;
	while (1)
	{
		/* is it time to increase the game level? */


		/* is it time to spawn an alien? */

		/* aliens */
		// prvCreateTasks(this_game.aliens, vAliensTask);
		/* babies */
		prvCreateTasks(this_game.babies, vBabiesTask);
		/* kitties */
		// prvCreateTasks(this_game.kitties, vKittiesTask);
	}
}
