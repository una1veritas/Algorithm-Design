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

	BTreeNode * parent;
	const Key * key[MAX_KEYS];
	BTreeNode * child[MAX_KEYS+1];
	unsigned int keycount;

public:
	BTreeNode(void) : parent(NULL), keycount(0) {
		key[0] = NULL;
		child[0] = NULL;
	}

	BTreeNode(const Key & k, BTreeNode * p = NULL, BTreeNode * l = NULL, BTreeNode * r = NULL)
	: parent(p), keycount(1) {
		key[0] = &k;
		child[0] = l;
		child[1] = r;
	}

	// constructor for a sibling
	BTreeNode(BTreeNode * node, unsigned int bix, unsigned int eix, BTreeNode * par = NULL)
	: parent(par) {
		unsigned int srcix, dstix;
		keycount = 0;
		for(srcix = bix, dstix = 0; srcix < eix; ++srcix, ++dstix) {
			key[dstix] = node->key[srcix];
			child[dstix] = node->child[srcix];
			++keycount;
		}
		child[dstix] = node->child[srcix];
	}

	~BTreeNode() {
		if (is_leaf())
			return;
		for(unsigned int i = 0; i < keycount + 1; ++i) {
			delete child[i];
		}
	}

	bool is_full() const {
		return keycount >= MAX_KEYS;
	}

	bool is_root() const {
		return parent->parent == NULL;
	}

	bool is_leaf() const {
		return keycount > 0 and child[0] == NULL;
	}

	unsigned int min_keycount() const {
		if (is_root())
			return 1;
		return MIN_KEYS;
	}

	BTreeNode * left_sibling() {
		if ( is_root() )
			return NULL;
		unsigned int ix;
		for(ix = 0; ix < parent->keycount + 1; ++ix)
			if (this == parent->child[ix])
				break;
		if ( ix == 0 or ix == parent->keycount + 2)
			return NULL;
		return parent->child[ix - 1];
	}

	BTreeNode * right_sibling() {
		if ( is_root() )
			return NULL;
		unsigned int ix;
		for(ix = 0; ix < parent->keycount + 1; ++ix)
			if (this == parent->child[ix])
				break;
		if ( ix > parent->keycount )
			return NULL;
		return parent->child[ix + 1];
	}

	unsigned int key_index(const Key & k) {
		unsigned int ix;
		for(ix = 0; ix < keycount; ++ix)
			if ( *key[ix] >= k)
				break;
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
			key[0] = key[midix];
			child[0] = lc;
			keycount = 1;
			child[keycount] = rc;
			//cout << *this << endl;
			return this;
		}
		//cout << "splitting non-root " << endl;
		BTreeNode * rs = new BTreeNode(this, midix+1, keycount, parent);
		parent->key_insert(*key[midix], this, rs);
		keycount = midix;
		//cout << "after split parent = " << *parent << endl;
		//cout << "left child " << *parent->keychild[0].left << " parent " << *(parent->keychild[0].left->parent) << endl;
		return parent;
	}

	unsigned int child_index(const BTreeNode * a_child) const {
		unsigned int ix;
		for(ix = 0; ix < keycount; ++ix)
			if (a_child == child[ix])
				break;
		return ix;
	}

	const Key & key_insert(const Key & k, BTreeNode * left = NULL, BTreeNode * right = NULL) {
		return key_insert(k, key_index(k), left, right);
	}

	const Key & key_insert(const Key & k, const unsigned int & ix, BTreeNode * left = NULL, BTreeNode * right = NULL) {
		if (is_full()) {
			cout << "error: node is full!" << endl;
		}
		for(unsigned int i = keycount; i > ix; --i) {
			key[i] = key[i-1];
			child[i+1] = child[i];
		}
		key[ix] = &k;
		child[ix] = left;
		child[ix+1] = right;
		++keycount;
		return *key[ix];
	}

	const Key & key_remove(unsigned int ix) {
		if (keycount <= ix) {
			cout << "error: key position out of range " << endl;
		}
		unsigned int i;
		const Key & k = *key[ix];
		for(i = ix; i < keycount; ++i) {
			key[i] = key[i+1];
			child[i] = child[i+1];
		}
		child[i] = child[i+1];
		--keycount;
		return k;
	}

	pair<BTreeNode *,unsigned int> find_and_split(const Key & k) {
		unsigned int ix;
		BTreeNode * cur = this;
		BTreeNode * par = this->parent;
		for( ;cur != NULL; ) {
			if ( cur != NULL and cur->is_full() ) {
				cur = cur->split();
			}
			par = cur;
			ix = cur->key_index(k);
			if (ix < cur->keycount and cur->is_leaf()) {
				//cout << *cur << endl;
				return pair<BTreeNode*,unsigned int>(cur,ix);
			} else {
				cur = cur->child[ix];
			}
		}
		//cout << *par << endl;
		return pair<BTreeNode*,unsigned int>(par,ix);
	}

	pair<BTreeNode *,unsigned int> find(const Key & k) {
		BTreeNode * cur = this;
		unsigned int ix = 0;
		for (; cur != NULL; ) {
			//cout << "cur = " << *cur << endl;
			ix = cur->key_index(k);
			//cout << "index " << ix << endl;
			if ( cur->is_leaf() )
				break;
			if ( *(cur->key[ix]) == k)
				break;
			//cout << *(cur->child[ix]) << endl;
			cur = cur->child[ix];
		}
		//cout << "exit find: cur = " << *cur << endl;
		return pair<BTreeNode*,unsigned int>(cur,ix);
	}

	BTreeNode * rightmost_leaf() {
		BTreeNode * node = this;
		for(; !node->is_leaf(); ) {
			node = node->child[node->keycount];
		}
		return node;
	}

	BTreeNode * remove(const Key & k, unsigned int ix) {
		BTreeNode * node = this;
		if (! is_leaf() ) {
			cout << *node << endl;
			BTreeNode * subst = child[ix]->rightmost_leaf();
			const Key * subkey = subst->key[subst->keycount - 1];
			subst->key[subst->keycount - 1] = &k;
			key[ix] = subkey;
			node = subst;
			ix = subst->keycount - 1;
		}
		cout << "remove from node = " << *node << endl;
		node->key_remove(ix);
		//cout << *this << endl;
		if ( node->keycount >= node->min_keycount() )
			return node;
		// node is a starred node.
		BTreeNode * ls, *rs;
		unsigned int myix;
		do {
			cout << *node << endl;
			// get the siblings.
			myix = node->parent->child_index(this);
			if (myix == 0) {
				ls = NULL;
				rs = node->parent->child[myix+1];
			} else if (myix == node->parent->keycount) {
				ls = node->parent->child[myix-1];
				rs = NULL;
			} else {
				ls = node->parent->child[myix-1];
				rs = node->parent->child[myix+1];
			}
			cout << "node->parent = " << *(node->parent) << endl;
			if (ls != NULL and ls->keycount > MIN_KEYS ) {
				// shift from left to right
				cout << "shift right" << endl;
				BTreeNode * ls_rightmost = ls->child[ls->keycount];
				const Key & lskey = ls->key_remove(ls->keycount - 1);
				node->key_insert(*(node->parent->key[myix-1]),0,ls_rightmost,node->child[0]);
				node->parent->key[myix-1] = &lskey;
				break;
			} else if (rs != NULL and rs->keycount > MIN_KEYS ) {
				// shift from right to left
				cout << "shift left" << endl;
				BTreeNode * rs_leftmost = rs->child[0];
				const Key & rskey = rs->key_remove(0);
				node->key_insert(*(node->parent->key[myix]),node->parent->keycount,node->child[node->keycount],rs_leftmost);
				node->parent->key[myix] = &rskey;
				break;
			} else if (ls != NULL and ls->keycount == MIN_KEYS ) {
				cout << "merge with left" << endl;
				ls->key_insert(*(node->parent->key[myix-1]),ls->keycount,ls->child[ls->keycount],NULL);
				for(unsigned int i = 0; i < node->keycount; ++i) {
					ls->key_insert(*(node->key[i]),ls->keycount,node->child[i],NULL);
				}
				ls->child[ls->keycount] = node->child[node->keycount];
				node->parent->key_remove(myix-1);
				node->parent->child[myix-1] = ls;
				delete node;
				node = node->parent;
				break;
			} else if (rs != NULL and rs->keycount == MIN_KEYS) {
				cout << "merge with right" << endl;
				node->key_insert(*(node->parent->key[myix]),node->keycount,node->child[node->keycount],NULL);
				for(unsigned int i = 0; i < rs->keycount; ++i) {
					node->key_insert(*(rs->key[i]),node->keycount,rs->child[i],NULL);
				}
				node->child[node->keycount] = rs->child[rs->keycount];
				node->parent->key_remove(myix);
				node->parent->child[myix] = node;
				delete rs;
				node = node->parent;
				break;
			} else if ( node->is_root() ){
				// reached to the root
				node = node->parent;
				delete node->child[0];
				node->child[0] = NULL;
				break;
			}
		} while (! (node->keycount >= node->min_keycount()) );

		return node;
	}

	friend std::ostream & operator<<(std::ostream & out, const BTreeNode & node) {
		out << "(";
		if (node.is_leaf()) {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << *node.key[i] << " ";
			}
		} else {
			for(unsigned int i = 0; i < node.keycount; ++i) {
				out << *(node.child[i]) << " ";
				out << *(node.key[i]) << " ";
			}
			out << *(node.child[node.keycount]);
		}
		out << ") ";
		return out;
	}

	friend struct BTree;
};

