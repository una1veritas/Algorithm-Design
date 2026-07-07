/*
 * 234Tree.h
 *
 *  Created on: 2026/06/16
 *      Author: sin
 */

#ifndef SRC_234TREE_H_
#define SRC_234TREE_H_

#include <iostream>
#include <cstdint>

#include "datatype.h"

// bi-directional node of rooted tree
// data are managed in the array (keys) in ascending order with the number of data (keycount)
struct Node234 {
private:
	constexpr static unsigned int data_max_num = 3;
	constexpr static unsigned int children_max_num = data_max_num + 1;

private:
	Data ring[data_max_num];
	unsigned int start, count; 	// the start index and the number of data in the ring buffer
	bool forward;
	Node234 * children[children_max_num];


	// internal data type for a pair of Node234 * and ub index
	struct NodeIndexPair {
		Node234 * node;
		unsigned int index;
	};

public:
	// empty node
	Node234() : start(0), count(0), forward(true) { }

	// construct a 2-node
	Node234(const Data & d, Node234 * left = NULL, Node234 * right = NULL) : start(0), count(0), forward(true) {
		ring[start + (forward ? count : -count)] = d; 	// copy data d
		count += 1;
		children[0] = left;
		children[1] = right;
	}

	~Node234() {
		// strings in keys are part of the node.
		for(unsigned int i = 0; i < count + 1; ++i) {
			delete children[i];
		}
	}

/*	bool is_empty() const {
		return count == 0;
	}*/

	bool is_leaf() const {
		return children[0] == NULL;
	}

	// is data_max_count ( = 4) node
	bool is_full() const {
		return count == data_max_num;
	}

	bool is_2node() const {
		return count == 1;
	}

private:

	unsigned int key_ub_index(const Data & k) const {
		// assuming one or more keys(s) exist(s).
		unsigned int i;
		for (i = 0 ; i < count ; ++i) {
			if ( k <= ring[start + (forward ? i : -i)] )
				break;
		}
		return i;
	}

	// insert the pointer of given key at an appropriate position
	// to keyptr[i] and copy the childptr[i] as its left and right
	unsigned int insert_key_to_node(const Data & k) {
		if ( is_full() ) {
			std::cerr << "error: insert_in_data234 failure." << std::endl;
			return data_max_count;
		}
		//std::cout << *this << ", " << k << endl;
		if (data_count == 0) { // empty root
			keys[data_count++] = k;
			children[0] = NULL;
			children[1] = NULL;
			return 0;
		}
		unsigned int i = key_ub_index(k);
		children[data_count+1] = children[data_count];
		for(unsigned int j = data_count; j > i; --j) {
			keys[j] = keys[j-1];
			children[j] = children[j-1];
		}
		keys[i] = k;
		++data_count;
		//std::cout << *this << endl;
		return i;
	}

