/*
 * LinkedList.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <cstddef>

#ifndef NULL
#define nullptr NULL
#endif

struct ListNode {
public:
	const void* data;
	ListNode * next;

public:
	ListNode(const void* d, ListNode * nodeptr = NULL) : data(d), next(nodeptr) { }
};


struct LinkedList {
public:
	ListNode head;
	ListNode * tailptr;
	unsigned int elemcount;

public:

	struct Iterator {
		ListNode * prevptr;

		Iterator(ListNode * ptr) : prevptr(ptr) { }
		Iterator & operator++() { prevptr = prevptr->next; return *this; }
		bool operator !=(const Iterator & itr) const { return (prevptr != itr.prevptr); }
		ListNode & operator*()  { return *(prevptr->next); }
		ListNode * operator->() { return prevptr->next; }
	};

public:
	LinkedList() : head(0, NULL), tailptr(&head), elemcount(0) { }
	~LinkedList();
	unsigned int size() const { return elemcount; }

	ListNode * append(const void* dataptr);
	ListNode * push(const void* dataptr);
	const void * pop();
	std::ostream & printOn(std::ostream & out) const;

	Iterator begin() { return Iterator(&head); }
	Iterator end()   { return Iterator(tailptr); }

	ListNode * make_tail_loop(unsigned int ith);

	friend std::ostream & operator<<(std::ostream & out, LinkedList & list) {
		return list.printOn(out);
	}

};

#endif /* LINKEDLIST_H_ */
