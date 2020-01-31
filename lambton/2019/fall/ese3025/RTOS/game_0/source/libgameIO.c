/*
 * libgameIO.c
 *
 *  Created on: Jan. 27, 2020
 *      Author: takis
 */

#include <stdlib.h>
#include "libgameds.h"
#include "libtakisbasics.h"
#include "libgameIO.h"

/*
 *	function to handle UART Transmissions for text
 */
void
sendUARTText (const char tx_text[])
{
  Chip_UART_SendRB (UART_SELECTION, &txring, tx_text, sizeof(tx_text) - 1);
}

/*
 *	function to handle UART Transmissions for graphics
 */
void
sendUARTGraphic (go_t *pGO)
{


}
