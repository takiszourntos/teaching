Ethernet example

Example description
The ENET example is a simple ethernet application for sending an ethernet
packet via the MAC and displaying received broadcast packets. The MAC example will
listen for all packets on the ethernet and display some stats via UART when a
packet is received. A dummy packet can also be sent out. Wireshark can be used to
view the outgoing packet.

To use the example, connect a serial cable to the board's RS232/UART port and
start a terminal program to monitor the port.  The terminal program on the host
PC should be setup for 115K8N1. For each packet received, the LED will toggle
and the packets source and destination MAC addresses will be displayed with the
packet type. Pressing any key will send a dummy packet.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
There are no special connection requirements for this example.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port and Ethernet port.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

