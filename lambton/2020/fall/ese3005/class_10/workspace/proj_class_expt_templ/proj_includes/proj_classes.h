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

template<class Type> class DB
{
public:
	long numelements() const;
	int& add(const Type&); // adds an element referenced in the argument
	int& del(const std::string&); // deletes an element specified by key argument
	Type& high() const; // finds the high-scoring element
	Type& low() const; // finds the low-scoring element
	double& average() const; // finds average score of all elements
	void sortDB();
	DB();

private:
	long DBi; // number of database elements
	std::string keygen(const Type) const; // returns the primary key for this element, must be the "key" field
	std::map<std::string, Type> DBmap; //
};

#endif /* PROJ_CLASSES_H_ */
