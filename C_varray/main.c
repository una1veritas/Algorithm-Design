#include <stdio.h>
#include <stdlib.h>

#include "varray.h"

int main(int argc, char **argv) {
	varray a;
	varray_init(&a, 8);
	varray_pushback(&a, 7);
	for(int i = 0; i < 20; ++i) {
		varray_pushback(&a, ((varray_back(&a) * 3 + 1) % 31) );
	}
	for(int i = 0; i < 20; ++i) {
		printf("%d, ", varray_at(&a,i));
	}
	printf("\n");

	varray_free(&a);
	return 0;
}
