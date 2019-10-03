/*
 * ds0.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */

#include <stdlib.h>

#define 	NUM_USERS	128U

/*
 * structure declaration
 */
struct addr
{
	char			name[30];
	unsigned int 	house_num;
	char			street[30];
	char 			city[20];
	char 			province[4];
	char			postal_code[8]; /* need room for space and null terminator */
};

typedef	struct 		addr addr_t; /* typedef declaration based on struct */

/*
 * declare variables based on this struct -- which looks better?
 */
struct	addr		addr_info_A; /* one way of declaring */
addr_t				addr_info_B; /* a slightly simpler way of declaring */

/*
 * declare a pointer to the structure type
 */
addr_t				*paddr_info;

/*
 * declare an array of structure elements
 */
addr_t				addr_users[NUM_USERS];

int main()
{
	/* set some values for the non-pointers */
	addr_info_A.house_num = 1227U;
	addr_info_B.house_num = 1211U;

	/* set some values when there is a pointer variable */
	paddr_info = &addr_info_A;
	(*paddr_info).house_num = 1227U; /* using a de-reference operator */
	paddr_info = &addr_info_B;
	paddr_info -> house_num = 1211U; /* using shorthand notation */

	/* access the array */
	unsigned int first_num;
	size_t	i;
	for (i=0; i != NUM_USERS; ++i)
	{
		if ((first_num = addr_users[i].house_num)==0)
		{
			first_num = addr_users[1].house_num;
			++i;
		}
	}
	return 0;
}




