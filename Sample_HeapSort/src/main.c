/*
 * main.c
 *
 *  Created on: 2019/04/18
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void * data;
typedef struct {
	unsigned int x, y;
} Point;

int Point_compare(const void * a, const void * b) {
	Point * pa = *(Point **) a, * pb = *(Point**) b;
	if ( (pa->x < pb->x) || (pa->x == pb->x && pa->y < pb->y) )
	 return -1;
	if ( pa->x == pb->x && pa->y == pb->y )
		return 0;
	return 1;
}

void down_to_leaf(data a[], unsigned int i, unsigned int n, int (*comp)(const void *, const void *)) {
	unsigned int j;
	data t;
	while ( 1 ) {
		j = (i<<1) + 1; // the left child
		if ( !(j < n) )
			break;
		if ( j+1 < n ) { // i has the right child
			if ( comp(&a[j], &a[j+1]) < 0 )
				j += 1; // select the right child
		}
		//printf("%d(%d, %d) -> %d(%d, %d), ", i, ((Point*)a[i])->x, ((Point*)a[i])->y, j, ((Point*)a[j])->x, ((Point*)a[j])->y);
		if ( comp(&a[j], &a[i]) < 0 )
			break;
		//printf("<-> ");
		t = a[i]; a[i] = a[j]; a[j] = t;
		i = j;
	}
	//printf("\n");
}

void make_heap(data a[], unsigned int n, int (*comp)(const void *, const void *) ) {
	for(unsigned int i = (n-1)>>1; ; --i) {
		down_to_leaf(a, i, n, comp);
		//printf("from %d: ", i);
		//for(unsigned int i = 0; i < n; ++i) {
		//	printf("%u(%u, %u), ", i, ((Point*)a[i])->x, ((Point*)a[i])->y );
		//}
		//printf("\n");
		if ( i == 0 )
			break;
	};
}

void heapSort(data a[], unsigned int n, int (*comp)(const void *, const void *) ){
	unsigned int i;
	data t;
	make_heap(a, n, comp);
	printf("\nheap constructed.\n");
	for(unsigned int i = 0; i < n; ++i) {
		printf("(%u, %u), ", ((Point*)a[i])->x, ((Point*)a[i])->y );
	}
	printf("\n\n");
	for(i = n - 1; i > 0; --i) {
		t = a[i]; a[i] = a[0]; a[0] = t;
		down_to_leaf(a, 0, i, comp);
		for(unsigned int j = 0; j < n; ++j) {
			printf("(%u, %u), ", ((Point*)a[j])->x, ((Point*)a[j])->y );
			if (i == j+1) printf("/ ");
		}
		printf("\n");
	}
}

/*
dataseq input_array(int argc, char * argv[]) {
	dataseq a;
	unsigned int length = argc-1, i;
	if (length == 1) {
		length = atoi(argv[1]);
	}
	a.elem = (data *) malloc(sizeof(data) * length);
	if ( length >= argc ) {
		srand((unsigned) 20190527 ); //time(NULL));
	    for(i = 0; i < length; ++i)
			a.elem[i] = rand() % (length<<1) + 1;
	} else {
		for(i = 0; i < length; ++i)
			a.elem[i] = atoi(argv[1+i]);
	}
	a.length = length;
	return a;
}
*/

int comp(const void * a, const void * b) {
	return *(int*)a - *(int*)b;
}

int main(int argc, char * argv[]) {
	Point points[] = {
			{5,6}, {3,8}, {5,7}, {6,2}, {4,2}, {5,6}, {6,6}, {4,2}, {6,8}, {6,2},
	};
	unsigned int n = sizeof(points)/sizeof(Point);

	data a[n];
	for(unsigned int i = 0; i < n; ++i) {
		a[i] = (data) & points[i];
		printf("(%u, %u), ", ((Point*)a[i])->x, ((Point*)a[i])->y);
	}
	printf("\n%d data.\n", n);

	//qsort(a, n, sizeof(Point*), Point_compare);
	heapSort(a, n, Point_compare);
	//selectionSort(a, n);

	printf("sorting done.\n");
	for(unsigned int i = 0; i < n; ++i) {
		Point * p = (Point *) a[i];
		printf("(%u, %u), ", p->x, p->y);
	}
	printf("\n");

	int d[] = {2, 3, -1, 4, 55, 32, 4 };
	int m = sizeof(d)/sizeof(int);
	qsort(d, m, sizeof(int), comp);
	for(int i = 0; i < m; ++i) {
		printf("%d, ", d[i]);
	}
	printf("\n");

	return 0;
}
