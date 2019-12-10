RTC example

Example description
This example shows how to use the RTC, generate periodic interrupts,
and use the alarm interrupt.

The RTC is configured to generate an interrupt on each second field
register change. An interrupt is also configured when certain alarm field
values match the time field values. The LEDs will toggle states based on
the RTC events. You can also use a terminal program with the UART to
monitor RTC time and events.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
There are no special connection requirements for this example.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

