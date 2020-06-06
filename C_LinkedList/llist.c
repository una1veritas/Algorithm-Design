/*
 * llist.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

LList * LList_init(LList * list) {
	list->head = NULL;        // the last node has NULL next.
	list->tail = NULL;  // got the end then prev == list->head
	list->elemcount = 0;
	return list;
}

void LList_free(LList * list) {
	ListNode * last;
	while ( list->head != NULL ) {
		last = list->head;
		list->head = last->next;
		free(last);
	}
	list->tail = NULL;
}

// append as the last node
ListNode * LList_append(LList * list, data d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->data = d;
	node->next = NULL;
	node->prev = list->tail;
	if ( list->tail == NULL ) {
		list->head = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
	list->elemcount += 1;
	return node;
}

ListNode * LList_append_node(LList * list, ListNode * node) {
	node->next = NULL;
	node->prev = list->tail;
	if ( list->tail == NULL ) {
		list->head = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
	list->elemcount += 1;
	return node;
}

// push into the first node
ListNode * LList_push(LList * list, data d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->data = d;
	node->next = list->head;
	node->prev = NULL;
	list->head = node;
	if ( list->elemcount == 0 ) {
		// ( list->tail == NULL )
		list->tail = node;
	} else {
		// ( node->next != NULL )
		node->next->prev = node;
	}
	list->elemcount += 1;
	return node;
}

data LList_pop(LList * list) {
	data d;
	if ( list->elemcount == 0 ) {
		/* tried pop an empty list */
		fprintf(stderr, "Error: LList_pop: list is empty.\n");
		return NULL;
	}
	ListNode * node = list->head;
	list->head = node->next;
	list->head->prev = NULL;
	d = node->data;
	free(node);
	list->elemcount -= 1;
	return d;
}

ListNode * LList_pop_node(LList * list) {
	if ( list->elemcount == 0 ) {
		/* tried pop an empty list */
		fprintf(stderr, "Error: LList_pop: list is empty.\n");
		return NULL;
	}
	ListNode * node = list->head;
	list->head = node->next;
	list->head->prev = NULL;
	list->elemcount -= 1;
	return node;
}

ListNode * LList_begin(LList * list) {
	return list->head;
}

ListNode * LList_last(LList * list) {
	return list->tail;
}

ListNode * LList_end(LList * list) {
	return NULL;
}

ListNode * LList_find(LList * list, data d) {
	for(ListNode * node = list->head;
			node != NULL; node = node->next ) {
		if ( node->data == d ) {
			return node;
		}
	}
	return NULL;
}


int LList_is_empty(LList * list) {
	return list->elemcount == 0;
}

void LList_printf(LList * list, char * sep) {
	ListNode * node = list->head;
	while ( node != NULL ) {
		printf("%p %s ", node->data, sep);
		node = node->next;
	}
}
