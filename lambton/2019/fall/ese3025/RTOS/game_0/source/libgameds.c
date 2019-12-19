/*
 * libgameds.c
 *
 * Game Data Structures and Data Manipulation Library
 *
 *  Created on: Dec. 18, 2019
 *      Author: takis
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "libgameds.h"

/*****************************************************************************
 *
 * FUNCTIONS
 *
 *****************************************************************************/

/*
 * function to edit the game "small lists" of type go_list_t
 */
void prvUpdateInteractionList(go_t *pSub, go_t *pObj, uint16_t distance, bool_t collision, bool_t seen)
{
	go_list_t	*pW=pSub;
	go_list_t	*ppW;
	size_t	obj_ID = pObj->ID;

	/* look for obj in sub's interaction list */
	bool_t	found = False;
	while (pW != NULL)
	{
		ppW=pW;
		if ((pW->ID)==obj_ID)
		{
			found = True;
			break;
		}
		pW = pW->pNext;
	}
	/* if obj not found, add it to the list */
	if (!found)
	{
		go_list_t 	*pNode = (go_list_t*) pvPortMalloc(sizeof(go_list_t));
		pNode->ID = obj_ID;
		pNode->distance = distance;
		pNode->seen = seen;
		pNode->collision = collision;
		pNode->pNext = NULL;
		pNode->pPrev = ppW;
		ppW->pNext = pNode;
	}
	else
	{
		/* obj is already on the interaction list; if already in collision,
		 * must remain so; if unseen, and not in collision, remove from list */
		if (pW->collision == False)
		{
			if ((!seen) && (!collision))
			{
				/* remove the node */
				ppW->pNext = pW->pNext;
				(pW->pNext)->pPrev = ppW;
				vPortFree((void *) pW);
			}
			else
			{
				/* update the interaction parameters */
				pW->seen = seen;
				pW->collision = collision;
			}
		}
	}
} /* end prvUpdateInteractionList */









