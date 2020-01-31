/*
 * libgametasks.c
 *
 *  Created on: Dec. 19, 2019
 *      Author: takis
 */

#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "libgameds.h"
#include "libgametasks.h"
#include "libtakisbasics.h"

/*************************************************************************
 *
 *
 * PRIVATE FUNCTIONS
 *
 *
 *************************************************************************/
/*
 * function to initialize game at very beginning
 */
static void
prvInitGame (game_t *this_game)
{
  /* initialize GO code books */
  for (size_t i = 0; i != MAX_GO_CODES; ++i)
    {
      /* GO IDs:
       * 			0x0000 000q: players
       * 			0x0000 00q0: aliens
       * 			0x0000 0q00: poohs
       * 			0x0000 q000: expungers
       * 			0x000q 0000: babies
       * 			0x00q0 0000: kitties
       */

      this_game->aliensID[i].code = 0x00000000 + (i << 4);
      this_game->poohsID[i].code = 0x00000000 + (i << 8);
      this_game->expungersID[i].code = 0x00000000 + (i << 12);
      this_game->babiesID[i].code = 0x00000000 + (i << 16);
      this_game->kittiesID[i].code = 0x00000000 + (i << 20);

      this_game->aliensID[i].available = True;
      this_game->poohsID[i].available = True;
      this_game->expungersID[i].available = True;
      this_game->babiesID[i].available = True;
      this_game->kittiesID[i].available = True;
    }

  this_game->number_of_aliens = 0;
  this_game->number_of_poohs = 0;
  this_game->number_of_expungers = 0;
  this_game->number_of_babies = 0;
  this_game->number_of_kitties = 0;

  return;
}

static bool_t
prvGetGOIDCode (go_ID_t *book, uint32_t *code)
{
  bool_t code_found = False;

  /* find an available code */
  for (size_t i = 0; i != MAX_GO_CODES; ++i)
    {
      if (book[i].available)
	{
	  *code = book[i].code;
	  code_found = True;
	  book[i].available = False;
	  break;
	}
    }
  return code_found;
}

/*
 *
 * function determines if an event happens, based on how likely it is...
 * the likelihood is passed in as a parameter
 *
 */

static bool_t
prvYesHappens (likely_t prob)
{
  /*
   HighlyLikely = 0U,		// < RAND_MAX (probability \approx 1)
   QuiteLikely = 1U, 		// < RAND_MAX / 2, prob. = 50 %
   ModeratelyLikely = 2U, 	// < RAND_MAX / 4, prob. = 25 %
   Maybe = 3U,			// < RAND_MAX / 8, prob. = 12.5 %
   Unlikely = 4U,		// < RAND_MAX / 16, prob. = 6.25 %
   QuiteUnLikely = 5U, 		// < RAND_MAX / 32, prob. = 3.125 %
   YeahRight = 6U,		// < RAND_MAX / 64, prob. = 1.5625 %
   */
  int r = rand (); /* pull my finger */
  register int s = RAND_MAX;

  s = s << prob;
  if (r < s)
    {
      return True;
    }
  else
    {
      return False;
    }
}

/*
 *
 * function provides an integer-friendly l1 metric,
 * namely, the sum of the absolute values of the element-wise
 * differences
 *
 */
uint16_t
uiCompareGODistance (go_coord_t A, go_coord_t B)
{
  return abs (A.X - B.X) + abs (A.Y - B.Y);
}

/*
 *
 * function updates GO interaction list of subject
 *
 */
static void
prvUpdateInteractionList (go_t *pSub, go_t *pObj, uint16_t distance,
			  bool_t collision, bool_t seen)
{
  go_list_t *pW = pSub->interactions;
  go_list_t *ppW;
  uint32_t objID = pObj->ID;

  /* look for obj in sub's interaction list */
  bool_t found = 0;
  while (pW != NULL)
    {
      ppW = pW;
      if (pW->ID == objID)
	{
	  found = 1;
	  break;
	}
      pW = pW->pNext;
    }
  if (!found)
    {
      /* add node to interaction list */
      go_list_t *pNew = (go_list_t *) pvPortMalloc (sizeof(go_list_t));
      pNew->ID = objID;
      pNew->distance = distance;
      pNew->seen = seen;
      pNew->collision = collision;
      pNew->pNext = NULL;
      pNew->pPrev = ppW;
      ppW->pNext = pNew;
    }
  else
    {
      /* object is already on the interaction list, update status:
       * 	- if already in collision, must remain so;
       * 	- if unseen, and not in collision, remove from list.
       */
      if (!pW->collision)
	{
	  if (!seen && !collision)
	    {
	      /* remove the node */
	      ppW->pNext = pW->pNext;
	      (pW->pNext)->pPrev = ppW;
	      pvPortFree ((void *) pW);
	    }
	  else
	    {
	      /* update parameters */
	      pW->seen = seen;
	      pW->collision = collision;
	    }
	}
    }
} /* end of prvUpdateInteractionList() */

