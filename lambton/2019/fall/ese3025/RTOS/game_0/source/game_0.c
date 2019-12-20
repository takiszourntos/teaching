/*
===============================================================================
 Name        : game_0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
	#if defined(NO_BOARD_LIB)
		#include "chip.h"
	#else
		#include "board.h"
	#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "libgameds.h"

// TODO: insert other definitions and declarations here

/* global variables */
volatile	queue_t	q; /* UART queue */
volatile	game_t	this_game;
ui_t		user;

/********************************************************************
 *
 * PRIVATE FUNCTIONS
 *
 ********************************************************************/

/*
 * function to initialize game at very beginning
 */
static void prvInitGame(void)
{
	/* new game parameters */
	this_game.score = 0;
	this_game.playerID="AAA";
	this_game.level = 1;
	/* allocate head for each GO list */
	this_game.aliens = (go_t *) pvPortMalloc(sizeof(go_t));
	this_game.poohs = (go_t *) pvPortMalloc(sizeof(go_t));
	this_game.expungers = (go_t *) pvPortMalloc(sizeof(go_t));
	this_game.babies = (go_t *) pvPortMalloc(sizeof(go_t));
	this_game.kitties = (go_t *) pvPortMalloc(sizeof(go_t));
	this_game.players = (go_t *) pvPortMalloc(sizeof(go_t));
}

/*
 * function to reset game board, called by vRunGameTask(), after scheduler has started
 */
static void prvResetBoard(void)
{
	/* send command to clear the game screen/board and wait for 5 seconds */
	taskENTER_CRITICAL();
	{
		prvUARTSend("C:clc"); /* command: clear console */
		vTaskDelay(configTICK_RATE_HZ*5); /* wait for a few seconds */
		prvUARTSend("D:emad studio inc. presents: ");
		vTaskDelay(configTICK_RATE_HZ*2);
		prvUARTSend("D:aliens & babies : at the daycare!");
		vTaskDelay(configTICK_RATE_HZ*5);
	}
	taskEXIT_CRITICAL();
}

/*
 * function to initialize hardware, run at the very beginning
 */
static void prvSetupHardware(void)
{
	#if defined (__USE_LPCOPEN)
		// Read clock settings and update SystemCoreClock variable
		SystemCoreClockUpdate();
	#if !defined(NO_BOARD_LIB)
		// Set up and initialize all required blocks and
		// functions related to the board hardware
		Board_Init();
		// Set the LED to the state of "On"
		Board_LED_Set(0, true);
	#endif
	#endif
}

/*
 *
 * MAIN FUNCTION
 *
 */
int main(void)
{
	char single_player_mode[30] = "single-player mode";

	/* hardware init */
	prvSetupHardware();

	/* new game init */
	prvInitGame();

	/* start game */
	xTaskHandle pvRunGameTaskHandle; /* supervisory task handle */
	xTaskCreate(vRunGameTask, "Supervisory Game Task", 4096,
				single_player_mode, &pvRunGameTaskHandle, RUN_GAME_PRIORITY);

	/* relinquish control to scheduler */
	vTaskStartScheduler();

	/* return error code if scheduler exits */
    return 1;
}
