#include <iostream>
#include <cstdlib>

#include "LinkedList.h"

int main(const int argc, const char *argv[]) {
	LinkedList list;

	std::cout << "Sample LinkedList main." << std::endl;

	list.append("Hello.");
	list.append("my");
	list.push("name");
	list.push("is");
	list.push("Chebrashka!");
	list.push("Ochi");
	list.push("priyatono!");
	std::cout << std::endl << "list size = " << list.size() << std::endl;
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*)(*i) << " (" << (i.nodeptr()) << ") ";
	}
	std::cout << std::endl;
	std::cout << (char *) list.pop() << std::endl;
	std::cout << "list size = " << list.size() << std::endl;
	std::cout << list << std::endl;
	list.make_tail_loop(2);
	for(LinkedList::Iterator i = list.begin(); i != list.end(); ++i ) {
		std::cout << (const char*)(*i)
				<< " (" << (i.nodeptr()) << "->"
				<< (i.nodeptr()->next)
				<< ") ";
	}
	std::cout << std::endl;

	int c = 0;
	LinkedList::Iterator fast = list.begin();
	LinkedList::Iterator slow = list.begin();
	do {
		fast += 2;
		++slow;
		c += 1;
		std::cout << c << ", ";
	} while ( slow != fast );
	std::cout << std::endl;
	std::cout << (char*) *slow << ", " << (char*) *fast << std::endl;
	std::cout << "finished." << std::endl;
	std::exit(EXIT_SUCCESS);
}
