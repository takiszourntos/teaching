//============================================================================
// Name        : proj_class_expt_templ.cpp
// Author      : takis
// Version     :
// Copyright   : copyright (C) 2020 emad studio inc.
// Description : code to experiment with templated classes
//============================================================================

#include <iostream>
#include "proj_classes.h"	// main templated class
#include "students.h"		// Student class
//#include "toys.h"			// Toys class

using namespace std;
// only use "using namespace" in your main code file

int main()
{
	// declare a student-database object, load from standard input
	DB<Student> myStudentDB;

	// experiment with adding and deleting object from database

	// your code goes here

	// print out the data
	myStudentDB.display();

	// exit
	cout << endl << myStudentDB.numelements() << " processed." << endl;
	return 0;
}
