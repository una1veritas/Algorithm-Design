//============================================================================
// Name        : C++std_list_Test.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>

using namespace std;

struct DataNode {
	char data[256];
	unsigned char length;

	DataNode(const char * str) {
		for(length = 0; length < 255; ++length) {
			if ( str[length] == 0 ) {
				break;
			}
			data[length] = str[length];
		}
	}

	bool operator==(const DataNode & another) const {
		if (another.length != length or strncmp(another.data, data, length) != 0 )
			return false;
		return true;
	}

	friend std::ostream & operator<<(ostream & out, const DataNode & d) {
		for(int i = 0; i < d.length; ++i) {
			out << d.data[i];
		}
		return out;
	}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	std::list<DataNode> mylist;

	mylist.push_back(DataNode("This is a pen."));
	mylist.push_back(DataNode("That is a cat."));
	mylist.push_back(DataNode("Methinks I am a prophet of new world."));

	DataNode key("That is a cat.");

	for (auto & entry : mylist) {
		std::cout << entry << std::endl;
	}

	for(std::list<DataNode>::const_iterator it = mylist.cbegin(); it != mylist.cend(); ++it) {
		if ( *it == key ) {
			std::cout << "matched." << std::endl;
			mylist.insert(it, DataNode("Wow!"));
		}
	}

	std::cout << "New contents of mylist: " << std::endl;
	for (auto & entry : mylist) {
		std::cout << entry << std::endl;
	}

	return 0;
}
