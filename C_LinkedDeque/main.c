/*
 * main.c
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "ldeque.h"

int equals(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) == 0;
}

int lessthan(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) < 0;
}

int lessoreq(const data * x, const data * y) {
	return strcmp((char *) x->name, (char *) y->name) <= 0;
}

long keyval(const void * x) {
	const char * str = ((const data *)x)->name;
	long t = 0;
	for (int i = 0; str[i]; ++i) {
		t *= 31;
		t += str[i];
	}
	return t;
}

int  fprintf_data(FILE * fp, const data * d) {
	//return fprintf(fp, "%s", *d);
	return fprintf(fp, "%s: %s", d->id, d->name);
}

int recursive_print(DequeNode * nodep) {
	if ( nodep == NULL )
		return 0;
	int n = printf("%s, ", nodep->datastr);
	return n + recursive_print(nodep->next);
}

int print(DequeNode * nodep) {
	int n = 0;
	for( ; nodep != NULL; nodep = nodep->next) {
		n += printf("%s, ", nodep->datastr);
	}
	return n;
}

int main(const int argc, const char * argv[]) {

	LinkedDeque list = { NULL, NULL, 0}; 	// カラのリスト

	for (int ix = 1; ix < argc; ++ix) {
		LinkedDeque_append(&list, argv[ix]);
	}

	int n;
	n = print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	n = recursive_print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	LinkedDeque_free(&list);

	return EXIT_SUCCESS;
}
