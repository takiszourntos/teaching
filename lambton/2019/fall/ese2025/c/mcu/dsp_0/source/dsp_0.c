/*
===============================================================================
 Name        : dsp_0.c
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

// TODO: insert other definitions and declarations here
/* DAC sample rate request time */
#define DAC_TIMEOUT 0x3FF
#define DAC_TICKRATE_HZ (50000)	/* 50000 ticks per second */

volatile uint32_t dacval = 0;


/**
 * @brief	do a DAC read using the interrupt handler for the SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	Chip_DAC_UpdateValue(LPC_DAC, dacval);
}



int main(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/***************     DAC Initialization      **********/
	{
		/* Setup DAC pins for board and common CHIP code */
		Chip_DAC_Init(LPC_DAC);

		/* Setup DAC timeout for polled and DMA modes to 0x3FF */
		/* 175x/6x devices have a DAC divider, set it to 1 */
		Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_1);
		Chip_DAC_SetDMATimeOut(LPC_DAC, DAC_TIMEOUT);

		/* Compute and show estimated DAC request time */
		dacClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_DAC);

		/* DEBUGOUT("DAC base clock rate = %dHz, DAC request rate = %dHz\r\n",
			dacClk, (dacClk / DAC_TIMEOUT)); */
	}

	/***************      SysTick Timer (for DAC) Initialization      ***************/
	{
		SysTick_Config(SystemCoreClock / DAC_TICKRATE_HZ);
	}






	while (!end_Flag)
	{
	}

	return 0;
}
