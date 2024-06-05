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
	for (unsigned int i = 0; i < (n>>1); ++i) {
		int lc = (i<<1) + 1;
		int rc = (i<<1) + 2;
		if ( ! greaterThanOrEq(a[i], a[lc]) ) {
			printf("(%d, %d), ", i, lc);
		}
		if ( ! greaterThanOrEq(a[i], a[rc]) ) {
			printf("(%d, %d), ", i, rc);
		}
	}
	printf("\n");
}

void down_to_leaf(long a[], const int n, int i) {
	int lc, rc, target;
	while ((i<<1)+1 < n) {
		lc = (i<<1) + 1;
		rc = (i<<1) + 2;
		target = i;
		if ( rc < n ) {
			if ( !greaterThanOrEq(a[i], a[lc]) ) {
				target = lc;
			}
			if ( !greaterThanOrEq(a[lc], a[rc]) ) {
				target = rc;
			}
		} else {
			if ( !greaterThanOrEq(a[i], a[lc]) ) {
				target = lc;
			}
		}
		if ( target != i ) {
			long t = a[target];
			a[target] = a[i];
			a[i] = t;
			i = target;
		} else
			break;
	}
}

void heapify(long a[], const int n) {
	for(int i = ((n-1)>>1) - 1; i >= 0; --i) {
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

	long t = a[n-1];
	a[n-1] = a[0];
	a[0] = t;
	down_to_leaf(a, n-1, 0);
	for (int i = 0; i < n-1; ++i) {
		printf("%ld, ", a[i]);
	}
	printf(";");
	for (int i = n-1; i < n; ++i) {
		printf("%ld, ", a[i]);
	}
	printf("\n");
	return 0;
}
