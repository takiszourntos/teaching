/*
 * main.cpp
 *
 *  Created on: Aug. 10, 2020
 *
 *  mutex example
 *
 *  	author: T. Zourntos
 *      some inspiration/lines from source: http://www.cpp.re/reference/mutex/mutex/
 *
 *      NB: to build, you should indicate the "pthread" library for your C++ linker
 */

// thread example
#include <iostream>		// std::cout
#include <thread>		// std::thread
#include <chrono>		// std::chrono
#include <mutex>        // std::mutex

std::mutex mtx;           // mutex for critical section

void thread_function(std::string text)
{
	while (1)
	{
		mtx.lock(); // thread takes mutex, gaining exclusive access to stdout

		for (std::string::size_type i = 0; i != text.size(); ++i)
		{
			std::cout << text[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		mtx.unlock(); // release mutex to allow other threads to access stdout
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // wait to be fair
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
