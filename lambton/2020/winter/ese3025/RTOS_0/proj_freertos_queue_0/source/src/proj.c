/*
 *

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
SemaphrHandle_t xMutex

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/



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
