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

public:
	RedBlackNode(const Data & d, RedBlackNode * par = NULL, RedBlackNode * left = NULL, RedBlackNode * right = NULL, const bool color = true)
	: parent(par), lchild(left), rchild(right), black(color), data(d) {}

	~RedBlackNode() {
		if (lchild != NULL)
			delete lchild;
		if (rchild != NULL)
			delete rchild;
		return;
	}

	bool is_root() const {
		return parent == NULL;
	}

	bool is_leaf() const {
		return rchild == NULL and lchild == NULL;
	}

	inline bool has_left() const {
		return lchild != NULL;
	}

	inline bool has_right() const {
		return rchild != NULL;
	}

	bool is_black() const {
		return black;
	}

	bool is_red() const {
		return !black;
	}

	bool set_black() {
		return black = true;
	}

	bool set_red() {
		return black = false;
	}

	RedBlackNode * another_sibling() const {
		if (parent->rchild == this)
			return lchild;
		else
			return rchild;
	}

private:
	std::pair<RedBlackNode *, RedBlackNode **> find_parent_childhandler(const Data & d) {
		RedBlackNode * current = this;
		std::pair<RedBlackNode *, RedBlackNode **> pc(this->parent, &current);
		//RedBlackNode * parent;
		while ( *pc.second != NULL ) {
			parent = pc.first;
			current = *pc.second;
			if (d < current->data) {
				pc.first = current;
				pc.second = &(current->lchild);
			} else if ( current->data < d ) {
				pc.first = current;
				pc.second = &(current->rchild);
			} else {
				if ( current->has_left() and d == current->lchild->data ) {
					pc.first = current;
					pc.second = &(current->lchild);
				} else if ( current->has_right() and d == current->rchild->data ) {
					pc.first = current;
					pc.second = &(current->rchild);
				} else if (current->lchild == NULL) {
					pc.first = current;
					pc.second = &(current->lchild);
				} else if (current->rchild == NULL) {
					pc.first = current;
					pc.second = &(current->rchild);
				} else
					break;
			}
		}
		return pc;
	}

public:
	RedBlackNode * insert(const Data & d) {
		std::pair<RedBlackNode *, RedBlackNode **> pc = this->find_parent_childhandler(d);
		RedBlackNode * parent = pc.first;
		RedBlackNode ** handler = pc.second;
		if ( parent == NULL) {
			std::cerr << "FAILURE: Can't insert a child to NULL parent." << std::endl;
			return NULL;
		}
		if ( *handler == NULL ) {
			// insert into left or right
			*handler = new RedBlackNode(d, parent, NULL, NULL, RED);
		}
		RedBlackNode * current = *handler, * uncle;
		for(;current != NULL;) {
			if (current->is_root()) {
				current->black = true;
				break;
			}
			if (current->parent->black) {
				std::cout << "parent is black." << std::endl;
				break;
			}
			uncle = current->parent->another_sibling();
			if (uncle != NULL and uncle->is_red()) {
				std::cout << "uncle is red." << *uncle << std::endl;
				current->parent->set_black();
				uncle->set_black();
				current->parent->parent->set_red();
				current = current->parent->parent;
			} else {
				std::cout << "unclde is black." << std::endl;
				/*
				b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)
				(i) Left Left Case (p is left child of g and x is left child of p)
				(ii) Left Right Case (p is left child of g and x is the right child of p)
				(iii) Right Right Case (Mirror of case i)
				(iv) Right Left Case (Mirror of case ii)
				*/
				break;
			}

		}
		return *handler;
	}

	friend ostream & operator<<(ostream & out, const RedBlackNode & node) {
		out << "(";
		if (node.lchild != NULL) {
			out << *node.lchild;
			out << ", ";
		}
		if (node.is_black())
			out << "* ";
		out << node.data << ", ";
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
	std::vector<std::string> args;
	for(int i = 1; i < argc; ++i){
		args.push_back(argv[i]);
	}

	for(auto p = args.begin(); p != args.end(); ++p){
		std::cout << *p << std::endl;

		if (tree == NULL) {
			tree = new RedBlackNode(*p);
		} else {
			tree->insert(*p);
		}
		if (tree != NULL)
			std::cout << *tree << std::endl;
	}

	std::cout << "done." << std::endl;
	delete tree;
	return 0;
}
