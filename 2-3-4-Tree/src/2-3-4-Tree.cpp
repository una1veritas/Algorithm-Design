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
	Node234() : parent(NULL), keycount(0) {
		keyptr[0] = NULL;
		childptr[0] = NULL;
	}

	Node234(const Key & k, Node234 * par = NULL, Node234 * left = NULL, Node234 * right = NULL)
	: parent(par), keycount(0) {
		// construct a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		keyptr[keycount++] = &k;
		childptr[0] = left;
		if (left != NULL) {
			childptr[0]->parent = this;
		}
		childptr[1] = right;
		if (right != NULL) {
			childptr[1]->parent = this;
		}

	}

	~Node234() {
		for(unsigned int i = 0; i < keycount; ++i) {
			delete childptr[i];
		}
		delete childptr[keycount];
		keycount = 0;
	}

	bool is_empty() const {
		return keycount == 0;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		if (childptr[0] == NULL)
			return true;
		return false;
	}

	bool is_full() const {
		return keycount == key_max_size;
	}

	bool is_2node() const {
		return keycount == 1;
	}

private:
	unsigned int key_ub_index(const Key & k) {
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
		if (keycount == 0) { // empty root
			keyptr[0] = &k;
			childptr[0] = NULL;
			childptr[1] = NULL;
			keycount = 1;
			return 0;
		}
		unsigned int i = key_ub_index(k);
		for(unsigned int j = keycount; j > i; --j) {
			keyptr[j] = keyptr[j-1];
			childptr[j+1] = childptr[j];
		}
		keyptr[i] = &k;
		childptr[i+1] = key_rightchild;
		keycount += 1;
		return i;
	}

	Node234 * find_leaf_or_node(const Key & k, const bool leaf = true, const bool split = true) {
		Node234 * att = this;
		for(;;) {
			cout << "find " << k << " in " << *att << std::endl;
			if (att->is_full() and split) {
				//std::cout << "encountered a node must be splitted." << std::endl;
				//cout << *att << endl;
				att = att->split();
				//cout << *att << endl;
			}
			if ( att->is_leaf() )
				break;
			unsigned int i = att->key_ub_index(k);
			std::cout << "att = " << *att << " pos = " << i << std::endl;
			if ( i < att->keycount and *(att->keyptr[i]) == k) {
				if (! leaf) break;
			}
			att = att->childptr[i];
		}
		return att;
	}

	Node234 * find_remove_leaf(const Key & k) {
		Node234 * att = this;
		Node234 * keynode = NULL;
		unsigned int keypos, i;
		for(;;) {
			att = att->find_leaf_or_node(k, false, false);
			i = att->key_ub_index(k);
			std::cout << *att << " pos = " << i << std::endl;
			if ( i < att->keycount and *(att->keyptr[i]) == k) {
				keynode = att;
				keypos = i;
			}
			if (att->is_leaf())
				break;
			att = att->childptr[i];
		}
		if (!keynode->is_leaf() and keynode != NULL) {
			const Key * tptr = keynode->keyptr[keypos];
			keynode->keyptr[keypos] = att->keyptr[att->keycount - 1];
			att->keyptr[att->keycount - 1] = tptr;
		}
		return att;
	}

	Node234 * split() {
		if ( !is_full() ) {
			std::cout << "error! tried to split a not-full node." << std::endl;
			return this;
		}
		Node234 * left, *right;
		if ( is_root() ) {
			//cout << "going to split the root." << endl;
			//cout << this << endl;
			right = new Node234(*keyptr[2], this, childptr[2], childptr[3]);
			left= new Node234(*keyptr[0], this, childptr[0], childptr[1]);
			//if (left != NULL and right != NULL)
			//	cout << "left = " << *left << " right = " << *right << endl;
			keyptr[0] = keyptr[1];
			childptr[0] = left;
			childptr[1] = right;
			keycount = 1;
			//cout << " this = " << *this << endl;
			return this;
		} else {
			right = new Node234(*keyptr[2], parent, childptr[2], childptr[3]);
			unsigned int pos = parent->insert_key_to_node(*keyptr[1]);
			keycount = 1;
			//cout << "left = " << *this << " right = " << *right << " parent = " << *parent << endl;
			parent->childptr[pos+1] = right;
			//cout << "parent = " << *parent << endl;
			return parent;
		}
	}

