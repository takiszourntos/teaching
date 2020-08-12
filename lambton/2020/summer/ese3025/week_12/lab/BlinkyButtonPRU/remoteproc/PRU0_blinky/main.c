/*
 * Blinky-Button Host C program (based on remoteproc) for Pocket Beagle
 * 	this project is documented elsewhere, link on github repository
 * 	
 * 	author: Takis Zourntos
 * 	date: 04-27-2019
 * 
 */

// libraries
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"

//definitions
#define SHARE_MEM  0x00010000

volatile uint32_t *shared =  (unsigned int *) SHARE_MEM;// typecasting a pointer to
							// a number yields immediate
							// access to the memory 
							// location specified by that
							// number... embedded-C trick
#define MIN_DELAY	10*1000*(200/2) // a 10-ms is as short as it gets
#define MAX_DELAY	MIN_DELAY*1000 // a 10-second delay is as long as it gets

extern void BEGIN(void); // in PRU0_blinky.asm

void main(void)
{
   // delay parameters
   shared[0]  = 50*MIN_DELAY;	// shared mem. loc. offset 0x0000 0000
   shared[1]  = MIN_DELAY;	// shared mem. loc. offset 0x0000 0004
   shared[2]  = MAX_DELAY;	// shared mem. loc. offset 0x0000 0008
   
   // exit status (0=keep going, 0xffffffff=halt!)
   shared[3]  = 0x00000000; 	// shared mem. loc. offset 0x0000 000c
   BEGIN();
}


/* LEGAL MUMBO-JUMBO FOLLOWS:
 *
 * 
 * Source modified yet again by Takis Zourntos for what are likely nefarious purposes...
 * 
 * Source Modified by Derek Molloy for Exploring BeagleBone Rev2
 * Based on the examples distributed by TI
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
