// PRUSS program to handle two buttons connected to enhanced GPIO pins.
//
// This program runs on PRU1.
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
	MOV	r1, 0		// clear r1
	MOV	r2, 0		// clear r2
	MOV	r3, 0		// clear r3
	MOV	r4, 0		// clear r4
	MOV	r5, 0		// clear r5
	MOV	r6, 0		// clear r6
	MOV	r7, 0		// clear r7
	LBBO	r6, r0, 4, 4	// store MIN_DELAY in r6
	LBBO	r7, r0, 8, 4	// place MAX_DELAY in r7
	MOV	r8, 0

BUTTON_CHK:
	MOV	r1, r31.w0	// load button status of Button 1
	CLR	r1.t14		// ignore other button state
	LSR	r1, r1, 15	// place Button 1 state in bit 0 of r1
	MOV	r3, r31.w0	// load button status of Button 2
	CLR	r3.t15		// ignore other button state
	LSR	r3, r3, 14	// place Button 2 state in bit 0 of r3
	AND	r4, r1, r3      // r4 = r1 && r3; if r4=1 then both buttons are pressed, else r4=0 
	QBGT	END, r4, 0	// if r4 > 0, we have a HALT condition (both buttons are pressed)

	MOV	r8, r6		// prepare for quick human-scale 
	LSL	r8, r8, 4	// delay of 160ms (similar to an RTOS tick)
SHORT_DELAY:			// give user time to get off the button
	SUB	r8, r8, 1	// decrement delay counter
	QBNE	SHORT_DELAY, r8, 0 // typical 2-instruction delay loop

	LBBO	r2, r0, 0, 4	// load current delay into r2 (initialized by host program)
	QBEQ	SKIP_DEC, r1, 0	// no decrement needed if Button 1 not pressed
	QBEQ	SKIP_DEC, r2, r6 // skip the decrement if we're at MIN_DELAY
	SUB	r5, r2, r6 	// r5 = current_delay - MIN_DELAY
	SBBO	r5, r0, 0, 4	// store updated delay

SKIP_DEC:
	QBEQ	BUTTON_CHK, r3, 0 // no increment needed if Button 2 not pressed, loop
	QBEQ	BUTTON_CHK, r2, r7 // skip increment if we're at MAX_DELAY, loop
	ADD	r5, r2, r6 	// otherwise, increment delay, r5 = r2 + MIN_DELAY
	SBBO	r5, r0, 0, 4	// store updated delay
	JMP	BUTTON_CHK	// resume checking buttons

END:
	MOV	r0, HALT_ba	// store halt condition base address in r0
	MOV	r1, HALT_val	// store halt value in r1
	SBBO	r1, r0, 0, 4	// store that value to inform other PRU
        MOV     r31.b0, PRU1_ARM_INTERRUPT+16 // send termination interrupt
        HALT                    // halt the pru program
