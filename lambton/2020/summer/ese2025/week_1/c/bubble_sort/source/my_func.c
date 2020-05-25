/*
 * my_func.c
 *
 *  Created on: May 25, 2020
 *      Author: takis
 */

#include<stdio.h>
#include<stdlib.h>
#include "my_func.h"

/*
 * function to print out the array contents
 */
void dispArray(const int *s, size_t N)
{
	for (size_t i=0; i != N; ++i)
	{
		printf("%d ",s[i]);
	}
	printf("\n");
	return;
}

/*
 * function to sort the array
 */
void bsort(int *s, size_t N)
{
	// note that s and N are the local find_largest_int variables!

	// your code goes here

	return;
}
