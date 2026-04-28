/*
 * llist.c
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

bool LinkedList_append(LinkedList * llistptr, const char * datastr) {
	ListNode * nodeptr = (ListNode *) malloc(sizeof(ListNode));
	if ( nodeptr == NULL )
		return false;
	if ( llistptr->tail == NULL ) {
		// リストがカラ
		llistptr->head = nodeptr;
		llistptr->tail = nodeptr;
		nodeptr->prev = NULL;
		nodeptr->next = NULL;
	} else {
		nodeptr->prev = llistptr->tail;
		nodeptr->next = NULL;
		nodeptr->prev->next = nodeptr;
		llistptr->tail = nodeptr;
	}
	nodeptr->datastr = datastr;

	llistptr->elemcount += 1;
	return true;
}

bool LinkedList_remove(LinkedList * llistptr) {
	ListNode * nodeptr = llistptr->tail;
	if ( nodeptr == NULL )
		return false;
	if ( nodeptr->prev == NULL ) {
		free(nodeptr);
		llistptr->head = NULL;
		llistptr->tail = NULL;
		llistptr->elemcount = 0;
	} else {
		nodeptr = nodeptr->prev;
		llistptr->tail = nodeptr;
		free(nodeptr->next);
		llistptr->elemcount -= 1;
	}
	return true;
}

void LinkedList_free(LinkedList * llistptr) {
	while ( LinkedList_remove(llistptr) ) {}
}
