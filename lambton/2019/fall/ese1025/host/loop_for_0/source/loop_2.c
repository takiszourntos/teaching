/*
 * loop_2.c
 *
 *  Created on: Sep. 23, 2019
 *      Author: takis
 */

#include <stdio.h>

int main(void)
{
	char d;
	d = '*';

	for (int x = 7; x != 0; --x)
	{
		printf("%c", d);
	}
	return 0;
}
