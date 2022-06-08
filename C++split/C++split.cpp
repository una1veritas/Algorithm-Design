#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string::const_iterator strbegin, std::string::const_iterator strend, const char separator) {
	std::stringstream buff("");
	std::vector<std::string> result;
/*
	buff.clear();
	for(std::string::const_iterator i = strbegin; i != strend; ++i) {
		if (*i == separator) {
			result.push_back(buff.str());
			//buff.str(std::string(""));
			buff.clear();
			continue;
		}
		buff << *i;
	};
	*/
	return result;
}

int main(const int argc, const char *argv[]) {
	std::string arg(argv[1]);
	std::cout << arg << std::endl;
	/*
	std::vector<std::string> res =  split(arg.cbegin(), arg.cend(), ',');

	for(auto & s : res) {
		std::cout << s << "\n";
	}
	*/
	std::cout << "finished." << std::endl;
	return 0;
}
