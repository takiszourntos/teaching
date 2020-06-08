/*
 * display.c
 *
 *  Created on: May 30, 2020
 *      author: takis
 *      note: a lot of this code adapted from the TDLP tutorial on ncurses,
 *      by Pradeep Padala
 */

#include "gol_config.h"
#include <unistd.h>
#include <ncurses.h>
#include "display.h"

/*
 * important variables, defined elsewhere
 */
extern cell_t env[config_NE][config_ME];
extern int STARTX;
extern int STARTY;
extern int ENDX;
extern int ENDY;
extern WINDOW *win;

/*
 * PRIVATE FUNCTIONS
 */
void create_newwin(int height, int width)
{
	win = newwin(height, width, STARTY, STARTX);
	box(win, 0, 0); /* 0, 0 gives default characters
	 * for the vertical and horizontal
	 * lines */
	wrefresh(win); /* show that box */

	return;
}

/*
 * PUBLIC FUNCTIONS
 */
void initDisplay(void)
{
	printf("\ninitializing display...\n");
	usleep(2 * config_TL);
	initscr();
	cbreak();
	timeout(TIME_OUT);
	keypad(stdscr, TRUE);
	create_newwin(config_NE, config_ME);
}

void updateDisplay(void)
{
//	ENDX = COLS - 1;
//	ENDY = LINES - 1;

	int i, j;
	wclear(win);
	for (i = STARTX; i != config_NE; ++i)
		for (j = STARTY; j != config_ME; ++j)
			if (env[i][j] == live)
				mvwaddch(win, j, i, CELL_CHAR);
	wrefresh(win);
}

/*
 ******************************************************************************************** reference
 */

