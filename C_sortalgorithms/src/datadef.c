/*
 * datadef_str.c
 *
 *  Created on: 2021/06/02
 *      Author: sin
 */


#include "datadef.h"

/*
int lessthan(const data * x, const data * y) {
	return *x < *y;
}

long keyval(const data * x) {
	return *x;
}
*/

#include <string.h>

int equals(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) == 0;
}

int lessthan(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) < 0;
}

int lessoreq(const data * x, const data * y) {
	return strcmp((char *) x->name, (char *) y->name) <= 0;
}

long keyval(const void * x) {
	const char * str = ((const data *)x)->name;
	long t = 0;
	for (int i = 0; str[i]; ++i) {
		t *= 31;
		t += str[i];
	}
	return t;
}

int  fprintf_data(FILE * fp, const data * d) {
	//return fprintf(fp, "%s", *d);
	return fprintf(fp, "%s: %s", d->id, d->name);
}
