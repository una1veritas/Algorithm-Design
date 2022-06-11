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
private:
	Node234 * parent;
	Node234 * rightmostchild;
	struct DataChild {
		Data data;
		Node234 * leftchild;
		/*
		DataChild(const Data & d, Node234 * ptr = NULL) : data(d), leftchild(ptr) {}
		DataChild(const DataChild & dc) : data(dc.data), leftchild(dc.leftchild) {}
		*/
	};
	vector<DataChild> data234;

	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

public:
	Node234(const Data & d, Node234 * p, Node234 * l = NULL, Node234 * r = NULL) {
		parent = p;
		data234.push_back(DataChild{d,l});
		rightmostchild = r;
	}

	bool is_leaf() const {
		for(auto & dc : data234) {
			if ( dc.leftchild != NULL )
				return false;
		}
		if ( rightmostchild != NULL )
			return false;
		return true;
	}

	bool is_full() const {
		return data234.size() == data_max_size;
	}

private:
	const DataChild * find_data_or_gap(const Data & d) {
		auto i = data234.cbegin();
		for ( ; i != data234.cend() ; ++i) {
			if ( !(i->data < d) )
				break;
		}
		if (i != data234.cend())
			return NULL;
		return &(*i);
	}

	bool insert_data234(const Data & d) {
		if ( data234.size() >= data_max_size ) {
			cerr << "error: insert_data failure." << endl;
			return false;
		}
		auto i = find_data_or_gap(d);
		DataChild dc = {d,NULL};
		if ( i == NULL ) {
			data234.push_back(dc);
		} else {
			data234.insert(i, dc);
		}
		return true;
	}

public:
	std::pair<Node234 *,DataChild *> find_node_and_dc(const Data & d) {
		Node234 * att = this;
		for(;;) {
			auto dcptr = att->find_data_or_gap(d);
			if (dcptr == NULL) {
				att = rightmostchild;
				if (att == NULL)
					return std::pair<Node234 *,DataChild *>(this,NULL);
			} else if (dcptr->data == d) {
				return std::pair<Node234 *,DataChild *>(this, dcptr);
			} else {
				att = dcptr->leftchild;
				if (dcptr->leftchild == NULL)
					return std::pair<Node234 *,DataChild *>(att,NULL);
			}
		}
		return std::pair<Node234 *,DataChild *>(this,NULL);
	}

	Node234 * insert(const Data & d) {
		Node234 * current = this->find_node_and_dc(d);
		bool stat;
		auto itr = current->find_data_or_gap(d);
		if (itr->data == d)
			return current;
		// d should be inserted.
		return NULL;
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

	Node234 root(argv[1],NULL);
	Node234 * tree = &root;
	tree->insert(argv[2]);
	tree->insert(argv[3]);
	tree->insert(argv[4]);

	cout << "Hello!" << endl;
	cout << *tree << endl;

	return 0;
}
