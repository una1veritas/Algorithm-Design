/*
 ============================================================================
 Name        : Sample_LinkedList.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

int main(void) {
	LinkedList list;

	LinkedList_init(&list);
	printf("List size = %d\n", list.elemcount);
	LinkedList_append(&list, "Hello.");
	LinkedList_append(&list, "-3");
	LinkedList_append(&list, "800,000,000");
	LinkedList_printf(&list, "; ");
	printf("\n");
	for(ListNode * ptr = LinkedList_begin(&list); ptr != NULL; ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->data );
	}
	printf("\n");
	fflush(stdout);
	LinkedList_pop(&list);
	LinkedList_push(&list,"CAGR");
	LinkedList_printf(&list, "; ");
	printf("\n");
	for(ListNode * ptr = LinkedList_begin(&list); ptr != NULL; ptr = ptr->next) {
		printf("%s ", (char *) ptr->data );
	}
	printf("\n");
	printf("List size = %d\n", list.elemcount);

	LinkedList_free(&list);
	return EXIT_SUCCESS;
}
