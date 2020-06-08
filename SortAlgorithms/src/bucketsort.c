/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#define DATA int

#include "llist.h"

void bucketsort(LList * dlist, int n, int bsize, int (*key)(const data)) {
	LList list[bsize];
	ListNode * node;
	for(int i = 0; i < bsize; ++i) {
		LList_init(&list[i]);
	}
	while ( !LList_is_empty(dlist) ) {
		node = LList_pop_node(dlist);
		LList_append_node(&list[key(node->data)], node);
	}
	for(int i = 0; i < bsize; ++i) {
		while ( ! LList_is_empty(&list[i]) ) {
			node = LList_pop_node(&list[i]);
			LList_append_node(dlist, node);
		}
	}
}

int key(const data d) {
	return (int)((long long) d);
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	LList list;
	LList_init(&list);
	for (int i = 0; i < n; ++i) {
		LList_append(&list, (data)(long long) atoi(argv[1+i]));
	}
	printf("input: \n");
	for (ListNode * i = LList_begin(&list);
			i != LList_end(&list); i = i->next) {
		printf("%d, ", (int) (long long) i->data);
	}
	printf("\n\n");
	fflush(stdout);

	bucketsort(&list, n, 100, key);

	for(ListNode * i = LList_begin(&list);
			i->next != NULL; i = i->next) {
		printf("%d, ", (int) (long long) i->data );
	}
	printf("\n");
	printf("size %d\n", list.elemcount);

	LList_free(&list);
	return 0;
}
