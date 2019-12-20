/*
 * libgametasks.c
 *
 *  Created on: Dec. 19, 2019
 *      Author: takis
 */

#include <stdlib.h>


void vRunGameTask(void *pvParams)
{
	go_t	*pW=NULL;
	xTaskHandle	pvImpactsTaskHandle;

	while (1)
	{
		/* find the active player, there must be one left or we would have exited before getting here */
		go_t *pWplayer = this_game.players; /* point to first player */
		while (!(pWplayer->active) || (pWplayer==NULL))
		{
			pWplayer = pWplayer->pNext;
		}
		prvResetBoard();
		prvGreetPlayer(pWplayer->ID);
		/* create remaining processes and GO tasks */
		xTaskCreate(vImpactsTask, "Impact-checking Task",
					2048, NULL, &pvImpactsTaskHandle, IMPACTS_TASK_PRIORITY);
		/* aliens */
		prvCreateTasks(this_game.aliens, vAliensTask);
		/* player */
		prvCreateTasks(this_game.players, vPlayersTask);
		/* babies */
		prvCreateTasks(this_game.babies, vBabiesTask);
		/* kitties */
		prvCreateTasks(this_game.kitties, vKittiesTask);
		/* keep running until player loses life */
		while ((pWplayer->alive))
		{

		}
		/* player died, update status */
		pWplayer->active=False;
		if (  ( --(pWplayer->numlives) ) == 0  )
		{
			pWplayer->gameover=True;
			/* inform player */
			taskENTER_CRITICAL();
			{
				prvUARTSend("C:clc\n");
				prvSayGoodbye(pWplayer->ID);
				vTaskDelay(configTICK_RATE_HZ*5);
			}
			taskEXIT_CRITICAL();

		}
		go_t *pWnextplayer = pWplayer->pNext;
		/* search remainder of list */
		while ((pWnextplayer->gameover == True) || pWnextplayer != NULL)
		{
			pWnextplayer = pWnextplayer->pNext;
		}
		if ((pWnextplayer==NULL))
		{
			/* try searching from the top */
			pWnextplayer == this_game.players;
			while ((pWnextplayer->gameover == True) || pWnextplayer != NULL)
			{
				pWnextplayer = pWnextplayer->pNext;
			}
			if ((pWnextplayer==NULL))
			{
				/* all players have GAME OVER, so game is truly over! */
				taskENTER_CRITICAL();
				{
					prvUARTSend("C:clc\n");
					prvUARTDisplay("D:INSERT COIN\n");
					vTaskDelay(configTICK_RATE_HZ*5);
				}
				taskEXIT_CRITICAL();
				vTaskEndScheduler(); /* shut down OS, restart required */
			}
		}
		/* we have found our next active player! */
		pWnextplayer->active=True;

	} /* end while (1)*/

}

