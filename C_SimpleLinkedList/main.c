/*
 * main.c
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

int recursive_print(ListNode * nodeptr) {
	if ( nodeptr == NULL )
		return 0;
	int n = printf("%s, ", nodeptr->datastr);
	return n + recursive_print(nodeptr->next);
}

int print(ListNode * nodeptr) {
	int n = 0;
	for( ; nodeptr != NULL; nodeptr = nodeptr->next) {
		n += printf("%s, ", nodeptr->datastr);
	}
	return n;
}

int main(const int argc, const char * argv[]) {

	LinkedList list = { NULL, NULL, 0}; 	// カラのリスト

	for (int ix = 1; ix < argc; ++ix) {
		LinkedList_append(&list, argv[ix]);
	}

	int n;
	n = print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	n = recursive_print(list.head);
	printf("\n");
	printf("total length = %d\n", n);

	LinkedList_free(&list);

	return EXIT_SUCCESS;
}
