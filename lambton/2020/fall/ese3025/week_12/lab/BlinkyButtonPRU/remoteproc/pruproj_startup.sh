# Shell script to configure enhanced GPIO pins for blinky-button
# project based on config-pin command in Beaglebone Debian
# 
# date: April 22, 2019
# author: Takis Zourntos (takis.zourntos@emads.org)
#
#!/bin/bash
echo "Configuring eGPIO pins for PRUSS blinky-button project"
echo

# temp filename, unique with probability ~ 1
tempfilesuffix=$(date +%N)
tempfile="temp_egpio_status_"${tempfilesuffix}".txt"

# define desired pins
egpioLEDred="p1_29"
egpioLEDblue="p1_31"
egpioButton1="p1_30"
egpioButton2="p1_32"

# display current pin status
touch $tempfile
config-pin -q $egpioLEDred >> $tempfile
config-pin -q $egpioLEDblue >> $tempfile
config-pin -q $egpioButton1 >> $tempfile
config-pin -q $egpioButton2 >> $tempfile
echo "current pin status"
cat $tempfile
rm $tempfile
echo

# change PRU0 eGPIO pins
	# egpioLEDred
	config-pin $egpioLEDred pruout
	config-pin -q $egpioLEDred >> $tempfile
	# epgioLEDblue
	config-pin $egpioLEDblue pruout
	config-pin -q $egpioLEDblue >> $tempfile

# change PRU1 eGPIO pins
	# egpioButton1
	config-pin $egpioButton1 pruin
	config-pin -q $egpioButton1 >> $tempfile
	# egpioButton2
	config-pin $egpioButton2 pruin
	config-pin -q $egpioButton2 >> $tempfile

# show status of updates
	echo "updated pin statuses"
	cat $tempfile
	rm $tempfile

# terminate successfully
exit 0
