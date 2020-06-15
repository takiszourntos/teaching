/*
 * stack.h
 *
 *  Created on: Jun. 15, 2020
 *      Author: takis
 */

#ifndef INCLUDES_STACK_H_
#define INCLUDES_STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	N	1024

/*
 * struct and typedef declarations
 */
struct stack_struct
{
	int data[N];
	size_t top;
};
typedef struct stack_struct stack_t;


bool stack_empty(stack_t *s);

void push(stack_t *s, int x);

int pop(stack_t *s);

#endif /* INCLUDES_STACK_H_ */
