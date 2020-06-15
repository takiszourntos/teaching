/*
 * stack.c
 *
 *  Created on: Oct. 7, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


/* *************** FUNCTIONS ***************** */
/*
 * stack_empty() implementation
 */
bool stack_empty(stack_t *s)
{
	if ((s->top) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * push() implementation
 */
void push(stack_t *s, int x)
{
	s->data[(s->top)++] = x; /* equivalent to: s -> data [(s->top)] = x; (s->top)++; */
	/* also equivalent to: (s->top)++; s -> data [(s->top)-1] = x; */
	return;
}

/*
 * pop() implementation
 */
int pop(stack_t *s)
{
	if (stack_empty(s))
	{
		printf("underflow error!");
		exit(EXIT_FAILURE);
	}
	else
	{
		return (*s).data[--(s->top)]; /* could also write: (s->data)[--(s->top)]; */
	}
}

