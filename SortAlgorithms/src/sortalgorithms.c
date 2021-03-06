/*
 * SortAlgorithms.c
 *
 */
#include <stdio.h>
#include "sortalgorithms.h"

int verify_sorted(const data d[], const int idx[], int n, int (*compare)(const data *, const int, const int) ) {
	for(unsigned int i = 0; i < n - 1; ++i) {
		if ( compare(d, idx[i], idx[i]) )
			return 0;
	}
	return 1;
}

void countingSort(data d[], int n, int m, int (*key)(const data)) {
	long number[m];
	long counter[m];

	for(long i = 0; i < m; ++i) {
		number[i] = 0;
	}
	for(long i = 0; i < n; ++i) {
		number[key(d[i]) % m] += 1;
	}
	for(long i = 1; i < m; ++i) {
		number[i] += number[i-1];
		counter[i] = number[i-1];
	}
	counter[0] = 0;
	for(long i = 0; i < n; ) {
		long idx = key(d[i]) % m;
		if ( counter[idx] != number[idx] ) {
			data t = d[counter[idx]];
			d[counter[idx]] = d[i];
			d[i] = t;
			counter[idx] += 1;
		} else {
			i += 1;
		}
	}
}

void down_to_leaf(const data d[], int idx[], int i, int end,
		int (*compare)(const data *, const int, const int)) {
	unsigned int larger, tmp;

	while ((i << 1) + 1 < end) {
		larger = (i << 1) + 1;
		if (((i << 1) + 2 < end)
				&& (compare(d, idx[(i << 1) + 1], idx[(i << 1) + 2] ))) {
			larger = (i << 1) + 2;
		}
		if (compare(d, idx[larger], idx[i])) {
			SWAP(idx[larger], idx[i], tmp);
			i = larger;
		} else {
			return;
		}
	}
	return;
}
	
void build_heap(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int) ) {
	long i;
		
		for (i = (n>>1) - 1 ; ! (i < 0); i--) {
			down_to_leaf(d, a, i, n, compare);
		}
		return;
    }
	
void heapSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int)) {
	long i;
	long t;

	build_heap(d, a, n, compare);
	for (i = n - 1; i > 0; i--) {
		// a[0] is always the maximum.
		SWAP(a[0], a[i], t);
		down_to_leaf(d, a, 0, i, compare);
	}
	return;
}

/*
void selectionSort_range(const data d[], unsigned int a[], unsigned int start, unsigned int end){
	long i, j, max, t; // i for the length (end+1) of sorted-array.
		
	for(i = end - 1; i > start; i--){
		for(j = start, max = i; j < i; j++ ){
			if(a[j] > a[max]) {
				max = j;
			}
		}
		SWAP(a[max], a[i], t);
		}
	return;
}

void selectionSort(const data d[], unsigned int a[], unsigned int n) {
	return selectionSort_range(d, a, 0, n);
}
*/

void selectionSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int)) {
	long t, x;
	for(long i = 0; i < n - 1; ++i) {
		x = i;
		for(long j = i + 1; j < n; ++j) {
			if ( compare(d, a[x], a[j] ) )
				x = j;
		}
		SWAP(a[i], a[x], t);
	}
	return;
}

void quickSort_range(const data d[], int array[], int start, int end,
				int (*compare)(const data *, const int, const int) ) {
	unsigned int smaller, larger, mid;
	unsigned int tmp;
		
	// do nothing if the size of array equals one.
	if (! (end - start > 1)) {
		return;
	}

	// order the first, the middle and the last elements.
	if ( compare(d, array[start], array[end - 1]) ) {
		SWAP(array[start], array[end - 1], tmp);
	}
	if (end - start == 2) {
		return;
	}
	mid = ((end - start)>>1) + start;
	if (compare(d, array[start], array[mid]) ) {
		SWAP(array[start], array[mid], tmp);
	}
	if (compare(d, array[mid], array[end - 1]) ) {
		SWAP(array[mid], array[end - 1], tmp);
	}
	// already enough if the size is no more than three.
	if (end - start == 3) {
		return;
	}
	// use the middle element as the pivot value.
	SWAP(array[start], array[mid], tmp);
	smaller = start + 1;
	larger = end - 1;
	while ( smaller < larger) {
		if ( !compare(d, array[smaller], array[start]) ) {
			++smaller;
		} else {
			// swap array[smaller] with array[larger - 1].
			--larger;
			SWAP(array[smaller], array[larger], tmp);
		}
	}

	// divide into two arrays; the latter always has at least one element.
	quickSort_range(d, array, start, smaller, compare);
	quickSort_range(d, array, smaller, end, compare);
	return;
}
    
