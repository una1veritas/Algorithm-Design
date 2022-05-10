/*
 * bucketsort.c
 */
#include <datadef.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

void bucketSort_list(LList * dlist, long m, long (*key)(const data)) {
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

void bucketSort(data a[], long n, long m, long (*key)(const data)) {
	LList list[m];
	for(long i = 0; i < m; ++i) {
		LList_init(&list[i]);
	}
	for (long i = 0; i < n; ++i) {
		LList_append(&list[key(a[i])], a[i]);
	}
	long count = 0;
	for(int i = 0; i < m; ++i) {
		while ( ! LList_is_empty(&list[i]) ) {
			a[count] = LList_pop(&list[i]);
			count += 1;
		}
		LList_free(&list[i]);
	}
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	data a[n];
	for (int i = 0; i < n; ++i) {
		a[i] = (long) atoi(argv[1+i]);
	}
	printf("input: \n");
	for(int i = 0; i < n; ++i) {
		printf("%ld, ", a[i]);
	}
	printf("\n");
	printf("size %d\n\n", n);

	bucketSort(a, n, 100, keycode);

	for(int i = 0; i < n; ++i) {
		printf("%ld, ", a[i]);
	}
	printf("\n\n");

	return 0;
}
