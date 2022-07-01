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
		unsigned int mid = this->keycount/2;
		BTreeNode * sibling = new BTreeNode();
		sibling->parent = this->parent;
		for(unsigned int ix = mid+1; ix < this->keycount; ++ix) {
			sibling->insert_key(keychild[ix].key,keychild[ix].left);
		}
		sibling->rightmost = rightmost;
		if (is_root()) {
			parent->rightmost = new BTreeNode();
			parent = parent->rightmost;
			sibling->parent = parent;
			parent->rightmost = this;
		}
		parent->insert_key(keychild[mid].key, keychild[mid].left);
		return parent;
	}

	BTreeNode * insert_key(Key & k, BTreeNode * left = NULL) {
		return insert_key(find_index(k), k, left);
	}

	BTreeNode * insert_key(const unsigned int & ix, Key & k, BTreeNode * left = NULL) {
		if (is_full()) {
			cout << "error: node is full!" << endl;
			return NULL;
		}
		for(unsigned int i = keycount; i > ix; --i) {
			keychild[i] = keychild[i-1];
		}
		keychild[ix].key = k;
		keychild[ix].left = left;
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
			for(auto kc : node.keychild) {
				out << kc.key << " ";
			}
		} else {
			for(auto kc : node.keychild) {
				out << *kc.left << " ";
				out << kc.key << " ";
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

	BTreeNode * root(BTreeNode * _root) {
		return stub.rightmost = _root;
	}

	BTreeNode * insert(Key & k) {
		if (root() == NULL) {
			return root(new BTreeNode(k));
		}
		pair<BTreeNode *,unsigned int> p = root()->find_and_split(k);
		BTreeNode * node = p.first;
		unsigned int ix = p.second;
		return node->insert_key(ix, k);
	}

	friend std::ostream & operator<<(std::ostream & out, const BTree & tree) {
		out << "BTree";
		out << *(tree.stub.rightmost);
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
