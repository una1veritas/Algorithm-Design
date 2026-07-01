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
		data[i] = node.data[i];
		child[i] = node.child[i];
	}
	child[keycount] = node.child[keycount];
}

BTreeNode::BTreeNode(const Data & k, BTreeNode * l, BTreeNode * r) : keycount(1) {
	data[0] = k;
	child[0] = l;
	child[1] = r;
	if (keycount+1 < MAX_DATA_NUMBER)
		child[keycount + 1] = NULL;
}

BTreeNode::BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to) : keycount(0) {
	unsigned int src, dst;
	for(src = from, dst = 0; from < to and src < node->keycount; ++src, ++dst) {
		data[dst] = node->data[src];
		child[dst] = node->child[src];
	}
	child[dst] = node->child[src];
	keycount = dst;
	if (keycount+1 < MAX_DATA_NUMBER)
		child[keycount + 1] = NULL;
}

void BTreeNode::clear() {
	for(unsigned int i = 0; i < keycount + 1; ++i) {
		child[i] = NULL;
	}
}

bool BTreeNode::is_full() const {
	return keycount >= MAX_DATA_NUMBER;
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

unsigned int BTreeNode::key_index(const Data & k) {
	unsigned int ix;
	for(ix = 0; ix < keycount; ++ix)
		if ( k <= data[ix] )
			break;
	return ix;
}

// split at the middle
BTreeNode * BTreeNode::split_child(const unsigned int &cix) {
	BTreeNode * node = child[cix];
	//cout << *this << ", " << *node << endl;
	unsigned int midix = node->keycount/2;
	BTreeNode * rchild = new BTreeNode(node, midix+1, node->keycount);
	key_insert(node->data[midix], cix, node, rchild);
	node->keycount = midix;
	//cout << "after split " << *this << endl;
	return this;
}

const Data & BTreeNode::key_insert(const Data & k, const unsigned int & ix, BTreeNode * left, BTreeNode * right) {
	//cout << *this << endl;
	for(unsigned int i = keycount; i > ix; --i) {
		data[i] = data[i-1];
		child[i+1] = child[i];
	}
	data[ix] = k;
	child[ix] = left;
	child[ix+1] = right;
	++keycount;
	if (keycount < MAX_DATA_NUMBER)
		child[keycount+1] = NULL;
	return data[ix];
}

const Data & BTreeNode::key_remove(const unsigned int & ix) {
	if (ix >= keycount)
		return data[ix]; // raise error.
	unsigned int i;
	const Data & k = data[ix];
	if (ix < keycount - 1) {
		// except the right-most data and the right most child
		for(i = ix; i < keycount; ++i) {
			data[i] = data[i+1];     // data[keycount-1] = data[keycount] is redundant
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
	const Data & mykey = data[cix];
	right->key_insert(mykey, 0, left->child[left->keycount], right->child[0]);
	//cout << *left << endl;
	data[cix] = left->key_remove(left->keycount-1);
	//cout << "right shitt finished: left = "  << *left << " right = " << *right << endl;
}

void BTreeNode::shift_to_left(const unsigned int & cix) {
	BTreeNode * left = child[cix], * right = child[cix+1];
	//cout << "left shift " << *left << " <- " << *right << " @ " << *this << endl;
	const Data & mykey = data[cix];
	left->key_insert(mykey, left->keycount, left->child[left->keycount], right->child[0]);
	data[cix] =right->key_remove(0);
	//cout << "left shitt finished " << *this << endl;
}

BTreeNode * BTreeNode::merge_into_left(const unsigned int & cix) {
	BTreeNode * left = child[cix], * right = child[cix+1];
	//cout << "merge left " << * left << ", right " << *right << " at " << * this << endl;
	const Data & mykey = data[cix];
	left->key_insert(mykey,left->keycount,left->child[left->keycount],right->child[0]);
	for(unsigned int i = 0; i < right->keycount; ++i) {
		left->data[left->keycount] = right->data[i];
		left->child[left->keycount+1] = right->child[i+1];
		left->keycount += 1;
	}
	if (left->keycount+1 < MAX_DATA_NUMBER)
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
			out << node.data[i] << " ";
		}
	} else {
		if (node.keycount > 0) {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << *(node.child[i]) << " ";
				out << (node.data[i]) << " ";
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
	return node->keycount >= BTreeNode::MIN_DATA_NUMBER;
}

const Data * BTree::find(const Data & k) const {
	BTreeNode * node = root;
	unsigned int ix;
	for(;node != NULL;) {
		ix = node->key_index(k);
		if (k == node->data[ix])
			return &node->data[ix];
		node = node->child[ix];
	}
	return NULL;
}

bool BTree::insert(const Data & k) {
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

vector<BTree::NodeIndexPair> BTree::find_and_remove_in_leaf(const Data & k) {
	BTreeNode * node = root;
	unsigned int ix;
	std::vector<NodeIndexPair> path;

	if ( node == NULL )
		return path;

	ix = node->key_index(k);
	path.push_back(NodeIndexPair{node, ix}); 	// search in the root node is finished before entering loop
	NodeIndexPair found_at = {NULL, 0}; // the most tip-side node having k
	for(;;) {
		//ix = node->key_index(k);
		//path.push_back(NodeIndexPair{node,0});
		// set the last position where the k is found
		if (ix < node->keycount and node->data[ix] == k) {
			found_at = {node, ix};
		}
		if (node->is_leaf()) {
			// finally reached to the leaf
			break;
		}
		node = node->child[ix];
		ix = node->key_index(k);
		path.push_back(NodeIndexPair {node, ix}); 	// add the tip to path
	}
	if ( found_at.node == NULL ) {
		// the data not found.
		path.clear();
		return path;
	}
	if ( ! found_at.node->is_leaf() ) {
		// swap k with its predecessor in the leaf
		// const Data & the_key = found_at.node->data[found_at.index];
		// the leaf and the predecessor is (node, ix - 1) where ix == keycount,
		// since ix is the first index satisfying k < data[ix]
		ix -= 1;
		Data substdata = node->data[ix];
		node->data[ix] = found_at.node->data[found_at.index];
		found_at.node->data[found_at.index] = substdata;
	}
	node->key_remove(ix);
	return path;
}

bool BTree::remove(const Data & k) {
	BTreeNode * parent;
	BTreeNode * node;
	unsigned int cix;
	std::vector<NodeIndexPair> path = find_and_remove_in_leaf(k);
	if (path.empty())
		return false;
	node = path.back().node;
	if ( has_min_keys(node) ) {
		--count;
		return true;
	} else if (node == root) {
		// parent == NULL so cannot enter the loop below
		--count;
		return true;
	}

	node = path.back().node;
	path.pop_back();
	parent = path.back().node;
	BTreeNode * leftsib;
	BTreeNode * rightsib;
	for(;;) {
		cix = parent->child_index(node);
		leftsib = parent->left_sibling_of(cix);
		rightsib = parent->right_sibling_of(cix);
		if (leftsib != NULL and leftsib->keycount > BTreeNode::MIN_DATA_NUMBER) {
			parent->shift_to_right(cix-1);
		} else if (rightsib != NULL and rightsib->keycount > BTreeNode::MIN_DATA_NUMBER) {
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
		parent = path.back().node;
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
