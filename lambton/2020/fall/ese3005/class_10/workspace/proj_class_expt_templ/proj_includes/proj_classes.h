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

template<class T> class DB
{
public:
	DB(void);
	std::size_t numelements() const;
	int add(const T&); // adds an element referenced in the argument
	int del(const std::string&); // deletes an element specified by key argument
	void display() const;


private:
	std::size_t DBi; // number of database elements
	std::map<std::string, T> DBmap; // our associative container
};

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
	T temp;
	auto c_iter = DBmap.begin();
	while (c_iter != DBmap.end())
	{
		temp = c_iter->second;
		temp.put();
		++c_iter;
	}
}


#endif /* PROJ_CLASSES_H_ */
