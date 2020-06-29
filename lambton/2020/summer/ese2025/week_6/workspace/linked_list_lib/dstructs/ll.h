/*
 * ll.h
 *
 *  Created on: Jun. 29, 2020
 *      Author: takis
 */

#ifndef DSTRUCTS_LL_H_
#define DSTRUCTS_LL_H_

#include <stdlib.h>

/*************************************************************
 * NODE STRUCT GOES HERE
 *************************************************************/

// nodes can be referenced by a KEY, of this type
typedef unsigned int data_key_t;

// nodes contain a PAYLOAD consisting of various elements and the key
struct data_struct
{
	double X;
	double Y;
	data_key_t key;
};
typedef struct data_struct data_t;

// actual node struct/typedef
struct linkedList
{
	data_t payload;
	struct linkedList *pNext; // recursively defined "next" pointer
};
typedef struct linkedList ll_t;

/************************************************************
 * USEFUL LINKED LIST FUNCTIONS
 ************************************************************/
/*
 * setPayload():
 *
 *		for the node pointed to by the first argument, this function
 *		sets the value of the node's payload to the function's
 *		second argument
 *
 */
void setPayload(ll_t*, data_t);


/*
 * createNode():
 *
 * 		creates a node of type ll_t from the heap, and returns
 * 		a pointer to this newly created node; sets the node's own
 * 	    pNext pointer to NULL;
 *
 */
ll_t* createNode(void);

/*
 * addNode():
 *
 * 		adds a new node (with payload given by second argument) to the
 * 		bottom/back of the list referenced by the pointer, head;
 * 		if head==NULL, a new list is created, and the new head pointer
 * 		is returned;
 *
 */
ll_t* addNode(ll_t*, data_t);

/*
 * insertNode():
 *
 * 		for a list with head pointer given by the first argument, this
 * 		function inserts a new node with payload given by the second argument
 * 		at the point just BEFORE the node whose key matches the third
 * 		argument; if head pointer returns NULL, a new list is created, and
 * 		the new head pointer is returned;
 *
 */
ll_t* insertNode(ll_t*, data_t payload, data_key_t insertionPoint);

/*
 * deleteNode():
 *
 * 		for a list with head pointer given by the first argument, this
 * 		function deletes the node whose key data matches the second argument;
 * 		if head pointer returns NULL, an error is generated, indicating that
 * 		the node is not found;
 *
 */
void deleteNode(ll_t*, data_key_t);


#endif /* DSTRUCTS_LL_H_ */
