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

int lessThan(const long a, const long b) {
	return a - b < 0;
}

int equals(const long a, const long b) {
	return a == b;
}

void heap_checker(long a[], const int n) {
	int counter = 0;
	for (unsigned int i = 0; i < (n - 1)>>1; ++i) {
		int lc = (i<<1) + 1;
		if ( lessThan(a[i], a[lc]) ) {
			printf("([%d] <- [%d]), ", i, lc);
			counter += 1;
		}
		if ( lc + 1 < n && lessThan(a[i], a[lc + 1]) ) {
			printf("([%d] <- [%d]), ", i, lc+1);
			counter += 1;
		}
	}
	printf("%d violations.\n", counter);
	printf("\n");
}

void down_to_leaf(long a[], const int n, int i) {
	int lc, tc; // left child, target child
	while ((lc = (i<<1) + 1) < n) {
		tc = i;
		if ( lessThan(a[i], a[lc]) ) {
			tc = lc;
		}
		// if i has a right child and not left is greater than or eq right
		if ( (lc + 1 < n)  && lessThan(a[tc], a[lc+1]) ) {
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
	for(int i = n>>1; i >= 0; --i) {
		down_to_leaf(a, n, i);
		printf("%d: ", i);
		for (int i = 0; i < n; ) {
			printf("%ld", a[i]);
			++i;
			if ( i < n ) {
				printf(", ");
			}
		}
		printf("\n");	}
}

unsigned int print_array(long a[], int b, int n) {
	unsigned int len = 0;
	for (int i = 0; i < n; ) {
		len += printf("%ld", a[i]);
		++i;
		if ( i == b - 1) {
			len += printf("| ");
		} else if ( i < n ) {
			len += printf(", ");
		}
	}
	len += printf("\n");
	return len;
}

void heap_sort(long a[], int n) {

	heapify(a, n);

	heap_checker(a,n);

	for (int i = 0; i < n; ) {
		printf("%ld", a[i]);
		++i;
		if ( i < n ) {
			printf(", ");
		} else {
			printf("| ");
		}
	}
	printf("\n");

	for(int heap_size = n; heap_size > 1; --heap_size) {
//		long t = a[sz-1];
//		a[sz-1] = a[0];
//		a[0] = t;
		a[0] ^= a[heap_size-1];
		a[heap_size-1] = a[0]^a[heap_size-1];
		a[0] = a[0]^a[heap_size-1];
		down_to_leaf(a, heap_size-1, 0);
		for (int i = 0; i < n; ) {
			printf("%ld", a[i]);
			++i;
			if ( i == heap_size - 1) {
				printf("| ");
			} else if ( i < n ) {
				printf(", ");
			}
		}
		printf("\n");
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

	heap_sort(a, n);

	return 0;
}
/*
 * 4, 1, 9, 3, 8, 5, 3, 6, 7, 4,
([1] <- [4]), ([1] <- [5]), ([3] <- [12]), 3 violations.

5: 4, 1, 9, 3, 8, 5, 3, 6, 7, 4
4: 4, 1, 9, 3, 8, 5, 3, 6, 7, 4
3: 4, 1, 9, 3, 8, 5, 3, 6, 7, 4
2: 4, 1, 9, 3, 8, 5, 3, 6, 7, 4
1: 4, 8, 9, 3, 1, 5, 3, 6, 7, 4
0: 8, 5, 9, 3, 1, 4, 3, 6, 7, 4
([3] <- [12]), 1 violations.

8, 5, 9, 3, 1, 4, 3, 6, 7, 4|
5, 4, 9, 3, 1, 4, 3, 6, 7| 8
7, 4, 9, 3, 1, 4, 3, 6| 5, 8
6, 4, 9, 3, 1, 4, 3| 7, 5, 8
4, 4, 9, 3, 1, 3| 6, 7, 5, 8
4, 3, 9, 3, 1| 4, 6, 7, 5, 8
3, 1, 9, 3| 4, 4, 6, 7, 5, 8
3, 1, 9| 3, 4, 4, 6, 7, 5, 8
9, 1| 3, 3, 4, 4, 6, 7, 5, 8
1| 9, 3, 3, 4, 4, 6, 7, 5, 8
 *
 */
