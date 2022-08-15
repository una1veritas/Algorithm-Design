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

BTreeNode * BTreeNode::left_sibling_of(const unsigned int & cix) {
	if ( cix == 0 or cix > keycount)
		return NULL;
	return child[cix - 1];
}

BTreeNode * BTreeNode::right_sibling_of(const unsigned int & cix) {
	if ( cix + 1 > keycount )
		return NULL;
	return child[cix + 1];
}

unsigned int BTreeNode::key_index(const Key & k) {
	unsigned int ix;
	for(ix = 0; ix < keycount; ++ix)
		if ( k <= *key[ix] )
			break;
	return ix;
}

// split at the middle
BTreeNode * BTreeNode::split_child(const unsigned int &cix) {
	BTreeNode * node = child[cix];
	//cout << *this << ", " << *node << endl;
	unsigned int midix = node->keycount/2;
	BTreeNode * rchild = new BTreeNode(node, midix+1, node->keycount);
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

const Key & BTreeNode::key_remove(const unsigned int & ix) {
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

void BTreeNode::shift_to_right(const unsigned int & cix) {
	BTreeNode * left = child[cix], * right = child[cix+1];
	//cout << "right shift: left = " << *left << " right = " << *right << endl;
	const Key * mykey = key[cix];
	right->key_insert(*mykey, 0, left->child[left->keycount], right->child[0]);
	//cout << *left << endl;
	key[cix] = &left->key_remove(left->keycount-1);
	//cout << "right shitt finished: left = "  << *left << " right = " << *right << endl;
}

void BTreeNode::shift_to_left(const unsigned int & cix) {
	BTreeNode * left = child[cix], * right = child[cix+1];
	//cout << "left shift " << *left << " <- " << *right << " @ " << *this << endl;
	const Key * mykey = key[cix];
	left->key_insert(*mykey, left->keycount, left->child[left->keycount], right->child[0]);
	key[cix] = &right->key_remove(0);
	//cout << "left shitt finished " << *this << endl;
}

BTreeNode * BTreeNode::merge_into_left(const unsigned int & cix) {
	BTreeNode * left = child[cix], * right = child[cix+1];
	//cout << "merge left " << * left << ", right " << *right << " at " << * this << endl;
	const Key * mykey = key[cix];
	left->key_insert(*mykey,left->keycount,left->child[left->keycount],right->child[0]);
	for(unsigned int i = 0; i < right->keycount; ++i) {
		left->key[left->keycount] = right->key[i];
		left->child[left->keycount+1] = right->child[i+1];
		left->keycount += 1;
	}
	if (left->keycount+1 < MAX_KEYS)
		left->child[left->keycount + 1] = NULL;

	key_remove(cix);
	child[cix] = left;
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

const Key * BTree::find(const Key & k) const {
	BTreeNode * node = root;
	unsigned int ix;
	for(;node != NULL;) {
		ix = node->key_index(k);
		if (k == *node->key[ix])
			return node->key[ix];
		node = node->child[ix];
	}
	return NULL;
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
			parent->split_child(parent->child_index(node));
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

vector<BTreeNode *> BTree::remove_in_leaf(const Key & k) {
	BTreeNode * node = root;
	std::pair<BTreeNode *,unsigned int> lowestpt = {NULL,0}; // lowest node having k
	std::vector<BTreeNode *> path;
	unsigned int ix;
	for(;;) {
		ix = node->key_index(k);
		path.push_back(node);
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
		const Key * the_key = lowestpt.first->key[lowestpt.second];
		ix = node->keycount - 1;
		lowestpt.first->key[lowestpt.second] = node->key[ix]; // substitute predecessor
		node->key[ix] = the_key;
	}
	node->key_remove(ix);
	return path;
}

bool BTree::remove(const Key & k) {
	BTreeNode * parent;
	BTreeNode * node;
	unsigned int cix;
	std::vector<BTreeNode *> path = remove_in_leaf(k);
	if (path.empty())
		return false;
	node = path.back();
	if ( has_min_keys(node) ) {
		--count;
		return true;
	} else if (node == root) {
		// parent == NULL so cannot enter the loop below
		--count;
		return true;
	}

	node = path.back();
	path.pop_back();
	parent = path.back();
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
		cix = parent->child_index(node);
		leftsib = parent->left_sibling_of(cix);
		rightsib = parent->right_sibling_of(cix);
		if (leftsib != NULL and leftsib->keycount > BTreeNode::MIN_KEYS) {
			parent->shift_to_right(cix-1);
		} else if (rightsib != NULL and rightsib->keycount > BTreeNode::MIN_KEYS) {
			parent->shift_to_left(cix);
		} else { //if (parent->keycount > parent->MIN_KEYS or (parent == root and parent->keycount > 1) ) {
			if (leftsib != NULL) {
				parent->merge_into_left(cix-1);
				node = leftsib;
			} else if (rightsib != NULL) {
				parent->merge_into_left(cix);
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
		parent = path.back();
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
