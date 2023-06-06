/*
 * C++11_unordered_map.cpp
 *
 *  Created on: 2022/05/31
 *      Author: sin
 */

#include <iostream>
#include <string>
#include <unordered_map>

struct MyDataType {
	std::string sid;
	std::string surname, givenname;

	size_t operator()(const MyDataType & data) const {
		size_t s = 0;
		for(int i = 4; i > 0; --i) {
			s <<= 7;
			s += data.sid[i-1] ^ data.sid[3 + i];
		}
		return s;
	}

	friend bool operator==(const MyDataType & a, const MyDataType & b) {
		return a.sid == b.sid;
	}
};

//template<> struct std::hash<MyDataType> {
//public:
//	size_t operator()(const MyDataType & data) const {
//		size_t s = 0;
//		for(int i = 4; i > 0; --i) {
//			s <<= 7;
//			s += data.sid[i-1] ^ data.sid[3 + i];
//		}
//		return s;
//	}
//};

int main(const int argc, const char * argv[]) {
	std::unordered_map<MyDataType, int, MyDataType> map;

	map[ {"228C3014", "Yamamoto", "Yama"} ] = 0;
	map[ {"228C3042", "Kawano", "Sakana"} ] = 2;
	map[ {"228E2204", "Murano", "Tanbo"} ] = 1;

	for (auto & data : map) {
		std::cout << data.first.sid << ": " << data.first.surname << ", " << data.first.givenname
				<< " -> " << data.second << std::endl;
	}
	return 0;
}
