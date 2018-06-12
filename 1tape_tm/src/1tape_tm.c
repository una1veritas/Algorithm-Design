/*
 ============================================================================
 Name        : 1tape_tm.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char * head = argv[1];
	/* 入力の確認とポインタのセットアップ */
	if ( argc < 2 )
		return EXIT_FAILURE;
	while ( *head == ' ' ) ++head;
	printf(">%s<\n", head);

	/* 主ルーチン */
	int c = 0;
	do {
		if ( c > 10 ) { break; } else { ++c; printf("c=%d, ",c); }
	q_0:
		printf(">%s<\n", head);
		while ( *head == 'a' || *head == 'b' ) ++head;
		if ( *head == '0' ) {
			*head++ = 'a';
			while ( *head == 'a' || *head == 'b' ) ++head;
			if ( *head == '#' ) {
				while ( *head == 'a' || *head == 'b' ) ++head;
				if ( *head == '0' ) {
					*head = 'a';
					--head;
					//goto q_1;
				}
			}
		} else if ( *head == '1' ) {
			*head++ = 'b';
			while ( *head == 'a' || *head == 'b' ) ++head;
			if ( *head == '#' ) {
				while ( *head == 'a' || *head == 'b' ) ++head;
				if ( *head == '1' ) {
					*head = 'b';
					--head;
					//goto q_1;
				}
			}
		} else if ( *head == '#' ) {
			++head;
			break;
		}

	q_1:
		while ( *head != ' ' ) --head;
		if ( *head == ' ' ) {
			++head;
		}
	} while (1);

	return EXIT_SUCCESS;

HALT_EXIT:
	printf("Machine halted.");
	return EXIT_FAILURE;
}
