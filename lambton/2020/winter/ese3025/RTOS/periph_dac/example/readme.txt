DAC example

Example description
This example shows how to use DAC peripheral with 2 modes:
POLLING mode or DMA mode.

The DAC will be initialized with maximum current is 700uA. This allows a
maximum update rate of 1Mhz DAC updated values have range from 0 to 0x3FF.
AOUT ouput voltage will change from: Vss to VDD. Run and observe AOUT signal 
by oscilloscope.

The UART is used with a small menu to start and control the program.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
Connect P0[26] (J3.28) to oscilloscope to observe the output signal.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port.
Connect P0[26] (J6.18) to oscilloscope to observe the output signal.
J31, J32 on base board should be closed to hear the sound.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

