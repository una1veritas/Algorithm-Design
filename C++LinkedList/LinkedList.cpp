/*
 * LinkedList.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include "LinkedList.h"


LinkedList::~LinkedList() {
	ListNode * t;
	while ( head.next != NULL ) {
		t = head.next;
		head.next = head.next->next;
		delete t;
	}
}

ListNode * LinkedList::append(const void* dptr) {
	ListNode * newnode = new ListNode(dptr, NULL);
	tailptr->next = newnode;
	elemcount += 1;
	tailptr = newnode;
	return newnode;
}

ListNode * LinkedList::push(const void* d) {
	head.next = new ListNode(d, head.next);
	elemcount += 1;
	return head.next;
}

const void * LinkedList::pop() {
	ListNode * t = head.next;
	const void* d = t->data;
	head.next = t->next;
	delete t;
	elemcount -= 1;
	return d;
}

ListNode * LinkedList::make_tail_loop(unsigned int ith) {
	ListNode * ptr = head.next;
	while ( ptr != NULL and ith != 0 ) {
		ptr = ptr->next;
		ith -= 1;
	}
	if ( ptr == NULL ) {
		tailptr->next = tailptr;
	} else {
		tailptr->next = ptr;
	}
	return tailptr->next;
}

std::ostream & LinkedList::printOn(std::ostream & out) const {
	const ListNode * ptr = &head;
	while ( ptr->next != NULL ) {
		out << "(" << std::hex << ptr->next->data << ", " << std::hex << ptr->next->data << "), ";
		if ( ptr == tailptr )
			break;
		ptr = ptr->next;
	}
	return out;
}
