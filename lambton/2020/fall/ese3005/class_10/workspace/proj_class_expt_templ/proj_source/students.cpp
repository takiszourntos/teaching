/*
 * students.cpp
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#include <iostream>
#include <string>
#include <vector>
#include "students.h"

// Student constructor, initializes the object
Student::Student(void)
{
}

// Student::end() method
bool Student::end()
{
	if (data.ID == END_MARKER)
	{
		return true;
	}
	return false;
}

// Student::get() method, populates the data record from standard input
int Student::get(void)
{
	long Nc; // stores the number of courses

	// get the student ID number (NOTE: this is not the same as the "key" information)
	std::cin >> data.ID;

	// get the last name
	std::cin >> data.last_name;

	// get the first name
	std::cin >> data.first_name;

	// get the student courses
	std::cin >> data.num_courses;
	Nc = data.num_courses;

	// get the course names and the grades
	std::string course_name;
	for (long j = 0; j != Nc; ++j)
	{
		std::cin >> course_name;
		Student::data.courses.push_back(course_name);
	}
	double grade;
	for (long j = 0; j != Nc; ++j)
	{
		std::cin >> grade;
		data.grades.push_back(grade);
	}

	// generate a unique key
	data.key = keygen(data.ID, data.last_name);

	return 0; // in the future, can add error checking
}

// Student::put() method, sends data contents to standard output
void Student::put(void) const
{
	long Nc = data.num_courses;

	// put key
	std::cout << "key: " << data.key << std::endl;

	// put the student ID number (NOTE: this is not the same as the "key" information)
	std::cout << "ID: " << data.ID << std::endl;

	// put the last name
	std::cout << "last name: " << data.last_name << std::endl;

	// put the first name
	std::cout << "first name: " << data.first_name << std::endl;

	// put  the student courses
	std::cout << "number of courses: " << Nc << std::endl;

	// put the course names and the grades
	std::string course_name;
	double grade;
	for (long j = 0; j != Nc; ++j)
	{
		course_name = data.courses[j];
		grade = data.grades[j];
		std::cout << "\t" << course_name << ":\t" << grade << std::endl;
	}

	// line spacing
	std::cout << std::endl << std::endl;
}

// Student::keygen() method
std::string Student::keygen(std::string A, std::string B)
{
	std::string ret = A + "_" + B;

	return ret;
}

