/*
 * 2-3-4-Tree-list.cpp
 *
 *  Created on: 2024/05/01
 *      Author: sin
 */

#include <iostream>
#include <list>
#include <string>

using namespace std;

typedef std::string Data;

struct Node234 {
private:
	//Node234 * parent;
	std::list<Data> data;
	std::list<Node234 *> children;

	constexpr static unsigned int key_max_size = 3;
	constexpr static unsigned int children_max_size = key_max_size + 1;

	typedef std::pair<std::list<Data>::iterator,std::list<Node234*>::iterator> iter_pair;

public:

	Node234(const Data & d, Node234 * left = NULL, Node234 * right = NULL) {
		// construct a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		data.clear();
		data.push_back(d);
		children.clear();
		if (right != NULL and left != NULL) {
			children.push_back(left);
			children.push_back(right);
		}
	}

	~Node234() {
		data.clear();
		children.clear();
	}

	bool empty() const {
		return data.empty();
	}

	const unsigned int count() const {
		return data.size();
	}

	/*
	bool is_root() const {
		return parent == NULL;
	}
	 */

	bool is_leaf() const {
		return children.empty();
	}

	bool is_full() const {
		return count() == key_max_size;
	}

	bool is_2node() const {
		return count() == 1;
	}


public:
	std::list<Data>::iterator upper_boud_data_iterator(const Data & k) {
		// assuming one or more data exist(s).
		auto key_itr = data.begin();
		for(;key_itr != data.end(); ++key_itr) {
			if ( k < *key_itr)
				return key_itr;
		}
		return data.end();
	}

	iter_pair upper_boud_iterators(const Data & k) {
		// assuming one or more data exist(s).
		auto key_itr = data.begin();
		auto cld_itr = children.begin();
		for(; *key_itr < k and key_itr != data.end(); ++key_itr, ++cld_itr) ;
		return iter_pair(key_itr, cld_itr);
	}

	// insert the pointer of given key at an apropriate position
	std::list<Data>::iterator insert_data_in_leaf(const Data & k) {
		if ( is_full() ) {
			cerr << "error: node is full, insert_data failed." << endl;
			return data.end();
		}
		cout << *this << ", " << k << endl;
		std::list<Data>::iterator itr = upper_boud_data_iterator(k);
		data.insert(itr, k);

		cout << *this << endl;
		return itr;
	}

