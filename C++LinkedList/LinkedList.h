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
	void * data;
	ListNode * next;

public:
	ListNode(void * ptr = NULL, ListNode * nodeptr = NULL) {
		data = ptr;
		next = nodeptr;
	}
};

struct LinkedList {
public:
	ListNode * head;
	ListNode * tail;
	unsigned int elemcount;

public:
	LinkedList();
	~LinkedList();
	unsigned int size() const { return elemcount; }

//	void LinkedList_printf(LinkedList *, char * sep);

	ListNode * append(void * dataptr);
	ListNode * push(void * dataptr);
	void * pop();

	friend std::ostream & operator<<(std::ostream & out, const LinkedList & list) {
		ListNode * ptr = list.head->next;
		while ( ptr != NULL ) {
			out << (unsigned long) ptr->data;
			ptr = ptr->next;
		}
		return out;
	}

};

#endif /* LINKEDLIST_H_ */
