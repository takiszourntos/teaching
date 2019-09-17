/*
 * pthreads_1.c
 *
 *  Created on: Sep. 13, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define 	MAXCOUNT	2147483647

// simple delay function
void short_delay(int count)
{
	for (int i=0; i != count; ++i);
	return;
}

// This is the thread function that will execute when the thread is created
//  it passes and receives data by void pointers
void *threadFunction_1(void *value)
{
	int *x = (int *)value;    //cast the data passed to an int

	while(*x<MAXCOUNT)
	{
		short_delay(10);      //sleep for a short delay
		++(*x);               //increment the value of x by 1
	}
	return x;                 //return the pointer to x
}

void *threadFunction_2(void *value)
{
	int *x = (int *)value;    //cast the data passed to an int

	while(*x<MAXCOUNT)
	{
		short_delay(10);      //sleep for a short delay
		++(*x);               //increment the value of x by 1
	}
	return x;                 //return the pointer to x
}

int main() {
    int x_1=0, x_2=0, y=0;
    pthread_t thread_1, thread_2;         //this is our handle to the pthread

    // create the threads, returns 0 on the successful creation of each thread
    if(pthread_create(&thread_1, NULL, &threadFunction_1, &x_1)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }
    if(pthread_create(&thread_2, NULL, &threadFunction_2, &x_2)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }

    // threads successfully created, move on to perform main program loop
    const int num_loops=10; // program will run for num_loops*100 milliseconds
    while (y != num_loops)
    {               // loop and increment y, displaying values
    	printf("The value of x_1=%d, x_2=%d and y=%d \n",x_1,x_2,y);
    	usleep(100);         // encourage the pthreads to run
    	++y;
    }

    // main loop completed, terminate all threads
    pthread_cancel(thread_1);
    pthread_cancel(thread_2);
    printf("Final: x_1=%d, x_2=%d, y=%d\n",x_1,x_2, y);
    return EXIT_SUCCESS;
}



