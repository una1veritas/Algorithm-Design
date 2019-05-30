#include <iostream>
#include <cstdlib>

#include "LinkedList.h"

int main(const int argc, const char *argv[]) {
	LinkedList list;

	std::cout << "Sample LinkedList main." << std::endl;

	list.append("3");
	list.append("4");
	list.append("5");
	list.append("6");
	list.append("7");
	list.append("8");
	list.push("2");
	list.push("1");
	list.push("0");
	std::cout << std::endl << "list size = " << list.size() << std::endl;
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*)(*i) << " (" << (&i.node()) << ") " << std::flush;
	}
	std::cout << std::endl;
	std::cout << (char *) list.pop() << std::endl;
	std::cout << "list size = " << list.size() << std::endl;
	std::cout << list << std::endl;
	list.make_tail_loop(4);
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*)(*i) << " -> " << (const char*) (i.node().next->data) << ", ";
	}
	std::cout << std::endl << std::endl;

	int c = 0;
	LinkedList::Iterator p1 = list.begin();
	LinkedList::Iterator p2 = list.begin();
	std::cout << c <<": (" << (const char*) *p1 << ", " << (const char*) *p2 << "); ";
	do {
		++p1;
		++p2; ++p2;
		c += 1;
		std::cout << c <<": (" << (const char*) *p1 << ", " << (const char*) *p2 << "); ";
	} while ( p1 != p2 );
	std::cout << std::endl;
	p1 = list.begin();
	do {
		++p1;
		++p2;
		c += 1;
		std::cout << c <<": (" << (const char*) *p1 << ", " << (const char*) *p2 << "); ";
	} while ( p1 != p2 );
	std::cout << std::endl;

	std::cout << "finished." << std::endl;
	std::exit(EXIT_SUCCESS);
}
