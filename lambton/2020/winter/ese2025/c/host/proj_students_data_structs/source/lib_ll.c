/*
 * lib_linked_lists.c
 *
 *  Created on: Mar 31, 2020
 *      Author: takis
 */

#include <stdlib.h>
#include "lib_ll.h"

/*
 * function source code for doubly-linked-list algorithms
 */

ll_node_t* createNode(data_t info)
{
	ll_node_t *pNew = (ll_node_t *) malloc(sizeof(ll_node_t));

	if (pNew != NULL)
	{
		// assign the new node's data
		pNew->key.ID = info.ID;
		pNew->key.GPA = info.GPA;
		pNew->key.surname = info.surname;

		// initialize the new node's pointers
		pNew->pPrev = NULL;
		pNew->pNext = NULL;
	}
	return pNew;
}

void addNode(ll_node_t *pHead, ll_node_t *pNode)
{
	if (pHead != NULL)
	{
		// find the last node in the linked list
		ll_node_t *pW = pHead;
		while (pW->pNext != NULL)
		{
			pW = pW->pNext; // traverse the tree
		}
		// at this point, pW points to the last node
		pW->pNext = pNode; // point the last node's pNext to the new last node
		pNode->pPrev = pW; // point the new node's pPrev pointer to previous last node
	}
	return;
}

void insertNode(ll_node_t *pHead, ll_node_t *pNode)
{
	// your code goes here
	return;
}

void deleteNode(ll_node_t *pHead, data_t info)
{
	// your code goes here
	return;
}

ll_node_t* findNode(ll_node_t *pHead, data_t info)
{
	ll_node_t *pNode = pHead;

	// your code goes here

	return pNode;
}
