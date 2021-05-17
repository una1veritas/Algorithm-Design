#include <stdio.h>
#include <stdlib.h>

int heapcheck(const int a[], const int n) {
	for(int i = 0; i < (n-1)>>1; ++i) {
		if ( !(a[(i<<1)+1]<= a[i]) )
			return 0;
		if ( ((i<<1) + 2 < n) && !(a[(i<<1)+2] <= a[i]) )
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
	if (heapcheck(a, n)) {
		printf("a heap.");
	} else {
		printf("not a heap.");
	}
	printf("\n");
	return 0;
}
