/*
 * dstructs.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takiss
 */

#include <stdlib.h>
#include "dstructs.h"

/*
 * createNode():
 *
 * 		creates a node of type ll_t from the heap, and returns
 * 		a pointer to this newly created node; sets the node's own
 * 	    pNext pointer to NULL
 *
 */
ll_t*	createNode()
{
	/* create a pointer for the new node */
    ll_t 	*node;

    /* allocate the node from heap */
    node = 	(ll_t *) malloc(sizeof(struct linkedList));

    /* make next point to NULL */
    node -> pNext = NULL;//

    /* return the pointer to the new node */
    return 	node;
}

/*
 * addNode():
 *
 * 		adds a new node (with node->data = value) to the bottom/back
 * 		of the list referenced by the pointer, head;
 * 		if head==NULL, a new list is created
 *
 */
ll_t* 	addNode(ll_t* head, int value)
{
	/* create two node pointers */
    ll_t *node;
	ll_t *p;

	/* prepare the new node to be added */
    node = createNode();
    node -> data = value; /* set the new element's data field to value */

    if (head == NULL)
    {
        head = node;     /* if the linked list has no nodes to begin with */
    }
    else
    {
        /* search through list until tail node is found */
        p  = head;
        while ((p->pNext) != NULL)
        {
            p = p -> pNext;
        }
        /* set the pointer from NULL to temp */
        p -> pNext = node;
    }
    return head;
}