void quickSort(const data d[], int array[], int n, int (*compare)(const data *, const int, const int)) {
	quickSort_range(d, array, 0, n, compare);
}


void bubbleSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int)){
	int i, j, tmp;

	for(i = 1; i < n; i++){
		for(j = n - 1; j >= i; j--){
			if(compare(d, a[j-1], a[j])) {
				tmp = a[j];
				a[j] = a[j-1];
				a[j-1] = tmp;
			}
		}
	}
	return;
}
	
void insertionSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int)){
	unsigned int i, j, t; // j for the length (end+1) of sorted-array.

	for(j = 1; j < n; j++) {
		t = a[j];
		for (i = j; i > 0; i--) {
			if ( compare(d, a[i-1], t) ) {
				a[i] = a[i-1];
				continue;
			}
		}
		a[i] = t;
	}
	return;
}
	
	

void merge(const data d[], int dst[], int lsrc[], int llen, int rsrc[], int rlen,
		int (*compare)(const data *, const int, const int)) {
	int dstlen = llen + rlen;
	int left, right, temp;
	for (left = 0, right = 0, temp = 0; temp < dstlen; temp++) {
		if (left < llen && right < rlen) {
			if (compare(d, rsrc[right], lsrc[left]) ) {
				dst[temp] = lsrc[left];
				left++;
			} else {
				dst[temp] = rsrc[right];
				right++;
			}
		} else {
			if (left < llen) {
				dst[temp] = lsrc[left];
				left++;
			} else {
				dst[temp] = rsrc[right];
				right++;
			}
		}
	}
}

void mergeSort_recursive(const data d[], int array[], int n,
		int (*compare)(const data *, const int, const int)) {
	int i, l, r;
	int bufl[n/2];
	int bufr[n/2+(n % 2)];

	if (n <= 1)
		return;
	for (i = 0; i < n/2; i++) {
		bufl[i] = array[i];
	}
	for (r = 0; i < n; i++, r++) {
		bufr[r] = array[i];
	}
	mergeSort_recursive(d, bufl, (n>>1), compare);
	mergeSort_recursive(d, bufr, n - (n>>1), compare);
	for (i = 0, l = 0, r = 0; i < n; i++){
		if ( !(r < n - (n>>1)) ) {
			array[i]=bufl[l];
			l++;
			continue;
		} else if ( !(l < n) ) {
			array[i]=bufr[r];
			r++;
			continue;
		} else if ( (bufl[l] < bufr[r]) ) {
			array[i]=bufl[l];
			l++;
		} else {
			array[i]=bufr[r];
			r++;
		}
	}
	return;
}
    

void mergeSort(const data d[], int array[], int n, int (*compare)(const data *, const int, const int)) {
	int buf[n];
	int i, len, start, llen, rstart, rlen;
	const int bubble_len = 8;

	for (len = bubble_len; len < n; len = len<<1) {
		for (start = 0; start < n; start += (len<<1)) {
			llen = MIN(len, n - start);
			rstart = start + len;
			rlen = MIN(len, n - rstart );
			if ( len == bubble_len ) {
				bubbleSort(d, array+start, llen, compare);
				if ( rstart < n )
					bubbleSort(d, array+rstart, rlen, compare);
			}
			if ( rstart < n ) {
				// merge array[start,...,start+len-1] and array[start+len,...,start+len+rlen-1]
				merge(d, buf+start, array+start, llen, array+rstart, rlen, compare);
				// copy back
				for (i = 0; i < llen + rlen; i++)
					array[start+i] = buf[start+i];
			}
		}
	}
	return;
}
    
