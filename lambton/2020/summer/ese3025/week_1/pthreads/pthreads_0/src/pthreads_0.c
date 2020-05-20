/*
 ================================================================================
 Name        : pthreads_0.c
 Author      : Takis Zourntos (adapted from Derek Molloy's pthreads.cpp program)
 Version     : 0.1
 Copyright   : (C) 2019 emad studio inc.
 Description : simple pthread example with two threads (including main thread)
 in C, Ansi-style
 ================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// This is the thread function that will execute when the thread is created
//  it passes and receives data by void pointers
void* threadFunction(void *value)
{
	int *x = (int*) value;    //cast the data passed to an int pointer
	while (*x < 5)
	{              //while the value of x is less than 5
		usleep(1000);         //sleep for 1ms - encourage main thread
		(*x)++;               //increment the value of x by 1
	}
	return x;                 //return the pointer x (as a void*)
}

int main()
{
	int x = 0, y = 0;
	pthread_t thread;         //this is our handle to the pthread
	// create the thread, pass the reference, address of the function and data
	// pthread_create() returns 0 on the successful creation of a thread
	if (pthread_create(&thread, NULL, &threadFunction, &x) != 0)
	{
		printf("Failed to create the thread\n");
		return 1;
	}
	// at this point the thread was created successfully
	while (y < 5)
	{               // loop and increment y, displaying values
		printf("The value of x=%d and y=%d \n", x, y);
		++y;
		usleep(1000);         // encourage the pthread to run
	}
	void *result;             // OPTIONAL: receive data back from pthread
	pthread_join(thread, &result);   // allow the pthread to complete
	int *z = (int*) result;         // cast from void* to int* to get z
	printf("Final: x=%d, y=%d and z=%d\n", x, y, *z);
	return EXIT_SUCCESS;
}
