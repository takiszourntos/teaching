LWIP TCP Echo without an RTOS

Example description
Welcome to the LWIP TCP Echo example using the raw API for standalone
(without an RTOS) operation. This example shows how to use the raw API with
the LWIP contrib TCP Echo example using the 17xx/40xx LWIP MAC and PHY drivers.
The example shows how to handle PHY link monitoring and indicate to LWIP that
a ethernet cable is plugged in. It also shows how to manage input packet
handling and reclaim transmit pbufs once they are transmitted in the main
processing loop.

To use the example, Simply connect an ethernet cable to the board. The board
will acquire an IP address via DHCP and you can ping the board at it's IP
address. You can monitor network traffice to the board using a tool such as
wireshark at the boards MAC address.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
There are no special connection requirements for this example.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port and Ethernet port.

