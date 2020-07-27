//============================================================================
// Name        : proj_streams_calling.cpp
// Author      : Akistay Ourntosay
// Version     :
// Copyright   : Copyright (C) 2020 DoofisDoodis Software
// Description : calling a more complex streams
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// type declaration
struct person_struct
{
	string name;
	unsigned int age;
	float salary;
};
typedef struct person_struct person_t;

// function declaration
istream& read(istream &is, person_t &rec)
{
	is >> rec.name >> rec.age >> rec.salary;
	return is;
}

bool people_sorter(person_t i, person_t j)
{
	if (i.salary > j.salary)
		return true;
	else
		return false;
}
// main code
int main()
{
	cout << "Please enter your peeps (name, age, salary)" << endl;
	cout << "and press <CTRL><D> when you are done:" << endl;
	vector<person_t> people;
	person_t individual;
	while (read(cin, individual))
	{
		people.push_back(individual);
	}

	sort(people.begin(), people.end(), people_sorter);

	cout << endl << "Here are your people, sorted:" << endl;
	for (vector<person_t>::size_type ii=0; ii != people.size(); ++ii)
	{
		cout << people[ii].name << "\t" << people[ii].age << "\t" << people[ii].salary << endl;
	}


	return 0;
}
