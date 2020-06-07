/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef void * data;

void bucketsort(const data d[], LList * outlist, int n, int bsize, int (*key)(const data)) {
	LList list[bsize];
	for(int i = 0; i < bsize; ++i) {
		LList_init(&list[i]);
	}
	for(int i = 0; i < n; ++i) {
		LList_append(&list[key(d[i])],d[i]);
	}
	for(int i = 0; i < bsize; ++i) {
		for(ListNode * ptr = LList_begin(&list[i]);
				ptr != LList_end(&list[i]); ptr = ptr->next) {
			LList_append(outlist, ptr->data);
		}
		LList_free(&list[i]);
	}
}

int key(const data d) {
	return (int) d;
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

	for(ListNode * litr = LList_begin(&result);
			litr->next != NULL; litr = litr->next) {
		printf("%ld, ", (long) litr->data);
	}
	printf("\n");
	printf("size %d\n", result.elemcount);

	LList_free(&result);
	return 0;
}
