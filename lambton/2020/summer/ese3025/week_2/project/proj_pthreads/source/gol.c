/*
 * gol.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
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

	// create the threads
	size_t index;
	for (size_t i = 0; i != config_K; ++i)
	{
		for (size_t j = 0; j != config_L; ++j)
		{
			index = i * config_K + j; // map (i,j) to an 1-d index
			threadID[index].row = i;
			threadID[index].col = j;
			// the following if condition returns 0 on the successful creation of each thread:
			if (pthread_create(&threadptrs[index], NULL, &updateCommFunc,
					&threadID[index]) != 0)
			{
				printf("failed to create the thread %d\n", (int) index);
				return 1;
			}
		}
	}

	// initialize display with ncurses
	initDisplay();

	unsigned short int ctr = 0;
	while (1)
	{
		reproduction_flag = true;
		usleep(config_TL / 2); // allow new generation to check in
		reproduction_flag = false;
		usleep(config_TL / 2); // put a hold on reproduction to update display
		if (++ctr == config_TDISP)
		{
			ctr = 0;
			updateDisplay();
		}
		copyEnvironment(); // write changes to the environment, env, from update_env
	}

	// should never arrive here;
	return 1;
}
