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
using std::vector;

typedef std::string DataType;

struct Node234 {
private:
	Node234 * parent;
	vector<DataType> data;
	vector<Node234 *> children;

	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

public:
	Node234() : parent(NULL) {
		data.clear();
		children.clear();
	}

	Node234(DataType & d, Node234 * par = NULL, Node234 * left = NULL, Node234 * right = NULL)
	: parent(par) {
		// construct a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		data.push_back(d);
		if (left != NULL) {
			children.push_back(left);
			children.back()->parent = this;
			children.push_back(right);
			children.back()->parent = this;
		}

	}

	~Node234() {
		for(unsigned int i = 0; i < data_count(); ++i) {
			delete children[i];
		}
		delete children[data_count()];
		data.clear();
		children.clear();
	}

	unsigned int data_count() const {
		return data.size();
	}

	bool is_empty() const {
		return data_count() == 0;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		if (children.size() == 0)
			return true;
		return false;
	}

	bool is_full() const {
		return data_count() == data_max_size;
	}

	bool is_2node() const {
		return data_count() == 1;
	}

private:
	unsigned int key_ub_index(const DataType & k) const {
		// assuming one or more key(s) exist(s).
		unsigned int i;
		for (i = 0 ; i < data_count() ; ++i) {
			if ( k <= data[i] )
				break;
		}
		return i;
	}

	// insert the pointer of given key at an appropriate position
	// to keyptr[i] and copy the childptr[i] as its left and right
	unsigned int insert_key_to_node(const DataType & k) {
		if ( is_full() ) {
			cerr << "error: insert_in_data234 failure." << endl;
			return data_max_size;
		}
		//cout << *this << ", " << k << endl;
		if (data_count() == 0) { // empty root
			data.push_back(k);
			children.clear();
			return 0;
		}
		unsigned int i = key_ub_index(k);
		children.push_back(children[data_count()]);
		for(unsigned int j = data_count(); j > i; --j) {
			data[j] = data[j-1];
			children[j] = children[j-1];
		}
		data[i] = k;
		//cout << *this << endl;
		return i;
	}

	Node234 * find_leaf_or_node(const DataType & k, const bool leaf = true, const bool split = true) {
		Node234 * att = this;
		for(;;) {
			//cout << "going to find " << k << " in " << *att << std::endl;
			if (att->is_full() and split) {
				//std::cout << "encountered a node must be splitted." << std::endl;
				att = att->split();
				//cout << *att << endl;
			}
			if ( att->is_leaf() )
				break;
			unsigned int i = att->key_ub_index(k);
			//std::cout << "att = " << *att << " pos = " << i << std::endl;
			if ( i < att->keycount and *(att->data[i]) == k) {
				if (! leaf) break;
			}
			att = att->children[i];
		}
		return att;
	}

	Node234 * find_remove_leaf(const DataType & k) {
		Node234 * att = this;
		Node234 * keynode = NULL;
		unsigned int keypos, i;
		for(;;) {
			att = att->find_leaf_or_node(k, false, false);
			cout << *att << endl;
			i = att->key_ub_index(k);
			std::cout << *att << " pos = " << i << std::endl;
			if ( i < att->keycount and *(att->data[i]) == k) {
				keynode = att;
				keypos = i;
			}
			if (att->is_leaf())
				break;
			att = att->children[i];
		}
		if (keynode != NULL and !keynode->is_leaf()) {
			const DataType * tptr = keynode->data[keypos];
			keynode->data[keypos] = att->data[att->keycount - 1];
			att->data[att->keycount - 1] = tptr;
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
			right = new Node234(*data[2], this, children[2], children[3]);
			left= new Node234(*data[0], this, children[0], children[1]);
			//if (left != NULL and right != NULL)
			//	cout << "left = " << *left << " right = " << *right << endl;
			data[0] = data[1];
			childptr[0] = left;
			children[1] = right;
			keycount = 1;
			//cout << " this = " << *this << endl;
			return this;
		} else {
			right = new Node234(*data[2], parent, children[2], children[3]);
			unsigned int pos = parent->insert_key_to_node(*data[1]);
			keycount = 1;
			//cout << "left = " << *this << " right = " << *right << " parent = " << *parent << endl;
			parent->childptr[pos+1] = right;
			//cout << "parent = " << *parent << endl;
			return parent;
		}
	}

