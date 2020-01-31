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
#include "libtakisbasics.h"

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
go_t*
getGODefaults (go_t *pRet, char taskstring[])
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
  pRet->ID = 0x00000000UL; /* to be defined by addGONode() */
  pRet->go_level = 1;
  pRet->health = 512;
  pRet->alive = True;
  pRet->active = True;
  pRet->gameover = False;
  pRet->pos.X = 0;
  pRet->pos.Y = 0;
  pRet->des_vel.X = 0;
  pRet->des_vel.Y = 0;
  pRet->can_move = True;
  pRet->acc.X = 0;
  pRet->acc.Y = 0;
  pRet->animstate = STOP;
  pRet->move_left = False;
  pRet->move_right = False;
  pRet->crouch_or_extra = False;
  pRet->shoot_or_pooh = False;
  pRet->numlives = 3; /* by default, every GO is made with 3 lives */
  pRet->interactions = NULL;
  pRet->task = NULL;
  pRet->taskText = taskstring;
  pRet->pNext = NULL;
  pRet->pPrev = NULL;

  return pRet;
}

/*
 * creates a basic GO node, with default information based on GO type
 */
go_t*
createDefaultGONode (game_t *this_game, uint8_t GOtype)
{
  /* GOtype values:
   * 		0 -> player
   * 		1 -> alien
   * 		2 -> poohs
   * 		3 -> expungers
   * 		4 -> babies
   * 		5 -> kitties
   */

  go_t *pNew = (go_t *) pvPortMalloc (sizeof(go_t));

  switch (GOType)
    {
    case 0: // player
      {
	pNew = getGODefaults (pNew, "player task");
	return pNew;
      }
    case 1: // aliens
      {
	pNew = getGODefaults (pNew, "aliens task");
	this_game->number_of_aliens++;
	return pNew;
      }
    case 2: // poohs
      {
	pNew = getGODefaults (pNew, "poohs (bombs) task");
	this_game->number_of_poohs++;
	return pNew;
      }
    case 3: // expungers
      {
	pNew = getGODefaults (pNew, "expungers task");
	this_game->number_of_expungers++;
	return pNew;
      }
    case 4: // babies
      {
	pNew = getGODefaults (pNew, "babies task");
	this_game->number_of_babies++;
	return pNew;
      }
    case 5: // kitties
      {
	pNew = getGODefaults (pNew, "kitties task");
	this_game->number_of_kitties++;
	return pNew;
      }
    }
}

/*
 *
 * creates a GO, adding it to the GO master list (e.g., this_game->aliens
 * or this_game->babies)
 *
 */
go_t*
addGONode (game_t *this_game, go_t* pGOHead, uint8_t GOtype,
	   go_coord_t GOstartcoord, uint32_t ID)
{
  go_t* pW = pGOHead; /* working pointer */

  if (pW == NULL)
    {
      /* create the first instance of this GO ... need to properly position and
       * initialize an object before game play can resume */
      go_t *pNode = createDefaultGONode (this_game, GOtype); // default settings
      pNode->kind = GOtype;
      pNode->ID = ID;
      pNode->pos = GOstartcoord;
      pW = pNode;
    }
  else
    {
      /* find the next available opening in the list */
      while (pW->pNext != NULL)
	{
	  pW = pW->pNext;
	}
      /* now add the GO there, with the proper settings */
      pW->pNext = createDefaultGONode (this_game, GOtype); // default settings
      pW->pNext->kind = GOtype;
      pW->pNext->ID = ID;
      pW->pNext->pos = GOstartcoord;
      pW->pNext->pPrev = pW;
    }
  return pW; /* return a pointer to the new element */
}

/*
 * function to edit the game "small lists" of type go_list_t
 */
void
prvUpdateInteractionList (go_t *pSub, go_t *pObj, uint16_t distance,
			  bool_t collision, bool_t seen)
{
  go_list_t *pW = pSub;
  go_list_t *ppW;
  size_t obj_ID = pObj->ID;
  gotype_t obj_kind = pObj->kind;

  /* look for obj in sub's interaction list */
  bool_t found = False;
  while (pW != NULL)
    {
      ppW = pW;
      if ((pW->ID) == obj_ID)
	{
	  found = True;
	  break;
	}
      pW = pW->pNext;
    }
  /* if obj not found, add it to the list */
  if (!found)
    {
      go_list_t *pNode = (go_list_t*) pvPortMalloc (sizeof(go_list_t));
      pNode->kind = obj_kind;
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
	      vPortFree ((void *) pW);
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

