/*
 * main.c
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
int  fprintf_data(FILE * fp, const data * d) {
	//return fprintf(fp, "%s", *d);
	return fprintf(fp, "%s: %s", d->id, d->name);
}
*/

int recursive_print(DequeNode * nodep) {
	if ( nodep == NULL )
		return 0;
	int n = printf("%s: %s, ", nodep->node_data.id, nodep->node_data.name);
	return n + recursive_print(nodep->next);
}

int print(DequeNode * nodep) {
	int n = 0;
	for( ; nodep != NULL; nodep = nodep->next) {
		n = printf("%s: %s, ", nodep->node_data.id, nodep->node_data.name);
	}
	return n;
}

int main(const int argc, const char * argv[]) {
	data d;
	LinkedDeque list = { NULL, NULL, 0}; 	// カラのリスト

	printf("reading input:\n");
	for (int ix = 1; ix < argc; ++ix) {
		snprintf(d.id, 9, "A%03d", ix);
		snprintf(d.name, 31, "%s", argv[ix]);
		printf("%s: %s, ", d.id, d.name);
		LinkedDeque_append(&list, &d);
	}
	printf("\n");

	printf("\nprint out linked deque:\n");

	int n;
	printf("\nby loop\n");
	n = print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	printf("\nby recursion\n");
	n = recursive_print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	LinkedDeque_free(&list);

	return EXIT_SUCCESS;
}
