/*
 * B-Tree.h
 *
 *  Created on: 2022/08/09
 *      Author: Sin Shimozono
 */

#ifndef B_TREE_H_
#define B_TREE_H_

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

#include "DataType.h"

struct BTreeNode {
	// class constants
private:
	static constexpr unsigned int MINIMUM_DEGREE = 3;
	static constexpr unsigned int MIN_KEYS = MINIMUM_DEGREE - 1;
	static constexpr unsigned int MAX_KEYS = 2*MINIMUM_DEGREE - 1;

	// member filed values
private:
	DataType data[MAX_KEYS];
	BTreeNode * child[MAX_KEYS+1];
	unsigned int keycount;

public:
	BTreeNode(void) : keycount(0) {
		child[0] = NULL;
	}

	~BTreeNode() { }

	// copy constructor
	BTreeNode(const BTreeNode & node);
	BTreeNode(const DataType & k, BTreeNode * l = NULL, BTreeNode * r = NULL);
	BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to);

	void clear();

	bool is_full() const;
	bool is_empty() const;
	bool is_leaf() const;

	static unsigned int max_number() { return MAX_KEYS; }


private:
	unsigned int child_index(const BTreeNode * node);

	BTreeNode * left_sibling_of(const unsigned int &);

	BTreeNode * right_sibling_of(const unsigned int &);

	unsigned int key_index(const DataType & k);

	// split at the middle
	BTreeNode * split_child(const unsigned int &);

	const DataType & key_insert(const DataType & k, const unsigned int & ix, BTreeNode * left = NULL, BTreeNode * right = NULL);
	const DataType & key_remove(const unsigned int & ix);
	const DataType & key_remove(const DataType & k);

	void shift_to_right(const unsigned int & cix);
	void shift_to_left(const unsigned int & ix);
	BTreeNode * merge_into_left(const unsigned int & ix);

	friend std::ostream & operator<<(std::ostream & out, const BTreeNode & node);

	friend struct BTree;
};

struct BTree {
private:
	BTreeNode * root;
	unsigned int count;

public:
	BTree(void) : root(new BTreeNode()), count(0) { }

	~BTree() {
		delete_node(root);
	}

private:
	bool has_min_keys(BTreeNode * node) const;

	struct NodeIndexPair {
		BTreeNode * node;
		unsigned int index;
	};

	vector<NodeIndexPair> find_and_remove_in_leaf(const DataType & k);

	void delete_node(BTreeNode * node);

public:
	unsigned int size(void) const {
		return count;
	}
	const DataType * find(const DataType & k) const;
	bool insert(const DataType & k);
	bool remove(const DataType & k);

	friend std::ostream & operator<<(std::ostream & out, const BTree & tree);

};




#endif /* B_TREE_H_ */