/*
 *
 * function computes determines the "relationship" between subject and object
 * GOs
 *
 */
static void
prvComputeProximities (go_t* pSubject, go_t* pObject)
{
  go_t *pW = pObject; /* working pointer */
  go_list_t *pWI = pSubject->interactions;

  uint16_t distance;

  while (pW != NULL)
    {
      /* is pObject in contact or seen? */
      distance = uiCompareGODistance (pSubject->pos, pObject->pos);
      if (distance <= THRESHOLD_COLLISION)
	{
	  /* object and subject are in contact */
	  prvUpdateInteractionList (pSubject, pObject, distance, 1, 1);
	}
      else if (distance <= THRESHOLD_SEEN)
	{
	  /* no contact, but object seen by subject */
	  prvUpdateInteractionList (pSubject, pObject, distance, 0, 1);
	}
      else
	{
	  /* no interaction between subject and object, consider removal */
	  prvUpdateInteractionList (pSubject, pObject, distance, 0, 0);
	}
      pW = pW->pNext;
    }
}

/*
 *
 * function deletes all GO nodes, terminates all GO tasks and
 * releases all GO ID codes
 *
 */
static void
prvDeleteAllTasks (game_t *this_game)
{
  go_t *pW = NULL;
  go_t *pTemp = NULL;

  /* eradicate aliens */
  pW = this_game->aliens;
  while (pW != NULL)
    {
      vTaskDelete (pW->task);
      pTemp = pW->pNext; /* save the pointer to the next GO node */
      vPortFree (pW); /* delete current GO node */
      pW = pTemp; /* move on to the next one */
    }
  /* eradicate poohs */
  pW = this_game->poohs;
  while (pW != NULL)
    {
      vTaskDelete (pW->task);
      pTemp = pW->pNext;
      vPortFree (pW);
      pW = pTemp;
    }
  /* eradicate babies */
  pW = this_game->babies;
  while (pW != NULL)
    {
      vTaskDelete (pW->task);
      pTemp = pW->pNext;
      vPortFree (pW);
      pW = pTemp;
    }
  /* eradicate kitties */
  pW = this_game->kitties;
  while (pW != NULL)
    {
      vTaskDelete (pW->task);
      pTemp = pW->pNext;
      vPortFree (pW);
      pW = pTemp;
    }
  /* eradicate expungers */
  pW = this_game->expungers;
  while (pW != NULL)
    {
      vTaskDelete (pW->task);
      pTemp = pW->pNext;
      vPortFree (pW);
      pW = pTemp;
    }
  /* free all codes from GO code book */
  for (size_t i = 0; i != MAX_GO_CODES; ++i)
    {
      /* GO IDs:
       * 			0x0000 000q: players
       * 			0x0000 00q0: aliens
       * 			0x0000 0q00: poohs
       * 			0x0000 q000: expungers
       * 			0x000q 0000: babies
       * 			0x00q0 0000: kitties
       */
      this_game->aliensID[i].available = True;
      this_game->poohsID[i].available = True;
      this_game->expungersID[i].available = True;
      this_game->babiesID[i].available = True;
      this_game->kittiesID[i].available = True;
    }
}

/*
 * Uses addGONode() to create a GO list element, then applies xTaskCreate()
 * to generate the behaviour for that GO
 */
