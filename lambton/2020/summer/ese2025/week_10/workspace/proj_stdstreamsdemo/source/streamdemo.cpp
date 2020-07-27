/*
 * from Introduction to Design Patterns in C++ with QT
 * by Alan & Paul Ezust
 *
 * slightly modified by Takis Z. 07/27/2020
 *
 * program shows various manipulators for streams, including
 * 	std::oct, std::hex, std::dec, std::showpos, std::showpoint, std::scientific, std::fixed, etc.
 *
 */

#include <iostream>

using namespace std;

int main()
{
	int num1(1234), num2(2345); // C++ style initialization using ()
	cout << oct << num2 << '\t' << hex << num2 << '\t' << dec << num2 << endl;
	cout << (num1 < num2) << endl;
	cout << boolalpha << (num1 < num2) << endl;
	double dub(1357); // C++ style initialization using ()
	cout << dub << '\t' << showpos << dub << '\t' << showpoint << dub << endl;
	dub = 1234.5678;
	cout << dub << '\t' << fixed << dub << '\t' << scientific << dub << '\n'
			<< noshowpos << dub << endl;
}

