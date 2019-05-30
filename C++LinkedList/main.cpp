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
	for(ListNode * i = list.begin(); i != list.end(); i = i->next ) {
		std::cout << (const char*) i->next->data << " (->" << i->next->next << "), " << std::flush;
	}
	std::cout << std::endl;
	list.pop();
	std::cout << "list data, next = " << list << std::endl;
	list.make_tail_loop(5);
	for(ListNode * i = list.begin(); i != list.end(); i = i->next ) {
		std::cout << (const char*) i->next->data << " ->(" << std::hex << (void*) i->next->next << "), ";
	}
	std::cout << std::endl << std::endl;

	int c = 0;
	ListNode * p1 = list.begin();
	ListNode * p2 = list.begin();
	do {
		std::cout << c <<": (" << (const char*) p1->next->data << ", " << (const char*) p2->next->data << "); ";
		p1 = p1->next;
		p2 = p2->next;
		p2 = p2->next;
		++c;
	} while (p1->next != p2->next);
	std::cout << c <<": (" << (const char*) p1->next->data << ", " << (const char*) p2->next->data << "); ";
	std::cout << std::endl;
	p1 = list.begin();
	do {
		std::cout << c <<": (" << (const char*) p1->next->data << ", " << (const char*) p2->next->data << "); ";
		p1 = p1->next;
		p2 = p2->next;
		++c;
	} while ( p1->next != p2->next );
	std::cout << c <<": (" << (const char*) p1->next->data << ", " << (const char*) p2->next->data << "); ";
	std::cout << std::endl;

	std::cout << "finished." << std::endl;

	std::exit(EXIT_SUCCESS);
}
