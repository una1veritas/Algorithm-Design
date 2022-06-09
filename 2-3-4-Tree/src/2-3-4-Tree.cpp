//============================================================================
// Name        : 2-3-4-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef std::string Data;

struct Node234 {
	Node234 * leftmost;
	struct DataChild {
		Data data;
		Node234 * rightchild;

		DataChild(const Data & d) : data(d), rightchild(NULL) {}
	};
	vector<DataChild> data234;

	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

	void initialize(void) {
		leftmost = NULL;
		data234.clear();
	}

	Node234(void) : leftmost(NULL), data234() { }

	bool insert_data(const std::string & str) {
		if ( data234.size() >= data_max_size ) {
			cerr << "error: insert_data failure." << endl;
			return false;
		}
		auto i = data234.cbegin();
		for ( ; i != data234.end() ; ++i) {
			if ( i->data > str )
				break;
		}
		if ( i == data234.end() ) {
			data234.push_back(DataChild(str));
		} else {
			data234.insert(i, DataChild(str));
		}
		return true;
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		for(auto & dc : node.data234) {
			out << dc.data << ", ";
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
	tree.insert_data(argv[1]);
	tree.insert_data(argv[2]);
	tree.insert_data(argv[3]);
	tree.insert_data(argv[4]);

	cout << "Hello!" << endl;
	cout << tree << endl;

	return 0;
}
