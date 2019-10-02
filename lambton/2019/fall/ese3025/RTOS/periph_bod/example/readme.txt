Brown-out detector example

Example description
The brown-out example shows how to use the brown-out detector (BOD)
on the LPC13xx.The BOD is setup to generate a BOD interrupt when
power is lost. The interrupt will attempt to toggle the LED on as
power is lost.

To use this example, build and program it and then run it on the board.
Power off the board by removing the power (USB) cable. As the power is
declining on the board, the LED will toggle on (quickly) and then turn
off as power is lost.  Note that because this pulse is very short and
dificult to see, the LED is toggled five times, producing two short pulses
before turning on the LED.  These pulses can be captured and viewed with 
an oscilloscope or logic analyzer.

Special connection requirements
There are no special connection requirements for this example.

Build procedures:
Visit the LPCOpen quickstart guides at link "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.

