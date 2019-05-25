/*
 * LinkedList.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include "LinkedList.h"

LinkedList::LinkedList() {
	head = new ListNode(0, NULL);
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

ListNode * LinkedList::append(void * dptr) {
	ListNode * newnode = new ListNode(dptr, NULL);
	tail->next = newnode;
	elemcount += 1;
	tail = tail->next;
	return newnode;
}

ListNode * LinkedList::push(void * dataptr) {
	head->data = dataptr;
	head = new ListNode(dataptr, head);
	elemcount += 1;
	return head->next;
}

void * LinkedList::pop() {
	ListNode * t = head;
	void * dataptr;
	head = head->next;
	dataptr = head->data;
	delete t;
	elemcount -= 1;
	return dataptr;
}

