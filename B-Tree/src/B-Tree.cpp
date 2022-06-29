//============================================================================
// Name        : B-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct BTreeNode {
	static constexpr int MINIMUM_DEGREE = 3;
	static constexpr int MIN_KEYS = MINIMUM_DEGREE - 1;
	static constexpr int MAX_KEYS = 2*MINIMUM_DEGREE - 1;

	BtreeNode() {

	}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
