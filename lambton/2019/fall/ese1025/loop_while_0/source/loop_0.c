/*
 * loop_0.c
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
	/*
	 	 invariant: x represents the number of characters remaining to be printed
	*/
	while (x != 0)
	{
		printf("%c",d);
		--x;
	}
	return 0;
}
