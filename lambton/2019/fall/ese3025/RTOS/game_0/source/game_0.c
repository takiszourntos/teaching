/*
 ===============================================================================
 Name        : game_0.c
 Author      : Takis Zourntos
 Version     : 0.1 beta
 Copyright   : emad studio, inc.
 Description : main definition
 ===============================================================================
 */

#include "chip.h"
#include "board.h"
#include <cr_section_macros.h>

// TODO: insert other include files here
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdlib.h>
#include "libgameds.h"
#include <string.h>
#include "libgameIO.h"
#include "libgametasks.h"

// TODO: insert other definitions and declarations here

/********************************************************************
 * Global Variables
 ********************************************************************/
/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];
/* Transmit and receive ring buffers */
static RINGBUFF_T txring, rxring;

//volatile queue_t q; /* UART queue */
ui_t user_input =
  { False, False, False, False };
size_t number_of_players = 0;

xSemaphoreHandle xGameMutex = NULL;

/********************************************************************
 * Private Functions
 ********************************************************************/
/*
 * function to display number of players
 */
static void
prvShowNumPlayers (void)
{
  sendUARTText ("C:clc\r\n");
  char numplayers_str[2];
  sprintf (numplayers_str, "%d", number_of_players);
  char mesg[40] = "D:enter number of players: ";
  strcat (mesg, numplayers_str);
  strcat (mesg, "\r\n");
  sendUARTText (mesg);
}
/*
 * function to determine the number of players in the game
 */
static void
prvGetNumberofPlayers (void)
{
  prvShowNumPlayers ();
  /* get number of players */
  while (user.shoot == False)
    {
      if (user.move_right)
	{
	  if (number_of_players <= MAX_NUMBER_OF_PLAYERS)
	    {
	      number_of_players++;
	      prvShowNumPlayers ();
	    }
	}
      else if (user.move_left)
	{
	  if (number_of_players != 1)
	    {
	      number_of_players--;
	      prvShowNumPlayers ();
	    }
	}
    }
}
/*
 * function to reset game board, called by vRunGameTask(), after scheduler has started
 */
static void
prvResetBoard (void)
{
  /* send command to clear the game screen/board and wait for 5 seconds */
  taskENTER_CRITICAL();
  sendUARTText ("C:clc"); /* command: clear console */
  vTaskDelay (configTICK_RATE_HZ * 5); /* wait for a few seconds */
  sendUARTText ("D:emad studio inc. presents: ");
  vTaskDelay (configTICK_RATE_HZ * 2);
  sendUARTText ("D:aliens & babies : at the daycare!");
  vTaskDelay (configTICK_RATE_HZ * 5);
  taskEXIT_CRITICAL();
}

/*
 * function to initialize hardware, run at the very beginning, BEFORE scheduler,
 * please!
 */
static void
prvSetupHardware (void)
{
  SystemCoreClockUpdate ();
  Board_Init ();
  Board_LED_Set (0, true);
  Board_LED_Set (1, true);
  Board_LED_Set (2, true);

  /* Setup UART for 115.2K8N1 */
  Chip_UART_Init (UART_SELECTION);
  Chip_UART_SetBaud (UART_SELECTION, 115200);
  Chip_UART_ConfigData (UART_SELECTION, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
  Chip_UART_SetupFIFOS (UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
  Chip_UART_TXEnable (UART_SELECTION);

  /* Before using the ring buffers, initialize them using the ring
   buffer init function */
  RingBuffer_Init (&rxring, rxbuff, 1, UART_RRB_SIZE);
  RingBuffer_Init (&txring, txbuff, 1, UART_SRB_SIZE);

  /* Reset and enable FIFOs, FIFO trigger level 1 (4 bytes --- need zero latency!) */
  Chip_UART_SetupFIFOS (UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
  UART_FCR_TX_RS | UART_FCR_TRG_LEV1));

  /* Enable receive data and line status interrupt */
  Chip_UART_IntEnable (UART_SELECTION, (UART_IER_RBRINT | UART_IER_RLSINT));

  /* preemption = 1, sub-priority = 1 */
  NVIC_SetPriority (IRQ_SELECTION, 1);
  NVIC_EnableIRQ (IRQ_SELECTION);

  /* set up GPIO pin interrupts for user interface */

  /* set up DAC for sound effects */
}

/********************************************************************
 * MAIN CODE
 ********************************************************************/
int
main (void)
{
  /* use a mutex to protect a player's game */
  xGameMutex = xSemaphoreCreateMutex();

  /* hardware init */
  prvSetupHardware ();

  /* get the number of players */
  prvGetNumberofPlayers ();

  /* start game */
  for (size_t i = 0; i != number_of_players; ++i)
    {
      xTaskCreate(vRunGameTask, "Supervisory Game Task",
		  4*configMINIMAL_STACK_SIZE, (void * ) &i, NULL,
		  RUN_GAME_PRIORITY);
    }

  /* relinquish control to scheduler */
  vTaskStartScheduler ();

  /* return error code if scheduler exits */
  return 1;
}
