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

typedef struct LinkedList {
	ListNode head;
	ListNode * tailptr;
	unsigned int elemcount;
} LinkedList;

LinkedList * LinkedList_init(LinkedList *);
void LinkedList_free(LinkedList *);
void LinkedList_printf(LinkedList *, char * sep);

ListNode * LinkedList_append(LinkedList * list, void*);
ListNode * LinkedList_push(LinkedList * list, void*);
void * LinkedList_pop(LinkedList * list);
ListNode * LinkedList_begin(LinkedList * list);
ListNode * LinkedList_end(LinkedList * list);
ListNode * LinkedList_find(LinkedList * list, void*);
void * LinkedList_remove(LinkedList * list, void*);

#endif /* LINKEDLIST_H_ */
