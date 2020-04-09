Please have a read through the introductory portions of the gnu-make.pdf document found in the documentation sub-directory 
of the teaching repository on github. When you build your applications with Eclipse, you are somewhat insulated from the 
build process, which includes various stages of compiling and linking. Behind the scenes of an IDE, there is often a utility 
like GNU make being used.

GNU make builds your project according to a kind of scripting language, similar to BASH, contained in a file named Makefile 
(or makefile or GNU-makefile). When you enter the command:

$ make

The program, make, searches for Makefile/makefile/GNUmakefile and parses the lines of that file.

In the simplest terms, a Makefile consists of a list of hierarchically organized rules. The rules have a specific structure, 
consisting of:

target_name : list of prerequisites or dependencies

TAB recipe

Whenever a file in the list of prerequisites is updated, make knows that the target must be re-created, so that a project 
is built with the minimum number of compilations. Sound familiar? It should, because this is precisely what Eclipse does.

The introductory chapter of the gnu-make.pdf document should clarify some make fundamentals. Then, have a look at the 
material I created for you at:

https://github.com/takiszourntos/teaching/tree/master/lambton/2020/winter/ese2025/c/beaglebone/make-tutorial

in the makefile_dir/ sub-directory, you'll find three "levels" of makefile, from beginner to advanced. Study these files 
and experiment. You should be able to use these makefiles when building your data structures project on the Beaglebone 
(where you don't have Eclipse available!). Note that the same directory structure, with source/ and my_includes/ 
directories is used (in addition to the same .c and .h files).

I will give an overview of these concepts (although briefly!) at the next lecture. Please continue to study hard!