static go_t*
spawnGONodeandTask (game_t *this_game, go_t *pGOHead, uint8_t GOtype,
		    go_coord_t GOstartcoord, go_id_t *codebook,
		    uint32_t GOIDcode)
{
  /* GOtype values (listed here for reference):
   * 		0 -> player
   * 		1 -> alien
   * 		2 -> poohs
   * 		3 -> expungers
   * 		4 -> babies
   * 		5 -> kitties
   */
  /* initialize working pointer */
  if (!GOtype) // if it's a player we're creating then
    {
      if (pGOHead == NULL) // list is empty, create the first player
	{
	  taskENTER_CRITICAL();
	  go_t *pW = addGONode (this_game, pGOHead, 0, GOstartcoord, GOIDcode);
	  xTaskCreate(vPlayerTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	  taskEXIT_CRITICAL();
	  return pW;
	}
    }
  else // any type of game object (GO) other than a player GO
    {
      taskENTER_CRITICAL();
      if (pGOHead == NULL) // the list is empty
	{
	  go_t *pW = addGONode (this_game, pGOHead, GOType, GOstartcoord,
				GOIDCode); // working ptr points to new node
	}
      else
	{
	  /* there is already at least one element in the GO list,
	   * so find the next available spot... */
	  go_t* pW = pGOHead;
	  while (pW->pNext != NULL)
	    {
	      pW = pW->pNext;
	    }
	  go_t* pNew = addGONode (this_game, pGOHead, GOType, GOstartcoord,
				  GOIDCode);
	  pW->pNext = pNew;
	  pW = pNew; // make working ptr point to new node
	}
      switch (GOType)
	{
	case alien:
	  xTaskCreate(vAliensTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	case pooh:
	  xTaskCreate(vPoohsTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	case expunger:
	  xTaskCreate(vExpungersTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	case baby:
	  xTaskCreate(vBabiesTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	case kitty:
	  xTaskCreate(vKittiesTask, pW->taskText, 256, (void * ) this_game,
		      &(pW->task), GO_TASK_PRIORITY);
	}
      taskEXIT_CRITICAL();
      return pW;
    }
} // end function

/*
 *
 * function called by vImpactsTask() to impose specific collision-type or
 * limit-induced interactions
 *	- the subject, pointed to by pSub, is checked (one subject only, not
 *		GO list)
 *	- if objInt is set to Other, we simply check whether the pSub
 *		is located at an extreme location, which requires that pSub
 *		terminate (as in the case of a missile or a bomb reaching the
 *		end of its path)
 *	- otherwise, (if objInt is player, alien, kitty or baby) then we
 *		check for collisions between subject and an object of kind
 *		objInt; if a collision has been registered, the subject's health
 *		is affected, and/or the subject is terminated (for example, if
 *		the subject is the player, and the object kind is pooh, then if
 *		a collision is detected, the player's health is reduced and/or
 *		the player is terminated, i.e., alive state is set to False)
 *		- it is presumed that objInt is either a pooh or an expunger
 *
 */
static void
prvImposeConstraints (go_t *pSub, gotype_t objInt)
{
  /* check for an interaction with an object of GO type objInt */
  go_t *pW = pSub;
  gotype_t subInt = pW->kind; // subject's kind
  go_list_t *pWi = pW->interactions;
  uint16_t health;
  /* perform checks by subject kind */
  switch (subInt)
    {
    case pooh: // look for pooh/bomb reaching the ground
      if (pW->pos.Y <= YBOTTOM)
	{
	  pW->alive = False; // terminate pooh
	}
    case expunger: // look for expunger hitting the ceiling
      if (pW->pos.Y >= YTOP)
	{
	  pW->alive = False; // terminate expunger
	}
    default: // player, alien, baby, kitty, being struck with a projectile
      while (pWi != NULL)
	{
	  if (pWi->kind == objInt)
	    {
	      // check for a collision
	      if (pWi->collision)
		{
		  pW->crouch_or_extra == True; // GO reacts to being struck
		  if ((pW->health -= 256) <= 0) // health reduces
		    {
		      pW->health = 0;
		      pW->alive = False;
		    }
		}
	    }
	  pWi = pWi->pNext; // chk all potentially interacting projectiles
	} // while
    } // switch
} // function

/*
 *
 * function updates the games screen, sending updated info for each character
 *
 */
static void
prvUpdateScreen (game_t *this_game)
{
  /*
   * go_t *player;
   * go_t *aliens;
   * go_t *poohs;
   * go_t *expungers;
   * go_t *babies;
   * go_t *kitties;
   */

  go_t *pW; // working pointer

  pW = this_game->player;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }

  pW = this_game->aliens;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }

  pW = this_game->poohs;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }

  pW = this_game->expungers;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }

  pW = this_game->babies;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }

  pW = this_game->kitties;
  while (pW != NULL)
    {
      sendUARTGraphic (pW);
      pW = pW->pNext;
    }
} // function

