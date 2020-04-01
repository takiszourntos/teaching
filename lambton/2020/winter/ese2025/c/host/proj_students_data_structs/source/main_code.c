/*
 * main_code.c
 *
 *  Created on: Mar 31, 2020
 *      Author: takis
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "lib_ll.h"
#include "lib_bst.h"

int main(void)
{
	// load data into linked list
	ll_node_t *pHead = NULL;
	int ID_x;
	float GPA_x;
	char surname_x[NAMESIZE];

	while (scanf("%s %d %f", surname_x, &ID_x, &GPA_x))
	{
		data_t token;
		token.ID = ID_x;
		token.GPA = GPA_x;
		strcpy(token.surname, surname_x);
		printf("Just read: %s %d %f \n \n", surname_x, ID_x, GPA_x);
		if (pHead == NULL) // if list is empty
		{
			pHead = createNode(token); // create the first node
		}
		else // if list is not empty, attempt to add a node
		{
			ll_node_t *pNode = createNode(token);
			if (pNode != NULL) // memory allocation was successful
			{
				addNode(pHead, pNode);
			}
			else
			{
				printf("error: cannot add node to list!");
				return 1;
			}
		}
	}

	// load data into binary search tree
	// years of interest: 1930 to 2000, location #138, first temp (use year as key)

	// demonstrate search, insertion, deletion

	return 0;
}
