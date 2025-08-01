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

typedef std::string Key;

struct RedBlackNode {
//private:
	RedBlackNode * parent;
	RedBlackNode * lchild, *rchild;
	bool color;
	const Key * keyptr;

public:
	enum NodeColor {
		BLACK = true,
		RED = false,
	};

public:
	RedBlackNode() : parent(NULL), lchild(NULL), rchild(NULL), color(BLACK), keyptr(NULL) {}

	RedBlackNode(const Key & k, RedBlackNode * par = NULL, RedBlackNode * left = NULL, RedBlackNode * right = NULL, const bool col = true)
	: parent(par), lchild(left), rchild(right), color(col), keyptr(&k) {}

	~RedBlackNode() {
		return;
	}

	static bool node_is_black(const RedBlackNode * ptr) {
		if (ptr == NULL)
			return true;
		return ptr->color;
	}

	static bool node_is_red(const RedBlackNode * ptr) {
		if (ptr != NULL and ptr->color == RED)
			return true;
		return false;
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

	RedBlackNode * find_parent(const Key & k, const bool stop = false) {
		// finds the parent of insertion point (NULL)
		RedBlackNode * par = NULL;
		RedBlackNode * cur = this;
		if ( cur->is_stub() ) {
			par = cur;
			cur = par->lchild;
		}
		for ( ;cur != NULL; ) {
			par = cur;
			if (k == *par->keyptr and stop)
				return par;
			if (k <= *par->keyptr) {
				cur = par->lchild;
			} else if ( *par->keyptr <= k ) {
				cur = par->rchild;
			}
		}
		return par;
	}

	void rotate_right() {
		//std::cout << "rotate right " << *this << " -> ";
		RedBlackNode ** handler;
		RedBlackNode * left = lchild;
		RedBlackNode * leftright = lchild->rchild;
		if ( is_left() )
			handler = &(parent->lchild);
		else
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
	RedBlackNode * insert(const Key & k) {
		RedBlackNode * p = this->find_parent(k);
		RedBlackNode ** handler = NULL;
		// re-determine the insertion point
		if ( p->is_stub() or k <= *p->keyptr )
			handler = &(p->lchild);
		else if ( *p->keyptr < k )
			handler = &(p->rchild);
		// insert into left or right
		//std::cout << "insert a node as a child " << parent << std::endl;
		*handler = new RedBlackNode(k, p, NULL, NULL, RED);

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

	RedBlackNode * rightmost_descendant() {
		RedBlackNode * node = this;
		while ( node->rchild != NULL )
			node = node->rchild;
		return node;
	}

	RedBlackNode * remove(const Key & k) {
		RedBlackNode * node = this->find_parent(k, true);
		// re-determine the insertion point
		if ( ! node->is_leaf() ) {
			RedBlackNode * rd = node->rightmost_descendant();
			const Key * t = node->keyptr;
			node->keyptr = rd->keyptr;
			rd->keyptr = t;
			node = rd;
		}
		// node is v
		RedBlackNode * par = node->parent;
		RedBlackNode * u;
		if (node->is_left()) {
			par->lchild = node->lchild;
			u = par->lchild;
		} else {
			par->rchild = node->lchild;
			u = par->rchild;
		}
		bool ex_node_color = node->color;
		delete node;
		if ( ex_node_color == RED or node_is_red(u) ) {
			if (u != NULL) {
				u->set_black();
				return u;
			}
			return par;
		}
		cout << "double black process" << endl;
		// *chandler is double black node.
		RedBlackNode * sibling;
		bool u_is_left;
		for (;;) {
			if ( u != NULL and u->is_root() ) {
				break;
				// exit
			}
			if (u == par->lchild) {
				// including both children of par are NULL
				sibling = par->rchild;
				u_is_left = true;
			} else {
				sibling = par->lchild;
				u_is_left = false;
			}
			if (node_is_black(sibling) and (sibling != NULL and
					(node_is_red(sibling->lchild) or node_is_red(sibling->rchild) ) )) {
				if ( u_is_left ) {
					if ( node_is_red(sibling->lchild) ) {
					// left-left case
					} else if ( node_is_red(sibling->rchild) ) {
					// left-right
					}
				} else { // u is right
					if ( node_is_red(sibling->rchild) ) {
						// right-right
					} else if (node_is_red(sibling->lchild) ) {
						// right-left
					}
				}
			} else if (node_is_black(sibling) and (sibling != NULL) and
					node_is_black(sibling->lchild) and node_is_black(sibling->rchild)) {
				// sibling and its children are black
			}
		}
		return node;
	}

	friend ostream & operator<<(ostream & out, const RedBlackNode & node) {
		out << "(";
		if (node.lchild != NULL) {
			out << *(node.lchild);
			out << ", ";
		}
		if (node.is_black())
			out << "*";
		out << *node.keyptr;
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
	RedBlackTree(void) : stub() { }

	RedBlackNode * root() const {
		return stub.lchild;
	}

	void clear() {
		return stub.lchild->clear();
	}

	RedBlackNode * insert(const Key & k) {
		return stub.insert(k);
	}

	RedBlackNode * remove(const Key & k) {
		return stub.remove(k);
	}

	friend ostream & operator<<(ostream & out, const RedBlackTree & tree) {
		out << "RedBlackTree";
		if (tree.root() == NULL) {
			out << "() ";
			return out;
		}
		out << *(tree.root());
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

	/*
	std::string s("Kilo");
	tree.remove(s);
	std::cout << "remove " <<  s << endl << "tree = " << tree << std::endl;
*/
	tree.clear();
	return 0;
}
