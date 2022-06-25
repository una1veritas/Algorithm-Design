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
//private:
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
		return;
	}

	void clear() {
		if ( lchild != NULL) {
			lchild->clear();
			delete lchild;
			lchild = NULL;
		}
		if ( rchild != NULL) {
			rchild->clear();
			delete rchild;
			rchild = NULL;
		}
	}

	bool is_root() const {
		return parent->parent == NULL;
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
			return parent->lchild;
		else
			return parent->rchild;
	}

	bool is_left() const {
		if ( is_root() )
			return false;
		if (parent->lchild == this)
			return true;
		else
			return false;
	}

	bool is_right() const {
		if ( is_root() )
			return false;
		if (parent->rchild == this)
			return true;
		else
			return false;
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

	void rotate_right() {
		RedBlackNode * g = this;
		RedBlackNode * l = lchild;
		RedBlackNode * lr = lchild->rchild;
		RedBlackNode * gg = g->parent;
		std::cout << "gg = " << *(gg->parent->parent) << std::endl;
		if ( g->is_left() ) {
			gg->lchild = l;
		} else {
			gg->rchild = l;
		}
		l->rchild = g;
		l->parent = g->parent;
		g->lchild = lr;
		g->parent = l;
		std::cout << "gg = " << *gg << std::endl;
	}

	void rotate_left() {
		RedBlackNode * g = this;
		RedBlackNode * r = rchild;
		RedBlackNode * rl = rchild->lchild;
		RedBlackNode * gg = g->parent;
		if ( gg->parent == NULL) {
			std::cout << "NULL ";
		}
		std::cout << *g << "original gg = " << *(gg->parent) << std::endl;
		if ( g->is_left() ) {
			gg->lchild = r;
		} else {
			gg->rchild = r;
		}
		r->lchild = g;
		r->parent = g->parent;
		g->rchild = rl;
		g->parent = r;
		if ( gg->lchild == NULL) {
			std::cout << "NULL!" << std::endl;
		}
		if ( gg->rchild == NULL) {
			std::cout << "NULL!" << std::endl;
		}
		std::cout << "gg2 = " << *gg << ", " << *g << ", " << *r << std::endl;
	}

public:
	RedBlackNode * insert(const Data & d) {
		std::pair<RedBlackNode *, RedBlackNode **> pc = this->find_parent_childhandler(d);
		RedBlackNode * parent = pc.first;
		RedBlackNode ** handler = pc.second;
		//if ( is_root() ) {
		//	std::cout << "FAILURE: Can't insert a child to NULL parent." << std::endl;
		//	return NULL;
		//}
		if ( *handler == NULL ) {
			// insert into left or right
			std::cout << "insert as a child" << std::endl;
			*handler = new RedBlackNode(d, parent, NULL, NULL, RED);
		}
		RedBlackNode * current = *handler, * uncle;
		for(;current != NULL;) {
			if (current->is_root()) {
				std::cout << "current is root." << std::endl;
				current->black = true;
				break;
			}
			if (current->parent->black) {
				std::cout << "parent is black." << std::endl;
				break;
			}
			uncle = current->parent->another_sibling();
			if (uncle != NULL and uncle->is_red()) {
				std::cout << "uncle " << *uncle << " is red." << std::endl;
				current->parent->set_black();
				uncle->set_black();
				current->parent->parent->set_red();
				current = current->parent->parent;
				// continue with grandfather
				std::cout << "continue with " << *current << std::endl;
			} else {
				std::cout << "unclde is black." << std::endl;
				if ( current->parent->is_left() ) {
					if ( current->is_left() ) {
						// left left
						std::cout << "left left" << std::endl;
						current->parent->parent->rotate_right();
						current->parent->set_black();
						current->parent->rchild->set_red();
					} else {
						// left right
						std::cout << "left right" << std::endl;					}
				} else if ( current->parent->is_right() ) {
					if ( current->is_right() ) {
						// right right
						std::cout << "right right" << std::endl;
					} else {
						// right left
						RedBlackNode * p = current->parent;
						RedBlackNode * g = p->parent;
						RedBlackNode * gg = g->parent;
						std::cout << "right left from " << *current << std::endl;
						std::cout << "gg = " << gg << ", g = " << g << ", p = " << p << ", c = " << current << std::endl;
						current->parent->rotate_right();
						std::cout << "after rotate right = " << *current << std::endl;
						std::cout << *(current->parent->parent->parent) << std::endl;
						current->parent->rotate_left();
						//std::cout << "after rotate left = " << *current << std::endl;
						current->set_black();
						current->lchild->set_red();
						//std::cout << "after color change = " << *r << std::endl;
					}
				}
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
		if ( node.parent == NULL ) {
			out << "@" << *node.lchild;
		} else {
			out << "(";
			if (node.lchild != NULL) {
				out << *node.lchild;
				out << ", ";
			}
			if (node.is_black())
				out << "*";
			out << node.data;
			if (node.rchild != NULL) {
				out << ", ";
				out << *node.rchild;
			}
			out << ")";
		}
		return out;
	}
};


int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}
	cout << "Hello!" << endl;

	RedBlackNode tree("",NULL,NULL,NULL,false);
	std::vector<std::string> args;
	for(int i = 1; i < argc; ++i){
		args.push_back(argv[i]);
	}

	for(auto p = args.begin(); p != args.end(); ++p){
		std::cout << *p << std::endl;

		if (tree.lchild == NULL) {
			// make root
			tree.lchild = new RedBlackNode(*p,&tree,NULL,NULL,true);
		} else {
			tree.lchild->insert(*p);
		}
		std::cout << "tree = " << tree << std::endl;
	}

	std::cout << "done." << std::endl;
	tree.clear();
	return 0;
}
