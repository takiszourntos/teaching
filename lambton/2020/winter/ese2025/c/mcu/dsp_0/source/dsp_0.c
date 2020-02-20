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
#include "buffer.h"

// TODO: insert other definitions and declarations here
/* DAC sample rate request time */
#define DAC_TIMEOUT 0x3FF
#define DAC_TICKRATE_HZ (50000)	/* 50000 ticks per second for DAC */
#define _ADC_CHANNEL ADC_CH0
#define _LPC_ADC_ID LPC_ADC
#define _LPC_ADC_IRQ ADC_IRQn

volatile uint32_t dacval = 0; /* storage for DAC data register */
volatile uint16_t adcval; /* storage for ADC data reads */

static ADC_CLOCK_SETUP_T ADCSetup;

/* initialize data storage variables */
buffer_t* pb_u = (buffer_t *) malloc(sizeof(buffer_t)); /* input buffer */
buffer_t* pb_y = (buffer_t *) malloc(sizeof(buffer_t)); /* output buffer */

/* filter coefficients */
uint16_t ycoeffs[]={25,36,72};
uint16_t ucoeffs[]={7,15};

item_t dspAlgo(void)
{
	item_t y_n;

	/* compute the next output sample */
	item_t f1, f2, iW=0;
	/* compute output sums */
	for (size_t if1=debuffer(pb_y,1);if1 != pb_y->K; if1++)
	{
		f1 += (pb_y->array(if1))*ycoeffs[iW];
		iW++;
	}
	iW = 0;
	/* compute input sums */
	for (size_t if2=debuffer(pb_u,0);if2 != pb_u->K; if2++)
	{
		f2 += (pb_u->array(if2))*ucoeffs[iW];
		iW++;
	}
	y_n = f1 + f2;
	enbuffer(pb_y,y_n)
	return y_n;
}

/**
 * @brief	do a DAC read using the interrupt handler for the SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	dacval = dspAlgo();
	Chip_DAC_UpdateValue(LPC_DAC, dacval);
}

/**
 * @brief	ADC0 interrupt handler sub-routine
 * @return	Nothing
 */
void ADC_IRQHandler(void)
{

	/* disable interrupt to process it --- no nested interrupt calls allowed */
	NVIC_DisableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNEL, DISABLE);

	/* read ADC data register */
	Chip_ADC_ReadValue(_LPC_ADC_ID, _ADC_CHANNEL, &adcval);
	enbuffer(pb_u, (item_t) adcval); /* store the read ADC value */

	/* reinstate interrupt to continue */
	NVIC_EnableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNEL, ENABLE);
}

int main(void)
{
	/* variable initialization */
	size_t M=2, N=3;
	init_buffer(pb_u, M); /* need u(n), u(n-1), ..., u(n-(M-1)) : depth = M */
	init_buffer(pb_y, N+1); /* need y(n), y(n-1), ..., y(n-N): depth = N+1 */


	/* initialize hardware */
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

	/***************     ADC Initialization      **********/
	/* from the NXP LPC1769 UM:
	 * 			"The A/D Status register allows checking the status of all A/D channels [, 0 through 7,] simultaneously.
				The DONE and OVERRUN flags appearing in the ADDRn register for each A/D channel
				are mirrored in ADSTAT. The interrupt flag (the logical OR of all DONE flags) is also found
				in ADSTAT."
				Therefore, the ADC Interrupt is issued whenever any of the ADC channels has completed a conversion.
	*/
	{
		Chip_ADC_Init(_LPC_ADC_ID, &ADCSetup);
		Chip_ADC_EnableChannel(_LPC_ADC_ID, _ADC_CHANNEL, ENABLE);
		Chip_ADC_SetSampleRate(_LPC_ADC_ID, &ADCSetup, ADC_MAX_SAMPLE_RATE/4);

		NVIC_EnableIRQ(_LPC_ADC_IRQ); /* Enable ADC Interrupt */
		Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE, ENABLE);
		Chip_ADC_SetBurstCmd(_LPC_ADC_ID, ENABLE); /* enable Burst Mode for regular conversions */
	}

	/***************      SysTick Timer (for DAC) Initialization      ***************/
	{
		SysTick_Config(SystemCoreClock / DAC_TICKRATE_HZ);
	}


	while (1)
	{

	}

	return 0;
}
