/*
 * q0.c
 *
 *  Created on: Oct. 30, 2019
 *      Author: takis
 */
#ifndef HEADERS_QUEUE_LIB_H_
#define HEADERS_QUEUE_LIB_H_

#include <stdlib.h>

#define Lq	1024 /* maximum number of queue elements */

struct q_rec
{
	int	x;
	int y;
	unsigned int key;
};
typedef struct q_rec qrec_t;

struct q_struct
{
	size_t head;
	size_t tail;
	qrec_t data[Lq];
};
typedef struct q_struct queue_t;

/*********************/
/* queuing functions */
/*********************/

/*
 *
 * enqueue(pq, d):
 * 		- adds new data, d, to queue, q, at q.tail (pq is pointer to q)
 * 		- updates q.tail
 *
 */
void enqueue(queue_t *, qrec_t );

/*
 *
 * d* = dequeue(pq):
 * 		- retrieves new data, d, from queue, q, at q.head  (pq is pointer to q)
 * 		- updates q.head
 * 		- for efficiency, returns a pointer to d
 *
 */
qrec_t* dequeue(queue_t *);

#endif /* HEADERS_QUEUE_LIB_H_ */

