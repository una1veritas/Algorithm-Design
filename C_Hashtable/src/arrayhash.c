/*
 * arrayhash.c
 *
 *  Created on: 2020/06/11
 *      Author: sin
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char str8[8];
typedef struct hashtbl {
	str8 * tbl;
	int m;
} hashtbl;

int hashtbl_init(hashtbl * htbl, int m) {
	htbl->tbl = (str8 *) malloc(sizeof(str8)*m);
	htbl->m = m;
	for(int i = 0; i < m; ++i) {
		htbl->tbl[i][0] = '\0';
	}
	return 0;
}

int hashtbl_add(hashtbl * htbl, const char c) {
	int key = (int)c % htbl->m;
	char * p = htbl->tbl[key];
	for ( ; *p != '\0'; ++p) {
		if ( *p == c )
			return 1;
	}
	*p = c;
	++p; *p = '\0';
	return 0;
}

int hashtbl_printf(hashtbl * htbl) {
	for(int i = 0; i < htbl->m; ++i) {
		printf("(");
		for(char * p = htbl->tbl[i]; *p != '\0'; ) {
			printf("%c", *p);
			++p;
			if ( *p != '\0' )
				printf(", ");
		}
		printf("), ");
	}
	printf("\n");
	return 0;
}

int main(const int argc, const char * argv[]) {
	if ( ! (argc > 2) ) {
		printf("give a number and an input text.\n");
		return EXIT_FAILURE;
	}
	const int m = atoi(argv[1]);
	const char * s = argv[2];
	printf("bucket number = %d, text = %s\n", m, s);

	hashtbl htbl;
	hashtbl_init(&htbl, m);
	for(const char * p = s; *p != '\0'; ++p) {
		hashtbl_add(&htbl, *p);
	}

	hashtbl_printf(&htbl);

	return EXIT_SUCCESS;
}
