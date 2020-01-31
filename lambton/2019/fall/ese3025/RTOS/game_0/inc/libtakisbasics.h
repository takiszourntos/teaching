/*
 * libtakisbasics.h
 *
 *  Created on: Jan. 31, 2020
 *      Author: takis
 */

#ifndef LIBTAKISBASICS_H_
#define LIBTAKISBASICS_H_

#include <stdlib.h>

enum boolean
{
  False = 0U, True = 1U
} boolean_enum;
typedef enum boolean bool_t;

/*
 *
 * signum function
 * 	integer-argument version
 *
 */
int
sgn (const void *parg)
{
  int arg = *((int *) parg);
  int ret = 0;

  if (arg > 0)
    ret = 1;
  else if (arg < 0)
    ret = -1;

  return ret;
}

/*
 *
 * signum function
 * 	integer-argument and boolean-result version
 *
 */
bool_t
sgn_bool (const void *parg)
{
  int arg = *((int *) parg);
  bool_t ret = False;

  if (arg > 0)
    ret = True;

  return ret;
}

#endif /* LIBTAKISBASICS_H_ */
