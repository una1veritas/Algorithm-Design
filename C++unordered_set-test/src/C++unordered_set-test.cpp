//============================================================================
// Name        : C++unordered_set-test.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_set>
#include <cinttypes>

struct edge {
	uint64_t src, dst;
	double weight;

	edge(const uint64_t & s, const uint64_t & d, const double & w) : src(s), dst(d), weight(w) {}

	bool operator==(const edge & other) const {
		return (src == other.src and dst == other.dst)
				or (src == other.dst and dst == other.src);
	}

	friend std::ostream & operator<<(std::ostream & out, const edge & e) {
		out << "(" << e.src << ", " << e.dst << ": " << e.weight << ")";
		return out;
	}
};

template <>
struct std::hash<edge>
{
	std::size_t operator()(const edge & e) const noexcept
	{
		return e.src ^ e.dst;
	}
};

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

    std::unordered_set<edge> mySet { {2, 3, 1.2}, {7, 1, 0.9}, {1, 3, 3.3}, {8,2, 1.6}, {3,2, 192.4}, {7,8, 18.0} };

    for (const auto &e : mySet) {
    	std::cout << e << ", ";
	}
    std::cout << std::endl;
/*
	mySet.insert((std::string)"5"); // puts an element 5 in the set
	for (auto &e : mySet) {
		cout << e << ", ";
	}
	cout << endl;

	mySet.erase("7"); // removes an element 7
	for (auto &e : mySet) {
		cout << e << ", ";
	}
	cout << endl;
*/
	return 0;
}
