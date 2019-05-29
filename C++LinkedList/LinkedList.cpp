/*
 * LinkedList.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include "LinkedList.h"

const void * LinkedList::Iterator::data() const {
	if ( preptr == NULL) {
		std::cerr << "LinkedList::Iterator::data() accessed NULL ptr." << std::endl;
	}
	return preptr->next->data;
}
LinkedList::Iterator & LinkedList::Iterator::operator++() { preptr = preptr->next; return *this; }
LinkedList::Iterator & LinkedList::Iterator::operator+=(int offset) {
	while ( offset-- ) {
		if ( preptr == NULL) {
			std::cerr << "LinkedList::Iterator::data() accessed NULL ptr." << std::endl;
			break;
		}
		preptr = preptr->next;
	}
	return *this;
}
const bool LinkedList::Iterator::operator==(const Iterator & itr) const {
	return preptr == itr.preptr;
}
const bool LinkedList::Iterator::operator!=(const Iterator & itr) const {
	return preptr != itr.preptr;
}


LinkedList::LinkedList() : head(0, NULL) {
	tailptr = &head;
	elemcount = 0;
}

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
		out << reinterpret_cast<unsigned long long>(ptr->next->data) << ' ';
		if ( ptr == tailptr )
			break;
		ptr = ptr->next;
	}
	return out;
}
