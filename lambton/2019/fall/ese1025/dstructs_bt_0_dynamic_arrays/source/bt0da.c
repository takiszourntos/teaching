/*
 * bt0da.c : demonstrate dynamic array allocation
 *
 *  Created on: Oct. 16, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>

typedef int	key_t;

key_t  pS[]={6,4,7,3,2,1,8,5,0,9};
size_t NS = sizeof(pS)/sizeof(key_t);

/*
 * compare function needed for qsort() in the stdlib
 */
int comp(const void* a, const void *b)
{
	int ia=*((int *) a);
	int ib=*((int *) b);

	if (ia<ib)
		return -1;
	else if (ia>ib)
		return +1;

	return 0; /* default return if ia==ib */
}

/*
 * median finder presumes set is sorted
 *
 * if the set contains an even number of elements, function
 * returns index to element just to left of median
 *
 * returns -1 if set is empty or contains only 1 element
 *
 */
size_t find_sorted_median(key_t *pset, size_t Lset)
{
	size_t i_median=-1;

	if (Lset != 0 )
	{
		i_median = Lset/2-1;
	}

	return i_median; /* set must contain at least two elements */
}

/*
 * function dynamically allocates an array of size given by
 * (iright-ileft)+1, made from another array pointed to by pset
 */
key_t	*form_set(const key_t *pset, size_t ileft, size_t iright)
{
	key_t *pnew = (key_t *) malloc((iright-ileft+1)*sizeof(key_t));

	for (size_t i=ileft; i != (iright+1); ++i)
	{
		pnew[i-ileft] = pset[i];
	}

	return pnew;
}

/*
 * function prints out an array on one line,
 * caller must provide the size of the set (Lset)
 */
void printset(key_t *pset, size_t Lset)
{

	for (size_t i=0; i != Lset; ++i)
	{
		printf("%d ",pset[i]);
	}
	printf("\n");

	return;
}

/*
 *
 * main code begins here
 *
 */
int main(void)
{
	size_t 	im;
	qsort(pS, NS, sizeof(key_t), comp);
	im = find_sorted_median(pS, NS);

	key_t *pSleft  = form_set(pS,0,im);
	key_t *pSright = form_set(pS,im+1,NS-1);

	printf("original (sorted) set is: ");
	printset(pS, NS);
	printf("left set is:  ");
	printset(pSleft, im+1);
	printf("right set is: ");
	printset(pSright, NS-im-1);

	free(pSleft);
	free(pSright);

	return 0;
}
