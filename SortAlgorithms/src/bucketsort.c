/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

long key(const data d) {
	return (long) d;
}

void bucketSort(LList * dlist, long m, long (*key)(const data)) {
	LList list[m];
	ListNode * node;
	for(int i = 0; i < m; ++i) {
		LList_init(&list[i]);
	}
	while ( !LList_is_empty(dlist) ) {
		node = LList_pop_node(dlist);
		LList_append_node(&list[key(node->data)], node);
	}
	for(int i = 0; i < m; ++i) {
		while ( ! LList_is_empty(&list[i]) ) {
			node = LList_pop_node(&list[i]);
			LList_append_node(dlist, node);
		}
	}
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	LList list;
	LList_init(&list);
	for (int i = 0; i < n; ++i) {
		LList_append(&list, (long) atoi(argv[1+i]));
	}
	printf("input: \n");
	LList_fprintf(stdout, &list, "%ld, ");
	printf("\n\n");
	fflush(stdout);

	bucketSort(&list, 100, key);

	LList_fprintf(stdout, &list, "%ld, ");
	printf("\n");
	printf("size %d\n", list.elemcount);

	LList_free(&list);
	return 0;
}
