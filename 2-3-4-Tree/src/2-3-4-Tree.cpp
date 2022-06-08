//============================================================================
// Name        : 2-3-4-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef const char * Data;

struct Node234 {
	vector<Data> data;
	vector<Node234 *> children;

	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

	void initialize(void) {
		data.clear();
		children.clear();
	}

	Node234(void) {
		initialize();
	}

	void data_insert(const char * d) {
		if ( data.size() == data_max_size ) {
			cerr << "error: data_insert failure." << endl;
			return;
		}
		vector<Data>::const_iterator i;
		for (i = data.begin(); i != data.end() ; ++i) {
			if ( strcmp(*i, d) > 0 )
				break;
		}
		if ( i == data.end() ) {
			data.push_back(d);
		} else {
			data.insert(i, d);
		}
		return;
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		for(auto & d : node.data) {
			out << d << ", ";
		}
		out << endl;
		return out;
	}
};

int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}

	Node234 tree;
	tree.data_insert(argv[1]);
	tree.data_insert(argv[2]);
	tree.data_insert(argv[3]);
	tree.data_insert(argv[4]);

	cout << "Hello!" << endl;
	cout << tree << endl;

	return 0;
}
