# Dynamically allocated arrays

This project demonstrates a couple of C-language features related to arrays and their dynamic allocation.<br>

1. Note the use of malloc(), which returns a void pointer (by default) to an area of memory in the heap which it (as a side effect) allocates for you

2. The amount of memory allocated (in bytes) is specified by the argument passed to malloc(), which usually makes use of the sizeof() compile-time operator.

3. The sizeof() operator returns the number of bytes associated with its argument. The argument can be a variable type (like int, char, double, or a typedef that you define), or an array identifier. If the argument is an array, sizeof() returns the number of bytes (not the number of elements!) associated with the array. If you want the number of elements of the array, you must divide by the size (in bytes) of each element type.

4. Also note the use of the qsort() function (found in stdlib). You must provide the name of a comparison function that qsort() can use in its sorting process.

5. The demo code takes an array (defined without a specific size parameter), sorts it, and divides it into two dynamically-allocated sub-arrays. 
