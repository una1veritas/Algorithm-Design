/*
 * heapchecker.c
 */
#include <stdio.h>
#include <stdlib.h>

void radixsort_binary(int d[], const int n) {
	int zero_count;
	int t, bit;
	for(int bitpos = 0; bitpos < 8; ++bitpos) {
		bit = 1<< bitpos;
		zero_count = 0;
		for(int i = 0; i < n; ++i) {
			if ( (d[i] & bit) == 0 ) {
				zero_count += 1;
			}
		}
		printf("[%d] ", zero_count);
		for(int i = 0, j = zero_count; i < zero_count && j < n; ) {
			if ( (d[i] & bit) == 0 ) {
				i += 1;
				continue;
			}
			if ( (d[j] & bit) != 0 ) {
				j += 1;
				continue;
			}
			t = d[j], d[j] = d[i], d[i] = t;
			printf("(%d, %d) ", i, j);
			i += 1;
			j += 1;
		}
		printf("%x: ", bit);
		for(int i = 0; i < n; ++i) {
			if (i == zero_count)
				printf("< ");
			printf("%d, ", d[i]);
		}
		printf("\n");
	}
}

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	int d[n];
	for (int i = 0; i < n; ++i) {
		d[i] = atoi(argv[1+i]);
	}
	printf("input: \n");
	for (int i = 0; i < n; ++i) {
		printf("%d, ", d[i]);
	}
	printf("\n\n");

	radixsort_binary(d, n);

	printf("\n");
	for (int i = 0; i < n; ++i) {
		printf("%d, ", d[i]);
	}
	printf("\n");

	return 0;
}
