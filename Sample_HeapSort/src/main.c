/*
 * main.c
 *
 *  Created on: 2019/04/18
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "mt.h"
#include <string.h>

typedef char * data;
typedef struct {
	data * elem;
	unsigned int length;
} dataseq;

int lt_or_eqs(data x, data y) {
	char * px, *py;
	int cnt, dx, dy;
	for(cnt = 0, px = x; cnt < 2 && *px != '\0'; ++px) {
		if (*px == '/')
			++cnt;
	}
	for(cnt = 0, py = y; cnt < 2 && *py != '\0'; ++py) {
		if (*py == '/')
			++cnt;
	}
	//printf("%s-%s, ",px,py);
	dx = strtol(px, &px, 10), dy = strtol(py, &py, 10);
	if (dx != dy)
		return dx <= dy;
	dx = strtol(++px, &px, 10), dy = strtol(++py, &py, 10);
	if (dx != dy)
		return dx <= dy;
	dx = strtol(++px, &px, 10), dy = strtol(++py, &py, 10);
	if (dx != dy)
		return dx <= dy;
	return 0;
}

/* passage counters */
long passcount[] = { 0, 0, };

void down_to_leaf(data a[], unsigned int i, unsigned int n) {
	unsigned int j;
	data t;
	while ( 1 ) {
		j = (i<<1) + 1; // the left child
		if ( !(j < n) )
			break;
		if ( j+1 < n ) { // i has the right child
			if ( lt_or_eqs(a[j], a[j+1]) )
				j += 1; // select the right child
		}
		//printf("%d -> %d, ", i, j);
		if ( lt_or_eqs(a[j], a[i]) )
			break;
		t = a[i]; a[i] = a[j]; a[j] = t;
		i = j;
	}
	//printf("\n");
}

void make_heap(data a[], unsigned int n) {
	for(unsigned int i = (n-1)>>1; ; --i) {
		printf("%d: ", i);
		down_to_leaf(a, i, n);
		if ( i == 0 )
			break;
	};
	printf("\n");
}

void heapSort(data a[], unsigned int n) {
	unsigned int i;
	data t;
	make_heap(a, n);
	for(unsigned int i = 0; i < n; ++i) {
		printf("%s, ", a[i]);
	}
	printf("\nheap constructed.\n");
	printf("\n");
	for(i = n - 1; i > 0; --i) {
		t = a[i]; a[i] = a[0]; a[0] = t;
		down_to_leaf(a, 0, i);
		for(unsigned int j = 0; j < n; ++j) {
			printf("%s, ", a[j]);
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

int main(int argc, char * argv[]) {
	char * member[] = { "Ito, Taro/M/1998-9-17", "Hayata, Masako/F/2001-3-2",
			"Tanaka, Rio/F/1984-8-18", "Sasaki, Jyouji/M/1978-10-27",
			"Agata, Maresuke/M/1952-2-29", "Sumi, Reika/F/1990-5-12",
			"Ooe, Marika/F/1978-11-21", "Takeda, Tesuji/M/1965-10-8" };
	dataseq d = { member, 8};

//	dataseq a = input_array(argc, argv);
	unsigned int i;
	for(i = 0; i < d.length; ++i) {
		printf("%s, ", d.elem[i]);
	}
	printf("\n%d data.\n", d.length);

	heapSort(d.elem, d.length);
	//insertionSort(a.elem, a.length);

	printf("sort has finished.\n");
	for(i = 0; i < d.length; ++i) {
		printf("%s, ", d.elem[i]);
	}
	printf("\n");

	//printf("passing counter [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	return 0;
}
