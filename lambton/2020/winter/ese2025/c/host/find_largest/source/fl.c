/*
 * fl.c
 *
 *  Created on: Sep. 19, 2019
 *      Author: takis
 */

#include<stdio.h>

#define	N	10

// function prototype
int largest(int *, int);

int main(void)
{
	int s[N] =
	{ 92, 3754, 1584, 22, 34, 89374, 234, 156, 56, 6 };
	int max;

	printf("\n\nYour set of integers is:\n");
	for (int i = 0; i != N; ++i)
	{
		printf("%d ", s[i]);
	}

	max = largest(s, N);
	printf("\nAnd the largest integer is: %d\n\n", max);

	return 0;
}

int largest(int *set, int N_s)
{
	int large = set[0];
	for (int i = 1; i != N_s; ++i)
	{
		if (set[i] > large)
		{
			large = set[i];
		}
	}
	return large;
}
