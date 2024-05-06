/*
 * llist.c
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datadef.h"
#include "llist.h"

LList * LList_init(LList * list) {
	list->head.next = &list->tail;
	list->head.prev = NULL;
	list->tail.next = NULL;
	list->tail.prev = &list->head;
	list->elemcount = 0;
	return list;
}

/*
void LList_part(LList * list, ListNode * ptr, LList * head, LList * tail) {
	head->head.next = list->head.next;
	head->head.prev = NULL;
	head->tail.next = list->head.next;
}
*/

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

/*
int LList_length(LList * list) {
	return list->elemcount;
}
*/

// append the node with data as the last node of list
ListNode * LList_append(LList * list, data * ptr) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->dataptr = ptr;
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

// push the node with data into the front of list
ListNode * LList_push(LList * list, data * ptr) {
	ListNode * node = (ListNode*) malloc(sizeof(ListNode));
	node->dataptr = ptr;
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

// pop from the front of list
data * LList_pop(LList * list) {
	ListNode * node = LList_pop_node(list);
	data * d = node->dataptr;
	free(node);
	return d;
}


data * LList_peek(LList * list) {
	if ( list->elemcount == 0 ) {
		/* tried pop an empty list */
		fprintf(stderr, "Error: LList_peek: list is empty.\n");
		return list->head.dataptr;
	}
	return list->head.next->dataptr;
}

ListNode * LList_begin(LList * list) {
	return list->head.next;
}

ListNode * LList_end(LList * list) {
	return &list->tail;
}

//ListNode * LList_find(LList * list, const data * ptr, int (*equals)(const data, const data) ) {
ListNode * LList_find(LList * list, const data * ptr) {
	ListNode * node;
	for(node = LList_begin(list);
			node != LList_end(list); node = node->next) {
		if ( equals(ptr, node->dataptr) )
			return node;
	}
	return node;
}

ListNode * LList_remove(LList * list, const data * d ) {
	ListNode * node = LList_find(list, d);
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

void LList_apart(LList * list, ListNode * nodeptr, LList * b) {
	LList_init(b);
	ListNode * lastnode = &list->head;
	// エラー処理

	b->head = *nodeptr;
	b->tail = *nodeptr;
	b->elemcount = 1;
	int count = 1;
	while ( lastnode != NULL ) {
		if ( lastnode == nodeptr || lastnode->next == nodeptr ) {
			break;
		}
		lastnode = lastnode->next;
		++count;
	}
	if (lastnode == NULL) {
		fprintf(stderr, "LList_apart encountered NULL.\n");
		return;
	}
	list->tail = *lastnode;
	b->elemcount = list->elemcount - count;
	list->elemcount = count;
}

void LList_fprintf(FILE * f, LList * list, const char * fmt) {
	ListNode * node = list->head.next;
	while ( node != &list->tail ) {
		fprintf(f, fmt, node->dataptr);
		node = node->next;
	}
}
