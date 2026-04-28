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
	data dataptr;
	struct ListNode * next, * prev;
} ListNode;

typedef struct LList {
	ListNode head;
	ListNode tail;
	long elemcount;
} LList;

LList * LList_init(LList *);
void LList_free(LList *);
void LList_fprintf(FILE *, LList *, const char * fmt);

ListNode * LList_push_back(LList * list, data);
ListNode * LList_push_front(LList * list, data);
data LList_pop_back(LList * list);
data LList_pop_front(LList * list);
//data LList_peek_front(LList * list);
//data LList_peek_back(LList * list);
ListNode * LList_begin(LList * list);
ListNode * LList_end(LList * list);
ListNode * LList_find(LList * list, const data d, int (*equals)(const data, const data) );
ListNode * LList_remove(LList * list, const data d, int (*equals)(const data, const data) );
ListNode * LList_last(LList * list);
int LList_is_empty(LList * list);

ListNode * LList_find_r(LList * list, ListNode * node, const data d, int (*equals)(const data, const data) );

#endif /* LLIST_H_ */
