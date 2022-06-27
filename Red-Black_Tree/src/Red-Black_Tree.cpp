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
	bool color;
	const Data & data;

public:
	enum NodeColor {
		BLACK = true,
		RED = false,
	};

public:
	RedBlackNode(const Data & d, RedBlackNode * par = NULL, RedBlackNode * left = NULL, RedBlackNode * right = NULL, const bool col = true)
	: parent(par), lchild(left), rchild(right), color(col), data(d) {}

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

	bool is_stub() const {
		return parent == NULL;
	}

	bool is_root() const {
		return parent->is_stub();
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
		return color == BLACK;
	}

	bool is_red() const {
		return color == RED;
	}

	bool set_black() {
		return color = BLACK;
	}

	bool set_red() {
		return color = RED;
	}

	RedBlackNode * another_sibling() const {
		if (parent->rchild == this)
			return parent->lchild;
		else
			return parent->rchild;
	}

	bool is_left() const {
		//if ( is_root() )
		//	return false;
		if (parent->lchild == this)
			return true;
		else
			return false;
	}

	bool is_right() const {
		//if ( is_root() )
		//	return false;
		if (parent->rchild == this)
			return true;
		else
			return false;
	}

private:
	/*
	RedBlackNode * find_root() {
		for (RedBlackNode * curr = this; curr != NULL; curr = curr->parent) {
			if (curr->is_root())
				return curr;
		}
		return NULL;
	}
	*/

	RedBlackNode * find_parent(const Data & d) {
		// finds the parent of insertion point (NULL)
		RedBlackNode * par = NULL;
		RedBlackNode * cur = this;
		for ( ;cur != NULL; ) {
			par = cur;
			if (par->is_stub() or d <= par->data) {
				cur = par->lchild;
			} else if ( par->data <= d ) {
				cur = par->rchild;
			}
		}
		return par;
	}

	void rotate_right() {
		//std::cout << "rotate right " << *this << " -> ";
		RedBlackNode ** handler;
		RedBlackNode * left = lchild;
		//RedBlackNode * leftleft  = lchild->lchild;
		RedBlackNode * leftright = lchild->rchild;
		//RedBlackNode * right = rchild;
		if ( is_left() )
			handler = &(parent->lchild);
		else //
			if ( is_right() )
			handler = &(parent->rchild);
		*handler = left;
		left->parent = parent;
		left->rchild = this;
		this->parent = left;
		this->lchild = leftright;
		if ( leftright != NULL)
			leftright->parent = this;
		//std::cout << **handler << std::endl;
	}

	void rotate_left() {
		//std::cout << "rotate left " << *this << " -> ";
		RedBlackNode ** handler;
		RedBlackNode * right = rchild;
		RedBlackNode * rightleft  = rchild->lchild;
		if ( is_left() )
			handler = &(parent->lchild);
		else
			handler = &(parent->rchild);
		*handler = right;
		right->parent = parent;
		right->lchild = this;
		this->parent = right;
		this->rchild = rightleft;
		if (rightleft != NULL)
			rightleft->parent = this;
		//std::cout << **handler << std::endl;
	}

public:
	RedBlackNode * insert(const Data & d) {
		RedBlackNode * p = this->find_parent(d);
		RedBlackNode ** handler;
		// re-determine the insertion point
		if ( p->is_stub() or d < p->data )
			handler = &(p->lchild);
		else if ( p->data < d )
			handler = &(p->rchild);
		else if ( p->lchild == NULL )
			handler = &(p->lchild);
		else
			handler = &(p->rchild);
		// insert into left or right
		//std::cout << "insert a node as a child " << parent << std::endl;
		*handler = new RedBlackNode(d, p, NULL, NULL, RED);

		RedBlackNode * current = *handler;
		RedBlackNode * uncle;
		for( ; ; ) {
			if (current->is_root()) {
				//std::cout << "current is root. " << std::endl;
				current->set_black();
				break;
			}
			if (current->parent->is_black()) {
				//std::cout << "parent is black." << std::endl;
				break;
			}
			uncle = current->parent->another_sibling();
			if (uncle != NULL and uncle->is_red()) {
				//std::cout << "uncle is red." << std::endl;
				current->parent->set_black();
				uncle->set_black();
				current->parent->parent->set_red();
				current = current->parent->parent;
				// continue with grandfather
			} else {
				//std::cout << "unclde is black." << std::endl;
				if ( current->parent->is_left() ) {
					if ( current->is_left() ) {
						// left left
						current->parent->parent->rotate_right();
						current->parent->set_black();
						current->parent->rchild->set_red();
					} else {
						// left right
						current->parent->rotate_left();
						current->parent->rotate_right();
						current->set_black();
						current->rchild->set_red();
					}
				} else if ( current->parent->is_right() ) {
					if ( current->is_right() ) {
						// right right
						current->parent->parent->rotate_left();
						current->parent->set_black();
						current->parent->lchild->set_red();
					} else {
						// right left
						current->parent->rotate_right();
						current->parent->rotate_left();
						current->set_black();
						current->lchild->set_red();
					}
				}
				break;
			}
		}
		return *handler;
	}

	friend ostream & operator<<(ostream & out, const RedBlackNode & node) {
		out << "(";
		if (node.lchild != NULL) {
			out << *(node.lchild);
			out << ", ";
		}
		if (node.is_black())
			out << "*";
		out << node.data;
		if (node.rchild != NULL) {
			out << ", ";
			out << *(node.rchild);
		}
		out << ")";
		return out;
	}
};

struct RedBlackTree {
private:
	RedBlackNode stub;

public:
	RedBlackTree(void) : stub("", NULL, NULL, NULL, false) { }

	RedBlackNode * root() const {
		return stub.lchild;
	}

	void clear() {
		return stub.lchild->clear();
	}

	RedBlackNode * insert(const Data & d) {
		return (&stub)->insert(d);
	}

	friend ostream & operator<<(ostream & out, const RedBlackTree & tree) {
		out << "RedBlackTree";
		if (tree.stub.lchild == NULL) {
			out << "() ";
			return out;
		}
		out << *(tree.stub.lchild);
		return out;
	}
};
// (((((A), *A), A, ((C), *E, (E))), *E, ((G), *H)),
// *I,
// ((((L), *M), N, (*P)), *R, (*S, (X))))

int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}
	cout << "Hello!" << endl;

	RedBlackTree tree;
	std::vector<std::string> args;
	for(int i = 1; i < argc; ++i){
		args.push_back(argv[i]);
	}

	for(auto p = args.begin(); p != args.end(); ++p){
		std::cout << *p << std::endl;

		tree.insert(*p);
		std::cout << "tree = " << tree << std::endl;
	}

	std::cout << "done." << std::endl;
	tree.clear();
	return 0;
}
