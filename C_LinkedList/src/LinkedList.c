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
	list->head = (LinkedListNode*) malloc(sizeof(LinkedListNode));
	list->head->next = NULL;
	list->tail = list->head;
	list->elemcount = 0;
	return list;
}

void LinkedList_free(LinkedList * list) {
	LinkedListNode * ptr = list->head->next;
	LinkedListNode * t;
	while ( ptr != NULL ) {
		t = ptr;
		ptr = ptr->next;
		free(t);
	}
	free(list->head);
}

LinkedListNode * LinkedList_append(LinkedList * list, datatype s) {
	LinkedListNode * newnode = (LinkedListNode*) malloc(sizeof(LinkedListNode));
	strcpy(newnode->data, s);
	newnode->next = NULL;
	list->tail->next = newnode;
	list->tail = newnode;
	list->elemcount += 1;
	return newnode;
}

LinkedListNode * LinkedList_push(LinkedList * list, datatype s) {
	LinkedListNode * newnode = (LinkedListNode*) malloc(sizeof(LinkedListNode));
	strcpy(newnode->data, s);
	newnode->next = list->head->next;
	list->head->next = newnode;
	list->tail = newnode;
	list->elemcount += 1;
	return newnode;
}

void LinkedList_printf(LinkedList * list, char * sep) {
	LinkedListNode * ptr = list->head->next;
	while ( ptr != NULL ) {
		printf("%s%s", ptr->data, sep);
		ptr = ptr->next;
	}
}
