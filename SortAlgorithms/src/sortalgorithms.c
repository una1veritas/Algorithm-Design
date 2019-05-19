/*
 * SortAlgorithms.c
 *
 */
#include <stdio.h>
#include "sortalgorithms.h"

int data_greaterThan(data * a, data * b) {
	return *a > *b;
}

void maxHeapify(data d[], index a[], index i, index end) {
	index larger, tmp;
		
		while ( (i<<1) + 1 < end ) {
			larger = (i<<1) + 1;
			if ( ((i<<1) + 2 < end) && (a[(i<<1) + 1] < a[(i<<1) + 2]) ) {
				larger = (i<<1) + 2;
			}
			if ( data_greaterThan(d+a[larger], d+a[i]) ) {
				SWAP(a[larger], a[i], tmp);
				i = larger;
			} else {
				return;
			}
		}
		return;
    }
	
void buildMaxHeap(data d[], index a[], index n) {
	long i;
		
		for (i = (n>>1) - 1 ; ! (i < 0); i--) {
			maxHeapify(d, a, i, n);
		}
		return;
    }
	
void heapSort(data d[], index a[], index n) {
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
	

void selectionSort_range(data d[], index a[], index start, index end){
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
	
void selectionSort(data d[], index a[], index n) {
	return selectionSort_range(d, a, 0, n);
}


void quickSort_range(data d[], index array[], index start, index end) {
	index smaller, larger, mid;
	index tmp;
		
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
			smaller++;
		} else {
			// swap array[smaller] with array[larger - 1].
			larger--;
			SWAP(array[smaller], array[larger], tmp);
		}
	}

	// divide into two arrays; the latter always has at least one element.
	quickSort_range(d, array, start, smaller);
	quickSort_range(d, array, smaller, end);
	return;
}
    
void quickSort(data d[], index array[], index n) {
	quickSort_range(d, array, 0, n);
}


void bubbleSort(data d[], index a[], index n){
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
	
void insertionSort(data d[], index a[], index n){
	index i, j, t; // j for the length (end+1) of sorted-array.

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
	
	

void merge(data d[], index dst[], index lsrc[], index llen, index rsrc[], index rlen) {
	index dstlen = llen + rlen;
	index left, right, temp;
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

void mergeSort_recursive(data d[], index array[], index n) {
	index i, l, r;
	index bufl[n/2];
	index bufr[n/2+(n % 2)];

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
    

void mergeSort(data d[], index array[], index n) {
	index buf[n];
	index i, len, start, llen, rstart, rlen;
	const index bubble_len = 8;

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
    
