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

LList * LinkedList_init(LList * list) {
	list->head.next = NULL;
	list->tailptr = &list->head;
	list->elemcount = 0;
	return list;
}

void LinkedList_free(LList * list) {
	ListNode * ptr = list->head.next;
	ListNode * t;
	while ( ptr != NULL ) {
		t = ptr;
		ptr = ptr->next;
		free(t);
	}
}

ListNode * LinkedList_append(LList * list, void * data) {
	ListNode * newnode = (ListNode*) malloc(sizeof(ListNode));
	newnode->data = data;
	newnode->next = NULL;
	list->tailptr->next = newnode;
	list->tailptr = newnode;
	list->elemcount += 1;
	return newnode;
}

ListNode * LinkedList_push(LList * list, void * data) {
	ListNode * newnode = (ListNode*) malloc(sizeof(ListNode));
	newnode->data = data;
	newnode->next = list->head.next;
	list->head.next = newnode;
	list->tailptr = newnode;
	list->elemcount += 1;
	return newnode;
}

void * LinkedList_pop(LList * list) {
	ListNode * ptr = list->head.next;
	void * d = ptr->data;
	list->head.next = ptr->next;
	free(ptr);
	list->elemcount -= 1;
	return d;
}

ListNode * LinkedList_begin(LList * list) {
	return &list->head;
}

ListNode * LinkedList_end(LList * list) {
	return list->tailptr;
}

ListNode * LinkedList_find(LList * list, void * data) {
	ListNode * preptr = &list->head;
	while ( preptr != list->tailptr ) {
		if ( preptr->next->data == data ) {
			return preptr;
		}
	}
	return NULL;
}

void * LinkedList_remove(LList * list, void * data) {
	ListNode * preptr = &list->head;
	while ( preptr != list->tailptr ) {
		if ( preptr->next->data == data ) {
			break;
		}
	}
	if ( preptr == list->tailptr ) {
		return NULL;
	}
	return preptr->next->data;
}


void LinkedList_printf(LList * list, char * sep) {
	ListNode * ptr = list->head.next;
	while ( ptr != NULL ) {
		printf("%p%s", ptr->data, sep);
		ptr = ptr->next;
	}
}
