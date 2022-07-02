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
	BTreeNode(Key & k, BTreeNode * p = NULL) : parent(p), rightmost(NULL), keycount(0) {
		keychild[keycount].key = k;
		keychild[keycount].left = NULL;
		++keycount;
	}

	// only for the stub node
	BTreeNode(void) : parent(NULL), rightmost(NULL), keycount(0) {
		keychild[0].left = NULL;
	}

	~BTreeNode() {
		if (is_leaf())
			return;
		for(auto kc: keychild) {
			delete kc.left;
		}
		delete rightmost;
	}

	bool is_stub() const {
		return keycount == 0;
	}

	bool is_full() const {
		return !(keycount < MAX_KEYS);
	}

	bool is_root() const {
		return parent->is_stub();
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
		cout << *this << endl;
		unsigned int mid = this->keycount/2;
		BTreeNode * sibling = new BTreeNode();
		sibling->parent = this->parent;
		for(unsigned int ix = mid+1; ix < this->keycount; ++ix) {
			sibling->insert_key(keychild[ix].key,keychild[ix].left);
		}
		cout << *sibling << endl;
		BTreeNode * midleftchild = keychild[mid].left;
		keycount = mid;
		rightmost = midleftchild;
		sibling->rightmost = rightmost;
		cout << *this << endl;
		if (is_root()) {
			BTreeNode * stub = parent;
			BTreeNode * newroot = new BTreeNode(keychild[mid].key, stub);
			newroot->keychild[0].left = this;
			newroot->rightmost = sibling;
			newroot->keycount = 1;
			parent = newroot;
			sibling->parent = newroot;
		} else {
			parent->insert_key(keychild[mid].key, this, sibling);
		}
		cout << *parent << endl;
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

	pair<BTreeNode *,unsigned int> find_and_split(Key & k) {
		unsigned int ix;
		BTreeNode * cur = this;
		BTreeNode * par = this->parent;
		for( ;cur != NULL; ) {
			if ( cur != NULL and cur->is_full() ) {
				cout << *cur << " must be splitted." << endl;
				cur = cur->split();
			}
			for(ix = 0; ix < cur->keycount; ++ix) {
				if (cur->keychild[ix].key >= k)
					break;
			}
			if (cur->keychild[ix].key == k and cur->is_leaf()) {
				cout << "Here!" << endl;
				return pair<BTreeNode*,unsigned int>(cur,ix);
			}
			par = cur;
			if (ix == cur->keycount)
				cur = cur->rightmost;
			else
				cur = cur->keychild[ix].left;
		}
		cout << "There." << endl;
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
		return stub.rightmost;
	}

	const BTreeNode * root() const {
		return stub.rightmost;
	}

	BTreeNode * root(BTreeNode * _root) {
		return stub.rightmost = _root;
	}

	BTreeNode * insert(Key & k) {
		if (root() == NULL) {
			return root(new BTreeNode(k,&stub));
		}
		pair<BTreeNode *,unsigned int> p = root()->find_and_split(k);
		BTreeNode * node = p.first;
		unsigned int ix = p.second;
		return node->insert_key(ix, k);
	}

	friend std::ostream & operator<<(std::ostream & out, const BTree & tree) {
		out << "BTree";
		out << *tree.root();
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
