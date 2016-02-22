/*
 * test.cpp
 *
 *  Created on: 2016/01/27
 *      Author: sin
 */

#include <iostream>

#include <string>
#include <unordered_map>

int main(int argc, char * argv[]) {

	std::hash<std::string> hasher;
	std::string str;

	std::cout << "--- Hash values ---" << std::endl;
	argv++;
	while(*argv != NULL) {
		str = *argv;
		unsigned long hashValue = hasher(str);
		std::cout << hashValue << "  \"" << str << "\" " << std::endl;
		argv++;
	}

	return EXIT_SUCCESS;
}
