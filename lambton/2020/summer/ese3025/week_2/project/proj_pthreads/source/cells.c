/*
 * cells.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol_config.h"
#include "cells.h"

/*
 * declare important variables (defined in main file as global variables)
 */
extern cell_t **env;
extern cell_t **update_env;

/*
 * PRIVATE FUNCTIONS
 */

/*
 * transfer a single community identified by the pair (iT,jT) to env and
 * update_env using data_init[][]
 */
void transferCommunity(size_t iT, size_t jT,
		const cell_t data_init[][config_MC])
{
	size_t i_0 = iT * config_NC;
	size_t j_0 = jT * config_MC;

	// copy this community to each community in env to initialize it
	for (size_t i = 0; i != config_NC; ++i)
	{
		for (size_t j = 0; j != config_MC; ++j)
		{
			env[i_0 + i][j_0 + j] = update_env[i_0 + i][j_0 + j] =
					data_init[i][j];
		}
	}
}

/*
 * function counts the number of live neighbours of a cell located
 * at row r and column c of the env array
 *
 * for reference, neighbours are designated as follows:
 *     			a b c
 *              d X e
 *              f g h
 *
 *
 */
size_t countLiveNeighbours(void row, void col)
{
	size_t cell_count = 0;

	// because we may have negative results, we need to switch to long (opposed to size_t)
	long s, t; // position parameters for referencing neighbour cells
	long r = (long) row;
	long c = (long) col;

	for (neighbour_t i = a_posn; i <= h_posn; ++i)
	{
		// your code goes here
	}

	// wrap around if needed
	if (s < 0)
		s = config_NE - 1;
	else if (s == NE)
		s = 0;

	if (t < 0)
		t = config_ME - 1;
	else if (t == ME)
		t = 0;

	// count the cell if it is living
	if (env[s][t] == live)
		++cell_count;
}

return cell_count;
}

/*
 * update cell located at row r and column c in env (indicated by X):
 *
 *  			a b c
 *              d X e
 *              f g h
 *
 * with nearest neighbours indicated as shown from a, b, ..., h.
 *
 */
void updateCell(size_t r, size_t c)
{
// your code goes here

return;
}

/*
 * PUBLIC FUNCTIONS
 */
/*
 * seed environment on a community-by-community basis,
 * from standard input; we assume that the seed input is exactly
 * the size of a community; 9999 indicates end of file;
 * run this before started ncurses environment;
 */
void initEnvironment(void)
{
// start by reading in a single community
int token;
cell_t datum;
cell_t community_init[config_NC][config_MC];
for (size_t i = 0; i != config_NC; ++i)
{
	for (size_t j = 0; j != config_MC; ++j)
	{
		scanf("%d", &token);
		datum = (cell_t) token;
		community_init[i][j] = datum;
	}
}

// copy this community to each community in env to initialize it
for (size_t i = 0; i != config_K; ++i)
{
	for (size_t j = 0; j != config_L; ++j)
	{
		transferCommunity(i, j, community_init);
	}
}
}

void copyEnvironment(void); // write changes to the environment, env, from update_env
{

}

/*
 * this function updates all the cells for a thread (corresponding to one community)
 */
void* updateCommFunc(void *param)
{
// identify the community corresponding to this thread
threadID_t index = *((threadID_t*) param);

// extract the row and column BLOCK position of community within the environment
const size_t thread_row = index.row;
const size_t thread_col = index.col;

// determine the row and column CELL offsets of the community with respect to the environment
size_t i_0 = thread_row * config_NC;
size_t j_0 = thread_col * config_MC;

// update each cell within the community
for (size_t i = 0; i != config_NC; ++i)
{
	for (size_t j = 0; j != config_MC; ++j)
	{
		updateCell(i_0 + i, j_0 + j); // write to update_env[][] based on data in env[][]
	}
}

}
