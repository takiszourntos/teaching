//============================================================================
// Name        : proj_trycatch_demo.cpp
// Author      : Akistay Ourntosay
// Version     :
// Copyright   : Copyright (C) 2020 DoofisDoodis Software
// Description : smarmy try/catch demo in C++
//============================================================================

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

int main()
{
	vector<int> data;

	int token;
	cout << "Please enter some integers: " << endl;
	while (cin >> token)
	{
		data.push_back(token);
	}

	for (vector<int>::size_type ii = 0; ii != data.size() + 3; ++ii)
	{
		try
		{
			if (ii < data.size())
			{
				int myint;
				myint = data[ii];
				cout << myint << endl;
			}
			else
			{
				throw out_of_range("out of fricken range"); // throw an out_of_range error
			}
		}
		catch (out_of_range t)
		{
			cout << "say " << t.what() << "!!!" << endl;
		}

	}
	cout << "Foresooth! what sayeth ye!!" << endl; // prints Foresooth! What sayeth ye!!
	return 0;
}