/*
 *
 * function determines player GO animation state, based on user input, and
 * elapsed time
 * every GO must have a STOP state, used as a default initial state of being
 * STOP, FIRE, CROUCH, R0, R1, R2, L0, L1, L2, // basic animation states, player
 * U0, D0, // additional states needed by aliens who move (U)p and (D)own
 * SELFCLEAN0, SELFCLEAN1, SELFCLEAN2, SELFCLEAN3 // states just for kitties
 *
 */
superstateGO_t
vPlayerStateMachine (superstateGO_t current_state)
{
  superstateGO_t next_state;

  switch (current_state)
    {
    case R0:
      next_state = R1;
    case R1:
      next_state = R2;
    case R2:
      if (user_input.left_button)
	{
	  next_state = STOP;
	}
      else
	{
	  next_state = R0;
	}
    case L0:
       next_state = L1;
    case L1:
       next_state = L2;
    case L2:
      if (user_input.right_button)
	{
	  next_state = STOP;
	}
      else
	{
	  next_state = L0;
	}
    case STOP:
      if (user_input.right_button)
	{
	  next_state = R0;
	}
      else if (user_input.left_button)
	{
	  next_state = L0;
	}
      else if (user_input.fire_button)
	{
	  next_state = FIRE;
	}
      else if (user_input.crouch_button)
	{
	  next_state = CROUCH;
	}
    case CROUCH:
      if (user_input.fire_button || user_input.left_button
	  || user_input.right_button)
	{
	  next_state = STOP;
	}
    case FIRE:
      if (user_input.crouch_button || user_input.left_button
	  || user_input.right_button)
	{
	  next_state = STOP;
	}
    default:
    }
  vTaskDelay (MOVE_TICKS);
  return next_state;
}

/*
 *
 * function determines alien GO animation state, based on user input, and
 * elapsed time
 *
 * every GO must have a STOP state, used as a default initial state of being
 * STOP, FIRE, CROUCH, R0, R1, R2, L0, L1, L2, // basic animation states, player
 * U0, D0, // additional states needed by aliens who move (U)p and (D)own
 * SELFCLEAN0, SELFCLEAN1, SELFCLEAN2, SELFCLEAN3 // states just for kitties
 *
 *
 *
 *
 */
superstateGO_t
vAlienStateMachine (superstateGO_t current_state, go_coord_t vel)
{
  superstateGO_t next_state;

  // determine direction of velocity
  bool_t moving_up = sgn_bool((void *) &vel.Y);
  bool_t moving_right = sgn_bool((void *) &vel.X);

  switch (current_state)
    {
    case STOP:
      if (moving_right)
	next_state = R0;
      else if (!moving_right)
	next_state = L0;
    case R0:
      if (!moving_right)
	next_state = STOP;
    case L0:
      if (moving_right)
	next_state = STOP;
    }
  vTaskDelay (MOVE_TICKS);
  return next_state;
}


/*
 *
 * function determines alien GO animation state, based on user input, and
 * elapsed time
 *
 * every GO must have a STOP state, used as a default initial state of being
 * STOP, FIRE, CROUCH, R0, R1, R2, L0, L1, L2, // basic animation states, player
 * U0, D0, // additional states needed by aliens who move (U)p and (D)own
 * SELFCLEAN0, SELFCLEAN1, SELFCLEAN2, SELFCLEAN3 // states just for kitties
 *
 *
 *
 *
 */
superstateGO_t
vAlienStateMachine (superstateGO_t current_state, go_coord_t vel)
{
  superstateGO_t next_state;

  // determine direction of velocity
  bool_t moving_up = sgn_bool(vel.Y);
  bool_t moving_right = sgn_bool(vel.X);

  switch (current_state)
    {
    case STOP:
      if (moving_right)
	next_state = R0;
      else if (!moving_right)
	next_state = L0;
    case R0:
      if (!moving_right)
	next_state = STOP;
    case L0:
      if (moving_right)
	next_state = STOP;
    }
  vTaskDelay (MOVE_TICKS);
  return next_state;
}


/****************************************************************************
 *
 *
 * PUBLIC FUNCTIONS
 *
 *
 ****************************************************************************/

void
vPlayerTask (void *pvParams)
{
  game_t 	*this_game = (game_t *) pvParams;
  playerstate_t xP = *((playerstate_t *) this_game->player->go_state);

  if ()
    {

    }

  // check for extermination

  // update state

} // end function
/*
 *
 * Impacts Task --- the task behind all the game action!
 *
 */
