//============================================================================
// Name        : STL-sample.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
// set implemented by red-black tree
#include <set>
// variable-length array
#include <vector>

using namespace std;

int main() {
	set<int> intset; 			// set of ints.
	set<vector<int> > vecset; 	// set of sequences of ints

	for(int i = 0; i < 10; ++i) {
		intset.insert(rand() % 10000);
	}

	for(int i = 0; i < 10; ++i) {
		vector<int> vec;
		for(int j = 0; j < i + 1; ++j)
			vec.push_back(rand() % 10000);
		vecset.insert(vec);
	}

	for(set<int>::iterator i = intset.begin(); i != intset.end(); ++i ) {
		printf("%d, ", *i);
	}

	for(set<vector<int> >::iterator i = intset.begin(); i != intset.end(); ++i ) {
		printf("%d, ", *i);
	}
printf("\n");

	return 0;
}
