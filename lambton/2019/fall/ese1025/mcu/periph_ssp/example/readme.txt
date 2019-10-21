SSP example

Example description
This example describes how to use SSP in POLLING, INTERRUPT or DMA mode.
It is needed to connect 2 hardware boards, one for Master and one for Slave.

SSP configuration:
- CPHA = 0: data is sampled on the first clock edge of SCK.
- CPOL = 0: SCK is active high.
- Sample rate = 400kHz.
- DSS = 8: 8 bits per transfer.
- FRF= 0: SPI Frame format.
After initialize transmit buffer, SPI master/slave will transfer a number of bytes
to SPI slave/master and receive data concurrently.
After a transfer completed, receive and transmit buffer will be compared and
the result will be print out via UART port.
This example supports 3 transfer modes: POLLING mode, INTERRUPT mode and DMA mode.

- Connect UART port on the master board and slave board to COM ports on your PC.
- Configure terminal program on the PC per the above Serial display configuration
- Configure hardware, connect master board and slave board as below
- Build and run the example. Following guidance on terminals of master and slave to do test.

Special connection requirements
How to run: hardware configuration
- Embedded Artists' LPC1788 Developer's Kit
* SSP0 connection:
				- P0.15: SSP0_SCK		J5.19
				- P0.16: SSP0_SSEL		J3.24
				- P0.17: SSP0_MISO		J5.20
				- P0.18: SSP0_MOSI		J3.23
* SSP1 connection:
				- P0.7:  SSP1_SCK		J5.17
				- P0.6:  SSP1_SSEL		J3.18
				- P0.8:  SSP1_MISO		J3.19
				- P0.9:  SSP1_MOSI		J5.18
- Embedded Artists' LPC4088 Developer's Kit
* SSP1 connection:
				- P0.7:  SSP1_SCK		J5.17
				- P0.6:  SSP1_SSEL		J3.18
				- P0.8:  SSP1_MISO		J3.19
				- P0.9:  SSP1_MOSI		J5.18
* SSP2 connection:
				- P5.2:  SSP2_SCK		J5.19
				- P5.3:  SSP2_SSEL		J3.24
				- P5.1:  SSP2_MISO		J5.20
				- P5.0:	 SSP2_MOSI		J3.23
Remove jumpers on JP24~JP27 when SSP1 is used.
- LPCXpresso LPC1769:
* SSP0 connection:
				- P0.15: SSP0_SCK 		J5/6.30 (on baseboard)
				- P0.16: SSP0_SSEL 		J5/6.31 (on baseboard)
				- P0.17: SSP0_MISO 		J5/6.29 (on baseboard)
				- P0.18: SSP0_MOSI 		J5/6.12 (on baseboard)
* SSP1 connection:
				- P0.7:  SSP1_SCK 		J5/6.40 (on baseboard)
				- P0.6:  SSP1_SSEL 		J5/6.7  (on baseboard)
				- P0.8:  SSP1_MISO 		J5/6.13 (on baseboard)
				- P0.9:  SSP1_MOSI 		J5/6.14 (on baseboard)
Need to connect with base board for using RS232/UART port. 
<dt>Common ground must be connected together between two boards.</dt>

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

