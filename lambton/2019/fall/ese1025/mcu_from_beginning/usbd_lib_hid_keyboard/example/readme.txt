Keyboard example

Example description
The example shows how to us USBD LIB stack to creates a HID keyboard.

Special connection requirements
The tiny joystick that is surface mounted on the eval board has 4 positions
and a button press. They act as number keys '2', '4', '6', '8', and NUMLOCK.
The joystick press toggles NUMLOCK. When NUMLOCK is ON the joystick positions
are mapped to the arrow keys. For most OSs, no drivers are needed.

Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 needs to be moved to short pins 2 and 3.

On EA Devkit 1788/4088 board jumper J15 must be closed, for the device
to be detected.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

