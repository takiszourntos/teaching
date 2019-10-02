I2C example

Example description
The I2C example shows how to use I2C interface in master and slave mode using
POLLING/INTERRUPT method.

To use the example, connect a serial cable to the board's RS232/UART port and
start a terminal program to monitor the port. The terminal program on the host
PC should be setup for 115K8N1.

For boards that does not have default UART, the user can enable debugging,
by defining ENABLE_DEBUG macro in sys_config.h and then connect FTDI UART cable
to the board to use the full functionality of the example. If no UART can be
connected see the paragraph below for using the example without uart

<i> If there is no UART connected to LPCXpresso board, and if ENABLE_DEBUG is not
defined then make connections as specified in the  "Special connection requirements"
section. When the board is reset or powered ON, the Master I2C will write to the
IO Expansion slave making the RED LED Glow, and the example will terminate</i>

After a Main menu is displayed via UART, I2C0 and I2C1 are configured with
100KHz speed.

User can access any I2C slave device (probe all devices by selecting option 3 from
main menu) connected to the bus using this example,
i.e, operations like WRITE/READ/WRITE&READ can be carried out by using any I2C
I2C0/I2C1 as master. The input from UART could be decimal, hexadecimal (prefixed
with 0x), or octal (prefixed with 0) and can be edited using backspace. User must
press enter key to complete the input.
This example simulates two slave devices (default by I2C0), an EEPROM (0x5A) and
an IO Extension device (0x5B). The EEPROM simulation is just to show how the I2C
can be used as a device (it will not retain contents across power cycles). IO
extention device have 2 ports, any single byte read will read 8 bit data from IN
port (8 bit input reg0), any single byte write will write to OUT port (8 bit output
reg1). Multibyte reads will read (IN REG, OUT REG) repeatedly, multi byte writes will
write to OUT REG repeatedly. OUT REG represent LEDS in the board set/reset them will
turn LED0-LED7 (If present) to ON/OFF, IN REG represent key press (KEY0 to KEY7).

To turn on LED1 and LED2, follow the steps given below 
1. Select I2C1 as default device by selecting option 1 and 1
2. Select option 5 to write data to slave
3. Enter 0x5B as the slave device address
4. Enter 1 as the number of bytes to write
6. Enter 6 as the data [Turn ON LED1 and LED2]

The EEPROM slave (simulation) device will work as any standard I2C EEPROM. To write
data 0xDE, 0xAD, 0xBE, 0xEF to address 0x10, 0x11, 0x12 & 0x13 respectively and to
read back the full content of the EEPROM follow the steps
1.  Select I2C1 as default device by choosing option 1 and give input 1
2.  Select option 5 to write data to slave
3.  Enter 0x5A as the slave device address
4.  Enter 5 as the number of bytes to write
5.  Enter 0x10 as the address to write
<blockquote> First byte written to device is always considered as the address
from/to which read/write to be performed, the EEPROM uses 64 byte memory hence
BIT0 to BIT5 will have address A0-A5 and BIT6 & BIT7 are don't cares. For every
read/write the address will auto increment upon reaching the end of the device
the address will automatically roll back to location 0.</blockquote>
6.  Enter data 0xDE,0xAD,0xBE,0xEF one by one
7.  Select option 6 to write/read the data from EEPROM
8.  Enter 0x5A as the slave address
9.  Enter 64 as the number of bytes to read
10. Enter 1 as the number of bytes to write
11. Enter 0 as the address from which read must start
12. Full content of EEPROM will be displayed on UART terminal with address
0x10 to 0x13 showing the data written in previous operation.

Special connection requirements
- EA-DEVKIT 1788/4088
- I2C1_SDA (J5 pin 45) connected to I2C0_SDA (J5 pin 25) 
- I2C1_SCL (J5 pin 54) connected to I2C0_SCL (J5 pin 26) 
- Jumper @a J5 is the 64 pin expansion connecter close to 200pin OEM board connector 
- Make sure double check the connected pins as there is a great possibility of connecting wrong pins
- LPCXpresso 1769 (using UART3)
- P0.19(SDA1) PAD17 connected to P0.27(SDA0) J6-PIN25
- P0.20(SCL1) PAD18 connected to P0.28(SCL0) J6-PIN26

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

