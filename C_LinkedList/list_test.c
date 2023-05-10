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

#include "datadef.h"
#include "llist.h"

#include <string.h>

int equals(const data d1, const data d2) {
	return 0 == strcmp((const char *) d1, (const char *) d2);
}

int main(void) {
	LList list;
	const char s[] = "Halo.";

	LList_init(&list);
	printf("List size = %d\n", list.elemcount);
	LList_append(&list, &"Hello.");
	LList_append(&list, &"-3");
	LList_append(&list, &"800,000,000");
	printf("List size = %d\n", list.elemcount);
	LList_fprintf(stdout, &list, "; ");

	printf("\n");
	for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->data );
	}
	printf("\n");

	LList_pop(&list);
	LList_push(&list,"Halo.");
	LList_push(&list,"Car");
	LList_push(&list,"Bag");
	for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->data );
	}
	printf("\n");

	ListNode * thenode = LList_find(&list, (void *)s, equals );
	if ( thenode != LList_end(&list) ) {
		printf("found: %s\n", (char *) thenode->data);
	} else {
		printf("not found.\n");
	}

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
