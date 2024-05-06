/*
 * llist.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LLIST_H_
#define LLIST_H_

#include "datadef.h"

typedef struct ListNode {
	data * dataptr;
	struct ListNode * next, * prev;
} ListNode;

typedef struct LList {
	ListNode head;
	ListNode tail;
	int elemcount;
} LList;

LList * LList_init(LList *);
void LList_free(LList *);
void LList_fprintf(FILE *, LList *, const char * fmt);

//int LList_length(LList * );
data * LList_pop(LList * list);
data * LList_peek(LList * list);
ListNode * LList_append(LList * list, data *);
ListNode * LList_push(LList * list, data *);
ListNode * LList_append_node(LList * list, ListNode * node);
ListNode * LList_pop_node(LList * list);
ListNode * LList_begin(LList * list);
ListNode * LList_end(LList * list);
ListNode * LList_find(LList * list, const data * d);
ListNode * LList_remove(LList * list, const data * d);
ListNode * LList_last(LList * list);
void LList_apart(LList * list, ListNode * nodeptr, LList * b);

int LList_is_empty(LList * list);

#endif /* LLIST_H_ */
