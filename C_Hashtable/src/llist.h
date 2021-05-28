/*
 * llist.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LLIST_H_
#define LLIST_H_

#include "datatype.h"

typedef struct ListNode {
	datatype data;
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

ListNode * LList_append(LList * list, datatype);
ListNode * LList_push(LList * list, datatype);
datatype LList_pop(LList * list);
ListNode * LList_append_node(LList * list, ListNode * node);
ListNode * LList_pop_node(LList * list);
ListNode * LList_begin(LList * list);
ListNode * LList_end(LList * list);
ListNode * LList_find(LList * list, const datatype d, int (*equals)(const datatype, const datatype) );
ListNode * LList_remove(LList * list, const datatype d, int (*equals)(const datatype, const datatype) );
ListNode * LList_last(LList * list);
int LList_is_empty(LList * list);

#endif /* LLIST_H_ */
