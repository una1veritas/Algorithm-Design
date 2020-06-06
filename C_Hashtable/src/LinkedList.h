/*
 * LinkedList.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct ListNode {
	void * data;
	struct ListNode * next;
} ListNode;

typedef struct LList {
	ListNode head;
	ListNode * tailptr;
	unsigned int elemcount;
} LList;

LList * LinkedList_init(LList *);
void LinkedList_free(LList *);
void LinkedList_printf(LList *, char * sep);

ListNode * LinkedList_append(LList * list, void*);
ListNode * LinkedList_push(LList * list, void*);
void * LinkedList_pop(LList * list);
ListNode * LinkedList_begin(LList * list);
ListNode * LinkedList_end(LList * list);
ListNode * LinkedList_find(LList * list, void*);
void * LinkedList_remove(LList * list, void*);

#endif /* LINKEDLIST_H_ */
