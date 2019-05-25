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
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	LinkedList * list = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList_init(list);
	printf("List size = %d\n", list->elemcount);
	LinkedList_append(list, "Hello.");
	LinkedList_append(list,"-3");
	LinkedList_append(list,"800,000,000");
	LinkedList_pop(list);
	LinkedList_push(list,"CAGR");
	LinkedList_printf(list, "; ");
	printf("List size = %d\n", list->elemcount);
	LinkedList_free(list);
	free(list);
	return EXIT_SUCCESS;
}
