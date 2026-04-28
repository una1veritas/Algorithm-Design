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
	LList_push_back(&list, &"Hello.");
	LList_push_back(&list, &"-3");
	LList_push_back(&list, &"800,000,000");
	printf("List size = %d\n", list.elemcount);
	LList_fprintf(stdout, &list, "; ");
	fflush(stdout);

	printf("\n");
	for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->dataptr );
	}
	printf("\n");

	LList_pop_back(&list);
	LList_push_back(&list,"Halo.");
	LList_push_back(&list,"Key");
	LList_push_back(&list,"Car");
	LList_push_back(&list,"Brdige");
	LList_push_back(&list,"Moon");
	LList_push_back(&list,"Brdige");
	for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
		printf("%s -> ", (char *) ptr->dataptr );
	}
	printf("\n");

	ListNode * thenode;

	thenode = LList_find_r(&list, LList_begin(&list), (void *)s, equals );
	if ( thenode != LList_end(&list) ) {
		printf("found: %s\n", (char *) thenode->dataptr);
	} else {
		printf("not found.\n");
	}

	void * data;
	while ( !LList_is_empty(&list) ) {
		data = LList_pop_back(&list);
		printf("%s \n", (char *) data );
		for(ListNode * ptr = LList_begin(&list); ptr != LList_end(&list); ptr = ptr->next) {
			printf("%s -> ", (char *) ptr->dataptr );
		}
		printf("\n");
	}
	printf("\n");
	printf("List size = %d\n", list.elemcount);

	LList_free(&list);
	return EXIT_SUCCESS;
}
