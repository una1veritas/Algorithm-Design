/*
 ============================================================================
 Name        : wrap-around-test.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	unsigned int counter = 0;
	unsigned int prev = counter;
	printf("size of short = %lu\n", sizeof(prev));

	counter = 10;
	prev = 0xffffffff - 1000;
	printf("counter - prev = %u\n", counter - prev);

	return EXIT_SUCCESS;
}