	std::pair<Node234 *,iter_pair> find_position(const Data & k, const bool leaf = true, const bool split = true) {
		Node234 * att = this;
		iter_pair itpair;
		for(;;) {
			//cout << "going to find " << k << " in " << *att << std::endl;
			/*
			if (att->is_full() and split) {
				//std::cout << "encountered a node must be splitted." << std::endl;
				//cout << *att << endl;
				att = att->split();
				//cout << *att << endl;
			}
			*/
			itpair = att->upper_boud_iterators(k);
			/*
			if ( itr_pair.first != att->data.end()) {
				cout << "reached the end." << endl ;
			}
			std::cout << "att = " << *att << " pos = " << *itr_pair.first << std::endl;
			*/
			if ( *itpair.first == k ) {
				//cout << " found " << endl;
				return std::pair<Node234 *,iter_pair>(att, itpair);
			} else {
				//cout << " not found " << endl;
				if ( att->is_leaf() ) {
					//cout << "i'm a leaf. " << endl;
					break;
				}
			}
			att = *(itpair.second);
		}
		//cout << " not found exit " << endl;
		return std::pair<Node234 *,iter_pair>(att, itpair);
	}
	/*

	Node234 * find_remove_leaf(const DataType & k) {
		Node234 * att = this;
		Node234 * keynode = NULL;
		unsigned int keypos, i;
		for(;;) {
			att = att->find_leaf_or_node(k, false, false);
			cout << *att << endl;
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
		if (keynode != NULL and !keynode->is_leaf()) {
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

	const DataType * rotate_into() {
		unsigned int ix;
		Node234 * sibling;
		for(ix = 0; parent->childptr[ix] != this and ix < parent->keycount; ++ix);
		cout << *parent << endl;
		if (ix > 0 and ! parent->childptr[ix-1]->is_2node()) {
			sibling = parent->childptr[ix-1];  // use left sibgling
			const Key & parentkey = * parent->keyptr[ix-1];
			cout << *sibling << ", " << *this << endl;
			const Key & slastkey = * sibling->keyptr[sibling->keycount - 1];
			Node234 * slastchild = sibling->childptr[sibling->keycount];
			sibling->remove_key_from_node(slastkey);
			parent->keyptr[ix-1] = &slastkey;
			insert_key_to_node(parentkey);
			childptr[0] = slastchild;
			cout << *parent << endl;
			return &parentkey;
		} else if (ix < parent->keycount and ! parent->childptr[ix+1]->is_2node()) {
			sibling = parent->childptr[ix+1];  // use right sibgling
			const Key & parentkey = * parent->keyptr[ix];
			cout << *sibling << endl;
			const Key & sfirstkey = * sibling->keyptr[0];
			Node234 * sfirstchild = sibling->childptr[0];
			sibling->remove_key_from_node(sfirstkey);
			parent->keyptr[ix] = &sfirstkey;
			insert_key_to_node(parentkey);
			childptr[keycount] = sfirstchild;
			cout << *parent << endl;
			return &parentkey;
		}
		return NULL;
	}
*/
public:
	const Data * find(const Data & key) {
		std::pair<Node234 *,iter_pair>  pos = find_position(key);
		if (* pos.second.first == key)
			return &(*pos.second.first);
		return NULL;
	}

	Node234 * insert(const Data & k) {
		std::cout << "inserting " << k << std::endl;
		std::pair<Node234 *,iter_pair> pos = this->find_position(k, true, true);
		Node234 *node = pos.first;
		cout << "node = " << *node << endl;
		//iter_pair itrs = pos.second;
		if (node->is_leaf()) {
			if ( !node->is_full() ) {
				//cout << "not full." << endl;
				node->insert_data_in_leaf(k);
				return node;

			} else {
				// split
				std::cout << "encountered full-node to insert " << *node << std::endl;
			}
		}
		return node;
	}
/*
	const DataType * remove_key_from_node(const DataType & k) {
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
	*/

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		//out << "[" << node.parent << "]";
		auto dt_itr = node.data.begin();
		auto ch_itr = node.children.begin();
		for( ;dt_itr != node.data.end(); ++dt_itr, ++ch_itr) {
			if (*ch_itr != NULL) {
				out << **ch_itr << ", ";
			}
			out << *dt_itr << ", ";
		}
		if (*ch_itr != NULL) {
			out << **ch_itr << ", ";
		}
		out << ") ";
		return out;
	}

	friend struct Tree234;
};

struct Tree234 {
	Node234 * root;
public:

	Tree234() : root(NULL) {}

	void insert(const Data & k) {
		if (root == NULL) {
			root = new Node234(k);
		} else {
			cout << "calling insert.,.. ";
			root->insert(k);
		}
	}

	/*
	void remove(const Key & k) {
		root.remove(k);
	}
*/
	friend ostream & operator<<(ostream & out, const Tree234 & tree) {
		out << "234Tree" << *(tree.root) ;
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
		cout << "Inserting " << args[i] << " to the tree." << endl;
		tree234.insert(args[i]);
		cout << tree234 << endl << endl;
	}

	if ( tree234.root->find("this") != NULL) {
		cout << "found.";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;


	cout << "done." << std::endl;

	/*
	tree234.remove(string("P"));
 	cout << tree234 << endl;
	tree234.remove(string("N"));
 	cout << tree234 << endl;
	tree234.remove(string("M"));
 	cout << tree234 << endl;
*/

	delete [] args;
	return 0;
}
