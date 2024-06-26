/*
 ============================================================================
 Name        : C_Heapsort_basic.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int greaterThanOrEq(const long a, const long b) {
	int res = a - b;
	return res >= 0;
}

void heap_checker(long a[], const int n) {
	for (unsigned int i = 0; i < (n-1)>>1; ++i) {
		int lc = (i<<1) + 1;
		if ( ! greaterThanOrEq(a[i], a[lc]) ) {
			printf("(%d, %d), ", i, lc);
		}
		if ( lc + 1 < n && ! greaterThanOrEq(a[i], a[lc + 1]) ) {
			printf("(%d, %d), ", i, lc+1);
		}
	}
	printf("\n");
}

void down_to_leaf(long a[], const int n, int i) {
	int lc, tc; // left child, target child
	while ((lc = (i<<1)+1) < n) {
		tc = i;
		if ( ! greaterThanOrEq(a[i], a[lc]) ) {
			tc = lc;
		}
		// if i has a right child and not left is greater than or eq right
		if ( (lc + 1 < n)  && (! greaterThanOrEq(a[tc], a[lc+1])) ) {
			tc = lc + 1;
		}
		if ( tc != i ) {
			long t = a[tc];
			a[tc] = a[i];
			a[i] = t;
			i = tc;
		} else
			break;
	}
}

void heapify(long a[], const int n) {
	for(int i = (n>>1); i >= 0; --i) {
		down_to_leaf(a, n, i);
	}
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	/* 引数の配列の最初の要素 argv[0] はコマンド名なのでソート対象から取り除く */
	long a[n];
	for (unsigned int i = 0; i < n; ++i) {
		a[i] = atol(argv[1+i]);
		printf("%ld, ", a[i]);
	}
	printf("\n");

	heap_checker(a, n);
	/*
	heap_sort(argv + 1, idx, n); //argv+1 は配列 argv の 2 番目の要素から始まる
	*/
	heapify(a, n);
	for (int i = 0; i < n; ++i) {
		printf("%ld, ", a[i]);
	}
	printf("\n");

	for(int sz = n; sz > 1; --sz) {
		long t = a[sz-1];
		a[sz-1] = a[0];
		a[0] = t;
		down_to_leaf(a, sz-1, 0);
		for (int i = 0; i < sz-1; ++i) {
			printf("%ld, ", a[i]);
		}
		printf(";");
		for (int i = sz-1; i < n; ++i) {
			printf("%ld, ", a[i]);
		}
		printf("\n");
	}
	return 0;
}
