/*
 * heapchecker.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data;

/*
int unlhd_str5cmp(const data * stra, const data * strb) {
	int res = strncmp(*stra, *strb, 5);
	return (res == 0) ? 1 : (res < 0 ? 1 : 0);
}
*/

int unlhd_intasc(const data * a, const data * b) {
	return *a <= *b;
}


int down_to_leaf(const data data[], int a[], int i, int n) {
	int j, t;
	for ( ;(j = (i<<1) + 1) < n ; i = j) {
		//printf("%s ", data[a[i]]);
		if ( (j + 1 < n) ) {
			if ( unlhd_intasc(data+a[j], data+a[j+1]) ) {
				j += 1;
			}
		}
		if ( unlhd_intasc(data+a[j], data+a[i]) )
			break;
		t = a[i], a[i] = a[j], a[j] = t;
	}
#ifdef DEBUG
	for (int j = 0; j < n; ++j) {
		printf("%d, ", data[a[j]]);
	}
	printf("\n");
#endif
	return 1;
}

void make_heap(const data data[], int a[], int n) {
	int i;
	for (i = (n>>1); i > 0; --i) {
		down_to_leaf(data, a, i-1, n);
	}
	return;
}

void heap_sort(const data data[], int a[], int n) {
	int i, t;
	make_heap(data, a, n);
	for(int j = 0; j < n; ++j) {
		printf("%d, ", data[a[j]]);
	}
	printf("\n");
	for (i = n - 1; i > 0; --i) {
		// a[0] is always the maximum.
		t = a[0], a[0] = a[i], a[i] = t;
		down_to_leaf(data, a, 0, i);

		for(int j = 0; j < n; ++j) {
			printf("%d, ", data[a[j]]);
		}
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

int main(const int argc, const char *argv[]) {
	int n = argc - 1;
	data d[n];
	int idx[n];
	for (int i = 0; i < n; ++i) {
		d[i] = atoi(argv[1+i]);
		idx[i] = i;
	}
	printf("input: \n");
	for (int i = 0; i < n; ++i) {
		printf("%d, ", d[idx[i]]);
	}
	printf("\n\n");

	heap_sort(d, idx, n);

	printf("\n");
	for (int i = 0; i < n; ++i) {
		printf("%d, ", d[idx[i]]);
	}
	printf("\n");

	return 0;
}
