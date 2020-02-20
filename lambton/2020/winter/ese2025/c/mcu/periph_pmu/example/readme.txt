Low Power (PMU) example

Example description
The PMU example demonstrates power state change using the RTC timer to wake-up 
the MCU from the following low power states, SLEEP, DEEP SLEEP, POWER DOWN, 
and DEEP POWER DOWN.
The wakeup timer is configurable, allowing the user to select the time delay
between power state changes. The chip is then placed into a low power mode and 
will wakeup from the RTC timer event. PMU power modes tested are:
MCU_SLEEP,
MCU_DEEP_SLEEP,
MCU_POWER_DOWN,
MCU_DEEP_POWER_DOWN
The UART serial output from the board will announce each power state change.
<i>Expect to lose your debugger connection with this example when the MCU
goes into low power states.</i>

Special connection requirements
This example requires a UART connection to display status.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

