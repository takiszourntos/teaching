/*
 * loop_1.c
 *
 *  Created on: Sep. 23, 2019
 *      Author: takis
 */

#include<stdio.h>

int main(void)
{
	char d;
	int x;

	x = 7;
	d = '*';

	printf("\n\n");
	do
	{
		printf("%c",d);
		--x;
	} while (x != 0);

	return 0;
}
