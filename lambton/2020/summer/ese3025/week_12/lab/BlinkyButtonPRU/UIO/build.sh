# build script, to be run on the pocket beagle
# assumes that (UIO) pasm assembler and necessary
# library and header files are installed
#
# to launch application: 
#
#	$ sudo pruproj_startup.sh
#	$ sudo ./blinkybutton 
#
#
# author: T. Zourntos 
# date: April 27, 2019
#
#!/bin/bash

pasm -b PRUSS_blinky.p
pasm -b PRUSS_button.p
gcc proj_PRUSS_blinky_button.c -o blinkybutton -lpthread -lprussdrv
