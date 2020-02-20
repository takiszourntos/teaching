/*
 * buffers.c
 *
 * 	useful library for ring buffers in DSP
 * 	the current pointer, b.current, always points
 * 	to buffer element x(n), where n is the current
 * 	time.
 *
 *
 *		 	  index	  element
 *				0		?
 *				1		?
 *				2		?
 *				.		.
 *				.		.
 *				.		.
 * b.offset-->	r		x(n-(K-1))
 *				r+1		x(n-(K-2))
 *				.		.
 *				.		.
 *				.		.
 *				s-1		x(n-1)
 * b.current-->	s   	x(n)
 *				.		.
 *				.		.
 *				.		.
 *				LB-2	?
 *				LB-1	?
 *
 *
 *  Created on: Dec. 15, 2019
 *      Author: takis
 */

#include <stdint.h>
#include <stdlib.h>
#include "buffers.h"

/*
 * size() function returns the number of valid elements in the buffer,
 * 		between b.current and b.offset; size() can return a maximum
 * 		of b->K.
 */
size_t size(buffer_t *b)
{
	size_t s = b->current - b->offset + 1;
	return s;
}

/*
 * init_buffer() function initializes the buffer (b) pointers and sets the "data
 * 		depth" of the buffer (depth parameter)
 */
void init_buffer(buffer_t *b, size_t depth)
{
	b->K=depth;
	b->offset=0;
	b->current=0;
	/* initialize array values to zero */
	for (size_t i=0; i!=LB; ++i) (b->array)[i]=0;
	return;
}

/*
 * enbuffer() function adds the current sample to the buffer, by updating
 * 		b->current and setting b->array[b->current] accordingly;
 * 		if the buffer size is equal to b->K, then the offset pointer
 * 		follows along, to maintain a fixed depth of valid data
 */
void enbuffer(buffer_t *b, item_t x_n)
{
	if ((b->current)==(LB-1))
	{
		b->current = 0;
	}
	else
	{
		(b->current)++;
	}
	(b->array)[b->current]=x_n; /* set the current-pointer value of the array to be x(n) */

	if (b.size() == (b->K))
	{
		/* offset must follow to keep b->size() fixed */
		if ((b->offset) == (LB-1))
		{
			b->offset=0;
		}
		else
		{
			(b->offset)++;
		}
	}
	return;
}

/*
 * debuffer() function returns an index to the element x(n-i), which gives access to the
 * 		buffer elements x(n-i) through x(n-(K-1))
 *
 */
size_t debuffer(buffer_t* b, size_t i)
{
	return (b->current) - i;
}




