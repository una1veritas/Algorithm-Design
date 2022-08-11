//============================================================================
// Name        : B-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include "B-Tree.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

// copy constructor
BTreeNode::BTreeNode(const BTreeNode & node) : keycount(node.keycount) {
	for(unsigned int i = 0; i < keycount; ++i) {
		key[i] = node.key[i];
		child[i] = node.child[i];
	}
	child[keycount] = node.child[keycount];
}

BTreeNode::BTreeNode(const Key & k, BTreeNode * l, BTreeNode * r) : keycount(1) {
	key[0] = &k;
	child[0] = l;
	child[1] = r;
	if (keycount+1 < MAX_KEYS)
		child[keycount + 1] = NULL;
}

BTreeNode::BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to) : keycount(0) {
	unsigned int src, dst;
	for(src = from, dst = 0; from < to and src < node->keycount; ++src, ++dst) {
		key[dst] = node->key[src];
		child[dst] = node->child[src];
	}
	child[dst] = node->child[src];
	keycount = dst;
	if (keycount+1 < MAX_KEYS)
		child[keycount + 1] = NULL;
}

void BTreeNode::clear() {
	for(unsigned int i = 0; i < keycount + 1; ++i) {
		child[i] = NULL;
	}
}

bool BTreeNode::is_full() const {
	return keycount >= MAX_KEYS;
}

bool BTreeNode::is_empty() const {
	return keycount == 0;
}

bool BTreeNode::is_leaf() const {
	return child[0] == NULL;
}

unsigned int BTreeNode::child_index(const BTreeNode * node) {
	unsigned int ix;
	for(ix = 0; ix < keycount + 1; ++ix)
		if (node == child[ix])
			break;
	return ix;
}

BTreeNode * BTreeNode::left_sibling_of(const BTreeNode * node) {
	unsigned int ix = child_index(node);
	if ( ix == 0 or ix > keycount)
		return NULL;
	return child[ix - 1];
}

BTreeNode * BTreeNode::right_sibling_of(const BTreeNode * node) {
	unsigned int ix = child_index(node);
	if ( ix + 1 > keycount )
		return NULL;
	return child[ix + 1];
}

unsigned int BTreeNode::key_index(const Key & k) {
	unsigned int ix;
	for(ix = 0; ix < keycount; ++ix)
		if ( k <= *key[ix] )
			break;
	return ix;
}

// split at the middle
BTreeNode * BTreeNode::split_child(BTreeNode * node) {
	//cout << *this << ", " << *node << endl;
	unsigned int midix = node->keycount/2;
	BTreeNode * rchild = new BTreeNode(node, midix+1, node->keycount);
	unsigned int cix = child_index(node);
	key_insert(*node->key[midix], cix, node, rchild);
	node->keycount = midix;
	//cout << "after split " << *this << endl;
	return this;
}

const Key & BTreeNode::key_insert(const Key & k, const unsigned int & ix, BTreeNode * left, BTreeNode * right) {
	//cout << *this << endl;
	for(unsigned int i = keycount; i > ix; --i) {
		key[i] = key[i-1];
		child[i+1] = child[i];
	}
	key[ix] = &k;
	child[ix] = left;
	child[ix+1] = right;
	++keycount;
	if (keycount < MAX_KEYS)
		child[keycount+1] = NULL;
	return *key[ix];
}

const Key & BTreeNode::key_remove(unsigned int ix) {
	if (ix >= keycount)
		return *key[ix]; // raise error.
	unsigned int i;
	const Key & k = *key[ix];
	if (ix < keycount - 1) {
		// except the right-most key and the right most child
		for(i = ix; i < keycount; ++i) {
			key[i] = key[i+1];     // key[keycount-1] = key[keycount] is redundant
			child[i] = child[i+1]; // child[keycount-1] is the last right child
		}
	}
	child[keycount] = NULL;
	--keycount;
	return k;
}

void BTreeNode::shift_right(BTreeNode * left, BTreeNode * right) {
	//cout << "right shift: left = " << *left << " right = " << *right << endl;
	unsigned int ix = child_index(left);
	const Key * mykey = key[ix];
	right->key_insert(*mykey, 0, left->child[left->keycount], right->child[0]);
	//cout << *left << endl;
	key[ix] = &left->key_remove(left->keycount-1);
	//cout << "right shitt finished: left = "  << *left << " right = " << *right << endl;
}

void BTreeNode::shift_left(BTreeNode * left, BTreeNode * right) {
	//cout << "left shift " << *left << " <- " << *right << " @ " << *this << endl;
	unsigned int ix = child_index(left);
	const Key * mykey = key[ix];
	left->key_insert(*mykey, left->keycount, left->child[left->keycount], right->child[0]);
	key[ix] = &right->key_remove(0);
	//cout << "left shitt finished " << *this << endl;
}

BTreeNode * BTreeNode::merge_into_left(BTreeNode * left, BTreeNode * right) {
	//cout << "merge left " << * left << ", right " << *right << " at " << * this << endl;
	unsigned int ix = child_index(left);
	const Key * mykey = key[ix];
	left->key_insert(*mykey,left->keycount,left->child[left->keycount],right->child[0]);
	for(unsigned int i = 0; i < right->keycount; ++i) {
		left->key[left->keycount] = right->key[i];
		left->child[left->keycount+1] = right->child[i+1];
		left->keycount += 1;
	}
	if (left->keycount+1 < MAX_KEYS)
		left->child[left->keycount + 1] = NULL;

	key_remove(ix);
	child[ix] = left;
	//cout << "merged at" << *this << endl;
	delete right;
	return this;
}

