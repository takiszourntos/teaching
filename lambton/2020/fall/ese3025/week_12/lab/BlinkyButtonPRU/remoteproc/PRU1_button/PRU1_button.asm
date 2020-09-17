
; PRUSS program to to handle two buttons connected to enhanced GPIO pins.
;
; This program runs on PRU1.
;
; The PRUSS program halts if it detects that the word in the shared memory location,
; at offset +0x000c, is not equal to zero. This halt condition is generated when 
; the user presses both buttons simultaneously.
;
; author: Takis Zourntos (takis.zourntos@emads.org)

        .cdecls "main.c"
        .clink
        .global BEGIN
        
        .asg    0x00010000,    SM_ba
        .asg    0x0001000c,    HALT_ba
        .asg    0xffffffff,    HALT_val

BEGIN:
        LDI32   r0, SM_ba       ; place shared memory address in register r0, where delay is
        LDI32   r1, 0           ; clear r1
        LDI32   r2, 0           ; clear r2
        LDI32   r3, 0           ; clear r3
        LDI32   r4, 0           ; clear r4
        LDI32   r5, 0           ; clear r5
        LDI32   r6, 0           ; clear r6
        LDI32   r7, 0           ; clear r7
        LBBO    &r6, r0, 4, 4   ; store MIN_DELAY in r6
        LBBO    &r7, r0, 8, 4   ; place MAX_DELAY in r7
        LDI32   r8, 0           ; clear r8

BUTTON_CHK:
        MOV     r1, r31.w0      ; load button status of Button 1
        CLR     r1, r1.t14      ; ignore other button state
        LSR     r1, r1, 15      ; place Button 1 state in bit 0 of r1
        MOV  	r3, r31.w0      ; load button status of Button 2
        CLR     r3, r3.t15      ; ignore other button state
        LSR     r3, r3, 14      ; place Button 2 state in bit 0 of r3
        AND     r4, r1, r3      ; r4 = r1 && r3; if r4=1 then both buttons are pressed, else r4=0 
        QBGT    END, r4, 0      ; if r4 > 0, we have a HALT condition (both buttons are pressed)
    
        MOV     r8, r6          ; prepare for quick human-scale 
        LSL     r8, r8, 4       ; delay of 160ms (similar to an RTOS tick)
SM_DELAY:                       ; give user time to get off the button
        SUB     r8, r8, 1       ; decrement delay counter
        QBNE    SM_DELAY, r8, 0 ; typical 2-instruction delay loop

        LBBO    &r2, r0, 0, 4   ; load current delay into r2 (initialized by host program)
        QBEQ    SKIPDEC, r1, 0  ; no decrement needed if Button 1 not pressed
        QBEQ    SKIPDEC, r2, r6 ; skip the decrement if we're at MIN_DELAY
        SUB     r5, r2, r6      ; r5 = current_delay - MIN_DELAY
        SBBO    &r5, r0, 0, 4   ; store updated delay

SKIPDEC:
        QBEQ    BUTTON_CHK, r3, 0   ; no increment needed if Button 2 not pressed, loop
        QBEQ    BUTTON_CHK, r2, r7  ; skip increment if we're at MAX_DELAY, loop
        ADD     r5, r2, r6          ; otherwise, increment delay, r5 = r2 + MIN_DELAY
        SBBO    &r5, r0, 0, 4       ; store updated delay
        JMP     BUTTON_CHK          ; resume checking buttons

END:
        LDI32   r0, HALT_ba         ; store halt condition base address in r0
        LDI32   r1, HALT_val        ; store halt value in r1
        SBBO    &r1, r0, 0, 4       ; store that value to inform other PRU
        HALT                        ; halt the pru program
