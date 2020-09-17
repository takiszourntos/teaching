The BlinkyButton PRU Project is intended to provide a learning context for developing applications with the real-time hardware resources of the AM335x MCU, under Linux. The AM335x is the basis for the open-source Beaglebone Black and Pocket Beagle development platforms and is a powerful chip for embedded applications, featuring 32-bit-wide data and address buses, 1-GHz clock frequency, ARM A8 core and a variety of useful microcontroller-esque resources like PWM, A/D conversion, flash-memory interfacing, as well as the usual peripheral buses (I2C, SPI, UART, CAN, etc.). In addition, the AM335x features two on-chip programmable real-time units (PRUs) which are themselves 32-bit RISC cores operating at 200-MHz. Because real-time operation is often critical in embedded systems applications, getting into the PRU subsystem (PRUSS) is important for developers who like the potential of Linux but need a hard real-time solution. This project covers the full range of a PRU application, from electronics to software.

The complete project overview for this project is available at:

https://docs.google.com/document/d/1s_AE1yhSqoCRC9qIvrGuEmumVsIWkeXPRe442tu0BoY/edit?usp=sharing

This directory contains:


1. remoteproc/ : the remoteproc version of the BlinkyButton PRU project
	* README.txt : instructions
	* pruproj_startup.sh : configures pins for enhanced GPIOs
  	* PRU0_blinky/ : assembly-language code and C container program for PRU0
	* PRU1_button/ : assembly-language code and C container program for PRU1

	
2. UIO/ : the UIO version of the BlinkyButton PRU project
	* README.txt : instructions
	* build.sh : builds the application, calls pasm and gcc
	* pruproj_startup.sh : configures pins for enhanced GPIOs
	* proj_PRUSS_blinky_button.c : C host program
	* PRU_blinky_button.hp : assembly-language header file
	* PRUSS_blinky.p : PRU0 assembly-language program
	* PRUSS_button.p : PRU1 assembly-language program


3. electronics/	: a KiCAD working directory containing the schematic for this project

author: T. Zourntos (takis.zourntos@emads.org) 
date: 04-28-2019