	const DataType * rotate_into() {
		unsigned int ix;
		Node234 * sibling;
		for(ix = 0; parent->children[ix] != this and ix < parent->keycount; ++ix);
		cout << *parent << endl;
		if (ix > 0 and ! parent->children[ix-1]->is_2node()) {
			sibling = parent->children[ix-1];  // use left sibgling
			const DataType & parentkey = * parent->data[ix-1];
			cout << *sibling << ", " << *this << endl;
			const DataType & slastkey = * sibling->data[sibling->keycount - 1];
			Node234 * slastchild = sibling->children[sibling->keycount];
			sibling->remove_key_from_node(slastkey);
			parent->data[ix-1] = &slastkey;
			insert_key_to_node(parentkey);
			children[0] = slastchild;
			cout << *parent << endl;
			return &parentkey;
		} else if (ix < parent->keycount and ! parent->children[ix+1]->is_2node()) {
			sibling = parent->children[ix+1];  // use right sibgling
			const DataType & parentkey = * parent->data[ix];
			cout << *sibling << endl;
			const DataType & sfirstkey = * sibling->data[0];
			Node234 * sfirstchild = sibling->children[0];
			sibling->remove_key_from_node(sfirstkey);
			parent->data[ix] = &sfirstkey;
			insert_key_to_node(parentkey);
			children[keycount] = sfirstchild;
			cout << *parent << endl;
			return &parentkey;
		}
		return NULL;
	}

public:
	Node234 * insert(const DataType & k) {
		// std::cout << "inserting " << d << std::endl;
		Node234 * node = this->find_leaf_or_node(k, true, true);

		if ( !node->is_full() ) {
			node->insert_key_to_node(k);
			return node;
		} else {
			// split
			std::cout << "error: encountered a 4-node to insert " << *node << std::endl;
		}
		return NULL;
	}

	const DataType * remove_key_from_node(const DataType & k) {
		const DataType * ptr = NULL;
		bool found = false;
		for(unsigned int i = 0; i < keycount - 1; ++i) {
			if (k == *data[i]) {
				found = true;
				ptr = data[i];
			}
			if (found) {
				data[i] = data[i+1];
			}
		}
		--keycount;
		return ptr;
	}

	Node234 * remove(const DataType & k) {
		Node234 * node = this->find_remove_leaf(k);
		unsigned int ix = node->key_ub_index(k);
		cout << *node << endl;
		if (ix > node->keycount)
			return this;  // no need to remove
		if ( ! node->is_2node() ) {
			node->remove_key_from_node(k);
			return node;
		} else {
			cout << "encountered a 2-leaf." << endl;
			if ( node->rotate_into() != NULL ) {
				// use a rotation.
				cout << * node << ", " << ix << endl;
				node->remove_key_from_node(k);
				cout << * node << endl;
			} else if ( true ) {
				// use a merge.
				cout << "use merge " << endl;
			}
			return node;
		}
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		//out << "[" << node.parent << "]";
		for(unsigned int i = 0; i < node.keycount; ++i) {
			if (node.children[i] != NULL) {
				out << * node.children[i];
				out << ", ";
			}
			out << * node.data[i] << ",";
		}
		if (node.children[node.keycount] != NULL)
			out << * node.children[node.keycount];
		out << ")";
		return out;
	}

	friend struct Tree234;
};

struct Tree234 {
	Node234 root;
public:

	Tree234() : root() {}

	void insert(const DataType & k) {
		root.insert(k);
	}

	void remove(const DataType & k) {
		root.remove(k);
	}

	friend ostream & operator<<(ostream & out, const Tree234 & tree) {
		out << "234Tree" << tree.root ;
		return out;
	}
};

int main(int argc, char * argv[]) {
	std::string * args;
	unsigned int idx, count;
	cout << "Hello!" << endl;
	if ( argc == 1 ) {
		cout << "Argument(s) required." << endl;
		return -1;
	}
	args = new std::string [argc-1];
	for(idx = 1, count = 0; idx < (unsigned int) argc; ++idx, ++count){
		if ( std::string("-r") == argv[idx] )
			break;
		args[count] = argv[idx];
	}

	Tree234 tree234;

	for(unsigned int i = 0; i < count; ++i){
		cout << "Inserting " << args[i] << " to the tree." << endl;
		tree234.insert(args[i]);
		cout << tree234 << endl << endl;
	}

	cout << "done." << std::endl;

	if ( string("-r") == argv[idx]) {
		++idx;
		for ( ; idx < (unsigned int) argc; ++idx) {
			cout << "Removing " << argv[idx] << endl;
			tree234.remove(std::string(argv[idx]));
			cout << tree234 << endl << endl;
		}
	}
	delete [] args;
	return 0;
}

