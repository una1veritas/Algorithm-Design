/*
 * linkedlist.h
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdbool.h>

typedef struct ListNode {
	const char * datastr;
	struct ListNode * prev, * next;
} ListNode;

typedef struct LinkedList {
	ListNode * head;
	ListNode * tail;
	unsigned int elemcount;
} LinkedList;

bool LinkedList_append(LinkedList * llistptr, const char * datastr);
void LinkedList_free(LinkedList * listptr);

#endif /* LINKEDLIST_H_ */
