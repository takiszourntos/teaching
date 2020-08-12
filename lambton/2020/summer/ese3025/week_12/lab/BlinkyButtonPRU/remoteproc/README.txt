To use this application on a Pocket Beagle:

1) $ sudo ./pruproj_startup.sh

2) run the blinky application on PRU0:
	$ cd PRU0_blinky/
	$ make
	$ sudo make install_PRU0
	$ cd ../

3) run the button application on PRU1:
	$ cd PRU1_button/
	$ make
	$ sudo make install_PRU1

author: Takis Zourntos
date: 04/27/2019

