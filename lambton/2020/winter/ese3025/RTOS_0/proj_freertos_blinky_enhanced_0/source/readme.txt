FLASH read/write/signature example

Example description
The IAP example demonstrates programming a FLASH block during run-time and
generating a FLASH signature. For this example, the code is running from FLASH
and a FLASH block not used for the executing code will be erased and programmed
with some data. After the program is complete, the signature for the programmed
area is generated. The example also toggles the LED in the systick interrupt.
The interrupts need to be disabled during the IAP calls that change FLASH data
and re-enabled after the calls are complete.>br>

Do not run this example too many times or set it up to repeatedly erase and
reprogram FLASH as it will wear out FLASH.

Special connection requirements
There are no special connection requirements for this example.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

