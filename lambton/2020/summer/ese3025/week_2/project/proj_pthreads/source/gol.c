/*
 * gol.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include "gol_config.h"
#include "cells.h"
#include "display.h"

/*
 * global variables
 */
const size_t n = config_NC;
const size_t m = config_MC;
const size_t N = config_NE;
const size_t M = config_ME;

cell_t env[config_NE][config_ME];
cell_t update_env[config_NE][config_ME];
bool reproduction_flag = false; // is high when it's mating season

/*
 * main code
 */
int main(void)
{
	pthread_t threadptrs[config_K * config_L]; // our thread handles
	threadID_t threadID[config_K * config_L]; // thread ID

	// initialize workspace
	initEnvironment();

	// initialize display
	initDisplay();

	// create the threads, returns 0 on the successful creation of each thread
	size_t index;
	for (size_t i = 0; i != config_K; ++i)
	{
		for (size_t j = 0; j != config_L; ++j)
		{
			index = i*config_K + j; // map (i,j) to an 1-d index
			threadID[index];
			threadID[index].row = i;
			threadID[index].col = j;
			if (pthread_create(&threadptrs[index], NULL, &updateCellFunc, &threadID[index]) != 0)
			{
				printf("failed to create the thread %d\n", i * j);
				return 1;
			}
		}
	}

	unsigned short int ctr=0;
	while (1)
	{
		udelay(config_TL / 2);
		reproduction_flag=true;
		udelay(config_TL / 2);
		reproduction_flag=false;
		if (++ctr==config_TDISP)
		{
			ctr=0;
			updateDisplay();
		}
	}

	// should never arrive here;
	return 1;
}
