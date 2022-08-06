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
	}

	BTreeNode(const BTreeNode * node, const unsigned int & from, const unsigned int & to) : keycount(0) {
		unsigned int src, dst;
		for(src = from, dst = 0; from < to and src < node->keycount; ++src, ++dst) {
			key[dst] = node->key[src];
			child[dst] = node->child[src];
		}
		child[dst] = node->child[src];
		keycount = dst;
	}

	~BTreeNode() {
		//cout << "going to be deleted!" << endl;
		if (is_leaf())
			return;
		for(unsigned int i = 0; i < keycount + 1; ++i) {
			delete child[i];
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
		if ( ix > keycount )
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
/*
	unsigned int node_index() const {
		unsigned int ix;
		for(ix = 0; ix < parent->keycount; ++ix)
			if (this == parent->childptr[ix])
				break;
		return ix;
	}
*/
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
		//cout << *this << endl;
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
		return k;
	}

	/*
	pair<BTreeNode *,unsigned int> find_to_insert(const Key & k) {
		unsigned int ix;
		BTreeNode * par = this;
		BTreeNode * node = NULL;
		for( ; ; ) {
			cout << *node << endl;
			ix = par->key_index(k);
			node = par->child[ix];
			if ( node->is_full() ) {
				if (par->keycount == 0) { // node is the root
					BTreeNode * newroot = new BTreeNode();
					newroot->child[0] = node;
					par->child[0] = newroot;
				}
				par->split_child(node);
				cout << *par << endl;
				continue;
			}


		}
		//cout << *par << endl;
		return pair<BTreeNode*,unsigned int>(par,ix);
	}
	*/
	/*
	BTreeNode * insert(const Key & k) {
		if ( is_stub() and child[0] == NULL ) {
			child[0] = new BTreeNode(k);
			return child[0];
		}
		pair<BTreeNode *, unsigned int> p = root()->find_and_split(k);
		BTreeNode * node = p.first;
		const unsigned int ix = p.second;
		node->key_insert(k, ix);
		return node;
	}
	*/
/*
	BTreeNode * merge_into_root() {
		BTreeNode * left = child[0];
		BTreeNode * right = child[1];
		cout << *this << endl;
		for(unsigned int i = 0; i < left->keycount; ++i) {
			if (left->child[i] != NULL)
				left->child[i]->parent = this;
			if (left->child[i+1] != NULL)
				left->child[i+1]->parent = this;
			key_insert(*left->key[i], left->child[i], left->child[i+1]);
		}
		cout << *this << endl;
		for(unsigned int i = 0; i < right->keycount; ++i) {
			if (right->child[i] != NULL)
				right->child[i]->parent = this;
			if (right->child[i+1] != NULL)
				right->child[i+1]->parent = this;
			key_insert(*right->key[i], right->child[i], right->child[i+1]);
		}
		cout << *this << endl;
		return this;
	}

	BTreeNode * shift_or_merge() {
		unsigned int myix = node_index();
		BTreeNode * ls, * rs;
		if (myix == 0) {
			ls = NULL;
			rs = parent->child[myix+1];
		} else if (myix == parent->keycount) {
			ls = parent->child[myix-1];
			rs = NULL;
		} else {
			ls = parent->child[myix-1];
			rs = parent->child[myix+1];
		}
		cout << *this << endl;
		if (ls != NULL and ls->keycount > MIN_KEYS ) {
			// shift from left to right
			cout << "shift right" << endl;
			BTreeNode * ls_rightmost = ls->child[ls->keycount];
			const Key & lskey = ls->key_remove(ls->keycount - 1);
			key_insert(*(parent->key[myix-1]),0,ls_rightmost,child[0]);
			parent->key[myix-1] = &lskey;
		} else if (rs != NULL and rs->keycount > MIN_KEYS ) {
			// shift from right to left
			cout << "shift left " << endl;
			BTreeNode * rs_leftmost = rs->child[0];
			const Key & rskey = rs->key_remove(0);
			key_insert(*(parent->key[myix]), keycount, child[keycount], rs_leftmost);
			//cout << *node << endl;
			parent->key[myix] = &rskey;
			//cout << *node->parent << endl;
		} else if (ls != NULL and ls->keycount == MIN_KEYS) {
			cout << "merge with left " << *ls << ", " << this << endl;
			ls->key_insert(*(parent->key[myix-1]), ls->keycount, ls->child[ls->keycount], NULL);
			for(unsigned int i = 0; i < keycount; ++i) {
				ls->key_insert(*key[i], ls->keycount,child[i], NULL);
			}
			ls->child[ls->keycount] = child[keycount];
			parent->key_remove(myix-1);
			parent->child[myix-1] = ls;
			// ls is finished.
			cout << *ls << parent << this << endl;
		} else if (rs != NULL and rs->keycount == MIN_KEYS) {
			cout << "merge with right" << *rs << endl;
			key_insert(*(parent->key[myix]), keycount, child[keycount], NULL);
			for(unsigned int i = 0; i < rs->keycount; ++i) {
				key_insert(*(rs->key[i]), keycount, rs->child[i], NULL);
			}
			child[keycount] = rs->child[rs->keycount];
			parent->key_remove(myix);
			parent->child[myix] = this;
		}
		cout << *this << endl;
		return this;
	}

	pair<BTreeNode *,unsigned int> find(const Key & k) {
		BTreeNode * node = this;
		unsigned int ix = 0;
		for (; node != NULL; ) {
			ix = node->key_index(k);
			cout << *node << ", index " << ix << endl;
			if ( node->is_leaf() )
				break;
			if ( ix < node->keycount and *(node->key[ix]) == k)
				break;
			node = node->child[ix];
		}
		if (node != NULL)
			cout << "found node = " << *node << endl;
		return pair<BTreeNode*,unsigned int>(node,ix);
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
			//cout << *node << endl;
			BTreeNode * subst = node->child[ix]->rightmost_leaf();
			const Key * tmpkey = subst->key[subst->keycount - 1];
			subst->key[subst->keycount - 1] = &k;
			node->key[ix] = tmpkey;
			node = subst;
			ix = subst->keycount - 1;
		}
		cout << "remove " << k << " from " << *node << endl;


		BTreeNode * lsib, * rsib;
		unsigned int cix;
		for(;;) {
			if (node->keycount > node->min_keycount()) {
				node->key_remove(ix);
				cout << " result = " << *node << endl;
				break;
			}
			if ( node->is_root() ) {
				// empty root
				BTreeNode * uqchild = node->child[0];
				for(unsigned int i = 0; i < uqchild->keycount; ++i) {
					node->child[i] = uqchild->child[i];
					node->key[i] = uqchild->key[i];
				}
				node->child[uqchild->keycount] = uqchild->child[uqchild->keycount];
				return node;
			}
			cix = node->node_index();
			lsib = node->left_sibling();
			rsib = node->right_sibling();
			if (lsib != NULL and lsib->keycount > lsib->min_keycount()) {
				node->shift_right(cix);
				node->key_remove(k);
				cout << *node->parent << endl;
				break;
			} else if (rsib != NULL and rsib->keycount > rsib->min_keycount()) {
				node->shift_left(cix);
				node->key_remove(k);
				cout << *node->parent << endl;
				break;
			} else {
				cout << * node << " " << cix << endl;
				node = node->merge(cix);
				if (node->parent->keycount >= node->parent->min_keycount() ) {
					break;
				} else {
					node = node->parent;
				}
			}
		}
		return node;
	}
*/
	void right_shift(BTreeNode * left, BTreeNode * right) {
		unsigned int ix = child_index(left);
		const Key * mykey = key[ix];
		right->key_insert(*mykey, 0, left->child[left->keycount], right->child[0]);
		key[ix] = &left->key_remove(left->keycount-1);
	}

	void left_shift(BTreeNode * left, BTreeNode * right) {
		unsigned int ix = child_index(left);
		const Key * mykey = key[ix];
		left->key_insert(*mykey, left->keycount, left->child[left->keycount], right->child[0]);
		key[ix] = &right->key_remove(0);
	}

	BTreeNode * merge(BTreeNode * left, BTreeNode * right) {
		unsigned int ix = child_index(left);
		const Key * mykey = key[ix];
		left->key_insert(*mykey,left->keycount,left->child[left->keycount],right->child[0]);
		for(unsigned int i = 0; i < right->keycount; ++i) {
			left->key[left->keycount] = right->key[i];
			left->child[left->keycount+1] = right->child[i+1];
			left->keycount += 1;
		}
		key_remove(ix);
		child[ix] = left;
		delete right;
		return this;
	}

	/*
		cout << *node << endl;
		if ( node->keycount >= node->min_keycount() )
			return node;
		// node is the starred-node.
		BTreeNode * ls, *rs;
		unsigned int myix;
		do {
			//cout << *node << endl;
			// get the siblings.
			if ( node->is_root() ){
				// whole tree is empty
				return NULL;
			}
			myix = node->child_index();
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
				cout << "shift left " << endl;
				BTreeNode * rs_leftmost = rs->child[0];
				const Key & rskey = rs->key_remove(0);
				node->key_insert(*(node->parent->key[myix]),node->keycount,node->child[node->keycount],rs_leftmost);
				//cout << *node << endl;
				node->parent->key[myix] = &rskey;
				//cout << *node->parent << endl;
				break;
			} else if (ls != NULL and ls->keycount == MIN_KEYS and node->parent->keycount > MIN_KEYS) {
				cout << "merge with left " << *ls << ", " << * node << endl;
				ls->key_insert(*(node->parent->key[myix-1]),ls->keycount,ls->child[ls->keycount],NULL);
				for(unsigned int i = 0; i < node->keycount; ++i) {
					ls->key_insert(*(node->key[i]),ls->keycount,node->child[i],NULL);
				}
				ls->child[ls->keycount] = node->child[node->keycount];
				node->parent->key_remove(myix-1);
				node->parent->child[myix-1] = ls;
				// ls is finished.
				cout << *ls << *node->parent << *node << endl;
				delete node;
				break;
			} else if (rs != NULL and rs->keycount == MIN_KEYS and node->parent->keycount > MIN_KEYS) {
				cout << "merge with right" << *rs << endl;
				node->key_insert(*(node->parent->key[myix]),node->keycount,node->child[node->keycount],NULL);
				for(unsigned int i = 0; i < rs->keycount; ++i) {
					node->key_insert(*(rs->key[i]),node->keycount,rs->child[i],NULL);
				}
				node->child[node->keycount] = rs->child[rs->keycount];
				node->parent->key_remove(myix);
				node->parent->child[myix] = node;
				delete rs;
				break;
			} else {

				break;
			}
		} while (! (node->keycount >= node->min_keycount()) );

		return node;
	}
	*/

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
		delete root;
	}

	bool insert(const Key & k) {
		BTreeNode * parent = NULL;
		BTreeNode * node = root;
		unsigned int ix;
		for(;;) {
			if ( node->is_full()) {
				if (node == root) {
					root = new BTreeNode();
					parent = root;
					parent->child[0] = node;
				}
				parent->split_child(node);
				//cout << *parent << endl;
				node = parent;
				continue;
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
		unsigned int ix;
		for(;;) {
			//cout << *node << ", " << ix << endl;
			ix = node->key_index(k);
			if (ix < node->keycount and *node->key[ix] == k) {
				lowest = node;
			}
			if (node->is_leaf())
				break;
			parent = node;
			node = node->child[ix];
		}
		if ( ! lowest->is_leaf() ) {
			unsigned int orgix = lowest->key_index(k);
			const Key *keyptr = node->key[node->keycount-1];
			node->key[node->keycount-1] = lowest->key[orgix];
			lowest->key[orgix] = keyptr;
		}
		if (node == root or node->keycount > node->MIN_KEYS) {
			node->key_remove(k);
		} else {
			//cout << "error! key shortage! " << endl;
			BTreeNode * leftsib = parent->left_sibling_of(node);
			BTreeNode * rightsib = parent->right_sibling_of(node);
			if (leftsib != NULL and leftsib->keycount > node->MIN_KEYS) {
				//cout << *parent << endl;
				parent->right_shift(leftsib, node);
				//cout << *parent << endl;
				node->key_remove(k);
			} else if (rightsib != NULL and rightsib->keycount > node->MIN_KEYS) {
				//cout << *parent << endl;
				parent->left_shift(node, rightsib);
				//cout << *parent << endl;
				node->key_remove(k);
			} else if (parent->keycount > node->MIN_KEYS or parent == root) {
				cout << *parent << endl;
				if (leftsib != NULL) {
					node->key_remove(k);
					cout << *parent << endl;
					parent->merge(leftsib, node);
					cout << *parent << endl;
				} else if (rightsib != NULL) {
					node->key_remove(k);
					cout << *parent << endl;
					parent->merge(node, rightsib);
					cout << *parent << endl;
				}
				cout << *parent << endl;
				node->key_remove(k);
			} else {
				cout << "only 2 nodes!" << endl;
				return false;
			}
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
		args.push_back(argv[i]);
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
