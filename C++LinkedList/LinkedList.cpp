/*
 * LinkedList.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include "LinkedList.h"


LinkedList::LinkedList() {
	head = new ListNode(NULL, NULL);
	tail = head;
	elemcount = 0;
}

LinkedList::~LinkedList() {
	ListNode * t;
	while ( head->next != NULL ) {
		t = head;
		head = head->next;
		delete t;
	}
	delete head;
}

ListNode * LinkedList::append(const void* dptr) {
	ListNode * newnode = new ListNode(dptr, NULL);
	tail->next = newnode;
	elemcount += 1;
	tail = tail->next;
	return newnode;
}

ListNode * LinkedList::push(const void* d) {
	head->data = d;
	head = new ListNode(d, head);
	elemcount += 1;
	return head->next;
}

const void * LinkedList::pop() {
	ListNode * t = head;
	const void* d;
	head = head->next;
	d = head->data;
	delete t;
	elemcount -= 1;
	return d;
}

ListNode * LinkedList::make_tail_loop(unsigned int ith) {
	ListNode * ptr = head->next;
	while ( ptr->next != NULL and ith != 0 ) {
		ptr = ptr->next;
		ith -= 1;
	}
	if ( ptr == NULL ) {
		tail->next = tail;
	}
	tail->next = ptr;
	return tail->next;
}
