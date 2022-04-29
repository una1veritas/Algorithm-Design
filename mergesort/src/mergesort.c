/*
 ============================================================================
 Name        : mergesort.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "stopwatch.h"

typedef struct {
	data d;
	struct ListNode * next;
} ListNode, * List;

List * new_List() {
	return (List*) malloc(sizeof(List));
}

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
