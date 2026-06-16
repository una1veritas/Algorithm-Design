//============================================================================
// Name        : 2-3-4-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef std::string MyDataType;

#include "234Tree.h"

int main(int argc, char * argv[]) {
	std::string * args;
	unsigned int idx, count;
	cout << "Hello!" << endl;
	if ( argc == 1 ) {
		cout << "Argument(s) required." << endl;
		return -1;
	}
	args = new std::string [argc-1];
	for(idx = 1, count = 0; idx < (unsigned int) argc; ++idx, ++count){
		if ( std::string("-r") == argv[idx] )
			break;
		args[count] = argv[idx];
	}

	Tree234 tree234;

	for(unsigned int i = 0; i < count; ++i){
		cout << "Inserting " << args[i] << " to the tree." << endl;
		tree234.insert(args[i]);
		cout << tree234 << endl << endl;
	}

	cout << "done." << std::endl;

	if ( string("-r") == argv[idx]) {
		++idx;
		for ( ; idx < (unsigned int) argc; ++idx) {
			cout << "Removing " << argv[idx] << endl;
			tree234.remove(std::string(argv[idx]));
			cout << tree234 << endl << endl;
		}
	}
	delete [] args;
	return 0;
}

