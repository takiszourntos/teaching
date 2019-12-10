HID generic example

Example description
The example shows how to us USBD LIB stack to creates a generic HID device.
The example supports 1 byte report and loops back the data received in
SET_REPORT message.

Special connection requirements
Connect the USB cable between micro connector on board and to a host.


The HID reports sent/received by this example are supported by HID_client.exe
program distributed as part of Keil installation "(C:\Keil\ARM\Utilities\HID_Client)".

Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 needs to be moved to short pins 2 and 3.

On EA Devkit 1788/4088 board jumper J15 must be closed, for the device
to be detected.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

