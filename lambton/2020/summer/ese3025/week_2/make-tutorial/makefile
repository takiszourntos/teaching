#
# Our most advanced makefile --- using implicit rules with CFLAGS, VPATH for prerequisites, .PHONY and
# suppressing errors in recipes. 
#
# author: T. Zourntos, emad studio
#

# define a variable to contain all of our object files (if this list changes, we only need to change the variable)
objects = main_code.o lib_ll.o lib_bst.o

# define a variable for our include directory
include = my_includes

# specify a search path for all prerequisites; looks for .o, .c or .h files in ./ or source/ or my_includes/
VPATH = source:my_includes

# provide a parameter for our implicit compilation rule (for gcc)
CFLAGS = -I$(include)

# our project will be called proj_ds, and it LINKS object files main_code.o, lib_ll.o and lib_bst.o
proj_ds : $(objects)
	gcc -o proj_ds $(objects)

# compile main_code.c to produce main_code.o, if needed
main_code.o : main_code.c lib_ll.h lib_bst.h

# compile lib_ll.c, if needed
lib_ll.o : lib_ll.c lib_ll.h

# compile lib_bst.c, if needed
lib_bst.o : lib_bst.c lib_bst.h

# a clean option that will remove proj_ds and any object files, with EXTRA features now!
.PHONY : clean # declaring clean as "phony" prevents it from being ignored if a file named "clean" happens to exist in the directory!
clean :
	-rm proj_ds $(objects)
#       ^
#       |_______ with the "-" in front of rm, the rm command will continue to execute in spite of any errors generated (such as "file does not exist")
