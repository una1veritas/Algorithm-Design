/*
 * SortAlgorithms.c
 *
 */
#include <stdio.h>

#define min(a,b) ((a) < (b)? (a) : (b))

void maxHeapify(long a[], long i, long end) {
	long larger, tmp;
		
		while ( 2*i + 1 < end ) {
			larger = 2*i + 1;
			if ( (2*i + 2 < end) && (a[2*i + 1] < a[2*i + 2]) ) {
				larger = 2*i + 2;
			}
			if ( a[larger] > a[i] ) {
				tmp = a[larger];
				a[larger] = a[i];
				a[i] = tmp;
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
			t = a[i];
			a[i] = a[0];
			a[0] = t;
			maxHeapify(a, 0, i);
		}
		return;
    }
	
	
void selectionSort(long a[], long n){
	long i, j, max, t; // i for the length (end+1) of sorted-array.
		
		for(i = n - 1; i > 0; i--){
			for(j = 0, max = i; j < i; j++ ){
				if(a[j] > a[max]) {
					max = j;
				}
			}
			t = a[max];
			a[max] = a[i];
			a[i] = t;
			}
		return;
    }
	
/*	
    static void buildMAXHeap(Object array[]) {
		int i;
		
		for (i = (array.length / 2) - 1 ; ! (i < 0); i--) {
			maxHeapify(array, i, array.length);
		}
		return;
    }
	
    private static void maxHeapify(Object array[], int i, int end) {
		int c;
		Object tmp;
		
		while ( 2*i + 1 < end ) {
			c = 2*i + 1;
			if ( 2*i + 2 < end ) {
				if ( ((Comparable) array[2*i + 1]).compareTo(array[2*i + 2]) < 0) {
					c = 2*i + 2;
				}
			}
			if ( ((Comparable) array[c]).compareTo(array[i]) > 0 ) {
				tmp = array[c];
				array[c] = array[i];
				array[i] = tmp;
				i = c;
			} else {
				return;
			}
		}
		return;
    }
	
    public static void heapSort(Object array[]) {
		int i;
		Object tmp;
		
		buildMaxHeap(array);
		for (i = array.length - 1; i > 0; i--) {
			tmp = array[i];
			array[i] = array[0];
			array[0] = tmp;
			maxHeapify(array, 0, i);
		}
		return;
    }
*/	

void quickSort_range(long array[], long start, long end) {
	long smaller, larger, mid;
	long tmp;
		
		// do nothing if the size of array equals one. 
		if (! (end - start > 1)) {
			return;
		}
		
		// order the first, the middle and the last elements. 
		mid = (end - start) / 2 + start;
		if (array[end - 1] < array[start]) {
			tmp = array[start];
			array[start] = array[end - 1];
			array[end - 1] = tmp;
		}
		if (array[mid] < array[start]) {
			tmp = array[start];
			array[start] = array[mid];
			array[mid] = tmp;
		}
		if (array[end - 1] < array[mid]) {
			tmp = array[mid];
			array[mid] = array[end - 1];
			array[end - 1] = tmp;
		}
		if ( end - 1 > 100000 )
			printf("[%ld, %ld, %ld] = %ld, %ld, %ld.\n", start, mid, end-1,
				array[start], array[mid], array[end - 1]);
		
		// already enough if the size is no more than three. 
		if (end - start <= 3) {
			return;
		}
		
		// use the middle element as the pivot value. 
		tmp = array[start];
		array[start] = array[mid];
		array[mid] = tmp;
		smaller = start + 1;
		larger = end - 1;
		while ( smaller < larger) {
			if (array[smaller] <= array[start]) {
				smaller++;
			} else {
				// swap array[smaller] with array[larger - 1].
				larger--;
				tmp = array[smaller];
				array[smaller] = array[larger];
				array[larger] = tmp;
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
					tmp = a[j];
					a[j] = a[j-1];
					a[j-1] = tmp;
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
		int i, l, s, e, cl, cr, ct;
		
		for (l = 1; l < n; l = l * 2) {
			for (s = 0; s < n; s = s + (2 * l)) {
				e = min(s + (2 * l), n);
				for (cl = s, cr = s + l, ct = cl; ct < e; ct++) {
					if (cl < s+l && cr < e) {
						if (array[cl] < array[cr]) {
							buf[ct] = array[cl];
							cl++;
						} else {
							buf[ct] = array[cr];
							cr++;
						}
					} else {
						if (cl < s+l) {
							buf[ct] = array[cl];
							cl++;
						} else {
							buf[ct] = array[cr];
							cr++;
						}
					}
				}
			}
			for (i = 0; i < n; i++)
				array[i] = buf[i];
		}
		return;
    }
    
