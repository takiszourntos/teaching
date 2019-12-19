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
#define IMPACTS_TASK_PRIORITY	2
#define GO_TASK_PRIORITY		1
#define DELAY_RUN_GAME			65536
#define	DELAY_GAME_TICK			8192
#define THRESHOLD_COLLISION	 	16
#define THRESHOLD_SEEN			32
#define MAX_ALIENS				3
#define MAX_POOHS				9
#define	MAX_EXPUNGERS			3
#define MAX_BABIES				3
#define	MAX_KITTIES				2


enum boolean {True, False} boolean_enum;
typedef enum boolean bool_t;


/* user-input tracking */
struct ui_struct
{
	bool_t	move_left;
	bool_t	move_right;
	bool_t 	crouch;
	bool_t	shoot;
};
typedef struct ui_struct ui_t;

/* game record-keeping */
struct game_struct
{
	uint32_t	score;
	char		playerID[4];
	uint16_t	game_level;
	ui_t		user;
	go_t		*aliens;
	go_t		*poohs;
	go_t		*expungers;
	go_t		*babies;
	go_t		*kitties;
	go_t		*players;
};
typedef	struct game_struct	game_t;

/* (g)ame (o)bject record-keeping */
struct go_struct
{
	size_t		ID;
	uint16_t	go_level;
	uint16_t	health;
	bool_t		alive;
	bool_t		on_screen;
	go_coord_t	pos;
	go_coord_t	vel;
	go_coord_t	acc;
	uint8_t		numlives;
	go_list_t	*interactions;
	xTaskHandle	task;
	char		taskText[32];
	struct		go_struct	*pNext;
	struct		go_struct	*pPrev;
};
typedef struct go_struct go_t;

struct go_list_struct
{
	size_t		ID;
	uint16_t	distance;
	bool_t		seen;
	bool_t		collision;
	struct	go_list_struct *pNext;
	struct	go_list_struct *pPrev;
};
typedef struct go_list_struct go_list_t;


#endif /* LIBGAMEDS_H_ */
