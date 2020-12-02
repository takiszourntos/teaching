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
Student::Student() : last_record(false){}

// Student::end() method
bool Student::end()
{
	if (Student::data.ID == END_MARKER)
	{
		Student::last_record = true;
		return true;
	}
	return false;
}

// Student::get() method
int Student::get(void)
{
	long Nc;

	// get the student ID number (NOTE: this is not the same as the "key" information)
	std::cin >> Student::data.ID;

	// get the last name
	std::cin >> Student::data.last_name;

	// get the first name
	std::cin >> Student::data.first_name;

	// get the student courses
	std::cin >> Student::data.num_courses;
	Nc = Student::data.num_courses;

	// get the course names and the grades
	std::string course_name;
	for (long j=0; j!= Nc; ++j)
	{
		std::cin >> course_name;
		Student::data.courses.push_back(course_name);
	}
	double grade;
	for (long j=0; j!= Nc; ++j)
	{
		std::cin >> grade;
		Student::data.grades.push_back(grade);
	}

	// generate a unique key
	Student::data.key = Student::keygen(Student::data.ID, Student::data.last_name);

	return 0; // in the future, can add error checking
}


