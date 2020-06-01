/*
 * qsort.c
 *
 *  Created on: 2019/06/23
 *      Author: Sin Shimozono
 */

#include <stdlib.h>

#include "sorting.h"

void stdlib_qsort(int a[], unsigned int n, int (*compare)(const void *, const void *) ) {
	return qsort(a, n, sizeof(int), compare);
}
