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
	Node234(const Data & d, Node234 * par = NULL, Node234 * left = NULL, Node234 * right = NULL) {
		// constructor of a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		parent = par;
		data234.push_back(DataChild{d,left});
		rightmostchild = right;
	}

	~Node234() {
		for(auto i = data234.cbegin(); i != data234.cend(); ++i) {
			if (i->leftchild != NULL)
				delete i->leftchild;
		}
		data234.clear();
		if (rightmostchild != NULL)
			delete rightmostchild;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		for(auto i = data234.cbegin(); i != data234.cend(); ++i) {
			if ( i->leftchild != NULL )
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
	unsigned int data_lowerbound(const Data & d) {
		// assuming one or more data exist(s).
		unsigned int i;
		for (i = 0 ; i < data234.size() ; ++i) {
			if ( d <= data234[i].data )
				break;
		}
		return i;
	}

	unsigned int insert_in_node(const Data & d) {
		if ( data234.size() == data_max_size ) {
			cerr << "error: insert_in_data234 failure." << endl;
			return data_max_size;
		}
		unsigned int i = data_lowerbound(d);
		DataChild dc = {d,NULL};
		if ( i == data234.size() ) {
			data234.push_back(dc);
		} else {
			data234.insert(data234.cbegin()+i, dc);
		}
		return i;
	}

	std::pair<Node234 *,unsigned int> find_node_index(const Data & d, const bool findBottom = true) {
		Node234 * att = this;
		unsigned int i;
		for(;;) {
			std::cout << "find " << d << " in " << *att << ", ";
			i = att->data_lowerbound(d);
			std::cout << " pos= " << i << std::endl;
			if (i == att->data234.size()) {
				std::cout << "here!" << std::endl;
				if (att->rightmostchild != NULL) {
					std::cout << "gogo!" << std::endl;
					att = att->rightmostchild;
					continue;
				} else {
					break;
				}
			} else if (att->data234[i].data == d) {
				if (! findBottom )
					break;
				if (att->data234[i].leftchild == NULL)
					break;
				att = att->data234[i].leftchild;

			} else {
				if ( att->data234[i].leftchild != NULL ) {
					att = att->data234[i].leftchild;
					continue;
				} else {
					break;
				}
			}
		}
		std::cout << std::endl;
		return std::pair<Node234 *,unsigned int>(att,i);
	}

public:
	Node234 * insert(const Data & d) {
		auto nodeix = this->find_node_index(d);
		Node234 * node = nodeix.first;
		unsigned int ix = nodeix.second;
		/*
		if (ix < node->data234.size()) {
			if (node->data234[ix].data == d) {
				// d already exists in the tree.
				return node;
			}
		}
		*/
		if ( !node->is_full() ) {
			node->insert_in_node(d);
			return node;
		} else {
			// split
			std::cout << *node << " will be splitted." << std::endl;
			node = node->split();
			std::cout << "after the split " << *node << std::endl;
			auto nextnodeix = node->find_node_index(d);
			std::cout << "adding to " << *(nextnodeix.first) << std::endl;
			nextnodeix.first->insert_in_node(d);
		}
		return NULL;
	}

	Node234 * split() {
		if (data234.size() != data_max_size) {
			std::cout << "error! try to split the not-full node." << std::endl;
			return NULL;
		}
		Node234 * left, *right;
		if ( is_root() ) {
			std::cout << "going to split the root." << std::endl;
			right = new Node234(data234[2].data,this,data234[2].leftchild,rightmostchild);
			left= new Node234(data234[0].data,this,data234[0].leftchild,data234[1].leftchild);
			data234[0] = data234[1];
			data234.pop_back(); data234.pop_back();
			data234[0].leftchild = left;
			rightmostchild = right;
			return this;
		}
		right = new Node234(data234[2].data,parent,data234[2].leftchild,rightmostchild);
		data234.pop_back();
		unsigned int pos = parent->insert_in_node(data234[1].data);
		parent->data234[pos].leftchild = this;
		if (pos + 1 < parent->data234.size()) {
			parent->data234[pos+1].leftchild = right;
		} else {
			parent->rightmostchild = right;
		}
		rightmostchild = data234[1].leftchild;
		data234.pop_back();
		return parent;
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		for(unsigned int i = 0; i < node.data234.size(); ++i) {
			if (node.data234[i].leftchild != NULL) {
				out << * node.data234[i].leftchild;
				out << ", ";
			}
			out << node.data234[i].data << ",";
		}
		if (node.rightmostchild != NULL)
			out << *node.rightmostchild;
		out << ")";
		return out;
	}
};

int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}
	cout << "Hello!" << endl;

	Node234 * tree = NULL;

	for(int i = 1; i < argc; ++i){
		std::cout << argv[i] << std::endl;

		if (tree == NULL) {
			tree = new Node234(argv[i]);
		} else {
			tree->insert(argv[i]);
		}
		if (tree != NULL)
			std::cout << *tree << std::endl;
	}

	std::cout << "done." << std::endl;
	delete tree;
	return 0;
}
