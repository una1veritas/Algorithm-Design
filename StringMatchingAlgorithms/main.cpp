#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define FIND_DEBUG
#include "stringmatching.h"

int main(const int argc, const char *argv[]) {
	const char p[] = "abaa", * pat;
	const char t[] = "baabaabaabaababbaaba", *txt;
	if ( argc >= 3 ) {
		txt = argv[1];
		pat = argv[2];
	} else {
		txt = t;
		pat = p;
	}
	naive nm(pat);
	kmp pm(pat);
	horspool hm(pat);
	std::string text(txt);

//	std::cout << nm << std::endl;
	std::cout << pm << std::endl;
	std::cout << hm << std::endl;
	std::cout << text << " (" << text.size() << ")" << std::endl;

	std::vector<int> res;

	std::cout << "kmp search: " << std::endl;
	res = pm.find_all(text);
	if ( res.size() ) {
		for(std::vector<int>::iterator i = res.begin(); i != res.end(); ++i) {
			std::cout << *i << ", ";
		}
	} else {
		std::cout << "not found.";
	}
	//std::cout << p.find(text);
	std::cout << std::endl << std::endl;

/*
	std::cout << "naive search: " << std::endl;

	res = nm.find_all(text);
	if ( res.size() ) {
		for(std::vector<int>::iterator i = res.begin(); i != res.end(); ++i) {
			std::cout << *i << ", ";
		}
	} else {
		std::cout << "not found.";
	}
	//std::cout << h.find(text);
	std::cout << std::endl << std::endl;
*/
	std::cout << "horspool search: " << std::endl;

	res = hm.find_all(text);
	if ( res.size() ) {
		for(std::vector<int>::iterator i = res.begin(); i != res.end(); ++i) {
			std::cout << *i << ", ";
		}
	} else {
		std::cout << "not found.";
	}
	//std::cout << h.find(text);
	std::cout << std::endl << std::endl;

	return 0;
}
