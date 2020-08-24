/*
 * proj.cpp
 *
 *  Created on: Aug. 24, 2020
 *      Author: takis
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>

/***************************************
 *
 * GLOBAL VARIABLES
 *
 ***************************************/
std::mutex m;				// mutex
std::condition_variable cv;	// condition variable
bool ready = false;			// ready flag (signals main() is ready)
bool processed = false;	// processed flag (signals sorter() has processed data)
std::vector<int> data;			// data

void sorter()
{
	std::unique_lock<std::mutex> lk(m);

	cv.wait(lk, []{return ready;}); 	// wait and release mutex

	// data is now updated by main(), sort our list (write code here)

	// print out the sorted numbers (write code here)

	processed = true;

	// release mutex, notify main
	lk.unlock();
	cv.notify_one();
}

int main(void)
{
	// get handle to thread
	std::thread sorter_handle(sorter);

	// send data to the worker thread
	{
		std::lock_guard<std::mutex> lk(m); // acquire the mutex
		// get data from the user, until <CTRL><D>
		int number;
		while (std::cin >> number)
		{
			data.push_back(number);
		}
		ready = true;
	}
	cv.notify_one(); // notify thread, release the mutex

	// wait for the sorter thread
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, []{return processed;});
	}

	// end
	sorter_handle.join();
	return 0; // exit
}
