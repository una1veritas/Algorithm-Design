/*
 * SortAlgorithms.c
 *
 */
#include <stdio.h>

#define MIN(a,b) ((a) < (b)? (a) : (b))
#define SWAP(a, b, t) 	{ (t) = (a); (a) = (b); (b) = (t); }

void maxHeapify(long a[], long i, long end) {
	long larger, tmp;
		
		while ( 2*i + 1 < end ) {
			larger = 2*i + 1;
			if ( (2*i + 2 < end) && (a[2*i + 1] < a[2*i + 2]) ) {
				larger = 2*i + 2;
			}
			if ( a[larger] > a[i] ) {
				SWAP(a[larger], a[i], tmp);
				i = larger;
			} else {
				return;
			}
		}
		return;
    }
	
void buildMaxHeap(long a[], long n) {
	long i;
		
		for (i = (n / 2) - 1 ; ! (i < 0); i--) {
			maxHeapify(a, i, n);
		}
		return;
    }
	
void heapSort(long a[], long n) {
	long i;
	long t;
		
		buildMaxHeap(a, n);
		for (i = n - 1; i > 0; i--) {
			// a[0] is always the maximum. 
			SWAP(a[i], a[0], t);
			maxHeapify(a, 0, i);
		}
		return;
    }
	

void selectionSort_range(long a[], long start, long end){
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
	
void selectionSort(long a[], long n) {
	return selectionSort_range(a, 0, n);
}


void quickSort_range(long array[], long start, long end) {
	long smaller, larger, mid;
	long tmp;
		
		// do nothing if the size of array equals one. 
		if (! (end - start > 1)) {
			return;
		}
		
		// order the first, the middle and the last elements. 
		if (array[end - 1] < array[start]) {
			SWAP(array[start], array[end - 1], tmp);
		}
		if (end - start == 2) {
			return;
		}
		mid = ((end - start)>>1) + start;
		if (array[mid] < array[start]) {
			SWAP(array[start], array[mid], tmp);
		}
		if (array[end - 1] < array[mid]) {
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
			if (array[smaller] <= array[start]) {
				smaller++;
			} else {
				// swap array[smaller] with array[larger - 1].
				larger--;
				SWAP(array[smaller], array[larger], tmp);
			}
		}
		
		// divide into two arrays; the latter always has at least one element. 
		quickSort_range(array, start, smaller);
		quickSort_range(array, smaller, end);
		return;
    }
    
void quickSort(long array[], long n) {
		quickSort_range(array, 0, n);
    }


void bubbleSort(int a[], int n){
		int i, j, tmp;
		
		for(i = 1; i < n; i++){
			for(j = n - 1; j >= i; j--){
				if(a[j-1] > a[j]) {
					SWAP(a[j], a[j-1], tmp);
				}
			}
		}
		return;
    }
	
void insertionSort(int a[], int n){
		int i, j, t; // j for the length (end+1) of sorted-array.
		
		for(j = 1; j < n; j++) {
			t = a[j];
			for (i = j; i > 0; i--) {
				if (a[i-1] > t) {
					a[i] = a[i-1];
					continue;
				}
			}
			a[i] = t;
		}
		return;
    }
	
	
void mergeSort_recursive(int array[], int n) {
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
		mergeSort_recursive(bufl, n/2);
		mergeSort_recursive(bufr, n - n/2);
		for (i = 0, l = 0, r = 0; i < n; i++){
			if ( !(r < n - n/2) ) {
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
    
    
void mergeSort(int array[], int n) {
		int buf[n];
		int i, len, start, end, cleft, cright, ctemp;
		
		for (len = 1; len < n; len = len<<1) {
			for (start = 0; start < n; start = start + (len<<1)) {
				end = MIN(start + (len<<1), n);
				//printf("cdp_merge %d [%d, %d)\n", len, start, end);
				for (cleft = start, cright = start + len, ctemp = cleft; ctemp < end; ctemp++) {
					if (cleft < start+len && cright < end) {
						if (array[cleft] < array[cright]) {
							buf[ctemp] = array[cleft];
							cleft++;
						} else {
							buf[ctemp] = array[cright];
							cright++;
						}
					} else {
						if (cleft < start+len) {
							buf[ctemp] = array[cleft];
							cleft++;
						} else {
							buf[ctemp] = array[cright];
							cright++;
						}
					}
				}
			}
			//copy back
			for (i = 0; i < n; i++)
				array[i] = buf[i];
		}
		return;
    }
    

int verify(long a[], long n) {
	long i;
	for(i = 1; i < n; i++) {
		if ( a[i-1] > a[i] )
			return 0;
	}
	return 1;
}
