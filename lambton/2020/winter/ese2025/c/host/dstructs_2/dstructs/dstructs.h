#ifndef DSTRUCTS_DSTRUCTS_H_
#define DSTRUCTS_DSTRUCTS_H_

/*
 * dstructs.h
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */


#include <stdlib.h>

/*************************************************************
 * NODE STRUCT GOES HERE
 *************************************************************/
struct linkedList
{
	int		data;
	struct 	linkedList *pNext;
};
typedef struct linkedList ll_t;


/************************************************************
 * USEFUL LINKED LIST FUNCTIONS
 ************************************************************/

/*
 * createNode():
 *
 * 		creates a node of type ll_t from the heap, and returns
 * 		a pointer to this newly created node; sets the node's own
 * 	    pNext pointer to NULL
 *
 */
ll_t*	createNode();

/*
 * addNode():
 *
 * 		adds a new node (with node->data = value) to the bottom/back
 * 		of the list referenced by the pointer, head;
 * 		if head==NULL, a new list is created
 *
 */
ll_t* 	addNode(ll_t*, int);

#endif /* DSTRUCTS_DSTRUCTS_H_ */
