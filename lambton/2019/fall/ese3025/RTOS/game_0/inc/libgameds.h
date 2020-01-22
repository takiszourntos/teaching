/*
 * libgameds.h
 *
 *
 * Game Data Structures and Data Manipulation Library
 *
 *
 *
 *  Created on: Dec. 19, 2019
 *      Author: takis
 */

#ifndef LIBGAMEDS_H_
#define LIBGAMEDS_H_

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "libgameds.h"

#define	RUN_GAME_PRIORITY		3
#define IMPACTS_TASK_PRIORITY		2
#define GO_TASK_PRIORITY		1
#define	MAX_NUMBER_OF_PLAYERS		4
#define DELAY_RUN_GAME			65536
#define	DELAY_GAME_TICK			8192
#define THRESHOLD_COLLISION	 	16
#define THRESHOLD_SEEN			32
#define MAX_ALIENS			3
#define MAX_POOHS			9
#define	MAX_EXPUNGERS			3
#define MAX_BABIES			3
#define	MAX_KITTIES			2
#define	XLEFT				0
#define XMIDDLE				63
#define XRIGHT				127
#define	YTOP				0
#define	YMIDDLE				31
#define YBOTTOM				63
#define LEVELUP				8192
#define	MAX_GO_CODES			16
#define LEVEL_UP_X			256 // determines scale of leveling up

enum boolean
{
  False = 0U,
  True = 1U
} boolean_enum;
typedef enum boolean bool_t;

enum likelihood
{
  HighlyLikely = 0U,		// < RAND_MAX (probability \approx 1)
  QuiteLikely = 1U,		// < RAND_MAX / 2, prob. = 50 %
  ModeratelyLikely = 2U,	// < RAND_MAX / 4, prob. = 25 %
  Maybe = 3U,			// < RAND_MAX / 8, prob. = 12.5 %
  Unlikely = 4U,		// < RAND_MAX / 16, prob. = 6.25 %
  QuiteUnLikely = 5U, 		// < RAND_MAX / 32, prob. = 3.125 %
  YeahRight = 6U,		// < RAND_MAX / 64, prob. = 1.5625 %
} likelihood_enum;
typedef enum likelihood likely_t;

enum gotype
{
  player = 0U, alien = 1U, pooh = 2U, expunger = 3U, baby = 4U, kitty = 5U
};
typedef enum gotype gotype_t;

/* GO ID code book */
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
struct go_ID_struct
{
  uint32_t code;
  bool_t available;
};
typedef struct go_ID_struct go_ID_t;

/* user-input tracking */
struct ui_struct
{
  bool_t move_left;
  bool_t move_right;
  bool_t crouch;
  bool_t shoot;
};
typedef struct ui_struct ui_t;

/* coordinate type */
struct go_coord_struct
{
  int16_t X;
  int16_t Y;
};
typedef struct go_coord_struct go_coord_t;

/* game record-keeping for each player
 * (we assume one player per game, right?) */
struct game_struct
{
  uint32_t score;
  char playerID[4];
  uint16_t game_level;
  ui_t user;
  /* GO lists */
  go_t *player;
  go_t *aliens;
  go_t *poohs;
  go_t *expungers;
  go_t *babies;
  go_t *kitties;
  /* ID code books for various GO types, other than player */
  go_ID_t aliensID[16];
  go_ID_t poohsID[16];
  go_ID_t expungersID[16];
  go_ID_t babiesID[16];
  go_ID_t kittiesID[16];
  /* record keeping for number of each GO type, other than player */
  size_t number_of_aliens;
  size_t number_of_poohs;
  size_t number_of_expungers;
  size_t number_of_babies;
  size_t number_of_kitties;
};
typedef struct game_struct game_t;

/* (g)ame (o)bject record-keeping */
struct go_struct
{
  uint32_t ID;
  uint16_t go_level;
  uint16_t health;
  bool_t alive;
  bool_t active;
  bool_t on_screen;
  bool_t gameover;
  go_coord_t pos;
  go_coord_t vel;
  go_coord_t acc;
  bool_t move_left;
  bool_t move_right;
  bool_t crouch_or_extra;
  bool_t shoot_or_pooh;
  uint8_t numlives;
  go_list_t *interactions;
  xTaskHandle task;
  char taskText[32];
  struct go_struct *pNext;
  struct go_struct *pPrev;
};
typedef struct go_struct go_t;

struct go_list_struct
{
  uint32_t ID;
  uint16_t distance;
  bool_t seen;
  bool_t collision;
  struct go_list_struct *pNext;
  struct go_list_struct *pPrev;
};
typedef struct go_list_struct go_list_t;

/*
 * FUNCTION PROTOTYPES
 */

#endif /* LIBGAMEDS_H_ */
