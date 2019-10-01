/*
 * simple_1.c
 *
 *  Created on: Oct. 1, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_vector_double.h> /* using double precision */

/* simple Fibonancci sequence generator, using recursion */
size_t fib(size_t k)
{
	if (k==0)
	{
		return 1;
	}
	else if (k==1)
	{
		return 2;
	}
	else /* k > 2 */
	{
		return fib(k-1) + fib(k-2);
	}
}

int main()
{
	/* vector parameters */
	size_t		N=10; /* index type, vector sizes */
	gsl_vector *a = gsl_vector_alloc(N); /* allocate vector of size N */
	gsl_vector *b = gsl_vector_calloc(N); /* allocate vector of size N, initialize entries to zero */

	/* initialize vectors */
	for (size_t i = 0; i != N; ++i)
	{

		gsl_vector_set(a, i, 1.23 + i);
	}







	return EXIT_SUCCESS;
}
