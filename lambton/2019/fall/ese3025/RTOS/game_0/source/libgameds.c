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


/* function sets up very basic default settings for a newly created GO
 *
 * 	NB: presumes that passed in GO pointer already points to valid memory
 *
 */
go_t* getGODefaults(go_t *pRet, char taskstring[])
{
	/*
	 * GO IDs:
	 * 			0x0000 000q: players
	 * 			0x0000 00q0: aliens
	 * 			0x0000 0q00: poohs
	 * 			0x0000 q000: expungers
	 * 			0x000q 0000: babies
	 * 			0x00q0 0000: kitties
	 *
	 * 			where q \in {0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F}
	 *
	 */
	pRet->ID		= 0x00000000UL; /* to be defined by genesisGO */
	pRet->go_level	= 1;
	pRet->health 	= 256;
	pRet->alive 	= True;
	pRet->active	= True;
	pRet->on_screen	= True;
	pRet->gameover	= False;
	pRet->pos.X = 0; pRet->pos.Y = 0;
	pRet->vel.X = 0; pRet->vel.Y = 0;
	pRet->acc.X = 0; pRet->acc.Y = 0;
	pRet->move_left = False;
	pRet->move_right = False;
	pRet->crouch_or_extra = False;
	pRet->shoot_or_pooh = False;
	pRet->numlives = 3; /* by default, every GO is made with 3 lives */
	pRet->interactions=NULL;
	pRet->task=NULL;
	pRet->taskText=taskstring;
	pRet->pNext=NULL;
	pRet->pPrev=NULL;

	return pRet;
}

/*
 * creates a basic GO node, with default information based on GO type
 */
go_t* createGONode(char GOtype[])
{
	go_t *pNew = (go_t *) pvPortMalloc(sizeof(go_t));

	if (strcmp(GOtype,"player")==0)
	{
		pNew = getGODefaults(pNew, "player task");
		return pNew;
	}
}

/*
 * creates a game object for the first time, adding it to the GO master list
 */
go_t*	genesisGO(go_t* pGOHead, char GOtype[], go_coord_t GOstartcoord, size_t ID)
{
	go_t* pW=pGOHead; /* working pointer */

	if (pW==NULL)
	{
		/* create the first instance of this GO */
		//taskENTER_CRITICAL(); /* need to properly position and initialize an object before game play can resume */
			go_t *pNode =createGONode(GOtype); /* creates a GO node of desired type with generic, default settings */
			pNode->ID = ID;
			pNode->pos = GOstartcoord;
		//taskEXIT_CRITICAL();
		return pNode;
	}
	else
	{
		/* find the next available opening in the list */
		while (pW->pNext != NULL)
		{
			pW = pW->pNext;
		}
		/* now add the GO there, with the proper settings */
		//taskENTER_CRITICAL();
			pW->pNext = createGONode(GOtype); /* creates a GO node of desired type with generic, default settings */
			pW->pNext->ID = ID;
			pW->pNext->pos = GOstartcoord;
			pW->pNext->pPrev=pW;
		//taskEXIT_CRITICAL();
	}
	return pGOHead;
}

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