public:
	Node234 * insert(const Key & k) {
		// std::cout << "inserting " << d << std::endl;
		Node234 * node = this->find_leaf_or_node(k, true, true);

		if ( !node->is_full() ) {
			node->insert_key_to_node(k);
			return node;
		} else {
			// split
			std::cout << "encountered full-node to insert " << *node << std::endl;
		}
		return NULL;
	}

	Node234 * sibling34() {
		Node234 * p = parent;
		unsigned int pos;
		for(pos = 0; this != p->childptr[pos] and pos < p->keycount; ++pos);
		if (pos > 0 and !p->childptr[pos-1]->is_2node()) {
			return p->childptr[pos-1];
		} else if (pos < p->keycount-1 and !p->childptr[pos+1]->is_2node()) {
			return p->childptr[pos+1];
		}
		return NULL;
	}

	const Key * extract_key(unsigned int ix) {
		const Key * ptr = NULL;
		if (ix < keycount) {
			ptr = keyptr[ix];
		}
		for(unsigned int i = ix; i < keycount; ++i) {
			keyptr[i] = keyptr[i+1];
			childptr[i+1] = childptr[i+2];
		}
		--keycount;
		return ptr;
	}

	const Key * remove_key_from_node(const Key & k) {
		const Key * ptr = NULL;
		bool found = false;
		for(unsigned int i = 0; i < keycount - 1; ++i) {
			if (k == *keyptr[i]) {
				found = true;
				ptr = keyptr[i];
			}
			if (found) {
				keyptr[i] = keyptr[i+1];
			}
		}
		--keycount;
		return ptr;
	}

	Node234 * remove(const Key & k) {
		Node234 * node = this->find_remove_leaf(k);
		unsigned int ix = node->key_ub_index(k);
		cout << *node << endl;
		if (ix > node->keycount)
			return this;  // no need to remove
		if ( ! node->is_2node() ) {
			node->extract_key(ix);
			return node;
		} else {
			cout << "hanged at 2-leaf." << endl;
			Node234 * s34 = node->sibling34();
			cout << *s34 << endl;
			if (s34 != NULL) {
				if (*s34->keyptr[0] < k) {
					// s34 is left sibling
					node->insert_key_to_node(*s34->extract_key(s34->keycount-1));
				} else {
					node->insert_key_to_node(*s34->extract_key(0));
				}
				cout << * node << ", " << ix << endl;
				node->remove_key_from_node(k);
				cout << * node << endl;
			}
			return node;
		}
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		//out << "[" << node.parent << "]";
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

	friend struct Tree234;
};

struct Tree234 {
	Node234 root;
public:

	Tree234() : root() {}

	void insert(const Key & k) {
		root.insert(k);
	}

	void remove(const Key & k) {
		root.remove(k);
	}

	friend ostream & operator<<(ostream & out, const Tree234 & tree) {
		out << tree.root;
		return out;
	}
};

int main(int argc, char * argv[]) {
	std::string * args;
	unsigned int i, count;
	cout << "Hello!" << endl;
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	} else {
		args = new std::string [argc-1];
		for(i = 1, count = 0; i < (unsigned int) argc; ++i, ++count){
			args[count] = argv[i];
		}
	}

	Tree234 tree234;

	for(unsigned int i = 0; i < count; ++i){
		std::cout << "Inserting " << args[i] << " to the tree." << std::endl;
		tree234.insert(args[i]);
		std::cout << tree234 << std::endl;
	}

	cout << "done." << std::endl;

	tree234.remove(string("P"));
 	cout << tree234 << endl;

	delete [] args;
	return 0;
}
