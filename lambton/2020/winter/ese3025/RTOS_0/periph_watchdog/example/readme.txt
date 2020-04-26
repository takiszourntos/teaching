Watchdog timer example

Example description
This example shows how to use Windowed watchdog timer to generate interrupts
to manage the watchdog timer. If the watchdog timer isn't 'fed' within it's
window time, it will reset the device. The LED will toggle states on each
watchdog feed event. You can also use a terminal program with the UART to
select the feed event. If the feed is disabled, the chip will reset.

The example works in one of 3 ways. If '1' is selected, WDT is fed by the
sysTick at 20Hz and should never time out (fast LED). If '2' is selcted, the
WDT is fed by the watchdog window interrupt (slow LED). If '3' is selected, the
watchdog times out and resets the device.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
There are no special connection requirements for this example.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

