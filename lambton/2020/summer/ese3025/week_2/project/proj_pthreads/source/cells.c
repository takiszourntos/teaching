/*
 * cells.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */


#include "gol_config.h"
#include "cells.h"

/*
 * important variables
 */
extern cell_t env;
extern cell_t update_env;
extern reproduction_flag; // is high when it's mating season

void initEnvironment(void)
{

}


void* updateCellFunc(void *param)
{
	size_t index = *((size_t *) param);
}
