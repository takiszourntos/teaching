/*
 * hello_1.c
 *
 *  Created on: Sep. 20, 2019
 *      Author: takis
 */

#include <stdio.h>

/* global variables */
	char message[50]="Hello it is nice to meet you, ";  /* allow message of up to 50 characters */
	char user_name[30]; /* allow a user name of up to 30 characters */

/* main code begins */
int main()
{
	/* main's local variables */
	int mood;
	char pets;

	/* request user's name */
	printf("Please enter your name: ");
	scanf("%s", user_name);

	/* display message */
	printf("%s",message);
	printf("%s!\n", user_name);

	/* ask questions */
	printf("\nI hope you do not mind answering some questions!\n");
	printf("\nDo you have any pets? (Y or N): ");
	scanf(" %c", &pets);
	printf("\nOn a scale from 1 to 10, how would rate your mood today? (1=very sad, 10=very happy): ");
	scanf("%d", &mood);

	/* wrap-up */
	printf("\n\nThank you for answering my questions, %s, goodbye!", user_name);

	/* exit successfully */
	return 0;
}
