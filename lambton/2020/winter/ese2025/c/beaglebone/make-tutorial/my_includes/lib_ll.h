/*
 * linked_lists.h
 *
 *  Created on: Mar 31, 2020
 *      Author: takis
 */

#ifndef MY_INCLUDES_LIB_LL_H_
#define MY_INCLUDES_LIB_LL_H_

#define NAMESIZE 	30

/*
 * typedefs for doubly-linked-list data structures
 */
struct data_struct
{
	int ID;
	float GPA;
	char surname[NAMESIZE];
};
typedef struct data_struct data_t;

struct ll_node_struct
{
	data_t key;
	struct ll_node_struct *pPrev;
	struct ll_node_struct *pNext;
};
typedef struct ll_node_struct ll_node_t;

/*
 * function prototypes for doubly-linked-list algorithms
 */

ll_node_t* createNode(data_t);

void addNode(ll_node_t*, ll_node_t*);

void insertNode(ll_node_t*, ll_node_t*, data_t);

void deleteNode(ll_node_t*, data_t);

ll_node_t* findNode(ll_node_t*, data_t);

#endif /* MY_INCLUDES_LIB_LL_H_ */
