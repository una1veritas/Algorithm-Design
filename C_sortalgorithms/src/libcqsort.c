/*
 * libcquick.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 文字列の先頭 3 文字の辞書式順序 */

int my_order(const void * a, const void * b) {
	/* 引数の方は void * と決められているので適切に型変換する */
	const int MIN_LEN = 3;
	const char * stra = *(const char**)a, * strb = *(const char**)b;
	int lena = strlen(stra), lenb = strlen(strb);
	for (int i = 0; i <= lena && i <= lenb && i < MIN_LEN; ++i) {
		int diff = stra[i] - strb[i];
		if ( diff != 0 ) {
			printf("%s - %s ? %d\n",stra, strb, diff);
			return diff;
		}
	}
	printf("%s - %s ? %d\n",stra, strb, 0);
	return 0;
}

/*
int order(const void * a, const void * b) {
	int inta = *(int*)a, intb = *(int*)b;
	inta %= 6, intb %= 6;
	return inta - intb;
}
*/

int main(const int argc, char *argv[]) {
	long n = argc - 1;
	char * a[n];
	for (int i = 0; i < n; ++i) {
		a[i] = argv[1 + i];
		printf("%s, ", a[i]);
	}
	printf("\n");

	qsort(a, n, sizeof(a[0]), my_order);

	for (int i = 0; i < n; ++i)
		printf("%s, ", a[i]);
	printf("\n\n");

	return 0;
}
