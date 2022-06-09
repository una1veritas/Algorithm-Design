//============================================================================
// Name        : C++stringsplit.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

std::vector<std::string> split(std::string::const_iterator strbegin, std::string::const_iterator strend, const char separator) {
	std::stringstream buff;
	std::vector<std::string> result;

	buff.clear();
	bool separatorexists = false;
	for(std::string::const_iterator i = strbegin; i != strend; ++i) {
		if (*i == separator) {
			separatorexists = true;
			result.push_back(buff.str());
			buff.str(std::string(""));
			buff.clear();
			continue;
		}
		buff << *i;
	};
	if (separatorexists or !buff.str().empty())
		result.push_back(buff.str());
	return result;
}

int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	std::string arg(argv[1]);
	//std::cout << arg << std::endl;

	std::vector<std::string> res =  split(arg.cbegin(), arg.cend(), ',');

	for(auto & s : res) {
		std::cout << s << "\n";
	}

	std::cout << "finished." << std::endl;
	return 0;
}
