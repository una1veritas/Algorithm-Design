/*
 * B-Tree_main.cpp
 *
 *  Created on: 2022/08/09
 *      Author: Sin Shimozono
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include "B-Tree.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

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

	std::vector<string *> keys;
	std::ostringstream osstream;

	for(unsigned int i = 1; i < (unsigned int)argc; ++i) {
		string arg = argv[i];
		if ( string("-i") == arg ) {
			mode = INSERT_FOLLOWING;
		} else if (string("-r") == arg) {
			mode = REMOVE_FOLLOWING;
		} else if ( string("-I") == arg ) {
			mode = RANDOM_INSERT;
		} else if (string("-R") == arg) {
			mode = RANDOM_REMOVE;
		} else {
			unsigned int val = std::stoi(arg); //, NULL, 10);
			if (mode == INSERT_FOLLOWING or mode == REMOVE_FOLLOWING) {
				osstream.str("");
				osstream.clear();
				osstream << std::setw(3) << std::setfill('0') << val;
				if (mode == INSERT_FOLLOWING) {
					keys.push_back(new string(osstream.str()));
					cout << "insert " << *keys.back() << endl;
					tree.insert(*keys.back());
					cout << tree << endl << endl;
				} else if (mode == REMOVE_FOLLOWING) {
					cout << "remove " << osstream.str() << endl;
					if ( tree.remove(osstream.str()) ) {
						cout << tree << endl << endl;
					}
				}
			}else {
				for(unsigned int i = 0; i < val; ++i) {
					osstream.str("");
					osstream.clear();
					unsigned int r = mt() % 129;;
					osstream << std::setw(3) << std::setfill('0') << r;
					if (mode == RANDOM_INSERT) {
						keys.push_back(new string(osstream.str()));
						cout << "insert " << *keys.back() << endl;
						tree.insert(*keys.back());
						cout << tree << endl << endl;
					} else if (mode == RANDOM_REMOVE) {
						if (! keys.empty()) {
							unsigned int x = mt() % keys.size();
							if ( tree.remove(*keys[x]) ) {
								cout << "remove " << *keys[x] << endl;
								cout << tree << endl << endl;
							}
						}
					}
				}
			}
		}
	}
	cout << tree.size() << " done." << endl;
	for(auto & k : keys) {
		delete k;
	}
	return 0;
}
