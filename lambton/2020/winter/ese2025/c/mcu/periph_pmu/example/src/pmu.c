/*
 * @brief PMU example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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
#include "stopwatch.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Change this value to increase/decrease the time between power state changes */
#define POWER_CYCLE_SEC_DELAY 10

/* Index of PMU GP registers */
#define PWR_CYCLE_COUNT_REG_INDEX 0

#define SEND_DELAY_MS 1000

static volatile bool fIntervalReached;
static volatile bool fAlarmTimeMatched;
RTC_TIME_T FullTime;


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Handle interrupt from GPIO pin or GPIO pin mapped to PININT */
static void ProcessPowerState(CHIP_PMU_MCUPOWER_T crntPowerSetting)
{
	volatile uint32_t tempTimeout;

	/* Output power status message, add separating space */
	DEBUGSTR("\r\n");

	/* Switch on current selected power setting */
	switch (crntPowerSetting) {
	case PMU_MCU_SLEEP:
	default:
		DEBUGSTR("-----------------------------------------------------------------\r\n");
		DEBUGSTR("     Entering SLEEP power setting\r\n");
		DEBUGOUT("       (System will exit SLEEP in %d seconds)\r\n", POWER_CYCLE_SEC_DELAY);
		DEBUGSTR("-----------------------------------------------------------------\r\n\r\n");

		/* Delay to allow all bytes to send out UART. */
		StopWatch_DelayMs(SEND_DELAY_MS);

		/* Enter MCU Sleep mode */
		Chip_PMU_SleepState(LPC_PMU);

		break;

	case PMU_MCU_DEEP_SLEEP:
		DEBUGSTR("-----------------------------------------------------------------\r\n");
		DEBUGSTR("     Entering DEEP SLEEP power setting\r\n");
		DEBUGOUT("       (System will exit DEEP SLEEP in %d seconds)\r\n", POWER_CYCLE_SEC_DELAY);
		DEBUGSTR("-----------------------------------------------------------------\r\n\r\n");

		/* Delay to allow all bytes to send out UART. */
		StopWatch_DelayMs(SEND_DELAY_MS);

		/* Enter MCU Deep Sleep mode */
		Chip_PMU_DeepSleepState(LPC_PMU);

		break;

	case PMU_MCU_POWER_DOWN:
		DEBUGSTR("-----------------------------------------------------------------\r\n");
		DEBUGSTR("     Entering POWER DOWN power setting\r\n");
		DEBUGOUT("       (System will exit POWER DOWN in %d seconds)\r\n", POWER_CYCLE_SEC_DELAY);
		DEBUGSTR("-----------------------------------------------------------------\r\n\r\n");

		/* Delay to allow all bytes to send out UART. */
		StopWatch_DelayMs(SEND_DELAY_MS);

		/* Enter MCU Power down mode */
		Chip_PMU_PowerDownState(LPC_PMU);

		break;

	case PMU_MCU_DEEP_PWRDOWN:
		DEBUGSTR("-----------------------------------------------------------------\r\n");
		DEBUGSTR("     Entering DEEP POWER DOWN power setting\r\n");
		DEBUGOUT("       (System will exit DEEP POWER DOWN in %d seconds)\r\n", POWER_CYCLE_SEC_DELAY);
		DEBUGSTR("-----------------------------------------------------------------\r\n\r\n");

		/* Delay to allow all bytes to send out UART. */
		StopWatch_DelayMs(SEND_DELAY_MS);

		/* Enter MCU Deep Power down mode */
		Chip_PMU_DeepPowerDownState(LPC_PMU);

		break;
	}
}

