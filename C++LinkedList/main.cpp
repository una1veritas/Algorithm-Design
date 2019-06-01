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
	list.push("-1");
	std::cout << std::endl << "list size = " << list.size() << std::endl;
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*) i->data << " (->" << i->next << "), " << std::flush;
	}
	std::cout << std::endl;
	list.pop();
	std::cout << "list data, next = " << list << std::endl;
	list.make_tail_loop(5);
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*) i->data << " ->(" << std::hex << (void*) i->next << "), ";
	}
	std::cout << std::endl << std::endl;

	int c = 0;
	LinkedList::Iterator p1 = list.begin();
	LinkedList::Iterator p2 = list.begin();
	do {
		std::cout << c <<": (" << (const char*) p1->data << ", " << (const char*) p2->data << "); ";
		++p1;
		++p2; ++p2;
		++c;
	} while (p1 != p2);
	std::cout << c <<": (" << (const char*) p1->data << ", " << (const char*) p2->data << "); ";
	std::cout << std::endl;
	p1 = list.begin();
	do {
		std::cout << c <<": (" << (const char*) p1->data << ", " << (const char*) p2->data << "); ";
		++p1;
		++p2;
		++c;
	} while ( p1 != p2 );
	std::cout << c <<": (" << (const char*) p1->data << ", " << (const char*) p2->data << "); ";
	std::cout << std::endl;

	std::cout << "finished." << std::endl;

	std::exit(EXIT_SUCCESS);
}
