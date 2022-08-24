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

#include "Union-Find.h"

using std::cout;
using std::cerr;
using std::endl;

/*
#include <stdio.h>
#include <stdlib.h>
*/

static int r;

int rnd() {
//	static int r = 1102; /* 自分の学生番号の下4 桁に書き換える */
	r = ((r + 1013) * 171) % 1331;
	return r;
}

int main(const int argc, const char * const argv[]) {

	if (argc <= 1) {
		cerr << "Supply a seed number." << endl;
		return EXIT_FAILURE;
	}
	r = std::stoi(argv[1]);
	if (!r) {
		cerr << "Supply a number." << endl;
		return EXIT_FAILURE;
	}
	cout << "Seed " << r << " will be used." << endl;

	UnionFindSet ufs(17);
	cout << ufs << endl << endl;

	int tp, arg1, arg2;
	for(int i = 0; i < 16; ++i) {
		tp = rnd() % 2;
		arg1 = rnd() % 17;
		arg2 = rnd() % 17;

		if (tp) {
			cout << "Find(" << arg1 << ")" << endl;
			ufs.find_set(arg1);
		} else {
			cout << "Union(" << arg1 << ", " << arg2 << ")" << endl;
			ufs.union_set(arg1, arg2);
		}
		cout << ufs << endl << endl;
	}
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