	// finds k, ignore data equals k if leaf == true and the containing node is internal one,
	// splits every encountered node if split == true and it is 4 node.
	Node234 * find_leaf_or_node(const Data & k, const bool leaf = true, const bool split = true) {
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
			if ( i < att->data_count and att->keys[i] == k) {
				if (! leaf) break;
			}
			att = att->children[i];
		}
		return att;
	}

	NodeIndexPair find_NodeIndexPair(const Data & k, const bool leaf = true, const bool split = true) {
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
			if ( index < att->data_count and att->keys[index] == k) {
				if (! leaf) break;
			}
			att = att->children[index];
		}
		return NodeIndexPair{att, index};
	}

	Node234 * find_remove_leaf(const Data & k) {
		Node234 * att = this;
		Node234 * keynode = NULL;
		unsigned int keypos, i;
		for(;;) {
			att = att->find_leaf_or_node(k, false, false);

			std::cout << *att << std::endl;

			i = att->key_ub_index(k);

			std::cout << *att << " pos = " << i << std::endl;

			if ( i < att->data_count and att->keys[i] == k) {
				keynode = att;
				keypos = i;
			}
			if (att->is_leaf())
				break;
			att = att->children[i];
		}
		// swap the keys
		if (keynode != NULL and !keynode->is_leaf()) {
			const Data tkey = keynode->keys[keypos];
			keynode->keys[keypos] = att->keys[att->data_count - 1];
			att->keys[att->data_count - 1] = tkey;
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
			right = new Node234(keys[2], this, children[2], children[3]);
			left= new Node234(keys[0], this, childptr[0], childptr[1]);
			//if (left != NULL and right != NULL)
			//	std::cout << "left = " << *left << " right = " << *right << endl;
			keys[0] = keys[1];
			children[0] = left;
			children[1] = right;
			data_count = 1;
			//std::cout << " this = " << *this << endl;
			return this;
		} else {
			right = new Node234(keys[2], parent, children[2], children[3]);
			unsigned int pos = parent->insert_key_to_node(keys[1]);
			data_count = 1;
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
		for(ix = 0; parent->children[ix] != this and ix < parent->data_count; ++ix);

		std::cout << *parent << std::endl;

		if (ix > 0 and ! parent->children[ix-1]->is_2node()) {
			sibling = parent->children[ix-1];  // use left sibgling
			Data parentkey = parent->keys[ix-1];

			std::cout << *sibling << ", " << *this << std::endl;

			Data slastkey = sibling->keys[sibling->data_count - 1];
			Node234 * slastchild = sibling->children[sibling->data_count];
			sibling->remove_key_from_node(slastkey);
			parent->keys[ix-1] = slastkey;
			insert_key_to_node(parentkey);
			children[0] = slastchild;

			std::cout << *parent << std::endl;

			return true;
		} else if (ix < parent->data_count and ! parent->children[ix+1]->is_2node()) {
			sibling = parent->children[ix+1];  // use right sibgling
			Data parentkey = parent->keys[ix];

			std::cout << *sibling << std::endl;

			Data sfirstkey = sibling->keys[0];
			Node234 * sfirstchild = sibling->children[0];
			sibling->remove_key_from_node(sfirstkey);
			parent->keys[ix] = sfirstkey;
			insert_key_to_node(parentkey);
			children[data_count] = sfirstchild;

			std::cout << *parent << std::endl;

			return true;
		}
		return false;
	}

	bool merge() {
		unsigned int ix;

		if ( parent->is_2node() )
			return false;

		for(ix = 0; parent->children[ix] != this and ix < parent->data_count; ++ix);

		if ( ix == 0 ) {
			// merge with right sibling
			keys[data_count++] = parent->keys[ix];
			keys[data_count++] = parent->children[ix+1]->keys[0];
			delete parent->children[ix+1];
			unsigned int iy;
			for (iy = ix; iy + 1 < parent->data_count; ++iy) {
				parent->keys[iy] = parent->keys[iy+1];
				parent->children[iy+1] = parent->children[iy+2];
			}
		}
		return true;
	}

public:

	Node234 * insert(const Data & k) {
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

	Data remove_key_from_node(const Data & k) {
		Data removed_key;
		bool found = false;
		for(unsigned int i = 0; i < data_count - 1; ++i) {
			if (k == keys[i]) {
				found = true;
				removed_key = keys[i];
			}
			if (found) {
				keys[i] = keys[i+1];
			}
		}
		--data_count;
		return removed_key;
	}

	Node234 * remove(const Data & k) {
		Node234 * node = this->find_remove_leaf(k);
		unsigned int ix = node->key_ub_index(k);
		std::cout << *node << std::endl;
		if (ix > node->data_count)
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
		for(unsigned int i = 0; i < node.data_count; ++i) {
			if (node.children[i] != NULL) {
				out << * node.children[i];
				out << ", ";
			}
			out << node.keys[i] << ",";
		}
		if (node.children[node.data_count] != NULL)
			out << * node.children[node.data_count];
		out << ")";
		return out;
	}

	friend struct Tree234;
};

struct Tree234 {
	Node234 root;
public:

	Tree234() : root() {}

	void insert(const Data & k) {
		root.insert(k);
	}

	void remove(const Data & k) {
		root.remove(k);
	}

	friend std::ostream & operator<<(std::ostream & out, const Tree234 & tree) {
		out << "234Tree" << tree.root ;
		return out;
	}
};


#endif /* SRC_234TREE_H_ */
