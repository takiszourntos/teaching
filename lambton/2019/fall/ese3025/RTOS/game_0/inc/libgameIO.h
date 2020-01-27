/*
 * libgameIO.h
 *
 *  Created on: Jan. 27, 2020
 *      Author: takis
 */

#ifndef LIBGAMEIO_H_
#define LIBGAMEIO_H_

/********************************************************************
 * UART Comm Setup
 ********************************************************************/
#define UART_SELECTION 	LPC_UART3
#define IRQ_SELECTION 	UART3_IRQn
#define HANDLER_NAME 	UART3_IRQHandler

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 32	/* Receive */

#endif /* LIBGAMEIO_H_ */
