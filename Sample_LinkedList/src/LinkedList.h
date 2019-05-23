/*
 * LinkedList.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef char datatype[32];
typedef struct LinkedListNode {
	datatype data;
	struct LinkedListNode * next;
} LinkedListNode;
typedef struct LinkedList {
	LinkedListNode * head;
	LinkedListNode * tail;
	unsigned int elemcount;
} LinkedList;

LinkedList * LinkedList_init(LinkedList *);
void LinkedList_free(LinkedList *);
void LinkedList_printf(LinkedList *, char * sep);

LinkedListNode * LinkedList_append(LinkedList * list, datatype);
LinkedListNode * LinkedList_push(LinkedList * list, datatype);
datatype * LinkedList_pop(LinkedList * list);

#endif /* LINKEDLIST_H_ */
