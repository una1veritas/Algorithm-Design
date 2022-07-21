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

struct UnionFindSet0 {
private:
	unsigned int * parent;
	unsigned int number;

public:
	UnionFindSet0(const unsigned int & n) : number(n) {
		parent = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i) {
			parent[i] = i; // follow itself.
		}
	}

	~UnionFindSet0() {
		delete [] parent;
	}

	unsigned int find_set(unsigned int x) {
		unsigned int p, gc = x;
		while (x != parent[x]) {
			p = parent[x];
			parent[gc] = p;
			gc = x;
			x = p;
		}
		return x;
	}

	unsigned int find_set(unsigned int x) const {
		while ( parent[x] != x) {
			x = parent[x];
		}
		return x;
	}

	unsigned int merge(unsigned int x, unsigned int y) {
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

	bool in_the_same(const unsigned int & x, const unsigned int & y) {
		return find_set(x) == find_set(y);
	}

	bool in_the_same(const unsigned int & x, const unsigned int & y) const {
		return find_set(x) == find_set(y);
	}

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet0 & ufs) {
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
				if ( ufs.in_the_same(x,i) ) {
					if ( x != i )
					cout << ", ";
					cout << i << " [" << ufs.parent[i] << "] ";
					printed[i] = true;
				}
			}
			cout << "}";
		}
		out << ") ";
		return out;
	}
};

struct UnionFindSet {
private:
	unsigned int * parent;
	unsigned int * rank;
	unsigned int number;

public:
	UnionFindSet(const unsigned int & n) : number(n) {
		parent = new unsigned int [number];
		rank = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i) {
			parent[i] = i; // follow itself.
			rank[i] = 0;
		}
	}

	~UnionFindSet() {
		delete [] parent;
		delete [] rank;
	}

	unsigned int find_set(const unsigned int & x) {
		unsigned int t = x, root;
		while (t != parent[t]) {
			t = parent[t];
		}
		root = t;
		t = x;
		while (t != parent[t]) {
			t = parent[t];
			parent[t] = root;
		}
		return root;
	}

	unsigned int find_set(unsigned int x) const {
		while ( parent[x] != x) {
			x = parent[x];
		}
		return x;
	}

	unsigned int merge(unsigned int x, unsigned int y) {
		x = find_set(x);
		y = find_set(y);
		if (rank[x] == rank[y]) {
			parent[x] = y; // tie break
			rank[y] = rank[y] + 1;
		} else if ( rank[x] > rank[y] ) {
			parent[y] = x;
		} else /* if (rank[x] <= rank[y]) */ {
			parent[x] = y;
		}
		return parent[x];
	}

	bool in_group(const unsigned int & x, const unsigned int & y) const {
		return find_set(x) == find_set(y);
	}

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
		bool printed[ufs.number];
		out << "UnionFindSet(";
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
				if ( ufs.in_group(x,i) ) {
					if ( x != i )
					cout << ", ";
					cout << i << " [" << ufs.parent[i] << ":" << ufs.rank[i]<< "] ";
					printed[i] = true;
				}
			}
			cout << "}";
		}
		out << ") ";
		return out;
	}
};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	UnionFindSet ufs(8);
	std::cout << ufs << endl;
	ufs.merge(0,1);
	std::cout << ufs << endl;
	ufs.merge(6,7);
	std::cout << ufs << endl;
	ufs.merge(2,3);
	std::cout << ufs << endl;
	ufs.merge(5,4);
	std::cout << ufs << endl;
	ufs.merge(5,6);
	std::cout << ufs << endl;
	ufs.merge(3,4);
	std::cout << ufs << endl;
	ufs.merge(1,2);
	std::cout << ufs << endl;
	std::cout << endl;
	unsigned int res = ufs.find_set(7);
	std::cout << res << endl;
	std::cout << ufs << endl;
	return 0;
}
