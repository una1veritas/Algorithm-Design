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
#include <inttypes.h>

typedef struct {
	char * name;
	char gender;
	uint32_t dateofbirth;
} Member;
typedef Member * data;

int lt_or_eqs(data x, data y) {
	return x->dateofbirth <= y->dateofbirth;
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
		printf("%s, %c, %x; ", a[i]->name, a[i]->gender, a[i]->dateofbirth);
	}
	printf("\nheap constructed.\n");
	printf("\n");
	for(i = n - 1; i > 0; --i) {
		t = a[i]; a[i] = a[0]; a[0] = t;
		down_to_leaf(a, 0, i);
		for(unsigned int j = 0; j < n; ++j) {
			printf("%s, %c, %x; ", a[j]->name, a[j]->gender, a[j]->dateofbirth);
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
	Member members[] = {
			{ "Ito, Taro", 'M', 0x19980917 },
			{ "Hayata, Masako", 'F', 0x20010302 },
			{ "Tanaka, Rio", 'F', 0x19840818 },
			{ "Sasaki, Jyouji", 'M', 0x19781027 },
			{ "Agata, Maresuke", 'M', 0x19520229 },
			{ "Sumi, Reika", 'F', 0x19900512 },
			{"Ooe, Marika", 'F', 0x19781121 },
			{"Takeda, Tesuji", 'M', 0x19651008},
	};
	unsigned int n = 8;
	data memberlist[8];

	for(unsigned int i = 0; i < n; ++i) {
		memberlist[i] = &members[i];
		printf("%s, ", memberlist[i]->name);
	}
	printf("\n%d data.\n", n);

	heapSort(memberlist, n);
	//insertionSort(a.elem, a.length);

	printf("sort has finished.\n");
	for(unsigned int i = 0; i < n; ++i) {
		printf("%s, %c, %03x-%02x-%02x\n",
				memberlist[i]->name,
				memberlist[i]->gender,
				memberlist[i]->dateofbirth>>16,
				memberlist[i]->dateofbirth>>8 & 0xff,
				memberlist[i]->dateofbirth & 0xff);
	}
	printf("\n");

	//printf("passing counter [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	return 0;
}
