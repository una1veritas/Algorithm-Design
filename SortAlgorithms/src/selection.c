/*
 * sel.c
 * selection sort sample
 *
 */
#include <stdio.h>
#include <stdlib.h>

void selectionSort(long a[], long n) {
  long t;
  for(long i = 0; i < n; ++i) {
    for(long j = i + 1; j < n; ++j) {
      if ( a[i] > a[j] ) {
	t = a[i];
	a[i] = a[j];
	a[j] = t;
      }
    }
  }
  return;
}

int main(const int argc, const char * argv[]) {
  long n = argc - 1, a[n];
  for(long i = 0; i < n; ++i) {
    a[i] = atol(argv[1+i]);
    printf("%ld, ", a[i]);
  }
  printf("\n\n");
  
  selectionSort(a, n);
  
  for(long i = 0; i < n; ++i) {
    printf("%ld, ", a[i]);
  }
  printf("\n\n");

  return 0;
}
