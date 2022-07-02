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

typedef string Key;

struct BTreeNode {
private:
	static constexpr unsigned int MINIMUM_DEGREE = 3;
	static constexpr unsigned int MIN_KEYS = MINIMUM_DEGREE - 1;
	static constexpr unsigned int MAX_KEYS = 2*MINIMUM_DEGREE - 1;

	BTreeNode * parent;
	BTreeNode * rightmost;
	struct {
		Key key;
		BTreeNode * left;
	} keychild[MAX_KEYS];
	unsigned int keycount;

public:
	BTreeNode(Key & k, BTreeNode * p = NULL, BTreeNode * l = NULL, BTreeNode * r = NULL)
	: parent(p), rightmost(NULL), keycount(0) {
		keychild[keycount].key = k;
		keychild[keycount].left = l;
		++keycount;
	}

	// constructor for a sibling
	BTreeNode(BTreeNode * nodeptr, unsigned int bix, unsigned int eix, BTreeNode * par = NULL)
	: parent(par), keycount(0) {
		unsigned int srcix, dstix;
		for(srcix = bix, dstix = 0; srcix < eix; ++srcix, ++dstix) {
			keychild[dstix] = nodeptr->keychild[srcix];
			++keycount;
		}
		if (eix == nodeptr->keycount) {
			rightmost = nodeptr->rightmost;
		} else {
			rightmost = nodeptr->keychild[eix].left;
		}
	}

	~BTreeNode() {
		if (is_leaf())
			return;
		for(unsigned int ix = 0; ix < keycount; ++ix) {
			delete keychild[ix].left;
		}
		delete rightmost;
	}

	bool is_full() const {
		return !(keycount < MAX_KEYS);
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		return rightmost == NULL;
	}

	unsigned int find_index(const Key & k) {
		unsigned int ix;
		for(ix = 0; ix < keycount; ++ix) {
			if (keychild[ix].key >= k)
				break;
		}
		return ix;
	}

	BTreeNode * split() {
		//cout << *this << endl;
		unsigned int midix = this->keycount/2;
		if (is_root()) {
			//cout << "splitting root " << endl;
			BTreeNode * lc = new BTreeNode(this, 0, midix, this);
			BTreeNode * rc = new BTreeNode(this,midix+1, keycount, this);
			//cout << *lc << " : " << *rc << endl;
			keychild[0].key = keychild[midix].key;
			keychild[0].left = lc;
			keycount = 1;
			rightmost = rc;
			//cout << *this << endl;
			return this;
		}
		//cout << "splitting non-root " << endl;
		BTreeNode * rs = new BTreeNode(this, midix+1, keycount, parent);
		parent->insert_key(keychild[midix].key, this, rs);
		rightmost = keychild[midix].left;
		keycount = midix;
		//cout << *parent << endl;
		return parent;
	}

	BTreeNode * insert_key(Key & k, BTreeNode * left = NULL, BTreeNode * right = NULL) {
		return insert_key(find_index(k), k, left, right);
	}

	BTreeNode * insert_key(const unsigned int & ix, Key & k, BTreeNode * left = NULL, BTreeNode * right = NULL) {
		if (is_full()) {
			cout << "error: node is full!" << endl;
			return NULL;
		}
		for(unsigned int i = keycount; i > ix; --i) {
			keychild[i] = keychild[i-1];
		}
		keychild[ix].key = k;
		if (ix < keycount) {
			keychild[ix].left = left;
			keychild[ix+1].left = right;
		} else {
			keychild[ix].left = left;
			rightmost = right;
		}
		keycount += 1;
		return this;
	}

	pair<BTreeNode *,unsigned int> find_leaf(Key & k) {
		unsigned int ix;
		BTreeNode * cur = this;
		BTreeNode * par = this->parent;
		for( ;cur != NULL; ) {
			if ( cur != NULL and cur->is_full() ) {
				//cout << *cur << " must be splitted." << endl;
				cur = cur->split();
			}
			for(ix = 0; ix < cur->keycount; ++ix) {
				if (cur->keychild[ix].key >= k)
					break;
			}
			if (cur->keychild[ix].key == k and cur->is_leaf()) {
				//cout << "Here!" << endl;
				return pair<BTreeNode*,unsigned int>(cur,ix);
			}
			par = cur;
			if (ix == cur->keycount)
				cur = cur->rightmost;
			else
				cur = cur->keychild[ix].left;
		}
		//cout << "There." << endl;
		return pair<BTreeNode*,unsigned int>(par,ix);
	}

	friend std::ostream & operator<<(std::ostream & out, const BTreeNode & node) {
		out << "(";
		if (node.is_leaf()) {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << node.keychild[i].key << " ";
			}
		} else {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << *(node.keychild[i].left) << " ";
				out << node.keychild[i].key << " ";
			}
			out << *node.rightmost;
		}
		out << ") ";
		return out;
	}

	friend struct BTree;
};

struct BTree {
private:
	BTreeNode * stub;

public:
	BTree(void) : stub(NULL) { }

	BTreeNode * root() {
		return stub;
	}

	const BTreeNode * root() const {
		return stub;
	}

	BTreeNode * root(BTreeNode * nodeptr) {
		return stub = nodeptr;
	}

	BTreeNode * insert(Key & k) {
		if (root() == NULL) {
			return root(new BTreeNode(k));
		}
		pair<BTreeNode *,unsigned int> p = root()->find_leaf(k);
		BTreeNode * node = p.first;
		return node->insert_key(p.second, k);
	}

	friend std::ostream & operator<<(std::ostream & out, const BTree & tree) {
		out << "BTree";
		out << *(tree.root());
		return out;
	}
};

int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	std::vector<string> args;
	for(int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	BTree tree;

	for(auto str : args) {
		cout << str << endl;
		tree.insert(str);
		cout << tree << endl << endl;
	}
	return 0;
}
