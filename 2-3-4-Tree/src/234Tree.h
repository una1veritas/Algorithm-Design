/*
 * 234Tree.h
 *
 *  Created on: 2026/06/16
 *      Author: sin
 */

#ifndef SRC_234TREE_H_
#define SRC_234TREE_H_

#include <iostream>

#include "DataType.h"

// bi-directional node of rooted tree
// data are managed in the array (keys) in ascending order with the number of data (keycount)
struct Node234 {
private:
	Node234 * parent;
	DataType keys[3];
	unsigned int keycount;  // == nodecount - 1
	Node234 * childptr[4];

	constexpr static unsigned int key_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

	// internal data type for a pair of Node234 * and ub index
	struct NodeIndexPair {
		Node234 * node;
		unsigned int index;
	};

public:
	// empty node
	Node234() : parent(NULL), keycount(0) {
		childptr[0] = NULL; // represents no children exist.
	}

	Node234(const DataType & key, Node234 * par = NULL, Node234 * left = NULL, Node234 * right = NULL)
	: parent(par), keycount(0) {
		// construct a 2-node.
		// NULL, NULL, NULL makes a root-leaf.
		keys[keycount++] = key;
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
		// strings in keys are part of the node.
		for(unsigned int i = 0; i < keycount + 1; ++i) {
			delete childptr[i];
		}
	}

	bool is_empty() const {
		return keycount == 0;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		return childptr[0] == NULL;
	}

	// is key_max_size ( = 4) node
	bool is_full() const {
		return keycount == key_max_size;
	}

	bool is_2node() const {
		return keycount == 1;
	}

private:
	unsigned int key_ub_index(const DataType & k) const {
		// assuming one or more keys(s) exist(s).
		unsigned int i;
		for (i = 0 ; i < keycount ; ++i) {
			if ( k <= keys[i] )
				break;
		}
		return i;
	}

	// insert the pointer of given key at an appropriate position
	// to keyptr[i] and copy the childptr[i] as its left and right
	unsigned int insert_key_to_node(const DataType & k) {
		if ( is_full() ) {
			std::cerr << "error: insert_in_data234 failure." << std::endl;
			return key_max_size;
		}
		//std::cout << *this << ", " << k << endl;
		if (keycount == 0) { // empty root
			keys[keycount++] = k;
			childptr[0] = NULL;
			childptr[1] = NULL;
			return 0;
		}
		unsigned int i = key_ub_index(k);
		childptr[keycount+1] = childptr[keycount];
		for(unsigned int j = keycount; j > i; --j) {
			keys[j] = keys[j-1];
			childptr[j] = childptr[j-1];
		}
		keys[i] = k;
		++keycount;
		//std::cout << *this << endl;
		return i;
	}

	// finds k, ignore data equals k if leaf == true and the containing node is internal one,
	// splits every encountered node if split == true and it is 4 node.
	Node234 * find_leaf_or_node(const DataType & k, const bool leaf = true, const bool split = true) {
		Node234 * att = this;
		for(;;) {
			//std::cout << "going to find " << k << " in " << *att << std::endl;
			if (att->is_full() and split) {
				//std::std::cout << "encountered a node must be splitted." << std::endl;
				att = att->split();
				//std::cout << *att << endl;
			}
			if ( att->is_leaf() )
				break;
			unsigned int i = att->key_ub_index(k);
			//std::cout << "att = " << *att << " pos = " << i << std::endl;
			if ( i < att->keycount and att->keys[i] == k) {
				if (! leaf) break;
			}
			att = att->childptr[i];
		}
		return att;
	}

	NodeIndexPair find_NodeIndexPair(const DataType & k, const bool leaf = true, const bool split = true) {
		Node234 * att = this;
		unsigned int index = 0;
		for(;;) {
			//std::cout << "going to find " << k << " in " << *att << std::endl;
			if (att->is_full() and split) {
				//std::std::cout << "encountered a node must be splitted." << std::endl;
				att = att->split();
				//std::cout << *att << endl;
			}
			index = att->key_ub_index(k);
			if ( att->is_leaf() )
				return NodeIndexPair{att, index};
			//std::cout << "att = " << *att << " pos = " << i << std::endl;
			if ( index < att->keycount and att->keys[index] == k) {
				if (! leaf) break;
			}
			att = att->childptr[index];
		}
		return NodeIndexPair{att, index};
	}

