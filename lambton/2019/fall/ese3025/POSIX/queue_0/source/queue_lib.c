/*
 * q0.c
 *
 *  Created on: Oct. 30, 2019
 *      Author: takis
 */

#include <stdlib.h>
#include "queue_lib.h"

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
void enqueue(queue_t *pq, qrec_t d)
{
	/* write the new record at the tail location */
	size_t i_new = pq->tail; /* index for new record in the array */
	(pq->data)[i_new].x = d.x;
	(pq->data)[i_new].y = d.y;
	(pq->data)[i_new].key = d.key;

	/* update the tail pointer */
	if (i_new == Lq)
	{
		pq->tail = 1;
	}
	else
	{
		++(pq->tail);
	}

	/* finish */
	return;
}

/*
 *
 * d* = dequeue(pq):
 * 		- retrieves new data, d, from queue, q, at q.head  (pq is pointer to q)
 * 		- updates q.head
 * 		- for efficiency, returns a pointer to d
 *
 */
qrec_t* dequeue(queue_t *pq)
{
	/* allocate memory from heap to store retrieved record */
	qrec_t *d = malloc(sizeof(qrec_t));
	size_t i_old = pq->head; /* index to old record at the head */

	/* update head pointer */
	if (i_old == Lq)
	{
		pq->head = 1;
	}
	else
	{
		++(pq->head);
	}
    return d;
}

