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

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

typedef string Key;

struct BTreeNode {
private:
	static constexpr unsigned int MINIMUM_DEGREE = 3;
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
	BTreeNode(const BTreeNode & node) : keycount(node.keycount) {
		for(unsigned int i = 0; i < keycount; ++i) {
			key[i] = node.key[i];
			child[i] = node.child[i];
		}
		child[keycount] = node.child[keycount];
	}

	BTreeNode(const Key & k, BTreeNode * p = NULL, BTreeNode * l = NULL, BTreeNode * r = NULL) : keycount(1) {
		key[0] = &k;
		child[0] = l;
		child[1] = r;
		if (keycount+1 < MAX_KEYS)
			child[keycount + 1] = NULL;
	}

	BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to) : keycount(0) {
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

	void clear() {
		for(unsigned int i = 0; i < keycount + 1; ++i) {
			child[i] = NULL;
		}
	}

	bool is_full() const {
		return keycount >= MAX_KEYS;
	}

	bool is_empty() const {
		return keycount == 0;
	}

	bool is_leaf() const {
 		return child[0] == NULL;
	}

private:
	unsigned int child_index(const BTreeNode * node) {
		unsigned int ix;
		for(ix = 0; ix < keycount + 1; ++ix)
			if (node == child[ix])
				break;
		return ix;
	}

	BTreeNode * left_sibling_of(const BTreeNode * node) {
		unsigned int ix = child_index(node);
		if ( ix == 0 or ix > keycount)
			return NULL;
		return child[ix - 1];
	}

	BTreeNode * right_sibling_of(const BTreeNode * node) {
		unsigned int ix = child_index(node);
		if ( ix + 1 > keycount )
			return NULL;
		return child[ix + 1];
	}

	unsigned int key_index(const Key & k) {
		unsigned int ix;
		for(ix = 0; ix < keycount; ++ix)
			if ( k <= *key[ix] )
				break;
		return ix;
	}

	// split at the middle
	BTreeNode * split_child(BTreeNode * node) {
		//cout << *this << ", " << *node << endl;
		unsigned int midix = node->keycount/2;
		BTreeNode * rchild = new BTreeNode(node, midix+1, node->keycount);
		unsigned int cix = child_index(node);
		key_insert(*node->key[midix], cix, node, rchild);
		node->keycount = midix;
		//cout << "after split " << *this << endl;
		return this;
	}

	const Key & key_insert(const Key & k, const unsigned int & ix, BTreeNode * left = NULL, BTreeNode * right = NULL) {
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

	const Key & key_remove(unsigned int ix) {
		if (keycount <= ix) {
			cout << "error: key position out of range " << endl;
		}
		unsigned int i;
		const Key & k = *key[ix];
		for(i = ix; i < keycount - 1; ++i) {
			key[i] = key[i+1];
			child[i] = child[i+1];
		}
		child[i] = child[i+1];
		--keycount;
		if (keycount+1 < MAX_KEYS)
			child[keycount + 1] = NULL;
		return k;
	}


	const Key & key_remove(const Key & k) {
		unsigned int ix;
		for(ix = 0; ix < keycount; ++ix) {
			if (*key[ix] == k)
				break;
		}
		if (ix < keycount) {
			for(unsigned int i = ix; i < keycount; ++i) {
				key[i] = key[i+1];
				child[i] = child[i+1];
			}
			child[keycount] = child[keycount+1];
			--keycount;
		}
		if (keycount+1 < MAX_KEYS)
			child[keycount + 1] = NULL;
		return k;
	}

	void shift_right(BTreeNode * left, BTreeNode * right) {
		cout << "right shift " << *left << " -> " << *right << " @ " << *this << endl;
		unsigned int ix = child_index(left);
		const Key * mykey = key[ix];
		right->key_insert(*mykey, 0, left->child[left->keycount], right->child[0]);
		key[ix] = &left->key_remove(left->keycount-1);
		cout << "right shitt finished " << *this << endl;
	}

	void shift_left(BTreeNode * left, BTreeNode * right) {
		cout << "left shift " << *left << " <- " << *right << " @ " << *this << endl;
		unsigned int ix = child_index(left);
		const Key * mykey = key[ix];
		left->key_insert(*mykey, left->keycount, left->child[left->keycount], right->child[0]);
		key[ix] = &right->key_remove(0);
		cout << "left shitt finished " << *this << endl;
	}

	BTreeNode * merge_into_left(BTreeNode * left, BTreeNode * right) {
		cout << "merge left " << * left << ", right " << *right << " at " << * this << endl;
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
		cout << "merged at" << *this << endl;
		delete right;
		return this;
	}

	friend std::ostream & operator<<(std::ostream & out, const BTreeNode & node) {
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
		out << ") ";
		return out;
	}

	friend struct BTree;
};

struct BTree {
private:
	BTreeNode * root;

public:
	BTree(void) : root(new BTreeNode()) { }

	~BTree() {
		delete_node(root);
	}

	void delete_node(BTreeNode * node) {
		if (node->keycount != 0) {
			if (node->child[0] != NULL)
				delete_node(node->child[0]);
			for(unsigned int i = 0; i < node->keycount; ++i)
				if (node->child[i+1] != NULL)
					delete_node(node->child[i+1]);
		}
		delete node;
	}

	bool has_min_keys(BTreeNode * node) const {
		if (node == root) {
			return node->keycount >= 1;
		}
		return node->keycount >= BTreeNode::MIN_KEYS;
	}

	bool insert(const Key & k) {
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
		return true;
	}


	bool remove(const Key & k) {
		BTreeNode * parent = NULL;
		BTreeNode * node = root;
		BTreeNode * lowest = NULL;
		std::vector<pair<BTreeNode *,unsigned int>> stack;
		unsigned int ix;
		for(;;) {
			//cout << *node << ", " << ix << endl;
			ix = node->key_index(k);
			stack.push_back(pair<BTreeNode *,unsigned int>(node, ix));
			if (ix < node->keycount and *node->key[ix] == k) {
				lowest = node;
			}
			if (node->is_leaf())
				break;
			parent = node;
			node = node->child[ix];
		}
		stack.pop_back(); // parent and leaf node are already set
		if ( ! lowest->is_leaf() ) {
			unsigned int orgix = lowest->key_index(k);
			const Key *keyptr = node->key[node->keycount-1];
			node->key[node->keycount-1] = lowest->key[orgix];
			lowest->key[orgix] = keyptr;
		}
		node->key_remove(k);
		if ( has_min_keys(node) ) {
			return true;
		} else if (node == root) {
			// parent == NULL so cannot enter the loop below
			return true;
		}

		BTreeNode * leftsib;
		BTreeNode * rightsib;
		for(;;) {
			if (node != NULL and parent != NULL)
				cout << "node = " << *node << ", parent = " << *parent << endl;
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
			}
			if ( has_min_keys(parent) )
				break;
			if (parent == root) {
				cout << "skip root." << endl;
				root = node;
				delete parent;
				break;
			}
			node = parent;
			stack.pop_back();
			parent = stack.back().first;
			ix = stack.back().second;
		}
		return true;
	}


	friend std::ostream & operator<<(std::ostream & out, const BTree & tree) {
		out << "BTree";
		if ( ! tree.root->is_empty() ) {
			out << *tree.root;
		} else {
			out << "( )";
		}
		return out;
	}
};

int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	std::vector<string> args;
	for(int i = 1; i < argc; ++i) {
		args.push_back(std::string(argv[i]));
	}

	BTree tree;

	enum {
		INSERT = 0,
		REMOVE,
	} mode = INSERT;

	for(auto & s : args) {
		if (s == "-R") {
			mode = REMOVE;
		} else if (s == "-I") {
			mode = INSERT;
		} else {
			if (mode == INSERT) {
				cout << "insert " << s << endl;
				tree.insert(s);
			} else if (mode == REMOVE) {
				cout << "remove " << s << endl;
				if (!tree.remove(s)) {
					cout << "failed!" << endl;
				}
			}
			cout << tree << endl << endl;
		}
	}
	cout << "done." << endl;

	return 0;
}