/* Gets and shows the current time and date */
static void showTime(RTC_TIME_T *pTime)
{
	DEBUGOUT("Time: %.2d:%.2d:%.2d %.2d/%.2d/%.4d\r\n",
			 pTime->time[RTC_TIMETYPE_HOUR],
			 pTime->time[RTC_TIMETYPE_MINUTE],
			 pTime->time[RTC_TIMETYPE_SECOND],
			 pTime->time[RTC_TIMETYPE_MONTH],
			 pTime->time[RTC_TIMETYPE_DAYOFMONTH],
			 pTime->time[RTC_TIMETYPE_YEAR]);
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	RealTimeClock (RTC) Interrupt Handler
 * @return	None
 */
void RTC_IRQHandler(void)
{
	/* Check for alarm match */
	if (Chip_RTC_GetIntPending(LPC_RTC, RTC_INT_ALARM)) {
		/* Clear pending interrupt */
		Chip_RTC_ClearIntPending(LPC_RTC, RTC_INT_ALARM);
		fAlarmTimeMatched = true;	/* set alarm handler flag */
	}

	Board_LED_Toggle(0);
}

/**
 * @brief	Main program body
 * @return	int
 */
int main(void)
{
	CHIP_PMU_MCUPOWER_T crntPowerSetting;

	/* Setup SystemCoreClock and any needed board code */
	SystemCoreClockUpdate();
	Board_Init();
	StopWatch_Init();


	fIntervalReached  = 0;
	fAlarmTimeMatched = 0;
	Board_LED_Set(2, false);

	Chip_RTC_Init(LPC_RTC);

	/* Set current time for RTC 2:00:00PM, 2012-10-05 */
	FullTime.time[RTC_TIMETYPE_SECOND]  = 0;
	FullTime.time[RTC_TIMETYPE_MINUTE]  = 0;
	FullTime.time[RTC_TIMETYPE_HOUR]    = 14;
	FullTime.time[RTC_TIMETYPE_DAYOFMONTH]  = 5;
	FullTime.time[RTC_TIMETYPE_DAYOFWEEK]   = 5;
	FullTime.time[RTC_TIMETYPE_DAYOFYEAR]   = 279;
	FullTime.time[RTC_TIMETYPE_MONTH]   = 10;
	FullTime.time[RTC_TIMETYPE_YEAR]    = 2012;

	Chip_RTC_SetFullTime(LPC_RTC, &FullTime);

	/* Set ALARM time for wakeup time */
	FullTime.time[RTC_TIMETYPE_SECOND]  = 
		(FullTime.time[RTC_TIMETYPE_SECOND] + POWER_CYCLE_SEC_DELAY) % 60;
	Chip_RTC_SetFullAlarmTime(LPC_RTC, &FullTime);

	/* Enable matching for alarm for second field only */
	Chip_RTC_AlarmIntConfig(LPC_RTC, RTC_AMR_CIIR_IMSEC, ENABLE);

	/* Clear interrupt pending */
	Chip_RTC_ClearIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE | RTC_INT_ALARM);

	/* Enable RTC interrupt in NVIC */
	NVIC_EnableIRQ((IRQn_Type) RTC_IRQn);

	/* Enable RTC (starts increase the tick counter and second counter register) */
	Chip_RTC_Enable(LPC_RTC, ENABLE);

	/* Output example's activity banner */
	DEBUGSTR("\r\n");
	DEBUGSTR("-----------------------------------------------------------------\r\n");
	DEBUGOUT("Power Control Example\r\n");
	DEBUGSTR("  System will cycle through SLEEP, DEEP SLEEP, POWER\r\n");
	DEBUGSTR("  DOWN, and DEEP POWER DOWN power states\r\n");
	DEBUGSTR("-----------------------------------------------------------------\r\n\r\n");

	/* Setup alarm, process next power state then wait for alarm to wake-up system */
	//crntPowerSetting = PMU_MCU_SLEEP;

	while (1) {

		if (fAlarmTimeMatched) {
			fAlarmTimeMatched = false;

			/* announce event */
			DEBUGSTR("ALARM triggered!\r\n");

			/* read and display time */
			Chip_RTC_GetFullTime(LPC_RTC, &FullTime);
			showTime(&FullTime);

			/* Set ALARM time for next wakeup time */
			FullTime.time[RTC_TIMETYPE_SECOND]  = 
				(FullTime.time[RTC_TIMETYPE_SECOND] + POWER_CYCLE_SEC_DELAY) % 60;
			Chip_RTC_SetFullAlarmTime(LPC_RTC, &FullTime);
			Chip_RTC_AlarmIntConfig(LPC_RTC, RTC_AMR_CIIR_IMSEC, ENABLE);
		}

		DEBUGOUT("PCON=0x%X SCB->SCR=0x%X - Clearing sleep mode flags\r\n", 
				 LPC_PMU->PCON, SCB->SCR);
		LPC_PMU->PCON |= PMU_PCON_SMFLAG | PMU_PCON_DSFLAG | PMU_PCON_PDFLAG | PMU_PCON_DPDFLAG;
		DEBUGOUT("PCON=0x%X\r\n", LPC_PMU->PCON);

		/* Enter first (or next) power state */
		ProcessPowerState(crntPowerSetting);


		/* Inc current power setting and test for overflow */
		if (crntPowerSetting == PMU_MCU_DEEP_PWRDOWN) {
			/* Reset to lowest power setting */
			crntPowerSetting = PMU_MCU_SLEEP;
		}
		else {
			crntPowerSetting++;
		}
	}

	return 0;
}
