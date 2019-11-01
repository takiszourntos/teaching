SPI example

Example description
This example describes how to use the on-chip SPI peripheral in POLLING and INTERRUPT mode.
The on-chip SSP1 peripheral is also used as the SPI partner. When SPI peripheral is configured 
as master, the SSP1 will be slave and vice versa.

SPI configuration:
- CPHA = 0: data is sampled on the first clock edge of SCK.
- CPOL = 0: SCK is active high.
- Sample rate = 400kHz.
- DSS = 8: 8 bits per transfer.
After initialize transmit buffer, SPI master/slave will transfer a number of bytes
to SPI slave/master and receive data concurrently.
After the transfer completed, receive and transmit buffer will be compared. If they are matching,
the on-board LED is ON. 
This example supports 2 transfer modes: POLLING mode and INTERRUPT mode . In case the SPI
peripheral is configued as slave, only interrupt mode can be selected.

Special connection requirements
How to run: hardware configuration
-NXP LPC1769 LPCXpresso board
* SPI connection:
		  - P0.15:  SPI_SCK (J6.13)
		  - P0.16 : SPI_SSEL (J6.14)
		  - P0.17:  SPI_MISO (J6.12)
		  - P0.18:  SPI_MOSI (J6.11)
* SSP1 connection:
		  - P0.7:  SSP1_SCK  (J6.7) 
		  - P0.6:  SSP1_SSEL (J6.8) 
		  - P0.8:  SSP1_MISO (J6.6) 
		  - P0.9:  SSP1_MOSI (J6.5)
	The SCK pin of SPI is connected to SCK of SSP1.
	The SSEL pin of SPI is connected to SSEL of SSP1.
	The MISO pin of SPI is connected to MISO of SSP1.
	The MOSI pin of SPI is connected to MOSI of SSP1.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

