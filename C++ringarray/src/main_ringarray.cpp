//============================================================================
// Name        : C++ringarray.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "ringarray.h"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	ringarray<int> ring(4);

	cout << "ring.size() = " << ring.size() << endl;
	cout << "ring.capacity() = " << ring.capacity() << endl;

	for (int i = 0; i < 29; ++i) {
		ring.push_back(i);
	}
	for (int i = 0; i < 19; ++i) {
		ring.pop_front();
	}
	for (int i = 29; i < 38; ++i) {
		ring.push_back(i);
	}
	for (int i = 38; i < 49; ++i) {
		ring.push_front(i);
	}
	for (int i = 0; i < 7; ++i) {
		ring.pop_back();
	}
	for (int i = 0; i < 3; ++i) {
		ring.pop_front();
	}
	for (int i = 100; i < 120; ++i) {
		ring.push_back(i);
	}
	cout << "ring.size() = " << ring.size() << endl;
	cout << ring << endl;

	return 0;
}
