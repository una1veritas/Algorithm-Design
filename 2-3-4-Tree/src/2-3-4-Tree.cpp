//============================================================================
// Name        : 2-3-4-Tree.cpp
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

struct Node234 {
private:
	Node234 * parent;
	Node234 * rightmostchild;
	struct DataChild {
		Data data;
		Node234 * leftchild;
		/*
		DataChild(const Data & d, Node234 * ptr = NULL) : data(d), leftchild(ptr) {}
		DataChild(const DataChild & dc) : data(dc.data), leftchild(dc.leftchild) {}
		*/
	};
	vector<DataChild> data234;

	constexpr static unsigned int data_max_size = 3;
	constexpr static unsigned int children_max_size = 4;

public:
	Node234(const Data & d, Node234 * par, Node234 * l = NULL, Node234 * r = NULL) {
		parent = par;
		data234.push_back(DataChild{d,l});
		rightmostchild = r;
	}

	bool is_leaf() const {
		for(auto i = data234.cbegin(); i != data234.cend(); ++i) {
			if ( i->leftchild != NULL )
				return false;
		}
		if ( rightmostchild != NULL )
			return false;
		return true;
	}

	bool is_full() const {
		return data234.size() == data_max_size;
	}

private:
	unsigned int find_data_or_gap(const Data & d) {
		unsigned int i;
		for (i = 0 ; i < data234.size() ; ++i) {
			if ( !(data234[i].data < d) )
				break;
		}
		return i;
	}

	bool insert_data234(const Data & d) {
		if ( data234.size() == data_max_size ) {
			cerr << "error: insert_data failure." << endl;
			return false;
		}
		unsigned int i = find_data_or_gap(d);
		DataChild dc = {d,NULL};
		if ( i == data234.size() ) {
			data234.push_back(dc);
		} else {
			data234.insert(data234.cbegin()+i, dc);
		}
		return true;
	}

public:
	std::pair<Node234 *,unsigned int> find_node_and_dataix(const Data & d) {
		Node234 * att = this;
		for(;;) {
			unsigned int i = att->find_data_or_gap(d);
			if (i == att->data234.size()) {
				att = rightmostchild;
				if (att == NULL)
					return std::pair<Node234 *,unsigned int>(this,i);
			} else if (att->data234[i].data == d) {
				return std::pair<Node234 *,unsigned int>(this, i);
			} else {
				att = att->data234[i].leftchild;
				if (att == NULL)
					return std::pair<Node234 *,unsigned int>(this,i);
			}
		}
		return std::pair<Node234 *,unsigned int>(this,data234.size());
	}

	Node234 * insert(const Data & d) {
		auto nodeix = this->find_node_and_dataix(d);
		Node234 * node = nodeix.first;
		unsigned int ix = nodeix.second;
		if (ix < node->data234.size())
			if (node->data234[ix].data == d)
				return node;
		// d must be inserted.
		if ( !node->is_full() ) {
			node->insert_data234(d);
			return node;
		} else {
			// split
			node = node->split();
			if ( !node->insert_data234(d) )
				std::cerr << "full!" << std::endl;
		}
		return NULL;
	}

	Node234 * split() {
		Node234 * rightsibling = new Node234(data234[2].data,parent,data234[2].leftchild,rightmostchild);
		data234.pop_back();
		Data & d = data234[1].data;
		rightmostchild = data234[1].leftchild;
		data234.pop_back();
		if ( parent == NULL ) {
			// make this node as parent
			Node234 * leftsibling = new Node234(data234[0].data,this,data234[0].leftchild,data234[1].leftchild);
			rightsibling->parent = this;
			data234.pop_back();
			data234.push_back(DataChild{d,leftsibling});
			rightmostchild = rightsibling;
			return this;
		}
		return parent;
	}

	friend ostream & operator<<(ostream & out, const Node234 & node) {
		out << "(";
		for(unsigned int i = 0; i < node.data234.size(); ++i) {
			if (node.data234[i].leftchild != NULL) {
				out << * node.data234[i].leftchild;
				out << ", ";
			}
			out << node.data234[i].data << ",";
		}
		if (node.rightmostchild != NULL)
			out << *node.rightmostchild;
		out << ")";
		return out;
	}
};

int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		cout << "supply arguments." << endl;
		return -1;
	}

	Node234 root(argv[1],NULL);
	Node234 * tree = &root;
	tree->insert(argv[2]);
	tree->insert(argv[3]);
	tree->insert(argv[4]);

	cout << "Hello!" << endl;
	cout << *tree << endl;

	return 0;
}
