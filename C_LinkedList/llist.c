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
}

// append as the last node
ListNode * LList_append(LList * list, data d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->data = d;
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
ListNode * LList_push(LList * list, data d) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->data = d;
	node->next = list->head.next;
	list->head.next = node;
	node->next->prev = node;
	node->prev = &list->head;
	list->elemcount += 1;
	return node;
}

data LList_pop(LList * list) {
	ListNode * node = LList_pop_node(list);
	data d = node->data;
	free(node);
	return d;
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

ListNode * LList_begin(LList * list) {
	return list->head.next;
}

ListNode * LList_last(LList * list) {
	return list->tail.prev;
}

ListNode * LList_end(LList * list) {
	return &list->tail;
}

int LList_is_empty(LList * list) {
	return list->elemcount == 0;
}

void LList_printf(LList * list, char * sep) {
	ListNode * node = list->head.next;
	while ( node->next != &list->tail ) {
		printf("%p %s ", node->data, sep);
		node = node->next;
	}
}
