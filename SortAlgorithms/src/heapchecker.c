/*
 * libcquick.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unlhd_str5cmp(const char * stra, const char * strb) {
	int res = strncmp(stra, strb, 5);
	return (res == 0) ? 0 : (res < 0 ? 1 : 0);
}

int down_to_leaf(const char * data[], int a[], int i, int n) {
	int j, right, t;
	for ( ; ; i = j) {
		j = (i<<1) + 1;
		if ( !(j < n) )
			break;
		right = (i<<1) + 2;
		if ( (right < n) && (unlhd_str5cmp(data[a[j]], data[a[right]])) )
			j = right;
		t = a[i], a[i] = a[j], a[j] = t;
		printf("%d <--> %d, ", i, j);
	}
	return 1;
}

void make_heap(const char * data[], int a[], int n) {
	int i;
	for (i = (n>>1); i > 0; --i) {
		printf("%d: ",i-1);
		down_to_leaf(data, a, i-1, n);
		printf("\n");
	}
	return;
}

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
	int idx[n];
	for (int i = 0; i < n; ++i) {
		idx[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		printf("'%s', ", (argv+1)[idx[i]]);
	}
	printf("\n");

	make_heap((const char **)argv+1, idx, n);

	printf("\n");
	for (int i = 0; i < n; ++i) {
		printf("'%s', ", (argv+1)[idx[i]]);
	}
	printf("\n");

	return 0;
}
