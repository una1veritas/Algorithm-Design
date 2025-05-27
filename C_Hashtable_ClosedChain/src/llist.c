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
	list->head.next = &list->tail;
	list->head.prev = NULL;
	list->tail.next = NULL;
	list->tail.prev = &list->head;
	list->elemcount = 0;
	return list;
}

void LList_free(LList * list) {
	ListNode * t;
	while ( list->head.next != &list->tail ) {
		t = list->head.next;
		list->head.next = t->next;
		free(t);
	}
	list->tail.prev = &list->head;
	list->elemcount = 0;
}

// append as the last node
ListNode * LList_append(LList * list, const datatype * d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	memcpy(& node->data, d, sizeof(datatype));
	LList_append_node(list, node);
	return node;
}

ListNode * LList_append_node(LList * list, ListNode * node) {
	node->next = &list->tail;
	node->prev = list->tail.prev;
	node->prev->next = node;
	list->tail.prev = node;
	list->elemcount += 1;
	return node;
}

// push into the first node
ListNode * LList_push(LList * list, const datatype * d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	memcpy(& node->data, d, sizeof(datatype));
	node->next = list->head.next;
	list->head.next = node;
	node->next->prev = node;
	node->prev = &list->head;
	list->elemcount += 1;
	return node;
}

ListNode * LList_pop_node(LList * list) {
	if ( list->elemcount == 0 ) {
		/* tried pop an empty list */
		fprintf(stderr, "Error: LList_pop: list is empty.\n");
		return NULL;
	}
	ListNode * node = list->head.next;
	list->head.next = node->next;
	node->next->prev = &list->head;
	list->elemcount -= 1;
	return node;
}

datatype LList_pop(LList * list) {
	ListNode * node = LList_pop_node(list);
	datatype d = node->data;
	free(node);
	return d;
}

ListNode * LList_begin(LList * list) {
	return list->head.next;
}

ListNode * LList_end(LList * list) {
	return &list->tail;
}

ListNode * LList_find(LList * list, const datatype * d, int (*equals)(const datatype *, const datatype *) ) {
	ListNode * node;
	for(node = LList_begin(list);
			node != LList_end(list); node = node->next) {
		if ( equals(d, & node->data) )
			return node;
	}
	return node;
}

ListNode * LList_remove(LList * list, const datatype * d, int (*equals)(const datatype *, const datatype *) ) {
	ListNode * node = LList_find(list, d, equals);
	if ( node != LList_end(list) ) {
		node->next->prev = node->prev;
		node->prev->next = node->next;
		free(node);
		node = NULL;
		list->elemcount -= 1;
	}
	return node;
}

ListNode * LList_last(LList * list) {
	return list->tail.prev;
}

int LList_is_empty(LList * list) {
	return list->elemcount == 0;
}

void LList_fprintf(FILE * f, LList * list, const char * fmt) {
	ListNode * node = list->head.next;
	while ( node != &list->tail ) {
		fprintf(f, fmt, node->data);
		node = node->next;
	}
}
