/*
 * proj_classes.c
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#include <iostream>
#include <string>
#include <map>
#include "proj_classes.h"


// DB::constructor, default constructor, initializes storage
template <typename T>
DB<T>::DB() :
			DBi(0)
{
		T record;
		while (!record.last_record)
		{
			record.get(); // retrieve a single record from standard input
			DBmap[record.key] = record;
			++DBi;
		}
}


// DB::numelements()
template <typename T>
long DB<T>::numelements() const
{
	return DBi;
}

// DB::add() method
template <typename T>
int& DB<T>::add(const T& token)
{
	std::string key = keygen(token); // find the key for this token
	DB::DBmap[key]=token; // add this element to the map

	// check if the element can be found
	if (DB::DBmap.find(key)->key == token.key)
		return 0;
	else
		return 1; // error: element not added to database
}
