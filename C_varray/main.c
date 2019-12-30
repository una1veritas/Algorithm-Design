#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "varray.h"

int main(int argc, char *argv[]) {
	char * str = " {-1, 3,-5,4,0, 2 }";
	char * ptr;
	varray a;
	varray_init(&a, 8);
	int count = varray_strscan(&a, str);
	printf("Got %d integers.\n", count);
	for(int i = 0; i < varray_size(&a); ++i) {
		printf("%d, ", varray_at(&a,i));
	}
	printf("\n");

	varray_free(&a);
	return 0;
}
