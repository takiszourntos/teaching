USB Keyboard Host example

Example Description
This example shows how to use the USB host stack to implement USB keyboard
class. This example will print the keys pressed in a connected USB keyboard
to an UART console.


Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 should be open and all 3 jumpers in J61 must be on.

On EA Devkit 1788/4088 boards Jumper JP15 must be open, else the pull-up
will make the host detect itself as a device.

Connection requirements
A USB keyboard device to be connected to the USB0 host port. Open terminal
program, connect UART and configure for baud 115200, 8-bits and 1 stopbit
