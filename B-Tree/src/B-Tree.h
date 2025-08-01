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

typedef string Key;

struct BTreeNode {
private:
	static constexpr unsigned int MINIMUM_DEGREE = 2;
	static constexpr unsigned int MIN_KEYS = MINIMUM_DEGREE - 1;
	static constexpr unsigned int MAX_KEYS = 2*MINIMUM_DEGREE - 1;

private:
	const Key * key[MAX_KEYS];
	BTreeNode * child[MAX_KEYS+1];
	unsigned int keycount;

public:
	BTreeNode(void) : keycount(0) {
		key[0] = NULL;
		child[0] = NULL;
	}

	~BTreeNode() { }

	// copy constructor
	BTreeNode(const BTreeNode & node);
	BTreeNode(const Key & k, BTreeNode * l = NULL, BTreeNode * r = NULL);
	BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to);

	void clear();

	bool is_full() const;
	bool is_empty() const;
	bool is_leaf() const;

private:
	unsigned int child_index(const BTreeNode * node);

	BTreeNode * left_sibling_of(const unsigned int &);

	BTreeNode * right_sibling_of(const unsigned int &);

	unsigned int key_index(const Key & k);

	// split at the middle
	BTreeNode * split_child(const unsigned int &);

	const Key & key_insert(const Key & k, const unsigned int & ix, BTreeNode * left = NULL, BTreeNode * right = NULL);
	const Key & key_remove(const unsigned int & ix);
	const Key & key_remove(const Key & k);

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
	vector<BTreeNode *> remove_in_leaf(const Key & k);

	void delete_node(BTreeNode * node);

public:
	unsigned int size(void) const {
		return count;
	}
	const Key * find(const Key & k) const;
	bool insert(const Key & k);
	bool remove(const Key & k);

	friend std::ostream & operator<<(std::ostream & out, const BTree & tree);

};




#endif /* B_TREE_H_ */
