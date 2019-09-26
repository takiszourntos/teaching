/*
 * fl.cpp
 *
 *  Created on: Sep. 26, 2019
 *      Author: takis
 */


#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/*
 * main code begins
 */
int main()
{
	/* store integers in a vector */
	vector<int> myarr;	// our container
	int fill=0; 			// our container content variable

	// invariant: fill is the integer to be stored
	while (fill != 10)
	{
		myarr.push_back(fill);
		++fill; // increment fill
	}

	/* print integers from vector */
	cout << "Your integers are:" << endl;
	for (vector<int>::size_type j=0; j != 10; ++j)
	{
		cout << myarr[j] << " ";
	}
	cout << endl;

	/* exit happily */
	return 0;
}
