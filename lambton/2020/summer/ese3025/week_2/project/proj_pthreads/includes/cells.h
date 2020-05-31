/*
 * cells.h
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#ifndef CELLS_H_
#define CELLS_H_

#include "gol_config.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>



/*
 * functions
 */
void initEnvironment(void);

void* updateCellFunc(void *);

#endif /* CELLS_H_ */
