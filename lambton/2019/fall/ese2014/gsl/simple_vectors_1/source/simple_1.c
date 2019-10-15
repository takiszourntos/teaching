/*
 * simple_1.c
 *
 *  Created on: Oct. 1, 2019
 *      Author: takis
 */

/*
 * standard includes
 */
	#include <stdio.h>
	#include <stdlib.h>
/*
 *  includes for GSL components
 *  	- use double precision
 */
	#include <gsl/gsl_vector_double.h>
	#include <gsl/gsl_matrix_double.h>
	#include <gsl/gsl_rng.h>
	#include <gsl/gsl_randist.h>

/*
 * FUNCTIONS
 */

/*
 * simple Fibonacci sequence generator function, using recursion
 * */
size_t fib(size_t k)
{
	if (k==0)
	{
		return 0;
	}
	else if (k==1)
	{
		return 1;
	}
	else /* k >= 2 */
	{
		return fib(k-1) + fib(k-2);
	}
}

gsl_matrix *embt_mm(const gsl_matrix *U, const gsl_matrix *V, size_t N)
{
	gsl_matrix *W = gsl_matrix_alloc(N,N);
	double dp;
	double uk,vk;

	for (size_t i=0; i != N; ++i)
	{
		for (size_t j=0; j != N; ++j)
		{
			/* compute element (i,j) of W */
			dp = 0;
			for (size_t k=0; k != N; ++k)
			{
				uk = gsl_matrix_get(U,i,k);
				vk = gsl_matrix_get(V,k,j);
				dp += uk*vk;
			}
			gsl_matrix_set(W,i,j,dp);
		}
	}
	return W;
}

int main()
{
	/*
	 * INITIALIZE PARAMETERS
	 */
		/* vectors parameters */
		size_t		N=10; /* index type, vector sizes */
		gsl_vector *a = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *b = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *c = gsl_vector_calloc(N); /* allocate vector of size N but initialize entries to zero */

		/* random number generator parameters */
		const gsl_rng_type *T;
		gsl_rng *r; /* handle for our random number generator */

		/* matrix parameters */
		gsl_matrix *A = gsl_matrix_alloc(N,N);
		gsl_matrix *B = gsl_matrix_alloc(N,N);
		gsl_matrix *C = gsl_matrix_calloc(N,N);

	/*
	 * SET UP RANDOM NUMBER GENERATION
	 */
		gsl_rng_env_setup();
		T = gsl_rng_default;
		r = gsl_rng_alloc(T);

	/*
	 *  VECTOR OPERATIONS
	 */
		/* set the vector elements */
		for (size_t i = 0; i != N; ++i)
		{
			gsl_vector_set(a, i, fib(i)); /* set element i of vector a to Fibonacci number i */
			gsl_vector_set(b, i, gsl_ran_flat(r,-1.0,+1.0)); /* set element of vector b to random number */
		}

		/* c = a + b */
		gsl_vector_add(c, a); /* c += a */
		gsl_vector_add(c, b); /* c += b */

		/* print results */
		for (size_t i = 0; i != N; ++i)
		{
			printf("i=%d, a(i)=%f, b(i)=%f, c(i)=%f\n", i,
			gsl_vector_get(a, i),
			gsl_vector_get(b, i),
			gsl_vector_get(c, i));
		}

	/*
	 *	MATRIX OPERATIONS - your homework!! :)
	 */
		/* fill A with first N*N Fibonacci numbers, starting with row 1 (cols 1-10), then row 2, etc. */
		for (size_t i=0; i != N; ++i)
		{
			for (size_t j = 0; j != N; ++j)
			{
				gsl_matrix_set(A, i, j, (double) fib(j+i*N));
			}
		}

		/* fill B with N*N random numbers, uniformly distributed over the interval (-100, 100) */
		for (size_t i=0; i != N; ++i)
		{
			for (size_t j = 0; j != N; ++j)
			{
				gsl_matrix_set(B, i, j, gsl_ran_flat(r,-100.0,+100.0));
			}
		}

		/* make C the product of A and B */
		C = embt_mm(A,B,N);


		/* print the results */


	/* de-allocate memory */
	gsl_vector_free(a);
	gsl_vector_free(b);
	gsl_vector_free(c);
	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(C);
	return EXIT_SUCCESS;
}
