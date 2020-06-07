/*
 * llist.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LLIST_H_
#define LLIST_H_

typedef void * data;

typedef struct ListNode {
	void * data;
	struct ListNode * next, * prev;
} ListNode;

typedef struct LList {
	ListNode head;
	ListNode tail;
	int elemcount;
} LList;

LList * LList_init(LList *);
void LList_free(LList *);
void LList_printf(LList *, char * sep);

ListNode * LList_append(LList * list, data);
ListNode * LList_push(LList * list, data);
data LList_pop(LList * list);
ListNode * LList_append_node(LList * list, ListNode * node);
ListNode * LList_pop_node(LList * list);
ListNode * LList_begin(LList * list);
ListNode * LList_last(LList * list);
ListNode * LList_end(LList * list);

int LList_is_empty(LList * list);

#endif /* LLIST_H_ */
