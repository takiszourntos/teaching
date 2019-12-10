LWIP TCP Echo with FreeRTOS

Example description
Welcome to the LWIP TCP Echo example using the NET API for RTOS based
operation. This example shows how to use the NET API with the LWIP contrib
TCP Echo (threaded) example using the 17xx/40xx LWIP MAC and PHY drivers.
The example shows how to handle PHY link monitoring and indicate to LWIP that
a ethernet cable is plugged in.

To use the example, Simply connect an ethernet cable to the board. The board
will acquire an IP address via DHCP and you can ping the board at it's IP
address. You can monitor network traffic to the board using a tool such as
wireshark at the boards MAC address.

When building the example to run in FLASH, the number of available
pbufs and memory size (in lwipopts.h) and the number of descriptors
(in lpc_17xx40xx_emac_config.h) can be increased due to more available
IRAM.

Special connection requirements
- Embedded Artists' LPC1788 Developer's Kit:
- Embedded Artists' LPC4088 Developer's Kit:
There are no special connection requirements for this example.
- LPCXpresso LPC1769:
Need to connect with base board for using RS232/UART port and Ethernet port.
