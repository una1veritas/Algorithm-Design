#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
unsigned int hash(const char * idstr) {
	unsigned int hv = 0;
	for(int i = 4; i > 0; --i) {
		hv <<= 7;
		hv += idstr[i] ^ idstr[3+i];
	}
	return hv;
}

std::vector<std::string> split(const std::string & line) {
	std::vector<std::string> items;
	int pos = 0, end = 0;
	for(;;) {
		for(; end < line.length() and line[end] != ','; ++end) ;
		items.push_back(line.substr(pos,end));
		if ( end == line.length() )
			break;
		++end;
		pos = end;
	}
	return items;
}

int main(int argc, char * argv[]) {
	std::istreambuff_iterator<char> inbuff;
	  std::ifstream in("input.txt");
	  std::cin.rdbuf(in.rdbuf());
	if (argc > 1) {
		std::ifstream inputfile(argv[1]);
		inbuff =
	} else {

	}
	std::istreambuf_iterator<char> infile(std::cin), infile_end;
	//infile.fopen();
	std::stringstream item;
	for (; infile != infile_end;) {
		for(char t = *infile; t != ','; ++infile) {
			if ( t == '\r' or t == '\n' ) {
				break;
			}
			item << t;
		}
		std::cout << item.str() << std::endl;
	}

}
