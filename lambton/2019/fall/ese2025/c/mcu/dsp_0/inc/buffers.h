/*
 * buffers.h
 *
 *  Created on: Dec. 15, 2019
 *      Author: takis
 */

#ifndef BUFFERS_H_
#define BUFFERS_H_

#include <stdint.h>
#include <stdlib.h>

#define	LB	128 /* maximum buffer size */

typedef uint32_t item_t;

struct buffer_struct
{
	size_t K;
	size_t current;
	size_t offset;
	item_t array[LB];
};
typedef struct buffer_struct buffer_t;

/*
 * size() function returns the number of valid elements in the buffer,
 * 			between b.current and b.offset; size() can return a maximum
 * 			of b->K.
 */
size_t size(buffer_t *);

/*
 * init_buffer() function initializes the buffer (b) pointers and sets the "data
 * 					depth" of the buffer (depth parameter)
 */
void init_buffer(buffer_t *, size_t);

/*
 * enbuffer() function adds the current sample to the buffer, by updating
 * 				b->current and setting b->array[b->current] accordingly;
 * 				if the buffer size is equal to b->K, then the offset pointer
 * 				follows along, to maintain a fixed depth of valid data
 */
void enbuffer(buffer_t *, item_t);

/*
 * debuffer() function returns an index to the element x(n-i), which gives access to the
 * 				buffer elements x(n-i) through x(n-(K-1))
 *
 */
size_t debuffer(buffer_t*, size_t);

#endif /* BUFFERS_H_ */
