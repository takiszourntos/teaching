
#include <iostream>
#include <string>

int main()
{
	// request name
	std::cout << "please enter your name: ";

	// read the name
	std::string name; // define the name
	std::cin >> name; // read the name

	// write the greeting
	std::cout << "Hello, " << name << "! " << "Your name has " << name.size() << " characters." << std::endl;

	return 0;
}
