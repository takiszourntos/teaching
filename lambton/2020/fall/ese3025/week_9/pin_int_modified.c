
/*

modified pin interrupt example for ESE3025, using two pushbuttons:

pushbutton A : P2.6

pushbutton B : P2.7

*/
#include "board.h"


/* GPIO pin for interrupt */
//#define GPIO_INTERRUPT_PIN     17	/* GPIO pin number mapped to interrupt */
//#define GPIO_INTERRUPT_PORT    GPIOINT_PORT0	/* GPIO port number mapped to interrupt */
#define GPIO_INTERRUPT_PIN_A	 6
#define GPIO_INTERRUPT_PORT_A	 GPIOINT_PORT2

#define GPIO_INTERRUPT_PIN_B	 7
#define GPIO_INTERRUPT_PORT_B	 GPIOINT_PORT2

/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  		EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    	EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */

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
 * @brief	Handle interrupt from GPIO pin or GPIO pin mapped to PININT
 * @return	Nothing
 */
void GPIO_IRQ_HANDLER (void)
{
  /* disable interrupt, clear status */
  NVIC_DisableIRQ (GPIO_INTERRUPT_NVIC_NAME);  // prevents interrupt nesting
  Chip_GPIOINT_ClearIntStatus (LPC_GPIOINT, GPIO_INTERRUPT_PORT,
			       1 << GPIO_INTERRUPT_PIN);

  /* main ISR steps */
  Board_LED_Toggle (red);

  /* re-enable interrupt */
  NVIC_EnableIRQ (GPIO_INTERRUPT_NVIC_NAME);
}

/**
 * @brief	Main program body
 * @return	Does not return
 */
int
main (void)
{
  /* Generic Initialization */
  SystemCoreClockUpdate ();

  /* Board_Init calls Chip_GPIO_Init and enables GPIO clock if needed,
   Chip_GPIO_Init is not called again */
  Board_Init ();
  Board_LED_Set (0, false);

  /* Configure GPIO interrupt pin as input */
  Chip_GPIO_SetPinDIRInput (LPC_GPIO, GPIO_INTERRUPT_PORT, GPIO_INTERRUPT_PIN);

  /* Configure the GPIO interrupt */
  Chip_GPIOINT_SetIntFalling (LPC_GPIOINT, GPIO_INTERRUPT_PORT,
			      1 << GPIO_INTERRUPT_PIN);

  /* Enable interrupt in the NVIC */
  NVIC_ClearPendingIRQ (GPIO_INTERRUPT_NVIC_NAME);
  NVIC_EnableIRQ (GPIO_INTERRUPT_NVIC_NAME);

  /* Wait for interrupts - LED will toggle on each wakeup event */
  while (1)
    {
      __WFI ();
    }

  return 0;
}


/*
 * @brief GPIO Pin Interrupt example
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