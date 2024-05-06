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
			if ( lessthanoreq( LList_begin(a)->dataptr, LList_begin(b)->dataptr) ) {
				LList_append(dst, LList_pop(a));
			} else {
				LList_append(dst, LList_pop(b));
			}
		}
	}
}

void merge_sort_llist(LList * list) {
	int n = list->elemcount;
	if (n <= 1)
		return;
	LList * a, * b;
	LList_init(a);
	LList_init(b);
	ListNode * ptr = LList_begin(list), * probe = ptr;
	while ( probe != LList_last(list) && probe != LList_end(list)) {
		ptr = ptr->next;
		probe = probe->next->next;
	}
	LList_apart(list, ptr, b);
	merge_sort_llist(a);
	merge_sort_llist(b);
	merge_llist(list, a, b);
	return;
}

