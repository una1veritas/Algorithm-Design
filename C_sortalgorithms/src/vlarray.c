/*
 * vlarray.c
 *
 *  Created on: 2023/05/27
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>

#include "vlarray.h"

#define VLARRAY_MIN_SIZE 8

int vlarray_init(vlarray * vla, unsigned int capa) {
	vla->limit = capa > VLARRAY_MIN_SIZE ? capa : VLARRAY_MIN_SIZE;
	vla->a = (data **) malloc(sizeof(data *) * vla->limit);
	if ( vla->a ) {
		vla->n = 0;
		return 0;
	}
	return -1; // malloc error
}

void vlarray_delete(vlarray * vla) {
	free(vla->a);
}

unsigned int vlarray_capacity(vlarray * vla) {
	return vla->limit;
}

int vlarray_append(vlarray * vla, data * d) {
	if ( ! (vla->n < vla->limit) )
		return -1; // capacity limit exceeded
	vla->a[vla->n++] = d;
	return 0;
}

int vlarray_enlarge(vlarray * vla) {
	data ** newarray = (data **) malloc(sizeof(data*) * (vla->limit << 1) );
	if (! newarray )
		return -1; // malloc error
	vla->limit <<= 1;
	for(long j = 0; j < vla->limit; ++j) {
		newarray[j] = vla->a[j];
	}
	free(vla->a);
	vla->a = newarray;
	return 0;
}
