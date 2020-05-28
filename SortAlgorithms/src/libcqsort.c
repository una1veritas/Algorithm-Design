/*
 * libcquick.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 文字列の後ろから見た辞書式順序 */
/*
int order(const void * a, const void * b) {
	const char * stra = *(const char**)a, * strb = *(const char**)b;
	int lena = strlen(stra), lenb = strlen(strb);
	int d;
	for (; lena && lenb; ) {
		--lena, --lenb;
		d = stra[lena] - strb[lenb];
		if ( d != 0 )
			return d;
	}
	if ( lena < lenb )
		return -1;
	if ( lena > lenb )
		return 1;
	return 0;
}
*/

int order(const void * a, const void * b) {
	int inta = *(int*)a, intb = *(int*)b;
	inta %= 6, intb %= 6;
	return inta - intb;
}

int main(const int argc, char *argv[]) {
	long n = argc - 1;
	int a[n];
	for (int i = 0; i < n; ++i) {
		a[i] = atoi(argv[1 + i]);
		printf("%d, ", a[i]);
	}
	printf("\n");

	qsort(a, n, sizeof(a[0]), order);

	for (int i = 0; i < n; ++i) {
		printf("%d, ", a[i]);
	}
	printf("\n\n");

	return 0;
}
