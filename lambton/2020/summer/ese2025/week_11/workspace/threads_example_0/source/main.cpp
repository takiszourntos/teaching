/*
 * main.cpp
 *
 *  Created on: Aug. 10, 2020
 *
 *  Two threads created from one thread function
 *
 *      NB: to build, you should indicate the "pthread" library for your C++ linker
 *
 *
 *  author: T. Zourntos
 *
 */

// thread example
#include <iostream>		// std::cout
#include <thread>		// std::thread
#include <chrono>		// std::chrono

void thread_function(std::string text)
{
	while (1)
	{
		for (std::string::size_type i=0; i != text.size(); ++i)
		{
			std::cout << text[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

int main()
{
	// spawn new thread called foo
	std::thread foo(thread_function,
			"--------- I'm just a foo --------------\n");

	// spawn new thread called bar
	std::thread bar(thread_function,
			"********* I'm going to the bar ********\n");

	// detach threads to allow "safe" termination
	foo.detach();
	bar.detach();

	// send status message and wait
	std::cout << "threads main, foo and bar now execute concurrently...\n";
	std::this_thread::sleep_for(std::chrono::seconds(60));

	// end proceedings...
	std::cout << "done.\n";
	return 0;
}
