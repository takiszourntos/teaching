/*
 * proj_classes.h
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#ifndef PROJ_CLASSES_H_
#define PROJ_CLASSES_H_

#include <iostream>
#include <string>
#include <map>

/***********************************************************
 * 			CLASS PROTOTYPE
 ***********************************************************/
template<class T> class DB
{
public: // this is the interface to the class
	DB(void); // constructor
	std::size_t numelements() const;
	int add(const T&); // adds an element referenced in the argument
	int del(const std::string&); // deletes an element specified by key argument
	void display() const; // displays all the records in the map

private: // these are needed by other methods of the class, but not needed externally
	std::size_t DBi; // number of database elements
	std::map<std::string, T> DBmap; // our associative container
};

/***********************************************************
 * 			CLASS SOURCE CODE
 ***********************************************************/

// DB::constructor, default constructor, initializes storage
template<class T>
DB<T>::DB(void) :
		DBi(0)
{
	T record;
	record.get(); // retrieve a single record from standard input
	while (!record.end())
	{
		DBmap[record.data.key] = record;
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
	// retrieve new element from standard input
	token.get();
	std::string key = token.key; // find the key for this token

	// add the new element to the database
	DBmap[key] = token; // add this element to the map

	// check if the element can be found
	if (DBmap.find(key)->key == token.key)
	{
		++DBi;
		return 0;
	}
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
		--DBi;
		return 0;
	}
	return 1; // error: element is not found
}

// DB::display() method
template<class T>
void DB<T>::display() const
{
	T temp;
	auto c_iter = DBmap.begin(); // instead of: std::map<std::string, T>::iterator c_iter
	while (c_iter != DBmap.end())
	{
		temp = c_iter->second; // c_iter->first corresponds to the key, c_iter->second corresponds to the value
		temp.put(); // writes the DBmap value to standard output
		++c_iter;
	}
}

#endif /* PROJ_CLASSES_H_ */
