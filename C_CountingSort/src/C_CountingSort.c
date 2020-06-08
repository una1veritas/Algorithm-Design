/*
 ============================================================================
 Name        : C_CountingSort.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void countingsort(int d[], int n, int m) {
	int number[m];
	int counter[m];

	for(int i = 0; i < m; ++i) {
		number[i] = 0;
	}
	for(int i = 0; i < n; ++i) {
		number[d[i]] += 1;
	}
	/*
	printf("number:\n");
	for(int i = 0; i < m; ++i) {
		printf("%d, ", number[i]);
	}
	printf("\n");
	*/
	for(int i = 1; i < m; ++i) {
		number[i] += number[i-1];
		counter[i] = number[i-1];
	}
	counter[0] = 0;
	/*
	for(int i = 0; i < m; ++i) {
		printf("%d, ", number[i]);
	}
	printf("\n");
	printf("counter\n");
	for(int i = 0; i < m; ++i) {
		printf("%d, ", counter[i]);
	}
	printf("\n");
	*/
	for(int i = 0; i < n; ) {
		int idx = d[i];
		if ( counter[idx] != number[idx] ) {
			int t = d[counter[idx]];
			d[counter[idx]] = d[i];
			d[i] = t;
			counter[idx] += 1;
			//printf("d[%d]<-->d[%d]\n", i, counter[idx]);
		} else {
			i += 1;
		}
		/*
		printf("i = %d elem:\n", i);
		for(int j = 0; j < n; ++j) {
			printf("%d, ", d[j]);
		}
		printf("\n\n");
		*/
	}
}

int main(int argc, char * argv[]) {
	int n = argc - 1;
	int d[n];

	printf("input:\n");
	for(int i = 0; i < n; ++i) {
		d[i] = atoi(argv[i+1]);
		printf("%d, ", d[i]);
	}
	printf("\n");

	countingsort(d, n, 20);


	printf("\noutput:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d, ", d[i]);
	}
	printf("\n");

return EXIT_SUCCESS;
}
