/*
 * mergesort.c
 *
 *  Created on: 2023/05/09
 *      Author: Sin Shimozono
 */

#include "datadef.h"
#include "llist.h"

void merge_llist(LList * dst, LList * a, LList * b) {
	while ( ! LList_is_empty(a) || ! LList_is_empty(b) ) {
		if ( LList_is_empty(a) ) {
			LList_append(dst, LList_pop(b));
		} else if ( LList_is_empty(b) ) {
			LList_append(dst, LList_pop(a));
		} else {
			if ( lessthanoreq( & LList_begin(a)->data, & LList_begin(b)->data) ) {
				LList_append(dst, LList_pop(a));
			} else {
				LList_append(dst, LList_pop(b));
			}
		}
	}
}

void merge_sort_llist(LList * list) {
	int n = LList_size(list);
	if (n <= 1)
		return;
	LList a, b;
	LList_init(&a);
	LList_init(&b);
	ListNode * ptr = list->head.next;
	while (ptr != list->tail.prev && ptr != &list->tail ) {
		ptr = ptr->next->next;
		LList_append_node(&a, LList_pop_node(list) );
	}
	while ( ! LList_is_empty(list) ) {
		LList_append_node(&b, LList_pop_node(list));
	}
	merge_sort_llist(&a);
	merge_sort_llist(&b);
	merge_llist(list, &a, &b);
	return;
}

