# C project to work on real climate data
This project is intended to work in conjunction with the climate data and BASH scripts found in the folder:

../../../ese2025/bash/bigdata/mean

This project includes some starter code, but you need to complete the project code. Study the project and develop the necessary 
functions found in the source folder. Note that there is a my_includes/ folder that contains the header files. Develop the source
code to correspond with the headers provided in my_includes/.

# Exercise
Develop a doubly-linked-list demonstration using the climate data provided in the file you generated with your testgen.sh script,
testdata.dat. You should use your C program to take its standard input from the file as follows:

$ cat testdata.dat | ./proj_students_data_structs

where your C-program name is proj_students_data_structs. Each node of your linked list should correspond to a different year of
climate data at the site you chose. Demonstrate that you can print (to standard output) any portion of the list that you desire.
In addition, show that you can insert and delete nodes.

# Exercise
Building on the previous exercise, now use the data in testdata.dat to work with binary search trees. For your BST node keys,
use the year associated with the temperature reading. Note that there is additional data you can store in the tree
called "payload data" which can be used to store the name of the site as well as the temperature (as a float). Find a way to 
construct your BST in a balanced way, using the doubly linked list that you created in the previous exercise. Remember that
you don't want to add nodes to the tree in an ordered fashion, or you'll end up with a "tall" tree. For example, your tree's
head node could be chosen as the "middle" year of your time range. Show that your BST is a relatively balanced construction.

