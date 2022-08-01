//============================================================================
// Name        : chrono_sample.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	std::chrono::system_clock::time_point start, stop;
	start = std::chrono::system_clock::now();

	stop = std::chrono::system_clock::now();



	std::time_t tstamp = std::chrono::system_clock::to_time_t(start);
	std::cout << std::ctime(&tstamp);
	auto diff = stop - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	std::cout << msec << " msec." << endl;
	return 0;
}
