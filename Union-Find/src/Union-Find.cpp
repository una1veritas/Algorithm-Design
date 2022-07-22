//============================================================================
// Name        : Union-Find.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using std::cout;
using std::endl;

struct UnionFindSet {
	unsigned int * parent;
	unsigned int number;

	UnionFindSet(const unsigned int & n) : number(n) {
		parent = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i)
			parent[i] = i; // follow itself.
	}

	virtual ~UnionFindSet() {
		//cout << "~UnionFindSet " << endl;
		delete [] parent;
	}

	// path halving
	virtual unsigned int find_set(unsigned int x) {
		unsigned int child;
		while (x != parent[x]) {
			child = x;
			x = parent[x];
			parent[child] = parent[x];
		}
		return x;
	}

	unsigned int find_set(unsigned int x) const {
		while ( parent[x] != x)
			x = parent[x];
		return x;
	}

	virtual unsigned int merge(unsigned int x, unsigned int y) {
		x = find_set(x);
		y = find_set(y);
		if ( x == y ) {
			return x;
		} else if (x < y) {
			parent[y] = x;
			return x;
		} else {
			parent[x] = y;
			return y;
		}
	}

	bool in_the_same_group(const unsigned int & x, const unsigned int & y) {
		return find_set(x) == find_set(y);
	}

	bool in_the_same_group(const unsigned int & x, const unsigned int & y) const {
		return find_set(x) == find_set(y);
	}

	virtual std::ostream & node_str(std::ostream & out, const unsigned int & x) const {
		out << x << "[" << parent[x] << "] ";
		return out;
	}

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
		bool printed[ufs.number];
		out << "UnionFindSet0(";
		for(unsigned int i = 0; i < ufs.number; ++i) {
			printed[i] = false;
		}
		bool comma = false;
		for(unsigned int x = 0; x < ufs.number; ++x) {
			if ( printed[x] )
				continue;
			if ( comma )
				cout << ", ";
			else
				comma = true;
			cout << "{";
			for(unsigned int i = 0; i < ufs.number; ++i) {
				if ( ufs.in_the_same_group(x,i) ) {
					if ( x != i )
					cout << ", ";
					ufs.node_str(cout, i);
					printed[i] = true;
				}
			}
			cout << "}";
		}
		out << ") ";
		return out;
	}
};

struct RankedUnionFindSet : public UnionFindSet {
	unsigned int * rank;

	RankedUnionFindSet(const unsigned int & n) :
		UnionFindSet(n) {
		rank = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i)
			rank[i] = 0;
	}

	~RankedUnionFindSet() {
		//cout << "~RankedUnionFindSet " << endl;
		delete [] rank;
	}

	unsigned int find_set(unsigned int x) {
		unsigned int root = x;
		while (root != parent[root])
			root = parent[root];
		unsigned int t;
		while (x != parent[x]) {
			t = x;
			x = parent[x];
			parent[t] = root;
		}
		return x;
	}
	unsigned int merge(unsigned int x, unsigned int y) {
		x = find_set(x);
		y = find_set(y);
		if (rank[x] == rank[y]) {
			parent[x] = y; // tie break
			rank[y] += 1;
		} else if ( rank[x] > rank[y] ) {
			parent[y] = x;
		} else /* if (rank[x] <= rank[y]) */ {
			parent[x] = y;
		}
		return parent[x];
	}

	std::ostream & node_str(std::ostream & out, const unsigned int & x) const {
		out << x << "[" << parent[x] << ":" << rank[x] << "] ";
		return out;
	}
};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	UnionFindSet ufs(8);
	std::cout << ufs << endl;
	ufs.merge(6,7);
	std::cout << ufs << endl;
	ufs.merge(4,5);
	std::cout << ufs << endl;
	ufs.merge(3,4);
	std::cout << ufs << endl;
	ufs.merge(2,3);
	std::cout << ufs << endl;
	ufs.merge(2,6);
	std::cout << ufs << endl;
	ufs.merge(1,2);
	std::cout << ufs << endl;
	ufs.merge(1,0);
	std::cout << ufs << endl << endl;
	std::cout << "find_set " <<  ufs.find_set(5) << endl;
	std::cout << ufs << endl << endl;


	UnionFindSet s(4);
	std::cout << s << endl;
	return 0;
}
