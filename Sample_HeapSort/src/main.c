/*
 * main.c
 *
 *  Created on: 2019/04/18
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "sorting.h"

typedef struct {
	int x, y;
} Point2D;

int get_Point2D(Point2D ** a, int argc, char * argv[]);

/* void == int  */
int int_lessthan(const void * a, const void * b) {
	return *(int*)a - *(int*)b;
}

/* void == char*  */
int str_lessthan(const void * a, const void * b) {
	return strcmp(*(char **) a, *(char **) b);
}

/* void == Point2D*  */
int Point2D_lessthan(const void * a, const void * b) {
	Point2D * pa = *(Point2D **) a, * pb = *(Point2D **) b;
	if ( (pa->x < pb->x) || (pa->x == pb->x && pa->y < pb->y) )
	 return -1;
	if ( pa->x == pb->x && pa->y == pb->y )
		return 0;
	return 1;
}



Point2D fixed_points[] = {
		{5,6}, {3,8}, {5,7}, {6,2}, {4,2}, {5,6}, {6,6}, {4,2}, {6,8}, {6,2},
};

int main(int argc, char * argv[]) {
	Point2D * points = NULL;
	unsigned int n = get_Point2D(&points, argc, argv);
	if ( n == 0 ) {
		printf("use fixed_points[] as input.\n");
		points = fixed_points;
		n = sizeof(fixed_points)/sizeof(Point2D);
	}

	int a[n]; // sort not the original data array, but the array of pointers to the data
	for(unsigned int i = 0; i < n; ++i)
		a[i] = (int) & points[i];

	printf("input: %d data,\n", n);
	for(unsigned int i = 0; i < n; ++i) {
		Point2D * p = a[i];
		printf("(%d, %d), ", p->x, p->y);
	}
	printf("\n\n");

	//stdlib_qsort(a, n, Point2D_lessthan);
	//heapSort(a, n, Point2D_lessthan);
	selectionSort(a, n, Point2D_lessthan);

	printf("sorting done.\n");
	for(unsigned int i = 0; i < n; ++i) {
		Point2D * p = (Point2D *) a[i];
		printf("(%d, %d), ", p->x, p->y);
	}
	printf("\n\n");

	return 0;
}


int get_Point2D(Point2D ** a, int argc, char * argv[]) {
	unsigned int n = argc - 1, i;
	for(int i = 0; i < argc; ++i) {
		printf("%s, ", argv[i]);
	}
	printf("\n");
	if (n == 0) {
		a = NULL;
		return n;
	}
	if ( argc == 2 && strncmp("-random=", argv[1], 8) == 0 ) {
		*a = NULL;
		return 0;
	}
	Point2D * d = (Point2D*) malloc(sizeof(Point2D) * n);
	for(i = 0; i < n; ++i) {
		char * p = argv[1+i];
		printf("%s ", p);
		fflush(stdout);
		d[i].x = strtol(p, &p, 10);
		fflush(stdout);
		while ( !(isdigit(*p) || *p == '-') ) {
			if (*p == 0 ) break;
			++p; }
		fflush(stdout);
		d[i].y = strtol(p, &p, 10);
		fflush(stdout);
		printf("(%d, %d), ", d[i].x, d[i].y);
	}
	printf("\n");
	fflush(stdout);
	*a = d;
	return n;
}