void
vImpactsTask (void *pvParams)
{
  game_t *this_game = (game_t *) pvParams;
  uint32_t GOIDcode;

  /*
   * to begin with, spawn off an alien and two babies...
   */
  if (prvGetGOIDCode (this_game->aliensID, &GOIDcode))
    {
      go_coord_t alien_start_posn =
	{ XMIDDLE, YMIDDLE };
      go_t *pAlien = spawnGONodeandTask (this_game, this_game->aliens, alien,
					 alien_start_posn, this_game->aliensID,
					 GOIDcode);
      pAlien->numlives = 1;
      pAlien->health = 1024;
    }
  if (prvGetGOIDCode (this_game->babiesID, &GOIDcode))
    {
      go_coord_t baby_start_posn_LEFT =
	{ XLEFT, YBOTTOM };
      go_t *pBaby = spawnGONodeandTask (this_game, this_game->babies, baby,
					baby_start_posn_LEFT,
					this_game->babiesID, GOIDcode);
      pBaby->numlives = 1;
      pBaby->health = 128;
    }
  if (prvGetGOIDCode (this_game->babiesID, &GOIDcode))
    {
      go_coord_t baby_start_posn_MID =
	{ XMIDDLE, YBOTTOM };
      go_t *pBaby = spawnGONodeandTask (this_game, this_game->babies, baby,
					baby_start_posn_MID,
					this_game->babiesID, GOIDcode);
      pBaby->numlives = 1;
      pBaby->health = 128;
    }

  /* main loop of Impacts Task */
  uint8_t levelLambda = 0U;

  while (1)
    {
      /*
       * simple way to set the game level:
       * 	level = log2(2*LEVEL_UP_X) = 1 + log2(LEVEL_UP_X)
       */
      levelLambda = this_game->score / (2 * LEVEL_UP_X);
      this_game->game_level = 1 << levelLambda;

      /*
       * is it time to spawn an alien? number of aliens
       * should be (game_level + 1)
       */
      if (this_game->number_of_aliens < (this_game->game_level + 1))
	{
	  /* a high probability exists of an alien being created */
	  if (prvYesHappens (QuiteLikely))
	    {
	      if (prvGetGOIDCode (aliensID, &GOIDcode)) /* is there room for
	       another alien */
		{
		  /* spawn an alien */
		  go_coord_t alien_start_posn =
		    { XMIDDLE, YMIDDLE };
		  go_t *pAlien = spawnGONodeandTask (this_game,
						     this_game->aliens, alien,
						     alien_start_posn,
						     this_game->aliensID,
						     GOIDcode);
		  pAlien->numlives = 1;
		  pAlien->health = 1024;
		}
	    }
	}

      /*
       * is it time to spawn a kitty? The number of kitties should be
       * (game_level)
       */
      if (this_game->number_of_kitties < (this_game->game_level))
	{
	  /* a some probability exists of a kitty showing up,
	   * in which case the alien's pooh may start dropping */
	  if (prvYesHappens (Maybe))
	    {
	      if (prvGetGOIDCode (kittiesID, &GOIDcode)) // kitties available?
		{
		  /* spawn a kitty */
		  go_coord_t kitties_start_posn =
		    { XRIGHT, YBOTTOM };
		  go_t *pKitty = spawnGONodeandTask (this_game,
						     this_game->kitties, kitty,
						     kitties_start_posn,
						     this_game->kittiesID,
						     GOIDcode);
		  pKitty->numlives = 9;
		  pKitty->health = 8192;
		}
	    }
	}

      /*
       *
       * UPDATE THE INTERACTION LISTS
       *
       */
      /* check alien proximity to kitties and expungers */
      pW = this_game->aliens;
      while (pW != NULL)
	{
	  prvComputeProximities (pW, this_game->expungers);
	  prvComputeProximities (pW, this_game->kitties);
	  pW = pW->pNext;
	}
      /* check player proximity to poohs, kitties or babies */
      pW = this_game->player;
      while (pW != NULL)
	{
	  prvComputeProximities (pW, this_game->poohs);
	  prvComputeProximities (pW, this_game->kitties);
	  prvComputeProximities (pW, this_game->babies);
	  pW = pW->pNext;
	}
      /* check babies for proximity to poohs */
      pW = this_game->babies;
      while (pW != NULL)
	{
	  prvComputeProximities (pW, this_game->poohs);
	  pW = pW->pNext;
	}

      /*
       *
       * IMPOSE COLLISION/LIMIT INTERACTIONS (characters have no say here!)
       *
       * 	- players:
       * 		- killed from contact with poohs
       * 	- aliens:
       * 		- die from enough expunger strikes
       * 	- babies:
       * 		- vapourized from contact with poohs
       * 	- kitties:
       * 		- essentially impervious, but have negative health
       * 		effects from pooh contact
       * 	- poohs:
       * 		- hit the ground
       * 	- expungers:
       * 		- reach the ceiling
       *
       */

      /* impose pooh strikes on player(s) */
      pW = this_game->player;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, pooh);
	  pW = pW->pNext;
	}
      /* impose expunger strikes on aliens */
      pW = this_game->aliens;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, expunger);
	  pW = pW->pNext;
	}
      /* impose pooh strikes on babies */
      pW = this_game->babies;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, pooh);
	  pW = pW->pNext;
	}
      /* impose pooh strikes on kitties */
      pW = this_game->kitties;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, pooh);
	  pW = pW->pNext;
	}
      /* check if pooh has hit the ground */
      pW = this_game->poohs;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, other);
	  pW = pW->pNext;
	}
      /* check if expunger has reached the ceiling */
      pW = this_game->expungers;
      while (pW != NULL)
	{
	  prvImposeConstraints (pW, other);
	  pW = pW->pNext;
	}
      /*
       * SEND INFORMATION TO UPDATE SCREEN
       */
      prvUpdateScreen (this_game);
    } // while (1)
} // end function

