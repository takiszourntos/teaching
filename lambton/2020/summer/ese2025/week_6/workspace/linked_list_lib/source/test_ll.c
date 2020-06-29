/*
 * test_ll.c
 *
 *
 * To use this code, enter the following at the command prompt ($):
 *
 * $ cat ../../data/data_text.txt | ./linked_list_lib | more
 *
 *
 *  Created on: Jun. 29, 2020
 *      Author: takis
 */

#include <stdlib.h>
#include <stdio.h>
#include "ll.h"

int main(void)
{
	ll_t *pLLHead=NULL; // pointer to list, must be initialized to NULL
	data_t token;

	// create the linked list from standard input;
	// user indicates end of data by entering "9999"
	// for X, Y and key values.
	printf("\nLoading data...\n");
	scanf("%lf %lf %lu", &token.X, &token.Y, &token.key);
	pLLHead = addNode(pLLHead, token);
	while (token.X != 9999 && token.Y != 9999 && token.key != 9999)
	{
		scanf("%lf %lf %lu", &token.X, &token.Y, &token.key);
		addNode(pLLHead, token);
	}
	printf("     ... done.\n\n");

	// send linked list to standard output
	printf("\nPrinting the entire linked list to standard output:\n");
	ll_t *pW = pLLHead;
	while (pW != NULL)
	{
		token.X = pW->payload.X;
		token.Y = pW->payload.Y;
		token.key = pW->payload.key;
		printf("%lf %lf %lu\n", token.X, token.Y, token.key);

		pW = pW->pNext;
	}

	// terminate
	printf("\n\n ...done!\n\n");
	return 0;
}
