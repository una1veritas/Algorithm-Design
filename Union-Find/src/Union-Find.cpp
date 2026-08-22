//============================================================================
// Name        : Union-Find.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Union-Find.h"

UnionFindSet::UnionFindSet(const unsigned int & first, const unsigned int & last) : start(first), number(last - first + 1) {
	parent = new unsigned int [start + number - 1];
	rank = new unsigned char [start + number - 1];
	for(unsigned int i = start; i < start + number; ++i) {
		parent[i] = i;
		rank[i] = 0;
	}
}

UnionFindSet::~UnionFindSet() {
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
unsigned int UnionFindSet::find(unsigned int x) {
	unsigned int root = x;
	while (root != parent[root])
		root = parent[root];
	unsigned int t;
	while (x != parent[x]) {
		t = x;
		x = parent[x];
		parent[t] = root;
//		if (root == 65545) {
//			std::cerr << "root = " << root << ", t = " << t << ", x = " << x << std::endl;
//		}
	}
	return x;
}

unsigned int UnionFindSet::find_nocompression(unsigned int x) const {
	while ( parent[x] != x)
		x = parent[x];
	return x;
}

unsigned int UnionFindSet::union_set(unsigned int x, unsigned int y) {
	x = find(x);
	y = find(y);
	//std::cout << "union_set(" << x << ", " << y << ")" << std::endl;
	if (x == y) // no need to merge;
		return parent[x];
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

/*
bool UnionFindSet::in_the_same(const unsigned int & x, const unsigned int & y) const {
	return find_set(x) == find_set(y);
}
*/

std::ostream & UnionFindSet::node_str(std::ostream & out, const unsigned int & x) const {
	out << x; // << "[" << parent[x] << ":" << int(rank[x]) << "] ";
	return out;
}

std::ostream & operator<<(std::ostream & out, const UnionFindSet & ufs) {
	bool * marked = new bool[ufs.size()];
	out << "UnionFindSet(";
	//out << "start + number=" << ufs.start + ufs.number << ", ";

	for(unsigned int x = ufs.start; x < ufs.start + ufs.number; ++x) {
		marked[x - ufs.start] = false;
	}
	for(unsigned int x = ufs.start; x < ufs.start + ufs.number; ++x) {
		// in the same group with x, and not marked yet
		if (marked[x - ufs.start]) {
			continue;
		}
		out << "{" << x ;
		marked[x - ufs.start] = true;
		for(unsigned int y = ufs.start; y < ufs.start + ufs.number; ++y) {
			if (ufs.find_nocompression(x) == ufs.find_nocompression(y) and ! marked[y - ufs.start]) {
				out << ", " << y;
				marked[y - ufs.start] = true;
			}
		}
		out << "}, ";
	}
	out << ") ";
	delete [] marked;
	return out;
}
