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
#include <string>

using namespace std;
// only use "using namespace" in your main code file

void clrscr(void)
{
	cout << "\033[2J\033[1;1H";
}

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

	cout << "Hit <CTRL><D> to continue..." << endl;
	// clear out the input
	string dummyString;
	cin.clear();
	while (cin >> dummyString); // waits for <CTRL><D>

	// display menu
	string userInput="";
	while (userInput != "0")
	{
		clrscr();
		cout << "1. add element" << endl;
		cout << "2. delete element" << endl;
		cout << "3. display database" << endl;
		cout << "0. EXIT" << endl;

		cin >> userInput;

		if (userInput == "1")
		{
			myStudentDB.add();
		}
		else if (userInput == "2")
		{
			myStudentDB.del();
		}
		else if (userInput == "3")
		{
			myStudentDB.display();
		}
		cout << endl << "press <c> to continue" << endl;
		while (userInput != "c" || userInput != "C")
		{
			// just wait around
		}
	}
	return 0;
}
