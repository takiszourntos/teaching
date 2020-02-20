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

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Handy list of GPIO pins on 17xx/40xx boards.
 
    LPCXpresso LPC1769 on base board...
 
		PORT	PIN	Xpresso Pin	Function
		----	---	-----------	------------------------------------------
		0		17	12			Joystick center button
		0		15	13			Joystick button
		0		16	14			Joystick button
		2		3	45			Joystick button (in towards battery on base board)
		2		4	46			Joystick button (towards closest corner)
		1		31	20			Wakeup button
		0		22	24			LED2 (LED 0 in the software).

		2		0	42			RGB LED RED   PIO1_9
		0		26	18			RGB LED BLUE  PIO1_2
		2		1	43			RGB LED GREEN PIO1_10
 
    Embedded Artists Devkit LPC1788/LPC4088 on base board...
 
		PORT	PIN	DIMM Pin	Function
		----	---	--------	------------------------------------------
		2		22	120-GPIO73	Joystick center button
		2		23	121-GPIO74	Joystick button
		2		25	122-GPIO75	Joystick button
		2		26	123-GPIO76  Joystick button
    	2		27  124-GPIO77	Joystick button
    	
    	2		10  35-GPIO10	Interrupt button SW6
 */

#ifdef CHIP_LPC175X_6X
/* GPIO pin for interrupt */
#define GPIO_INTERRUPT_PIN     17	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PORT    GPIOINT_PORT0	/* GPIO port number mapped to interrupt */

/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */

#elif defined(CHIP_LPC177X_8X) || defined(CHIP_LPC40XX)
/* GPIO pin for interrupt */
#define GPIO_INTERRUPT_PIN     10	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PORT    GPIOINT_PORT2	/* GPIO port number mapped to interrupt */

#define GPIO_IRQ_HANDLER  			GPIO_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    GPIO_IRQn	/* GPIO interrupt NVIC interrupt name */

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
 * @brief	Handle interrupt from GPIO pin or GPIO pin mapped to PININT
 * @return	Nothing
 */
void GPIO_IRQ_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);
	Board_LED_Toggle(0);
}

/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();

	/* Board_Init calls Chip_GPIO_Init and enables GPIO clock if needed,
	   Chip_GPIO_Init is not called again */
	Board_Init();
	Board_LED_Set(0, false);

	/* Configure GPIO interrupt pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIO_INTERRUPT_PORT, GPIO_INTERRUPT_PIN);

	/* Configure the GPIO interrupt */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);

	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);

	/* Wait for interrupts - LED will toggle on each wakeup event */
	while (1) {
		__WFI();
	}

	return 0;
}
