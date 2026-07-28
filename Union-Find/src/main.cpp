/*
 ============================================================================
 Name        : sample-random.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

#include "Union-Find.h"

using std::cout;
using std::cerr;
using std::endl;

/*
#include <stdio.h>
#include <stdlib.h>
*/

static int r = 99;

int rnd() {
	r = ((r + 1019) * 179) % 1331;
	return (r % 16) + 1;
}

int main(void) {

	cout << "Seed " << r << " will be used." << endl;

	UnionFindSet ufs(1, 16);
	cout << ufs << endl << endl;

	int arg1, arg2;
	for(int i = 0; i < 11; ++i) {
		arg1 = rnd();
		arg2 = rnd();

		cout << i << ": " << "Union(" << arg1 << ", " << arg2 << ")" << endl;

		ufs.union_set(arg1, arg2);
		cout << ufs << endl << endl;
	}

	unsigned int hirank = 0;
	for(unsigned int i = ufs.first(); i < ufs.first() + ufs.size(); ++i) {
		cout << std::setw(3) << i << " |";
	}
	cout << endl;
	for(unsigned int i = ufs.first(); i < ufs.first() + ufs.size(); ++i) {
		cout << std::setw(3) << ufs.element_parent(i) << " |";
	}
	cout << endl;
	for(unsigned int i = ufs.first(); i < ufs.first() + ufs.size(); ++i) {
		cout << std::setw(3) << ufs.element_rank(i) << " |";
		hirank = std::max(ufs.element_rank(i),hirank);
	}
	cout << endl;
	cout << "maximum = " << hirank << endl;

	return EXIT_SUCCESS;
}

/*
int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	if (argc == 1) {
		cout << "no arguments. exit." << endl;
		return EXIT_SUCCESS;
	}
	unsigned int number = std::strtol(argv[1], NULL, 10);
	int seed;
	if (argc <= 2) {
		std::random_device rnd;
		seed = rnd();
	} else {
		seed = std::strtol(argv[2],NULL,10);
	}
	long repeats;
	if ( argc <= 3 ) {
		repeats = 1000;
	} else {
		repeats = std::strtol(argv[3],NULL, 10);
	}

	std::mt19937 mt(seed);
	long count_union = 0;
	long count_find = 0;
	cout << "union-find set size = " << number << endl;

	std::chrono::system_clock::time_point start, stop;
	start = std::chrono::system_clock::now();

	UnionFindSet ufs(number);

	for(long i = 0; i < repeats; ++i) {
		unsigned int x = mt() % number;
		unsigned int y = mt() % number;
		switch( mt() % 2 ) {
		case 0:
			//cout << x << ", " << y << endl;
			ufs.union_set(x, y);
			++count_union;
			break;
		case 1:
			//cout << x << endl;
			ufs.find_set(x);
			++count_find;
			break;
		}
	}

	stop = std::chrono::system_clock::now();
	//std::time_t tstamp = std::chrono::system_clock::to_time_t(start);
	//std::cout << std::ctime(&tstamp);
	auto diff = stop - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	std::cout << msec << " msec." << endl;
	std::cout << "union " << count_union << ", find " << count_find << endl;

	//cout << ufs << endl;
	return EXIT_SUCCESS;
}
*/
