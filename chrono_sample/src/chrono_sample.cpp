//============================================================================
// Name        : chrono_sample.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
	vector<long> array;

	std::chrono::system_clock::time_point start, stop;
	start = std::chrono::system_clock::now();

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	for(long i = 0; i < 10000; ++i)
		for(long j = i; j < 10000; ++j)
			array.push_back(j);

	long sum = 0;
	for(long i = 0; i < array.size(); ++i)
		sum += array[i];
	cout << "sum = " << sum << endl;

	stop = std::chrono::system_clock::now();



	std::time_t tstamp = std::chrono::system_clock::to_time_t(start);
	std::cout << std::ctime(&tstamp);
	auto diff = stop - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	std::cout << msec << " msec." << endl;
	return 0;
}
