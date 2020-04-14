/*
 *
 * enhanced blinky with buttons
 *
 *
 */

#include <stdint.h>

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
/* GPIO pin for interrupt */
#define GPIO_INTERRUPT_PIN_A   MYBUTTON_A_BIT_NUM	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PIN_B   MYBUTTON_B_BIT_NUM	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PORT    GPIOINT_PORT2		/* GPIO port number mapped to interrupt;
 	 	 	 	 	 	 	 	 	 	 	 	 	   we ASSUME that both GPIOs are on the
 	 	 	 	 	 	 	 	 	 	 	 	 	   same port! */

/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler	/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn			/* GPIO interrupt NVIC interrupt name */

/* global variables */
static volatile bool stateButtonA = false; // state of ButtonA, either pressed (true) or not
static volatile bool stateButtonB = false; // state of ButtonB, either pressed (true) or not
static volatile portTickType T_LED = configTICK_RATE_HZ / 2; // LED off time (configTICK_RATE_HZ corresponds to one second)
static const portTickType T_inc = 5; // configTICK_RATE_HZ / 8;
static const LED_t RLED = Red;
static const LED_t GLED = Green;
static const LED_t BLED = Blue;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
/**
 * @brief	Handle interrupt from GPIO pin or GPIO pin mapped to PININT
 * @return	Nothing
 */
void GPIO_IRQ_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT,
			(1 << GPIO_INTERRUPT_PIN_A) | (1 << GPIO_INTERRUPT_PIN_B));

	// check the button states
	stateButtonA = Board_MyButtons_Test(ButtonA); // Button A raises period
	stateButtonB = Board_MyButtons_Test(ButtonB); // Button B lowers period

	if (stateButtonA)
	{
		//  frequency decreases
		T_LED += T_inc;

	}
	else if (stateButtonB && (T_LED >= 2 * T_inc))
	{
		// frequency increases
		T_LED -= T_inc;
	}
}

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED states are OFF */
	Board_LED_Set(Red, Off);
	Board_LED_Set(Green, Off);
	Board_LED_Set(Blue, Off);

	/* Configure the GPIO interrupt */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIO_INTERRUPT_PORT,
			(1 << GPIO_INTERRUPT_PIN_A) | (1 << GPIO_INTERRUPT_PIN_B));

	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);

}

/* LED Task Function */
static void vLEDTask(void *pvParameters)
{
	LED_t LED = *((LED_t*) pvParameters); // get the LED colour
	volatile portTickType TInitOff, TOff; // temporal parameters of LED flashing
	volatile portTickType xLastWakeUpTime = 0; // needed for vTaskDelayUntil, "absolute time"

	while (1)
	{
		// update duration parameters (T_LED is changing based on ISR)
		TInitOff = ((portTickType) LED) * (T_LED + T_LED / 2); // initial off time is LED*1.5*T_LED
		TOff = (3 * T_LED + T_LED / 2) - TInitOff; // off "remainder" time is 3.5T_LED - TInitOff

		// delay relative to t = k*4.5*T_LED, k = 0, 1, 2, 3, ..., when Red LED comes on
		vTaskDelayUntil(&xLastWakeUpTime, TInitOff);
		//vTaskDelay(TInitOff);

		// turn LED on
		Board_LED_Set(LED, On);
		vTaskDelayUntil(&xLastWakeUpTime, T_LED);
		//vTaskDelay(T_LED);

		// turn LED off and wait for TOff ticks
		Board_LED_Set(LED, Off);
		vTaskDelayUntil(&xLastWakeUpTime, TOff);
		//vTaskDelay(TOff);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* Red LED thread */
	xTaskCreate(vLEDTask, (signed char* ) "R_LED Task",
			configMINIMAL_STACK_SIZE, (void* ) &RLED, (tskIDLE_PRIORITY + 3UL),
			(xTaskHandle *) NULL);

	/* Green LED thread */
	xTaskCreate(vLEDTask, (signed char* ) "G_LED Task",
			configMINIMAL_STACK_SIZE, (void* ) &GLED, (tskIDLE_PRIORITY + 2UL),
			(xTaskHandle *) NULL);

	/* Blue LED thread */
	xTaskCreate(vLEDTask, (signed char* ) "B_LED Task",
			configMINIMAL_STACK_SIZE, (void* ) &BLED, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * ORIGINAL PREAMBLE:
 */
/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
