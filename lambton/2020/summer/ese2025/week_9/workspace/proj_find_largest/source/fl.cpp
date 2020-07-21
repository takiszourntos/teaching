/*
 * fl.cpp
 *
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

/*
 * main code begins
 */
int main()
{
	/* store integers in a vector from standard input */
	vector<int> myarr;	// our container
	int token; 			// our container content variable
	cout << "Please enter some integers, followed by <CTRL><D>:" << endl;
	while (cin >> token) // loop exits when user enters <CTRL><D>
	{
		myarr.push_back(token);
	}
	cout << endl << endl;

	/* print integers from vector */
	cout << "Your integers are:" << endl;
	for (vector<int>::size_type j = 0; j != myarr.size(); ++j)
	{
		cout << myarr[j] << endl;
	}
	cout << endl;

	/* find the largest element, manually */
	int max = myarr[0];
	int next;
	vector<int>::size_type i = 1;
	while (i != myarr.size())
	{
		next = myarr[i];
		if (max < next)
		{
			max = next;
		}
		++i;
	}
	cout << endl << "... and your largest integer is: " << max << endl << endl;

	/* exit happily */
	return 0;
}
