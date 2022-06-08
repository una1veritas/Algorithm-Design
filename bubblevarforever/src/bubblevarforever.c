/*
 ============================================================================
 Name        : bubblevarforever.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	int n = argc - 1;
	int a[n];
	printf("input:\n");
	for(int i = 0; i < n; ++i) {
		a[i] = atoi(argv[i+1]);
		printf("%d, ",a[i]);
	}
	printf("\n");

	printf("bubble sort var. infinite loop.\n");
	int finished;
	int counter = 0;
	for(;;) {
		counter += 1;
		finished = 1;
		for(int i = 0; i < n-1; ++i) {
			if (a[i] > a[i+1]) {
				int t = a[i];
				a[i] = a[i+1];
				a[i+1] = t;
				finished = 0;
			}
		}
		if (finished) break;
	}

	printf("result:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d, ",a[i]);
	}
	printf("\n");
	printf("iterated %d times.\n",counter);

	return EXIT_SUCCESS;
}
