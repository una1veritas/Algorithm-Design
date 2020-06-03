/*
 * SortAlgorithms.c
 *
 */
#include <stdio.h>
#include "sortalgorithms.h"

int verify_sorted(const data d[], const unsigned int idx[], unsigned int n) {
	for(unsigned int i = 0; i < n - 1; ++i) {
		if ( data_greaterThan(d, idx[i], idx[i]) )
			return 0;
	}
	return 1;
}

void maxHeapify(const data d[], unsigned int idx[], unsigned int i, unsigned int end) {
	unsigned int larger, tmp;

	while ((i << 1) + 1 < end) {
		larger = (i << 1) + 1;
		if (((i << 1) + 2 < end)
				&& (greaterThan(d, idx[(i << 1) + 1], idx[(i << 1) + 2] ))) {
			larger = (i << 1) + 2;
		}
		if (data_greaterThan(d, idx[larger], idx[i])) {
			SWAP(idx[larger], idx[i], tmp);
			i = larger;
		} else {
			return;
		}
	}
	return;
}
	
void buildMaxHeap(const int d[], unsigned int a[], unsigned int n) {
	long i;
		
		for (i = (n>>1) - 1 ; ! (i < 0); i--) {
			maxHeapify(d, a, i, n);
		}
		return;
    }
	
void heapSort(const int d[], unsigned int a[], unsigned int n) {
	long i;
	long t;

	buildMaxHeap(d, a, n);
	for (i = n - 1; i > 0; i--) {
		// a[0] is always the maximum.
		SWAP(a[0], a[i], t);
		maxHeapify(d, a, 0, i);
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

void selectionSort(const int d[], unsigned int a[], unsigned int n) {
	long t, x;
	for(long i = 0; i < n - 1; ++i) {
		x = i;
		for(long j = i + 1; j < n; ++j) {
			if ( d[a[x]] > d[a[j]] )
				x = j;
		}
		SWAP(a[i], a[x], t);
	}
	return;
}

void quickSort_range(const int d[], unsigned int array[], unsigned int start, unsigned int end) {
	unsigned int smaller, larger, mid;
	unsigned int tmp;
		
	// do nothing if the size of array equals one.
	if (! (end - start > 1)) {
		return;
	}

	// order the first, the middle and the last elements.
	if ( data_greaterThan(d+array[start], d+array[end - 1]) ) {
		SWAP(array[start], array[end - 1], tmp);
	}
	if (end - start == 2) {
		return;
	}
	mid = ((end - start)>>1) + start;
	if (data_greaterThan(d+array[start], d+array[mid]) ) {
		SWAP(array[start], array[mid], tmp);
	}
	if (data_greaterThan(d+array[mid], d+array[end - 1]) ) {
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
		if ( !data_greaterThan(d+array[smaller], d+array[start]) ) {
			++smaller;
		} else {
			// swap array[smaller] with array[larger - 1].
			--larger;
			SWAP(array[smaller], array[larger], tmp);
		}
	}

	// divide into two arrays; the latter always has at least one element.
	quickSort_range(d, array, start, smaller);
	quickSort_range(d, array, smaller, end);
	return;
}
    
void quickSort(const int d[], unsigned int array[], unsigned int n) {
	quickSort_range(d, array, 0, n);
}


void bubbleSort(const int d[], unsigned int a[], unsigned int n){
	int i, j, tmp;

	for(i = 1; i < n; i++){
		for(j = n - 1; j >= i; j--){
			if(data_greaterThan(&d[a[j-1]], &d[a[j]])) {
				tmp = a[j];
				a[j] = a[j-1];
				a[j-1] = tmp;
			}
		}
	}
	return;
}
	
void insertionSort(const int d[], unsigned int a[], unsigned int n){
	unsigned int i, j, t; // j for the length (end+1) of sorted-array.

	for(j = 1; j < n; j++) {
		t = a[j];
		for (i = j; i > 0; i--) {
			if ( data_greaterThan(&d[a[i-1]], &d[t]) ) {
				a[i] = a[i-1];
				continue;
			}
		}
		a[i] = t;
	}
	return;
}
	
	

void merge(const int d[], unsigned int dst[], unsigned int lsrc[], unsigned int llen, unsigned int rsrc[], unsigned int rlen) {
	unsigned int dstlen = llen + rlen;
	unsigned int left, right, temp;
	for (left = 0, right = 0, temp = 0; temp < dstlen; temp++) {
		if (left < llen && right < rlen) {
			if (data_greaterThan(d+rsrc[right], d+lsrc[left]) ) {
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

void mergeSort_recursive(const int d[], unsigned int array[], unsigned int n) {
	unsigned int i, l, r;
	unsigned int bufl[n/2];
	unsigned int bufr[n/2+(n % 2)];

	if (n <= 1)
		return;
	for (i = 0; i < n/2; i++) {
		bufl[i] = array[i];
	}
	for (r = 0; i < n; i++, r++) {
		bufr[r] = array[i];
	}
	mergeSort_recursive(d, bufl, (n>>1) );
	mergeSort_recursive(d, bufr, n - (n>>1));
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
    

void mergeSort(const int d[], unsigned int array[], unsigned int n) {
	unsigned int buf[n];
	unsigned int i, len, start, llen, rstart, rlen;
	const unsigned int bubble_len = 8;

	for (len = bubble_len; len < n; len = len<<1) {
		for (start = 0; start < n; start += (len<<1)) {
			llen = MIN(len, n - start);
			rstart = start + len;
			rlen = MIN(len, n - rstart );
			if ( len == bubble_len ) {
				bubbleSort(d, array+start, llen);
				if ( rstart < n )
					bubbleSort(d, array+rstart, rlen );
			}
			if ( rstart < n ) {
				// merge array[start,...,start+len-1] and array[start+len,...,start+len+rlen-1]
				merge(d, buf+start, array+start, llen, array+rstart, rlen);
				// copy back
				for (i = 0; i < llen + rlen; i++)
					array[start+i] = buf[start+i];
			}
		}
	}
	return;
}
    
