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
volatile	queue_t	q;
volatile	game_t	this_game;
ui_t		user;

/*
 * PRIVATE FUNCTIONS
 */
static void prvInitGame(void)
{
	this_game.score = 0;
	this_game.playerID = {'A','A','A','\0'};
	this_game.level = 1;
	this_game.aliens = (go_t *) pvPortMalloc(MAXALIENS*sizeof(go_t));
	this_game.poohs = (go_t *) pvPortMalloc(MAXPOOHS*sizeof(go_t));
	this_game.expungers = (go_t *) pvPortMalloc(MAXEXPUNGERS*sizeof(go_t));
	this_game.babies = (go_t *) pvPortMalloc(MAXBABIES*sizeof(go_t));
	this_game.kitties = (go_t *) pvPortMalloc(MAXKITTIES*sizeof(go_t));
	this_game.players = (go_t *) pvPortMalloc(MAXPLAYERS*sizeof(go_t));
}

int main(void) {

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

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
