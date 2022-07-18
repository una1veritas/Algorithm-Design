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

class UnionFindSet {
	unsigned int * follow;
	unsigned int number;

public:
	UnionFindSet(const unsigned int & n) : number(n) {
		follow = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i)
			follow[i] = i; // follow itself.
	}

	~UnionFindSet() {
		delete [] follow;
	}

	unsigned int repr(unsigned int x) {
		unsigned int last = x;
		while ( follow[x] != x) {
			last = x;
			x = follow[x];
			follow[last] = x;
		}
		return x;
	}

	unsigned int repr(unsigned int x) const {
		while ( follow[x] != x) {
			x = follow[x];
		}
		return x;
	}

	unsigned int merge(const unsigned int & x, const unsigned int & y) {
		unsigned int xrepr = repr(x), yrepr = repr(y);
		if ( xrepr == yrepr )
			return xrepr;
		if ( xrepr < yrepr ) {
			follow[y] = xrepr;
			return xrepr;
		} else {
			follow[x] = yrepr;
			return yrepr;
		}
	}

	bool in_group(const unsigned int & x, const unsigned int & y) {
		return repr(x) == repr(y);
	}

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
		bool check[ufs.number];
		out << "UnionFindSet(";
		for(unsigned int i = 0; i < ufs.number; ++i) {
			check[i] = false;
		}
		bool comma = false;
		for(unsigned int x = 0; x < ufs.number; ++x) {
			if ( check[x] )
				continue;
			if ( comma )
				cout << ", ";
			else
				comma = true;
			cout << "{" << x ;
			for(unsigned int i = 0; i < ufs.number; ++i) {
				if ( i == x )
					continue;
				unsigned int r = ufs.repr(i);
				if ( x == r ) {
					cout << ", " << i ;
					check[i] = true;
				}
			}
			cout << "}";
			check[x] = true;
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
	ufs.merge(1,2);
	std::cout << ufs << endl;
	ufs.merge(3,6);
	std::cout << ufs << endl;
	return 0;
}