	Node234 * find_remove_leaf(const DataType & k) {
		Node234 * att = this;
		Node234 * keynode = NULL;
		unsigned int keypos, i;
		for(;;) {
			att = att->find_leaf_or_node(k, false, false);

			std::cout << *att << std::endl;

			i = att->key_ub_index(k);

			std::cout << *att << " pos = " << i << std::endl;

			if ( i < att->keycount and att->keys[i] == k) {
				keynode = att;
				keypos = i;
			}
			if (att->is_leaf())
				break;
			att = att->childptr[i];
		}
		// swap the keys
		if (keynode != NULL and !keynode->is_leaf()) {
			const DataType tkey = keynode->keys[keypos];
			keynode->keys[keypos] = att->keys[att->keycount - 1];
			att->keys[att->keycount - 1] = tkey;
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
			//std::cout << "going to split the root." << endl;
			//std::cout << this << std::endl;
			right = new Node234(keys[2], this, childptr[2], childptr[3]);
			left= new Node234(keys[0], this, childptr[0], childptr[1]);
			//if (left != NULL and right != NULL)
			//	std::cout << "left = " << *left << " right = " << *right << endl;
			keys[0] = keys[1];
			childptr[0] = left;
			childptr[1] = right;
			keycount = 1;
			//std::cout << " this = " << *this << endl;
			return this;
		} else {
			right = new Node234(keys[2], parent, childptr[2], childptr[3]);
			unsigned int pos = parent->insert_key_to_node(keys[1]);
			keycount = 1;
			//std::cout << "left = " << *this << " right = " << *right << " parent = " << *parent << std::endl;
			parent->childptr[pos+1] = right;
			//std::cout << "parent = " << *parent << std::endl;
			return parent;
		}
	}

	bool rotate_into() {
		unsigned int ix;
		Node234 * sibling;

		// find the index ix of children that pointing me.
		for(ix = 0; parent->childptr[ix] != this and ix < parent->keycount; ++ix);

		std::cout << *parent << std::endl;

		if (ix > 0 and ! parent->childptr[ix-1]->is_2node()) {
			sibling = parent->childptr[ix-1];  // use left sibgling
			DataType parentkey = parent->keys[ix-1];

			std::cout << *sibling << ", " << *this << std::endl;

			DataType slastkey = sibling->keys[sibling->keycount - 1];
			Node234 * slastchild = sibling->childptr[sibling->keycount];
			sibling->remove_key_from_node(slastkey);
			parent->keys[ix-1] = slastkey;
			insert_key_to_node(parentkey);
			childptr[0] = slastchild;

			std::cout << *parent << std::endl;

			return true;
		} else if (ix < parent->keycount and ! parent->childptr[ix+1]->is_2node()) {
			sibling = parent->childptr[ix+1];  // use right sibgling
			DataType parentkey = parent->keys[ix];

			std::cout << *sibling << std::endl;

			DataType sfirstkey = sibling->keys[0];
			Node234 * sfirstchild = sibling->childptr[0];
			sibling->remove_key_from_node(sfirstkey);
			parent->keys[ix] = sfirstkey;
			insert_key_to_node(parentkey);
			childptr[keycount] = sfirstchild;

			std::cout << *parent << std::endl;

			return true;
		}
		return false;
	}

	bool merge() {
		unsigned int ix;

		if ( parent->is_2node() )
			return false;

		for(ix = 0; parent->childptr[ix] != this and ix < parent->keycount; ++ix);

		if ( ix == 0 ) {
			// merge with right sibling
			keys[keycount++] = parent->keys[ix];
			keys[keycount++] = parent->childptr[ix+1]->keys[0];
			delete parent->childptr[ix+1];
			unsigned int iy;
			for (iy = ix; iy + 1 < parent->keycount; ++iy) {
				parent->keys[iy] = parent->keys[iy+1];
				parent->childptr[iy+1] = parent->childptr[iy+2];
			}
		}
		return true;
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

	DataType remove_key_from_node(const DataType & k) {
		DataType removed_key;
		bool found = false;
		for(unsigned int i = 0; i < keycount - 1; ++i) {
			if (k == keys[i]) {
				found = true;
				removed_key = keys[i];
			}
			if (found) {
				keys[i] = keys[i+1];
			}
		}
		--keycount;
		return removed_key;
	}

	Node234 * remove(const DataType & k) {
		Node234 * node = this->find_remove_leaf(k);
		unsigned int ix = node->key_ub_index(k);
		std::cout << *node << std::endl;
		if (ix > node->keycount)
			return this;  // no need to remove
		if ( ! node->is_2node() ) {
			node->remove_key_from_node(k);
			return node;
		} else {
			std::cout << "encountered a 2-leaf." << std::endl;
			if ( node->rotate_into() ) {
				// use a rotation.
				std::cout << * node << ", " << ix << std::endl;
				node->remove_key_from_node(k);
				std::cout << * node << std::endl;
			} else if ( node->merge() ){
				// use a merge.
				std::cout << "use merge " << std::endl;
				node->remove_key_from_node(k);
				std::cout << * node << std::endl;
			} else {
				std::cout << "error! no way to remove!" << std::endl;
			}
			return node;
		}
	}

	friend std::ostream & operator<<(std::ostream & out, const Node234 & node) {
		out << "(";
		//out << "[" << node.parent << "]";
		for(unsigned int i = 0; i < node.keycount; ++i) {
			if (node.childptr[i] != NULL) {
				out << * node.childptr[i];
				out << ", ";
			}
			out << node.keys[i] << ",";
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

	void insert(const DataType & k) {
		root.insert(k);
	}

	void remove(const DataType & k) {
		root.remove(k);
	}

	friend std::ostream & operator<<(std::ostream & out, const Tree234 & tree) {
		out << "234Tree" << tree.root ;
		return out;
	}
};


#endif /* SRC_234TREE_H_ */
