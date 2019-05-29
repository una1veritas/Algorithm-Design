/*
 * LinkedList.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

LinkedList * LinkedList_init(LinkedList * list) {
	list->head.next = NULL;
	list->tailptr = &list->head;
	list->elemcount = 0;
	return list;
}

void LinkedList_free(LinkedList * list) {
	ListNode * ptr = list->head.next;
	ListNode * t;
	while ( ptr != NULL ) {
		t = ptr;
		ptr = ptr->next;
		free(t);
	}
}

ListNode * LinkedList_append(LinkedList * list, void * data) {
	ListNode * newnode = (ListNode*) malloc(sizeof(ListNode));
	newnode->data = data;
	newnode->next = NULL;
	list->tailptr->next = newnode;
	list->tailptr = newnode;
	list->elemcount += 1;
	return newnode;
}

ListNode * LinkedList_push(LinkedList * list, void * data) {
	ListNode * newnode = (ListNode*) malloc(sizeof(ListNode));
	newnode->data = data;
	newnode->next = list->head.next;
	list->head.next = newnode;
	list->tailptr = newnode;
	list->elemcount += 1;
	return newnode;
}

void * LinkedList_pop(LinkedList * list) {
	ListNode * ptr = list->head.next;
	void * d = ptr->data;
	list->head.next = ptr->next;
	free(ptr);
	list->elemcount -= 1;
	return d;
}

void LinkedList_printf(LinkedList * list, char * sep) {
	ListNode * ptr = list->head.next;
	while ( ptr != NULL ) {
		printf("%p%s", ptr->data, sep);
		ptr = ptr->next;
	}
}
