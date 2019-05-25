#include <iostream>
#include <cstdlib>

#include "LinkedList.h"

int main(const int argc, const char *argv[]) {
	LinkedList list;

	std::cout << "Sample LinkedList main." << std::endl;

	list.append((void*) "Hello.");
	list.append((void*) "What is your name?");
	list.push((void*) "Hi!");
	std::cout << std::endl << "list size = " << list.size() << std::endl;
	for(ListNode * ptr = list.head->next; ptr != NULL; ptr = ptr->next ) {
		std::cout << (char*) ptr->data << " (" << (unsigned long) ptr->data << ") ";
	}
	std::cout << std::endl;
	std::cout << (char *) list.pop() << std::endl;
	std::cout << "list size = " << list.size() << std::endl;
	for(ListNode * ptr = list.head->next; ptr != NULL; ptr = ptr->next ) {
		std::cout << (char*) ptr->data << " (" << (unsigned long) ptr->data << ") ";
	}
//	std::cout << list << std::endl;
	std::cout << std::endl;
	std::exit(EXIT_SUCCESS);
}
