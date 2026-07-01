/*
 * B-Tree_main.cpp
 *
 *  Created on: 2022/08/09
 *      Author: Sin Shimozono
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <sstream>
#include <random>
#include "B-Tree.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

#include "DataType.h"

int main(const int argc, const char * argv[]) {
	cout << "MIN " << BTreeNode::min_keys() << " MAX " << BTreeNode::max_keys() << endl; // prints !!!Hello World!!!
	cout << "Node size in bytes = " << sizeof(BTreeNode) << endl; // prints !!!Hello World!!!

	BTree tree;

	enum {
		INSERT_FOLLOWING = 0,
		REMOVE_FOLLOWING,
		RANDOM_INSERT,
		RANDOM_REMOVE,
	} mode = INSERT_FOLLOWING;

	std::random_device rnd;
	int seed = 1123; //rnd();
	std::mt19937 mt(seed);

	std::ostringstream osstream;

	for(unsigned int i = 1; i < (unsigned int)argc; ++i) {
		string arg(argv[i]);
		if ( string("-i") == arg ) {
			mode = INSERT_FOLLOWING;
		} else if (string("-r") == arg) {
			mode = REMOVE_FOLLOWING;
		} else if ( string("-I") == arg ) {
			mode = RANDOM_INSERT;
		} else if (string("-R") == arg) {
			mode = RANDOM_REMOVE;
		} else {
			//unsigned int val = std::stoi(arg); //, NULL, 10);
			std::string val = arg;
			if (mode == INSERT_FOLLOWING or mode == REMOVE_FOLLOWING) {
				osstream.str("");
				osstream.clear();
				osstream << val; //std::setw(3) << std::setfill('0') << val;
				if (mode == INSERT_FOLLOWING) {
					string key(osstream.str());
					cout << "insert " << key << endl;
					tree.insert(key);
					cout << tree << endl << endl;
				} else if (mode == REMOVE_FOLLOWING) {
					cout << "remove " << osstream.str() << endl;
					if ( tree.remove(osstream.str()) ) {
						cout << tree << endl << endl;
					}
				}
			}
		}
	}
	cout << tree.size() << " done." << endl;
	return 0;
}
