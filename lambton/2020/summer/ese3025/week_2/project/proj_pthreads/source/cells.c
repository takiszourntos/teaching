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
void transferCommunity(size_t iT, size_t jT, const cell_t data_init[][config_MC])
{
	size_t i_0 = iT * config_NC;
	size_t j_0 = jT * config_MC;

	// copy this community to each community in env to initialize it
	for (size_t i = 0; i != config_NC; ++i)
	{
		for (size_t j = 0; j != config_MC; ++j)
		{
			env[i_0+i][j_0+j] = update_env[i_0+i][j_0+j] = data_init[i][j];
		}
	}
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

void* updateCellFunc(void *param)
{
	size_t index = *((size_t*) param);
}
