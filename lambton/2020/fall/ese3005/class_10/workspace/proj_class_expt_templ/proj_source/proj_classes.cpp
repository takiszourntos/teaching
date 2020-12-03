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
template<class T>
DB<T>::DB(void) :
		DBi(0)
{
	T record;
	record.get(); // retrieve a single record from standard input
	while (!record.last_record)
	{
		DBmap[record.key] = record;
		record.get(); // retrieve a single record from standard input
	}
	DBi = DBmap.size();
}

// DB::numelements()
template<class T>
std::size_t DB<T>::numelements() const
{
	return DBi;
}

// DB::add() method
template<class T>
int DB<T>::add(const T &token)
{
	std::string key = token.key; // find the key for this token
	DBmap[key] = token; // add this element to the map

	// check if the element can be found
	if (DBmap.find(key)->key == token.key)
		return 0;
	else
		return 1; // error: element not added to database
}

// DB::del() method
template<class T>
int DB<T>::del(const std::string &key)
{
	auto iter = DBmap.find(key); // auto infers variable type from initializer type
	if (iter != DBmap.end())
	{
		// element is found
		DBmap.erase(iter);
		return 0;
	}
	return 1; // error: element is not found
}

// DB::display() method
template<class T>
void DB<T>::display() const
{
	const auto iter = DBmap.begin();
	while (iter != DBmap.end())
	{
		iter->second.put();
		++iter;
	}
}

