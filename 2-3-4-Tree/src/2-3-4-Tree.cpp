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

typedef std::string Key;

struct Node234 {
private:
	Node234 * parent;
	const Key * keyptr[3];
	unsigned int keycount;
	Node234 * childptr[4];

	constexpr static unsigned int key_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

public:
	// construct a stab node.
	Node234(void) {
		parent = NULL;
		childptr[0] = NULL;
		keycount = 0;
	}

	Node234(const Key & k, Node234 * par = NULL, Node234 * left = NULL, Node234 * right = NULL)
	: parent(par), keycount(0) {
		// construct a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		keyptr[keycount++] = &k;
		childptr[0] = left;
		childptr[1] = right;
	}

	~Node234() {
		for(unsigned int i = 0; i < keycount; ++i) {
			delete childptr[i];
		}
		delete childptr[keycount];
		keycount = 0;
	}

	bool is_stub() const {
		return keycount == 0;
	}

	bool is_root() const {
		return parent == NULL or parent->is_stub();
	}

	bool is_leaf() const {
		if (keycount != 0 and childptr[0] == NULL)
			return true;
		return false;
	}

	bool is_full() const {
		return keycount == key_max_size;
	}

private:
	unsigned int key_upperbound_index(const Key & k) {
		// assuming one or more key(s) exist(s).
		unsigned int i;
		for (i = 0 ; i < keycount ; ++i) {
			if ( k <= *keyptr[i] )
				break;
		}
		return i;
	}

	unsigned int insert_key_to_node(const Key & k, Node234 * key_rightchild = NULL) {
		if ( is_full() ) {
			cerr << "error: insert_in_data234 failure." << endl;
			return key_max_size;
		}
		if (keycount == 0) {
			keyptr[0] = &k;
			childptr[0] = NULL;
			childptr[1] = NULL;
			keycount = 1;
			return 0;
		}
		unsigned int i = key_upperbound_index(k);
		for(unsigned int j = keycount; j > i; --j) {
			keyptr[j] = keyptr[j-1];
			childptr[j+1] = childptr[j];
		}
		keyptr[i] = &k;
		childptr[i+1] = key_rightchild;
		keycount += 1;
		return i;
	}

	Node234 * find_insert_node(const Key & k, const bool findBottom = true) {
		Node234 * att = this;
		for(;;) {
			//std::cout << "find " << d << " in " << *att << std::endl;
			if (!att->is_leaf() and att->is_full()) {
				std::cout << "encountered a node must be splitted." << std::endl;
				att->split();
				att = att->parent;
			}
			if ( att->is_leaf() )
				break;
			unsigned int i = att->key_upperbound_index(k);
			//std::cout << " pos= " << i << std::endl;
			att = childptr[i];
			if ( i < keycount and *keyptr[i] == k) {
				if ( findBottom )
					continue;
				break;
			}
		}
		return att;
	}

public:
	Node234 * insert(const Key & k) {
		// std::cout << "inserting " << d << std::endl;
		Node234 * node = this->find_insert_node(k, true);

		if ( !node->is_full() ) {
			node->insert_key_to_node(k);
			return node;
		} else {
			// split
			std::cout << "encountered full-node to insert " << *node << std::endl;
		}
		return NULL;
	}

	void split() {
		if ( !is_full() ) {
			std::cout << "error! tried to split a not-full node." << std::endl;
			return;
		}
		Node234 * left, *right;
		if ( is_root() ) {
			std::cout << "going to split the root." << std::endl;
			right = new Node234(*keyptr[2], this, childptr[2],childptr[3]);
			left= new Node234(*keyptr[0], this, childptr[0], childptr[1]);
			keyptr[0] = keyptr[1];
			childptr[0] = childptr[1];
			childptr[1] = childptr[2];
			keycount = 1;
			return;
		}
		right = new Node234(*keyptr[2], parent, childptr[2], childptr[3]);
		unsigned int pos = parent->insert_key_to_node(*keyptr[1]);
		parent->childptr[pos+1] = this;
		keycount = 1;
		return;
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		for(unsigned int i = 0; i < node.keycount; ++i) {
			if (node.childptr[i] != NULL) {
				out << * node.childptr[i];
				out << ", ";
			}
			out << * node.keyptr[i] << ",";
		}
		if (node.childptr[node.keycount] != NULL)
			out << * node.childptr[node.keycount];
		out << ")";
		return out;
	}

	friend Node234;
};

struct Tree234 {
	Node234 root;
public:

	Tree234() : root() {	}

	void insert(const Key & k) {
		root.insert(k);
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
		std::cout << "Inserting " << argv[i] << " to the tree." << std::endl;

		if (tree == NULL) {
			tree = new Node234(argv[i]);
		} else {
			tree->insert(argv[i]);
		}
		if (tree != NULL) {
			std::cout << *tree << std::endl;
		}
	}

	std::cout << "done." << std::endl;
	delete tree;
	return 0;
}
