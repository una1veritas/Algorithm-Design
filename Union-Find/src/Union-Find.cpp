//============================================================================
// Name        : Union-Find.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <random>
#include <chrono>

using std::cout;
using std::endl;

class UnionFindSet {
	unsigned int * parent;
	unsigned char * rank;
	unsigned int number;

public:
	UnionFindSet(const unsigned int & n) : number(n) {
		parent = new unsigned int [number];
		rank = new unsigned char [number];
		for(unsigned int i = 0; i < number; ++i) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	virtual ~UnionFindSet() {
		//cout << "~UnionFindSet " << endl;
		delete [] parent;
		delete [] rank;
	}

	// path halving
	/*
	virtual unsigned int find_set(unsigned int x) {
		unsigned int child;
		while (x != parent[x]) {
			child = x;
			x = parent[x];
			parent[child] = parent[x];
		}
		return x;
	}
	*/

	// path compression
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

	unsigned int find_set(unsigned int x) const {
		while ( parent[x] != x)
			x = parent[x];
		return x;
	}

	unsigned int union_set(unsigned int x, unsigned int y) {
		x = find_set(x);
		y = find_set(y);
		if (rank[x] == rank[y]) {
			if (x < y) {
				parent[y] = x;
				rank[x] += 1;
			} else {
				parent[x] = y;
				rank[y] += 1;
			}
		} else if ( rank[x] > rank[y] ) {
			parent[y] = x;
		} else /* if (rank[x] <= rank[y]) */ {
			parent[x] = y;
		}
		return parent[x];
	}

	bool in_the_same(const unsigned int & x, const unsigned int & y) {
		return find_set(x) == find_set(y);
	}

	bool in_the_same(const unsigned int & x, const unsigned int & y) const {
		return find_set(x) == find_set(y);
	}

	std::ostream & node_str(std::ostream & out, const unsigned int & x) const {
		out << x; // << "[" << parent[x] << ":" << int(rank[x]) << "] ";
		return out;
	}

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
		out << "UnionFindSet0(";
		for(unsigned int x = 0; x < ufs.number; ++x) {
			if ( ufs.parent[x] == x ) {
				// root
				cout << "{" << x ;
				for(unsigned int y = 0; y < ufs.number; ++y) {
					if (x != y and ufs.in_the_same(x, y) ) {
						cout << ", " << y ;
					}
				}
				cout << "}, ";
			}
		}
		out << ") ";
		return out;
	}
};


int main(const int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	if (argc == 1) {
		cout << "no arguments. exit." << endl;
		return EXIT_SUCCESS;
	}
	unsigned int number = std::strtol(argv[1], NULL, 10);
	int seed;
	if (argc <= 2) {
		std::random_device rnd;
		seed = rnd();
	} else {
		seed = std::strtol(argv[2],NULL,10);
	}
	long repeats;
	if ( argc <= 3 ) {
		repeats = 1000;
	} else {
		repeats = std::strtol(argv[3],NULL, 10);
	}

	std::mt19937 mt(seed);
	long count_union = 0;
	long count_find = 0;
	cout << "union-find set size = " << number << endl;

	std::chrono::system_clock::time_point start, stop;
	start = std::chrono::system_clock::now();

	UnionFindSet ufs(number);

	for(long i = 0; i < repeats; ++i) {
		unsigned int x = mt() % number;
		unsigned int y = mt() % number;
		switch( mt() % 2 ) {
		case 0:
			//cout << x << ", " << y << endl;
			ufs.union_set(x, y);
			++count_union;
			break;
		case 1:
			//cout << x << endl;
			ufs.find_set(x);
			++count_find;
			break;
		}
	}

	stop = std::chrono::system_clock::now();
	//std::time_t tstamp = std::chrono::system_clock::to_time_t(start);
	//std::cout << std::ctime(&tstamp);
	auto diff = stop - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	std::cout << msec << " msec." << endl;
	std::cout << "union " << count_union << ", find " << count_find << endl;

	//cout << ufs << endl;
	return EXIT_SUCCESS;
}
