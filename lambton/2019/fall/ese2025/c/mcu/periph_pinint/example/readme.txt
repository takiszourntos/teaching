GPIO pin Interrupt example

Example description
This example demonstrates use of the GPIO pin interrupts.

This example configures a GPIO interrupt as a falling edge wake up interrupt. 
The application will wait for interrupts in a loop.  With every interrupt the 
board LED0 will be toggled.

Special connection requirements
On LPC1769:
- PIO0_17 - J6-12 on LPCXpresso board, Joystick center button on base board

On LPC1788 and LPC4088:
- PIO1_10 - X4-35 on DIMM header, SW6 on OEM Base Board

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

