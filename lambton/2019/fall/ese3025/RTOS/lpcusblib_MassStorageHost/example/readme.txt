USB Massstorage Host example

Example Description
This example shows how to use the USB host stack to implement USB mass storage
class. This example will read the files from USB mass storage device connected
to the USB host port and prints the results to an UART console.

Note that on the LPCXpresso LPC1769 board connected to an LPCXpresso/mbed 
Base Board J14 should be open and all 3 jumpers in J61 must be on.

On EA Devkit 1788/4088 boards Jumper JP15 must be open, else the pull-up
will make the host detect itself as a device.
