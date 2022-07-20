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
	unsigned int * repr;
	unsigned int * rank;
	unsigned int number;

public:
	UnionFindSet(const unsigned int & n) : number(n) {
		repr = new unsigned int [number];
		rank = new unsigned int [number];
		for(unsigned int i = 0; i < number; ++i) {
			repr[i] = i; // follow itself.
			rank[i] = 0;
		}
	}

	~UnionFindSet() {
		delete [] repr;
		delete [] rank;
	}

	unsigned int find_set(unsigned int x) {
		unsigned int path[number];
		unsigned int length = 0;
		while (x != repr[x]) {
			path[length++] = x;
			x = repr[x];
		}
		for(unsigned int i = 0; i < length; ++i)
			repr[path[i]] = x;
		return x;
	}

	unsigned int find_set(unsigned int x) const {
		while ( repr[x] != x) {
			x = repr[x];
		}
		return x;
	}

	unsigned int merge(unsigned int x, unsigned int y) {
		x = find_set(x);
		y = find_set(y);
		if ( rank[x] > rank[y] ) {
			repr[y] = x;
		} else {
			repr[x] = y;
			if (rank[x] == rank[y])
				rank[y] = rank[y] + 1;
		}
		return repr[x];
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
					cout << i << " [" << ufs.repr[i] << ":" << ufs.rank[i]<< "] ";
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
	ufs.merge(5,3);
	std::cout << ufs << endl;
	ufs.merge(3,6);
	std::cout << ufs << endl;
	ufs.merge(1,7);
	std::cout << ufs << endl;
	return 0;
}
