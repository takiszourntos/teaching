/*
 * mylib.c
 *
 *  Created on: Sep. 26, 2019
 *      Author: takis
 */

/*
 * this amazing function finds the largest element of an array
 *
 * params:
 * 		- pointer to the array (int *)
 * 		- number of elements in the array (int)
 */

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
