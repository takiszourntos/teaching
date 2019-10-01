# GNU Scientific Library

1) please install using the command:
    $ sudo apt install libgsl-dev
    
2) note the very useful on-line documentation at:
    https://www.gnu.org/software/gsl/doc/html
    
3) point Eclipse to the gsl and gslcblas libraries

4) alternatively, you can use these commands for compiling and linking from the command line: <br>
    $ gcc -Wall -I/usr/include -c yourprog.c <br>
    $ gcc -L/usr/include yourprog.o -lgsl -lgslcblas -lm <br>
   which produces a default executable (a.out), and I have assumed installation of the GSL in /usr/include (your installation directory may be different)
   
