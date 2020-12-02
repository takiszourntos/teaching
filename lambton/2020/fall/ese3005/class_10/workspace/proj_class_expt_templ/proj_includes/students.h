/*
 * students.h
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#ifndef STUDENTS_H_
#define STUDENTS_H_

#define END_MARKER "-9999"

//#include <iostream>
#include <string>
#include <vector>

typedef struct
{
	std::string key; // primary key/ID; unique and must be included
	std::string ID;
	std::string last_name;
	std::string first_name;
	long num_courses;
	std::vector<std::string> courses;
	std::vector<double> grades;
} record_t;


class Student
{
public:
	// data on the student
	record_t data;
	int get(); // get the data from standard input and keygen();
	bool last_record;
	Student();

private:
	bool end(); // checks if record if student record is the last one, updates last_record
	std::string keygen(std::string, std::string);
};

#endif /* STUDENTS_H_ */
