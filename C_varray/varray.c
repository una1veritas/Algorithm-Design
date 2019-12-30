#include "varray.h"
#include <ctype.h>

void varray_init(varray * v, unsigned int minsize) {
	if ( minsize < 8 ) minsize = 8;
	v->capacity = minsize;
	v->array = (data*) malloc(sizeof(data) * v->capacity);
	v->size = 0;
}

void varray_free(varray * v) {
	free(v->array);
	v->capacity = 0;
	v->size = 0;
}

int varray_capacity(varray * v) {
	return v->capacity;
}

int varray_size(varray * v) {
	return v->size;
}

void varray_reallocate(varray * v) {
	unsigned int newcapa = 8;
	while ( newcapa <= v->capacity ) {
		newcapa <<= 1;
	}
	data * newarray = (data*)malloc(sizeof(data)*newcapa);
	v->capacity = newcapa;
	for(int i = 0; i < v->size; ++i) {
		newarray[i] = v->array[i];
	}
	free(v->array);
	v->array = newarray;
}

data varray_at(varray * v, unsigned int i) {
	return v->array[i];
}

data varray_back(varray * v) {
	return v->array[v->size - 1];
}

void varray_pushback(varray * v, data d) {
	if ( !(v->size < v->capacity) ) {
		varray_reallocate(v);
	}
	v->array[v->size] = d;
	v->size += 1;
}

int varray_strscan(varray * v, char * ptr) {
	int cnt = 0;
	while ( *ptr != 0 ) {
		//printf("'%s'\n", ptr);
		while ( !isdigit(*ptr) && *ptr != '-' && *ptr != 0 ) { ++ptr; }
		if ( *ptr == 0 )
			break;
		long val = strtol(ptr, &ptr, 10);
		//printf("%ld, '%s'\n", val, ptr);
		varray_pushback(v, val);
		++cnt;
	}
	return cnt;
}
