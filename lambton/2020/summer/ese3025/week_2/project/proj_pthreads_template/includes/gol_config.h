/*
 * gol_config.h
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#ifndef GOL_CONFIG_H_
#define GOL_CONFIG_H_

#include <stdlib.h>

/*
 * "community of cells" (handled by one thread) parameters
 */
#define config_NC		32 // # of cell rows in a community
#define config_MC		16 // # of cell columns in a community

/*
 * overall environment parameters
 */
#define config_K		1 // # of communities "down"
#define config_L		4 // # of communities "across"
#define config_NE 		config_K*config_NC // number of environment rows
#define config_ME 		config_L*config_MC // number of environment columns

/*
 * temporal parameters
 */
#define config_TL		1048576 // microseconds between generation
#define	config_TDISP	1 // number of generations between plots

/*
 * basic cell type
 */
enum cell_enum
{
	dead = 0U, live = 1U
};
typedef enum cell_enum cell_t;

/*
 * thread identifier (in units of community BLOCKS not cells!)
 */
struct threadID_struct
{
	size_t row;
	size_t col;
};
typedef struct threadID_struct threadID_t;

/*
 * a neighbour type for cells... here, X represents the cell:
 *
 *    			a b c
 *              d X e
 *              f g h
 *
 */
enum neighbour_enum
{
	a_posn=0U,
	b_posn,
	c_posn,
	d_posn,
	e_posn,
	f_posn,
	g_posn,
	h_posn
};
typedef enum neighbour_enum neighbour_t;


#endif /* GOL_CONFIG_H_ */
