/*
 * q0.c:
 *
 * 		queue data structure demonstrator code
 * 		(main queue functions and data types are found in queue_lib library)
 *
 *  Created on: Oct. 30, 2019
 *      Author: takis
 */

#include <stdlib.h>
#include "queue_lib.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


/*
 * transmitter function: as a thread, it send a new elements to a queue after a delay,
 *   sending a maximum of 2*Lq elements before quitting
 */
void	*funcTx(void *pds)
{
	/* cast the passed data structure to our queue variable */
	queue_t 	*q = (queue_t *) pds;
	int xpos = 0;
	int ypos = 0;
	unsigned int key = 0;
	qrec_t newrec;
	unsigned long i=0;

	while (i != Lq/2)
	{
		/* create a new record with contrived data */
		newrec.x = xpos;
		newrec.y = ypos;
		newrec.key = key;
		key = (++xpos)*(++ypos);

		/* enqueue this record */
		enqueue(q, newrec);

		/* delay a bit to let dequeueing happen without overflowing */
		usleep(2000);

		/* increment counter */
		++i;
	}

	return q; // return the set, unchanged
}

/*
 * receiver function: as a thread, it receives new elements from a queue after a delay,
 *   removing a maximum of Lq elements before quitting
 */
void	*funcRx(void *pds)
{
	/* cast the passed data structure to our queue variable */
	queue_t *q = (queue_t *) pds;

	/* storage for the retrieved record */
	qrec_t 	*pnewrec;

	unsigned long i=0;
	while (i != Lq/2)
	{
		if ( (q->head) != (q->tail) ) /* simple check to ensure that an underflow won't happen */
		{
			/* storage for retrieved record */
			pnewrec = dequeue(q);

			/* delay a bit to allow queue to build up somewhat */
			usleep(2000);
		}
		/* increment counter */
		++i;
	}

	return q; // return the set, unchanged
}


int main()
{
    pthread_t 	thread_sender;	// our handle for the averaging thread
	pthread_t	thread_receiver;	// our handle for the sorting thread

	/* define and initialize main queue, qm */
	queue_t qm;
	qm.head = 0;
	qm.tail = 0;
	queue_t *pqm = &qm;

    /* create threads */
    if(pthread_create(&thread_sender, NULL, &funcTx, (void *) pqm)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }
    if(pthread_create(&thread_receiver, NULL, &funcRx, (void *) pqm)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }

    /* allow threads to complete */
    void *result;
    pthread_join(thread_sender, &result);
    pthread_join(thread_receiver, &result);

    /* print results */
    printf("final state of the queue: q.head=%zu and q.tail=%zu\n",qm.head,qm.tail);

    return 0;
}
