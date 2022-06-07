#include <iostream>
#include <vector>
#include <string>

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

int main() {
	std::istream & infile = std::cin;
	//infile.fopen();
	std::vector<std::string> lines;
	const int buffer_size = 32;
	char buffer[buffer_size];
	std::string line;
	for (;;) {
		std::cin.getline(buffer, buffer_size);
	    if (std::cin.bad() || std::cin.eof()) {
	      break;
	    }
	    if (std::cin.fail()) {
	    	// 1行の途中までしか入力できていない。
	    	line += buffer;
	    	std::cin.clear(std::cin.rdstate() & ~std::ios_base::failbit);
	    } else {
	      // 行の終わりまで入力できたのでループを脱出する。
	    	line += buffer;
	    	//std::cout << line << std::endl;
	    	lines.push_back(line);
	    	line.clear();
	    }
	}

	for(auto & l : lines) {
		for(auto & item : split(l)) {
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "size of unsigned int = " << sizeof(unsigned int) << std::endl;
	std::cout << hash("212C1099") << std::endl;
}
