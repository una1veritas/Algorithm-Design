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

#include "234Tree.h"
#include "datatype.h"

int main(int argc, char * argv[]) {
	std::string * args;
	unsigned int idx, count;
	std::cout << "Hello!" << std::endl;
	if ( argc == 1 ) {
		std::cout << "Argument(s) required." << std::endl;
		return -1;
	}
	args = new Data [argc-1];
	for(idx = 1, count = 0; idx < (unsigned int) argc; ++idx, ++count){
		if ( std::string("-r") == argv[idx] )
			break;
		args[count] = argv[idx];
	}

	Tree234 tree234;

	for(unsigned int i = 0; i < count; ++i){
		std::cout << "Inserting " << args[i] << "." << std::endl;
		tree234.insert(args[i]);
		std::cout << tree234 << std::endl << std::endl;
	}

	std::cout << "done." << std::endl;

	if ( std::string("-r") == argv[idx]) {
		++idx;
		for ( ; idx < (unsigned int) argc; ++idx) {
			std::cout << "Removing " << argv[idx] << "." << std::endl;
			tree234.remove(Data(argv[idx]));
			std::cout << tree234 << std::endl << std::endl;
		}
	}
	delete [] args;
	return 0;
}

