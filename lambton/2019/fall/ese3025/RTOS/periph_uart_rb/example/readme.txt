UART example with ring buffers

Example description
The UART example shows how to use the UART in interrupt mode with transmit
and receive ring buffers.

To use the example, connect a serial cable to the board's RS232/UART port and
start a terminal program to monitor the port.  The terminal program on the host
PC should be setup for 115200-8-N-1.
Once the example is started, a small message is printed on terminal. Any data
received will be returned back to the caller.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
Default is UART0. This uses the UART-to-USB bridge.
If using UART2: Connects UART pins to COM Port (J17)
JP6-1-2: OFF:
JP6-3-4: OFF:
JP6-5-6: ON:
JP12: 2-3
JP13: 2-3
Other jumpers: Default
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

