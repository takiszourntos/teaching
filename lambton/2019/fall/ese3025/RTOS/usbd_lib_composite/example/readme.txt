USB Composite device example

Example description
The example shows how to us USBD LIB stack to creates a composite device. A USB
device which has multiple class interface in single configuration is termed as
composite device. In this example and virtual comm port interface (using CDC-ACM class) and
a HID-mouse interfaces are combined together to form a composite device. The VCOM interface
could be used for out putting debug messages.

Special connection requirements
Connect the USB cable between micro connector on board and to a host.

Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 needs to be moved to short pins 2 and 3.

When connected to Windows host use the .inf included with the LPCOPen example
Windows USB driver package. You can get this package on the LPCOpen download
page at link "http://www.lpcware.com/content/nxpfile/lpcopen-platform".
For OSx (Mac) host, no drivers are needed.

On EA Devkit 1788/4088 board jumper J15 must be closed, for the device
to be detected.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

