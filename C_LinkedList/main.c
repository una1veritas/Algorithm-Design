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

#include "llist.h"

int main(void) {
	LList list;

	LList_init(&list);
	printf("List size = %d\n", list.elemcount);
	LList_append(&list, "Hello.");
	LList_append(&list, "-3");
	LList_append(&list, "800,000,000");
	printf("List size = %d\n", list.elemcount);
	LList_printf(&list, "; ");

	printf("\n");
	for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->data );
	}
	printf("\n");

	LList_pop(&list);
	LList_push(&list,"CAGR");
	LList_printf(&list, "; ");
	printf("\n");

	void * data;
	while ( !LList_is_empty(&list) ) {
		data = LList_pop(&list);
		printf("%s \n", (char *) data );
		for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
			printf("%s -> ", (char *) ptr->data );
		}
		printf("\n");
	}
	printf("\n");
	printf("List size = %d\n", list.elemcount);

	LList_free(&list);
	return EXIT_SUCCESS;
}
