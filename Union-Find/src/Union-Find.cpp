//============================================================================
// Name        : Union-Find.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Union-Find.h"

UnionFindSet::UnionFindSet(const unsigned int & n) : number(n) {
	parent = new unsigned int [number];
	rank = new unsigned char [number];
	for(unsigned int i = 0; i < number; ++i) {
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
unsigned int UnionFindSet::find_set(unsigned int x) {
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

unsigned int UnionFindSet::find_set(unsigned int x) const {
	while ( parent[x] != x)
		x = parent[x];
	return x;
}

unsigned int UnionFindSet::union_set(unsigned int x, unsigned int y) {
	x = find_set(x);
	y = find_set(y);
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

bool UnionFindSet::in_the_same(const unsigned int & x, const unsigned int & y) {
	return find_set(x) == find_set(y);
}

bool UnionFindSet::in_the_same(const unsigned int & x, const unsigned int & y) const {
	return find_set(x) == find_set(y);
}

std::ostream & UnionFindSet::node_str(std::ostream & out, const unsigned int & x) const {
	out << x; // << "[" << parent[x] << ":" << int(rank[x]) << "] ";
	return out;
}
