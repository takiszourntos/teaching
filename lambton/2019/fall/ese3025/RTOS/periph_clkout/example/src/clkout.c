/*
 * @brief CLKOUT example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

#include "board.h"
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static volatile uint32_t ticks100;

#define MIN_CLKOUT_SELECTION SYSCTL_CLKOUTSRC_CPU
#if defined(CHIP_LPC175X_6X)
#define MAX_CLKOUT_SELECTION SYSCTL_CLKOUTSRC_RTC
#else
#define MAX_CLKOUT_SELECTION SYSCTL_CLKOUTSRC_WATCHDOGOSC
#endif

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
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	ticks100++;
	if ((ticks100 % 100) == 0) {
		Board_LED_Toggle(0);
	}
}

/**
 * @brief	main routine for CLKOUT example
 * @return	Always returns 0
 */
int main(void)
{
	CHIP_SYSCTL_CLKOUTSRC_T clkoutClks;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Enable and setup SysTick Timer at a 100Hz rate */
	SysTick_Config(SystemCoreClock / 100);

	/* Cycle through all clock sources for the CLKOUT pin */
	for (clkoutClks = MIN_CLKOUT_SELECTION;
		 clkoutClks <= MAX_CLKOUT_SELECTION; clkoutClks++) {
		ticks100 = 0;

		/* Setup CLKOUT pin for specific clock with a divider of 1 */
		Chip_Clock_SetCLKOUTSource(clkoutClks, 1);

		/* Enable CLKOUT */
		Chip_Clock_EnableCLKOUT();

		/* Wait 5 seconds */
		while (ticks100 < 500) {
			__WFI();
		}
	}

	/* Disable CLKOUT */
	Chip_Clock_DisableCLKOUT();

	return 0;
}

/**
 * @}
 */
