/*
===============================================================================
 Name        : hello_blinky_0.c
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

#define TICKRATE_HZ1 (10)	/* 10 ticks per second */

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

typedef enum
{
	Red = 0U,
	Green = 1U,
	Blue = 2U
} colour_t;

volatile colour_t LEDoi = Red;
volatile bool	 onPhase = true;

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	switch (LEDoi)
	{
		case Red:
		{
			if (onPhase==true)
			{
				Board_LED_Set(Red, true);
			}
			else // LED must go off
			{
				Board_LED_Set(Red, false);
				LEDoi=Green;
			}
			onPhase = !onPhase;
			break;
		}
		case Green:
		{
			if (onPhase==true)
			{
				Board_LED_Set(Green, true);
			}
			else // LED must go off
			{
				Board_LED_Set(Green, false);
				LEDoi=Blue;
			}
			onPhase = !onPhase;
			break;
		}
		case Blue:
		{
			if (onPhase==true)
			{
				Board_LED_Set(Blue, true);
			}
			else // LED must go off
			{
				Board_LED_Set(Blue, false);
				LEDoi=Red;
			}
			onPhase = !onPhase;
			break;
		}
	}
}


int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    /* Turn off all LEDs before starting */
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in interrupt handlers */
	while (1) {
		__WFI();
	}

	return 0;
}
