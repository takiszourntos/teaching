// PRUSS program to flash two LEDs connected to enhanced GPIO pins alternately
// at a rate determined by a value stored in the shared memory location, at offset 0.
//
// This program runs on PRU0.
//
// The PRUSS program halts if it detects that the word in the shared memory location,
// at offset +0x000c, is not equal to zero. This halt condition is generated when 
// the user presses both buttons simultaneously.
//
// author: Takis Zourntos (takis.zourntos@emads.org)
//

.origin 0
.entrypoint BEGIN

#include "PRU_blinky_button.hp"

BEGIN:
	MOV	r0, SM_ba	// place shared memory address in register r0, where delay is
LEDOFF:
	CLR	r30.t7		// clear (turn off) the red LED
	SET	r30.t4		// set (turn on) the blue LED
	LBBO	r1, r0, 0, 4	// load r1 with 32-bit word stored at SM_ba, offset 0
DELAYOFF:
	SUB	r1, r1, 1	// count down the delay
	QBNE	DELAYOFF, r1, 0	// do the 2-instruction delay loop thing until r1=0
LEDON:
	SET	r30.t7		// set red LED
	CLR	r30.t4		// clear blue LED
	LBBO	r1, r0, 0, 4	// load r1 with the potentially updated delay count
DELAYON:
	SUB	r1, r1, 1	// count down the delay 	
	QBNE	DELAYON, r1, 0	// do the 2-instruction delay loop thing until r1=0
CHKHALT:
	LBBO	r2, r0, 0x0c, 4	// load r2 with the 32-bit word stored at SM_ba, offset 0x10
	QBEQ	LEDOFF, r2, 0   // if the status=0, we can keep running
END:
	MOV	r31.b0, PRU0_ARM_INTERRUPT+16 // send termination interrupt
	HALT			// halt the pru program

