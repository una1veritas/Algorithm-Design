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
/*
int unlhd(const int ptra, const int ptrb) {
	return ptra <= ptrb;
}
*/
int heapcheck(const int a[], const int n) {
	for(int i = 0; i < n>>1; ++i) {
		if ( ! (a[(i<<1)+1] <= a[i]) )
			return 0;
		if ( i < (i<<1)+2 )
			continue;
		if ( ! (a[(i<<1)+2] <= a[i]) )
			return 0;
	}
	return 1;
}

int main(const int argc, char *argv[]) {
	int n = argc - 1;
	int a[n];
	for (int i = 0; i < n; ++i) {
		a[i] = atoi(argv[1 + i]);
		printf("%d, ", a[i]);
	}
	printf("\n");

	printf("this is ");
	if ( heapcheck(a, n) ) {
		printf("a heap.");
	} else {
		printf("not a heap.");
	}
	printf("\n");

	return 0;
}
