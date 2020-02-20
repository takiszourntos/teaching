ADC example

Example description
This example describes how to use ADC conversion in POLLING mode, INTERRUPT mode
and DMA mode.

For LPC1788 and LPC4088, the ADC conversion rate is 400KHz. A/D converter requires 31 clocks
for a fully accurate conversion. Therefore, ADC clock = 400KHz * (number of clocks for 1 measure = 31 clocks).
Note that maximum ADC clock input is 12.4MHz.

For LPC1769, the maximum ADC clock input is 13MHz. 65 ADC converter's clocks are required
for a full conversion. The conversion rate is 200KHz.

The ADC value can be read in POLLING mode, INTERRUPT mode or DMA mode. Converted ADC values
displayed periodically via the UART. Turn potentiometer to change ADC signal input.

Setting up the demo requires connecting a UART cable between the board and a host PC. The
terminal program on the host PC should be setup for 115K8N1. Press the appropriate key via
the menu to change the ADC conversion mode.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
By default, the UART-to-USB bridge is used for the UART.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port.
J27 on the base board must be closed.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

