/*
 * heapchecker.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unlhd_str5cmp(const char * stra, const char * strb) {
	int res = strncmp(stra, strb, 5);
	return (res == 0) ? 1 : (res < 0 ? 1 : 0);
}

int down_to_leaf(const char * data[], int a[], int i, int n) {
	int j, t;
	for ( ;(j = (i<<1) + 1) < n ; i = j) {
		//printf("i = %d, ", i);
		if ( (j + 1 < n) ) {
			//printf("r a[%d] <= a[%d]", j, j+1);
			if (unlhd_str5cmp(data[a[j]], data[a[j+1]]) ) {
				j += 1;
			}
		}
		if ( unlhd_str5cmp(data[a[j]], data[a[i]]) )
			break;
		t = a[i], a[i] = a[j], a[j] = t;
		//printf("%d <-- %d, ", j, i);
	}
	return 1;
}

void make_heap(const char * data[], int a[], int n) {
	int i;
	for (i = (n>>1); i > 0; --i) {
		//printf("%d: ",i-1);
		down_to_leaf(data, a, i-1, n);
		//printf("\n");
	}
	return;
}

void heap_sort(const char * data[], int a[], int n) {
	int i, t;
	make_heap(data, a, n);
	for (i = n - 1; i > 0; --i) {
		// a[0] is always the maximum.
		t = a[0], a[0] = a[i], a[i] = t;
		down_to_leaf(data, a, 0, i);
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

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	int idx[n];
	for (int i = 0; i < n; ++i) {
		idx[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		printf("'%s', ", (argv+1)[idx[i]]);
	}
	printf("\n");

	heap_sort(argv+1, idx, n);

	printf("\n");
	for (int i = 0; i < n; ++i) {
		printf("'%s', ", (argv+1)[idx[i]]);
	}
	printf("\n");

	return 0;
}
