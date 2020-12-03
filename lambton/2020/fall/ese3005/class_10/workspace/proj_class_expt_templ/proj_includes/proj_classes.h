/*
 * proj_classes.h
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#ifndef PROJ_CLASSES_H_
#define PROJ_CLASSES_H_

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
	std::map<std::string, T> DBmap; //
};

#endif /* PROJ_CLASSES_H_ */
