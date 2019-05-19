//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>

int main(const int argc, const char * argv[]) {
	std::cout << "!!!Hello World!!!" << std::endl;
	std::cout << argc << std::endl;
	for(int i = 0; i < argc; ++i)
		std::cout << argv[i] << ", ";
	std::cout << std::endl;
	return EXIT_SUCCESS;
}