struct BTree {
private:
	BTreeNode stub;

public:
	BTree(void) : stub() { }

	BTreeNode * root() {
		return stub.child[0];
	}

	const BTreeNode * root() const {
		return stub.child[0];
	}

	BTreeNode * insert(const Key & k) {
		if (root() == NULL) {
			stub.child[0] = new BTreeNode(k, &stub);
			return stub.child[0];
		}
		pair<BTreeNode *, unsigned int> p = root()->find_and_split(k);
		BTreeNode * node = p.first;
		const unsigned int ix = p.second;
		node->key_insert(k, ix);
		return node;
	}

	BTreeNode * remove(const Key & k) {
		pair<BTreeNode *, unsigned int> p = root()->find(k);
		if (p.first != NULL and *(p.first->key[p.second]) != k) {
			cout << k << ": no such key, can't remove." << endl;
			return NULL;
		}
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

	for(auto & s : args) {
		cout << s << endl;
		tree.insert(s);
		cout << tree << endl << endl;
	}

	string k;
	k = "29";
	cout << "remove " << k << endl;
	tree.remove(k);
	cout << tree << endl << endl;

	k = "43";
	cout << "remove " << k << endl;
	tree.remove(k);
	cout << tree << endl << endl;

	k = "33";
	cout << "remove " << k << endl;
	tree.remove(k);
	cout << tree << endl << endl;

	k = "76";
	cout << "remove " << k << endl;
	tree.remove(k);
	cout << tree << endl << endl;

	return 0;
}
