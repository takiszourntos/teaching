/*
 * ds1.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */

#include <stdlib.h>

/*
 * define a linked list node structure
 */
struct linkedList
{
	int data;
	struct linkedList *pNext;
};
typedef struct linkedList ll_t;

/*
 * define basic functions
 */
ll_t* createNode()
{
	/* create a pointer for the new node */
	ll_t *node;

	/* allocate the node from heap */
	node = (ll_t *) malloc(sizeof(ll_t));

	/* make next point to NULL */
	node->pNext = NULL; //

	/* return the pointer to the new node */
	return node;
}

ll_t* addNode(ll_t* head, int value)
{
	/* create two node pointers */
	ll_t *node;
	ll_t *p;

	/* prepare the new node to be added */
	node = createNode();
	node->data = value; /* set the new element's data field to value */

	if (head == NULL)
	{
		head = node; /* if the linked list has no nodes to begin with */
	}
	else
	{
		/* search through list until tail node is found */
		p = head;
		while ((p->pNext) != NULL)
		{
			p = p->pNext;
		}
		/* set the pointer from NULL to temp */
		p->pNext = node;
	}
	return head;
}

int main()
{
	return 0;
}

