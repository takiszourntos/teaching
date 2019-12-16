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
	item_t array[L];
};
typedef struct buffer_struct buffer_t;

#endif /* BUFFERS_H_ */