/*
 *
 * High-level supervisory task for each game (one game for each human player)
 *
 */
void
vRunGameTask (void *pvParams)
{
  /* variables */
  size_t player = *((size_t *) pvParams); // the human player
  go_t *pW = NULL;
  xTaskHandle pvImpactsTaskHandle;

  /* this entire game is stored in the following local variable: */
  game_t *this_game = (game_t *) pvPortMalloc (sizeof(game_t));

  /* set some of this game's parameters, just to get us started */
  this_game->score = 0;
  for (size_t i = 0; i != 3; ++i)
    this_game->playerID[i] = 'A';
  this_game->playerID[3] = '\0';
  this_game->level = 1;
  /* initialize GO lists */
  this_game->aliens = NULL;
  this_game->poohs = NULL;
  this_game->expungers = NULL;
  this_game->babies = NULL;
  this_game->kitties = NULL;
  this_game->player = NULL;
  /* initialize code books and record-keeping variables */
  prvInitGame (this_game);

  /* give birth to the player GO for this game (recall that one game is
   * allocated per player) */
  go_coord_t player_start_posn =
    { XMIDDLE, YBOTTOM };
  this_game->player = spawnGONodeandTask (this_game, this_game->player, 0,
					  player_start_posn, NULL, 0x00000001);

  while (1)
    {
      xSemaphoreTake (xGameMutex, portMAX_DELAY);
      go_t *pWplayer = this_game->player; // point to this game's player
      if (pWplayer->active)
	{
	  prvResetBoard ();
	  prvUARTSend ("D: Player %zu", player); // prompt the player
	  vTaskDelay (5 * configTICK_RATE_HZ); // wait 5 seconds

	  /*
	   * create ImpactsTask (with lower priority than RunGameTask())
	   * to run the show
	   */
	  xTaskCreate(vImpactsTask, "Impact-checking Task", 1024,
		      (void * ) &this_game, &pvImpactsTaskHandle,
		      IMPACTS_TASK_PRIORITY);

	  /* keep running until player loses life */
	  while ((pWplayer->alive))
	    {
	      vTaskDelay (DELAY_RUN_GAME); // relinquish control of game
	    }
	  /* player died, update status */
	  if ((--(pWplayer->numlives)) == 0)
	    {
	      pWplayer->gameover = True;
	      vTaskDelete (pvImpactsTaskHandle);
	      prvDeleteAllTasks (this_game);
	      /* inform player */
	      prvUARTSend ("C:clc\n");
	      prvSayGoodbye (pWplayer->ID); /* say goodbye to player,
	       get their initials */
	      vTaskDelay (configTICK_RATE_HZ * 5); /* wait 5 seconds */
	    }
	}
      xSemaphoreGive (xGameMutex);
    } /* end while (1) */
} // end function