std::ostream & operator<<(std::ostream & out, const BTreeNode & node) {
	out << "(";
	if (node.is_leaf()) {
		for(unsigned int i = 0; i < node.keycount; ++i) {
			out << *node.key[i] << " ";
		}
	} else {
		if (node.keycount > 0) {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << *(node.child[i]) << " ";
				out << *(node.key[i]) << " ";
			}
			out << *(node.child[node.keycount]);
		} else if (node.keycount == 0 and node.child[0] != NULL) {
			out << "->" << *(node.child[0]) << " ";
		}
	}
	out << ")";
	return out;
}

void BTree::delete_node(BTreeNode * node) {
	if (node->keycount != 0) {
		if (node->child[0] != NULL)
			delete_node(node->child[0]);
		for(unsigned int i = 0; i < node->keycount; ++i)
			if (node->child[i+1] != NULL)
				delete_node(node->child[i+1]);
	}
	delete node;
}

bool BTree::has_min_keys(BTreeNode * node) const {
	if (node == root) {
		return node->keycount >= 1;
	}
	return node->keycount >= BTreeNode::MIN_KEYS;
}

bool BTree::insert(const Key & k) {
	BTreeNode * parent = NULL;
	BTreeNode * node = root;
	unsigned int ix;

	for(;;) {
		if ( node->is_full()) {
			if (node == root /* root->is_full() */) {
				root = new BTreeNode();
				root->child[0] = node;
				parent = root;
			}
			parent->split_child(node);
			node = parent;
		}
		ix = node->key_index(k);
		//cout << *node << ", " << ix << endl;
		if (node->is_leaf()) {
			node->key_insert(k, ix);
			break;
		}
		parent = node;
		node = node->child[ix];
	}
	++count;
	return true;
}

vector<std::pair<BTreeNode *,unsigned int>> BTree::find_leaf(const Key & k) {
	BTreeNode * node = root;
	std::pair<BTreeNode *,unsigned int> lowestpt = {NULL,0}; // lowest node having k
	std::vector<std::pair<BTreeNode *,unsigned int>> path;
	unsigned int ix;
	for(;;) {
		ix = node->key_index(k);
		path.push_back(std::pair<BTreeNode *,unsigned int>(node, ix));
		if (ix < node->keycount and *node->key[ix] == k) {
			lowestpt = {node, ix};
		}
		if (node->is_leaf())
			break;
		node = node->child[ix];
	}
	if ( lowestpt.first == NULL ) {
		// the key not found.
		path.clear();
		return path;
	} else if ( ! lowestpt.first->is_leaf() ) {
		BTreeNode * subst = path.back().first;
		const Key *substkey = subst->key[subst->keycount-1]; // the predecessor
		subst->key[subst->keycount-1] = lowestpt.first->key[lowestpt.second];
		lowestpt.first->key[lowestpt.second] = substkey;
	}
	return path;
}

bool BTree::remove(const Key & k) {
	BTreeNode * parent;
	BTreeNode * node;
	unsigned int ix;
	std::vector<std::pair<BTreeNode *,unsigned int>> path = find_leaf(k);
	if (path.empty())
		return false;
	node = path.back().first;
	ix = path.back().second;
	path.pop_back();
	parent = path.empty() ? NULL : path.back().first;
	if (ix >= node->keycount)
		ix = node->keycount - 1;
	node->key_remove(ix);
	if ( has_min_keys(node) ) {
		--count;
		return true;
	} else if (node == root) {
		// parent == NULL so cannot enter the loop below
		--count;
		return true;
	}

	BTreeNode * leftsib;
	BTreeNode * rightsib;
	for(;;) {
		/*
		if (node != NULL and parent != NULL) {
			cout << "node = " << *node << endl;
			cout << "parent = " << *parent << endl;
			cout << "root = " << *root << endl;
		}
		*/
		leftsib = parent->left_sibling_of(node);
		rightsib = parent->right_sibling_of(node);
		if (leftsib != NULL and leftsib->keycount > BTreeNode::MIN_KEYS) {
			parent->shift_right(leftsib, node);
		} else if (rightsib != NULL and rightsib->keycount > BTreeNode::MIN_KEYS) {
			parent->shift_left(node, rightsib);
		} else { //if (parent->keycount > parent->MIN_KEYS or (parent == root and parent->keycount > 1) ) {
			if (leftsib != NULL) {
				parent->merge_into_left(leftsib, node);
				node = leftsib;
			} else if (rightsib != NULL) {
				parent->merge_into_left(node, rightsib);
			}
			//if (node != NULL and parent != NULL)
			//	cout << "after merge: node = " << *node << ", parent = " << *parent << endl;
		}
		if ( has_min_keys(parent) )
			break;
		if (parent == root) {
			//cout << "skip root." << endl;
			root = node;
			delete parent;
			break;
		}
		node = parent;
		path.pop_back();
		parent = path.back().first;
		ix = path.back().second;
	}
	--count;
	return true;
}


std::ostream & operator<<(std::ostream & out, const BTree & tree) {
	out << "BTree";
	if ( ! tree.root->is_empty() ) {
		out << *tree.root;
	} else {
		out << "( )";
	}
	return out;
}
