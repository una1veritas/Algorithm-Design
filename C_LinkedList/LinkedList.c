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
	list->tailptr->next = (ListNode*) malloc(sizeof(ListNode));
	list->tailptr = list->tailptr->next;
	list->tailptr->data = data;
	list->tailptr->next = NULL;
	list->elemcount += 1;
	return list->tailptr;
}

ListNode * LinkedList_push(LinkedList * list, void * data) {
	ListNode * t_node = (ListNode*) malloc(sizeof(ListNode));
	t_node->data = data;
	t_node->next = list->head.next;
	list->head.next = t_node;
	if ( list->tailptr == &list->head )
		list->tailptr = t_node;
	list->elemcount += 1;
	return t_node;
}

void * LinkedList_pop(LinkedList * list) {
	if ( list->elemcount == 0 ) {
		/* tried pop an empty list */
		fprintf(stderr, "Error: LinkedList_pop: list is empty.\n");
		return NULL;
	}
	ListNode * ptr = list->head.next;
	void * d = ptr->data;
	list->head.next = ptr->next;
	if ( list->tailptr == ptr ) {
		list->tailptr = &list->head;
	}
	free(ptr);
	list->elemcount -= 1;
	return d;
}

ListNode * LinkedList_begin(LinkedList * list) {
	return list->head.next;
}

ListNode * LinkedList_last(LinkedList * list) {
	return list->tailptr;
}

ListNode * LinkedList_end(LinkedList * list) {
	return NULL;
}

ListNode * LinkedList_find(LinkedList * list, void * dataptr) {
	ListNode * preptr = &list->head;
	while ( preptr != list->tailptr ) {
		if ( preptr->next->data == dataptr ) {
			return preptr;
		}
	}
	return NULL;
}


int LinkedList_is_empty(LinkedList * list) {
	return list->elemcount == 0;
}

void LinkedList_printf(LinkedList * list, char * sep) {
	ListNode * ptr = list->head.next;
	while ( ptr != NULL ) {
		printf("%p%s", ptr->data, sep);
		ptr = ptr->next;
	}
}
