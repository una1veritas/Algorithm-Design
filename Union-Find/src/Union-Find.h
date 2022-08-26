//============================================================================
// Name        : Union-Find.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

class UnionFindSet {
	unsigned int * parent;
	unsigned char * rank;
	unsigned int number;

public:
	UnionFindSet(const unsigned int & n);

	virtual ~UnionFindSet();

	unsigned int size() const {
		return number;
	}

	unsigned int element_rank(unsigned int & x) const {
		return rank[x];
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
	unsigned int find_set(unsigned int x);
	unsigned int find_set(unsigned int x) const;

	unsigned int union_set(unsigned int x, unsigned int y);
	bool in_the_same(const unsigned int & x, const unsigned int & y);
	bool in_the_same(const unsigned int & x, const unsigned int & y) const;

	std::ostream & node_str(std::ostream & out, const unsigned int & x) const;

	friend std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
		out << "UnionFindSet(";
		for(unsigned int x = 0; x < ufs.number; ++x) {
			if ( ufs.parent[x] == x ) {
				// root
				out << "{" << x << ":" << int(ufs.rank[x]);
				for(unsigned int y = 0; y < ufs.number; ++y) {
					if (x != y and ufs.in_the_same(x, y) ) {
						out << ", " << y  << ":" << int(ufs.rank[y]);
					}
				}
				out << "}, ";
			}
		}
		out << ") ";
		return out;
	}
};

/*
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
*/
