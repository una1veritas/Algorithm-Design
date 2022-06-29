//============================================================================
// Name        : B-Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using std::cout;
using std::endl;

typedef std::string Key;

struct BTreeNode {
private:
	static constexpr int MINIMUM_DEGREE = 4;
	static constexpr int MIN_KEYS = MINIMUM_DEGREE - 1;
	static constexpr int MAX_KEYS = 2*MINIMUM_DEGREE - 1;

	BTreeNode * parent;
	BTreeNode * rightmost;
	struct {
		Key key;
		BTreeNode * left;
	} keychild[MAX_KEYS];
	unsigned int keycount;

public:
	BTreeNode(Key & k, BTreeNode * p = NULL) : parent(p), rightmost(NULL), keycount(0) {
		keychild[keycount].key = k;
		keychild[keycount].left = NULL;
		++keycount;
	}

	bool is_root() const {
		return parent == NULL;
	}

	BTreeNode * insert(Key & k) {
		return NULL;
	}

	BTreeNode * find(Key & k) {
		unsigned int ix;
		BTreeNode * current = this;
		BTreeNode * prev = this->parent;
		for(;current != NULL;) {
			for(ix = 0; ix < keycount; ++ix) {
				if (keychild[ix].key >= k)
					break;
			}
			if (keychild[ix].key == k) {
				return current;
			}
			prev = current;
			if (ix == keycount)
				current = rightmost;
			else
				current = keychild[ix].left;
		}
		return current;
	}
};

struct BTree {
private:
	BTreeNode * root;

public:
	BTree(void) : root(NULL) { }

	BTreeNode * insert(Key & k) {
		if (root == NULL) {
			return root = new BTreeNode(k);
		}
		root->find_parent(k);
		return root->insert(k);
	}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
