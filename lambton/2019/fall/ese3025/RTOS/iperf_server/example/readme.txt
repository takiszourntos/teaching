IPERF Server example

Example description

This example demonstrates the iperf server functionality using LWIP stack.
To use the example, connect an ethernet cable to the board. The board
will acquire an IP address via DHCP and you can ping the board at it's IP
address. 

From the host PC execute the iperf tool with following options: 
- iperf -i 5 -c < Target IP address > -m 
It will display the Interval, Transfer size, bandwidth, etc 

Special connection requirements
There are no special connection requirements for this example.

