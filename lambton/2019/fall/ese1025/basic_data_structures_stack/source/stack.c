/*
 * stack.c
 *
 *  Created on: Oct. 7, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>

#define	L	1024
#define	TRUE	1U
#define	FALSE	0U

/*
 * struct and typedef declarations
*/
struct	stack_struct
{
	int	data[L];
	size_t 	top;
};
typedef struct stack_struct	stack_t;
typedef unsigned short int	bool_t;

/* *************** FUNCTIONS ***************** */
/*
 * stack_empty() implementation
 */
bool_t	stack_empty(stack_t* s)
{
	if ((s -> top) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 * push() implementation
 */
void push(stack_t* s, int x)
{
	s -> data[ (s->top)++ ] = x; /* equivalent to: s -> data [(s->top)] = x; (s->top)++; */
				     /* also equivalent to: (s->top)++; s -> data [(s->top)-1] = x; */
	return;
}

/*
 * pop() implementation
 */
int pop(stack_t* s)
{
	if (stack_empty(s))
	{
		printf("underflow error!");
		exit(EXIT_FAILURE);
	}
	else
	{
		return (*s).data[--(s->top)];
	}
}

int main()
{
	/* declare and initialize variables */
	stack_t	stack;
	stack.top = 0;

	int loadarr[10] = {52, -29, 36, 1154, 72,
			    0, 68, 44, 33, 59};

	/* load stack */
	size_t	i;
	for (i=0; i != 10; ++i)
	{
		printf("stack.top = %zu, ", stack.top);
		push(&stack, loadarr[i]);
		printf("pushing %d\n", loadarr[i]);
	}

	/* pop stack */
	int x;
	while (stack_empty(&stack) == FALSE)
	{
		printf("stack.top = %zu, ", stack.top);
		x = pop(&stack);
		printf("popping %d\n", x);
	}

	/* test error function */
	x = pop(&stack); /* comment this out to avoid error */

	return EXIT_SUCCESS;
}
