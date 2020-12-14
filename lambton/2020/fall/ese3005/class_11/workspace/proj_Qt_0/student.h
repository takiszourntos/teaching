/*
 * students.h
 *
 *  Created on: Dec. 2, 2020
 *      Author: takis
 */

#ifndef STUDENT_H
#define STUDENT_H

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

/*
 * this defines a Student object
 */
class Student
{
public:
    Student(void); // constructor
    // data on the student
    record_t data;
    int get(); // get the data from standard input and keygen();
    void put() const; // send the record to standard output;
    bool end(); // checks if record if student record is the last one, updates last_record

private:
    std::string keygen(std::string, std::string);
};


#endif // STUDENT_H
