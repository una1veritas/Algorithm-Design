//============================================================================
// Name        : Red-Black_Tree.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef std::string Data;

struct RedBlackNode {
private:
	RedBlackNode * parent;
	RedBlackNode * lchild, *rchild;
	bool black;
	const Data & data;

	enum NodeColor {
		BLACK = true,
		RED = false,
	};
	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

public:
	RedBlackNode(const Data & d, RedBlackNode * par = NULL, RedBlackNode * left = NULL, RedBlackNode * right = NULL, const bool color = true)
	: parent(par), lchild(left), rchild(right), black(color), data(d) {}

	~RedBlackNode() {
		delete lchild;
		delete rchild;
		return;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		return rchild == NULL and lchild == NULL;
	}

	bool is_black() const {
		return black;
	}

	bool is_red() const {
		return black;
	}

private:
	std::pair<RedBlackNode *, RedBlackNode *> find_parent_child(const Data & d) {
		std::pair<RedBlackNode *, RedBlackNode *> pc(this->parent, this);
		RedBlackNode * parent;
		RedBlackNode * current;
		while ( pc.second != NULL ) {
			parent = pc.first;
			current = pc.second;
			if (d < current->data) {
				pc.first = current;
				pc.second = current->lchild;
			} else if ( current->data < d ) {
				pc.first = current;
				pc.second = current->rchild;
			} else {
				if ( d == current->lchild->data ) {
					pc.first = current;
					pc.second = current->lchild;
				} else if ( d == current->rchild->data ) {
					pc.first = current;
					pc.second = current->rchild;
				}
				else break;
			}
		}
		return pc;
	}

public:
	RedBlackNode * insert(const Data & d) {
		std::pair<RedBlackNode *, RedBlackNode *> pc = this->find_parent_child(d);
		RedBlackNode * parent = pc.first;
		RedBlackNode * current = pc.second;
		if ( parent == NULL) {
			std::cerr << "FAILURE: Can't insert a child to NULL parent." << std::endl;
			return NULL;
		}
		if ( current == NULL ) {
			// insert into left or right
			if ( d <= parent->data ) {
				parent->lchild = new RedBlackNode(d, parent, NULL, NULL);
				//
				current = parent->lchild;
			} else {
				parent->rchild = new RedBlackNode(d, parent, NULL, NULL);
				//
				current = parent->rchild;
			}
		}
		return current;
	}

	friend ostream & operator<<(ostream & out, const RedBlackNode & node) {
		out << "(";
		if (node.lchild != NULL) {
			out << *node.lchild;
			out << ", ";
		}
		out << "[" << node.data << "], ";
		if (node.rchild != NULL) {
			out << *node.rchild;
		}
		out << ")";
		return out;
	}
};

int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}
	cout << "Hello!" << endl;

	RedBlackNode * tree = NULL;

	for(int i = 1; i < argc; ++i){
		std::cout << argv[i] << std::endl;

		if (tree == NULL) {
			tree = new RedBlackNode(argv[i]);
		} else {
			tree->insert(argv[i]);
		}
		if (tree != NULL)
			std::cout << *tree << std::endl;
	}

	std::cout << "done." << std::endl;
	delete tree;
	return 0;
}
