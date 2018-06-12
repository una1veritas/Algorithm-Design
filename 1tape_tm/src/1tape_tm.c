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
	while ( *head == 'B' ) ++head;
	printf(">%s<\n", head);

	/* 主ルーチン */
	int c = 0;
	do {
		if ( c > 10 ) { break; } else { ++c; printf("c=%d, ",c); }
	q_0:
		printf("q0: %s\n", head);
		printf(">%s< %d\n", argv[1], (unsigned long) head & 0xffff);
		while ( *head == 'a' || *head == 'b' ) ++head;
		printf("q0 %s\n", head);
		if ( *head == '0' ) {
			*head++ = 'a';
			printf("q2\n");
			while ( *head == '0' || *head == '1' ) ++head;
			if ( *head == '#' ) {
				++head;
				printf("q4 %s\n", head);
				while ( *head == 'a' || *head == 'b' ) ++head;
				if ( *head == '0' ) {
					*head = 'a';
					--head;
					//goto q_1;
				} else {
					goto q_halt;
				}
			}
		} else if ( *head == '1' ) {
			*head++ = 'b';
			while ( *head == '0' || *head == '1' ) ++head;
			if ( *head == '#' ) {
				++head;
				while ( *head == 'a' || *head == 'b' ) ++head;
				if ( *head == '1' ) {
					*head = 'b';
					--head;
					//goto q_1;
				} else {
					goto q_halt;
				}
			}
		} else if ( *head == '#' ) {
			++head;
			while ( *head == 'a' || *head == 'b' )
				++head;
			if ( *head == 'B' )
				goto q_accept;
			break;
		} else {
			break;
		}

	q_1:
		printf("q1: \n");
		while ( *head != 'B' ) {
			--head;
			printf("%s\n", head);
		}
		++head;
		printf("%s\n", head);
	} while (1);

q_halt:
	printf("Machine halted.");
	return EXIT_FAILURE;

q_accept:
	printf("accepted.\n");
	return EXIT_SUCCESS;

}
