Virtual Comm port example

Example description
The example shows how to us USBD LIB stack to creates a virtual comm port.

Special connection requirements
Connect the USB cable between micro connector on board and to a host.
When connected to Windows host use the .inf included in the project
directory to install the driver. For OSx (Mac) host, no drivers are needed.

Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 needs to be moved to short pins 2 and 3.

On EA Devkit 1788/4088 board jumper J15 must be closed, for the device
to be detected.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

