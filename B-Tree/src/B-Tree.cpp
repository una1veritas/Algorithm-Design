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

	bool is_minimum() const {
		if (is_root())
			return keycount <= 1;
		return keycount <= MIN_KEYS;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		return rightmost == NULL;
	}

	BTreeNode * left_sibling(unsigned int ix) {
		if ( is_root() )
			return NULL;
		if (ix == 0) {
			return NULL;
		}
		return parent->keychild[ix-1].left;
	}

	BTreeNode * right_sibling(unsigned int ix) {
		if ( is_root() )
			return NULL;
		if (ix >= parent->keycount)
			return NULL;
		if (ix == parent->keycount - 1)
			return parent->rightmost;
		return parent->keychild[ix+1].left;
	}

	unsigned int find_key_index(const Key & k) {
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
		cout << "after split parent = " << *parent << endl;
		cout << "left child " << *parent->keychild[0].left << " parent " << *(parent->keychild[0].left->parent) << endl;
		return parent;
	}

	BTreeNode * insert_key(Key & k, BTreeNode * left = NULL, BTreeNode * right = NULL) {
		return insert_key(find_key_index(k), k, left, right);
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

	BTreeNode * remove_key(unsigned int ix) {
		if (keycount <= ix) {
			cout << "error: key position out of range " << endl;
			return NULL;
		}
		for(unsigned int i = ix; i < keycount; ++i) {
			keychild[i] = keychild[i+1];
		}
		--keycount;
		return this;
	}

	pair<BTreeNode *,unsigned int> find_to_insert(Key & k) {
		unsigned int ix;
		BTreeNode * cur = this;
		BTreeNode * par = this->parent;
		for( ;cur != NULL; ) {
			if ( cur != NULL and cur->is_full() ) {
				cur = cur->split();
			}
			par = cur;
			ix = cur->find_key_index(k);
			if (ix == cur->keycount) {
				cur = cur->rightmost;
			} else {
				if (cur->keychild[ix].key == k and cur->is_leaf()) {
					cout << *cur << endl;
					return pair<BTreeNode*,unsigned int>(cur,ix);
				}
				cur = cur->keychild[ix].left;
			}
		}
		cout << *par << endl;
		return pair<BTreeNode*,unsigned int>(par,ix);
	}

	pair<BTreeNode *,unsigned int> find_to_remove(Key & k) {
		BTreeNode * cur = this;
		unsigned int ix = 0;
		for (; cur != NULL; ) {
			ix = cur->find_key_index(k);
			if (cur->keychild[ix].key == k) {
				break;
			}
			if ( cur->is_leaf() )
				break;
			if (ix == cur->keycount) {
				cur = cur->rightmost;
			} else {
				if (cur->keychild[ix].key == k) {
					break;
				}
				cur = cur->keychild[ix].left;
			}
		}
		return pair<BTreeNode*,unsigned int>(cur,ix);
	}

	BTreeNode * remove(Key & k, unsigned int ix) {
		cout << *this << endl;
		if (ix >= keycount) {
			cout << "no key found. " << endl;
			return NULL;
		}
		if ( is_leaf() ) {
			if ( is_minimum() ) {
				cout << "remove key from a leaf with the min number of keys." << endl;
				BTreeNode * par = parent;
				unsigned int pix = par->find_key_index(k);
				BTreeNode * sleft = left_sibling(pix);
				BTreeNode * sright = right_sibling(pix);
				if (sleft != NULL)
					cout << *sleft << endl;
				if (sright != NULL)
					cout << *sright << endl;
				if (sleft != NULL and ! sleft->is_minimum() ) {
					// rotate right
					cout << "rotate right" << endl;
					insert_key(0,par->keychild[pix-1].key);
					par->keychild[pix-1].key = sleft->keychild[sleft->keycount - 1].key;
					sleft->remove_key(sleft->keycount - 1);
				} else if (sright != NULL and ! sright->is_minimum() ) {
					// rotate left
					cout << "rotate left" << endl;
					insert_key(sright->keycount,par->keychild[pix].key);
					par->keychild[pix].key = sright->keychild[0].key;
					sright->remove_key(0);
					remove_key(keycount - 1);
				} else if (sright == NULL and sleft->is_minimum()) {
					for(unsigned int i = 0; i < sleft->keycount; ++i) {
						insert_key(sleft->keychild[i].key);
					}
					delete sleft;
					insert_key(par->keychild[pix-1].key);
					par->remove_key(pix-1);
					par->rightmost = this;
				} else if (sleft == NULL and sright->is_minimum()) {
					cout << "sright = " << *sright << endl;
					for(unsigned int i = 0; i < sright->keycount; ++i) {
						insert_key(sright->keychild[i].key);
					}
					delete sright;
					insert_key(par->keychild[0].key);
					par->remove_key(0);
					par->keychild[0].left = this;
				} else {
					cout << "still not working." << endl;
				}
				return this;
			}
			cout << "remove key from a leaf with plenty of keys." << endl;
			remove_key(ix);
			return NULL;

		}
		return NULL;
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
		pair<BTreeNode *, unsigned int> p = root()->find_to_insert(k);
		BTreeNode * node = p.first;
		return node->insert_key(p.second, k);
	}

	BTreeNode * remove(Key & k) {
		pair<BTreeNode *, unsigned int> p = root()->find_to_remove(k);
		cout << "remove key " << k;
		if (p.first != NULL)
			cout << " at " << *p.first;
		cout << endl;
		p.first->remove(k, p.second);
		return NULL;
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


	cout << "remove" << endl;
	string k("D");
	tree.remove(k);
	cout << tree << endl;

	return 0;
}
