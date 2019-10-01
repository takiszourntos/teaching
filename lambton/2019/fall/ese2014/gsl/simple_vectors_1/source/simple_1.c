/*
 * simple_1.c
 *
 *  Created on: Oct. 1, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_vector_double.h> /* using double precision */
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

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
	/* parameters */
		/* vectors */
		size_t		N=10; /* index type, vector sizes */
		gsl_vector *a = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *b = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *c = gsl_vector_calloc(N); /* allocate vector of size N but initialize entries to zero */

		/* random numbers */
		const gsl_rng_type *T;
		gsl_rng *r; /* handle for our random number generator */

	/* set up random number generation */
	gsl_rng_env_setup();
	T = gsl_rng_default;
	r = gsl_rng_alloc(T);

	/* initialize vectors */
	for (size_t i = 0; i != N; ++i)
	{
		gsl_vector_set(a, i, fib(i)); /* set element i of vector a to Fibonacci number i */
		gsl_vector_set(b, i, gsl_ran_flat(r, -1.0, +1.0));
//		gsl_vector_set(b, i, 1.0);
		gsl_vector_add(c, a); /* c += a */
		gsl_vector_add(c, b); /* c += b */
		printf("i=%d, a(i)=%f, b(i)=%f, c(i)=%f\n", i,
													gsl_vector_get(a, i),
													gsl_vector_get(b, i),
													gsl_vector_get(c, i));
	}
	/* de-allocate memory */
	gsl_vector_free(a);
	gsl_vector_free(b);
	gsl_vector_free(c);
	return EXIT_SUCCESS;
}
