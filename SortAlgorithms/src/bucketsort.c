/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef void * data;

void bucketsort(const data d[], LList * outlist, int n, int bsize, int (*key)(const data)) {
	LList list[bsize];
	int k;
	for(int i = 0; i < bsize; ++i) {
		LList_init(&list[i]);
	}
	for(int i = 0; i < n; ++i) {
		k = key(d[i]);
		LList_append(&list[k],d[i]);
	}
	for(int i = 0; i < bsize; ++i) {
		while ( ! LList_is_empty(&list[i]) ) {
			LList_append_node(outlist, LList_pop_node(&list[i]));
			printf("%d ",list[k].elemcount);
		}
	}
}

int key(const data d) {
	return (long)d;
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	long d[n];
	for (int i = 0; i < n; ++i) {
		d[i] = atoi(argv[1+i]);
	}
	printf("input: \n");
	for (int i = 0; i < n; ++i) {
		printf("%ld, ", d[i]);
	}
	printf("\n\n");

	LList result;
	LList_init(&result);
	bucketsort((data *)d, &result, n, 100, key);

	printf("\n");
	for(ListNode * litr = LList_begin(&result);
			litr != LList_end(&result); litr = litr->next) {
		printf("%ld, ", (long) litr->data);
	}
	printf(".\n");

	LList_free(&result);
	return 0;
}
