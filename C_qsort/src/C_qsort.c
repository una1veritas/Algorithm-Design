#include <stdio.h>
#include <stdlib.h>

int order(const void * a, const void * b) {
      int inta = * (int*)a, intb = * (int*)b;
      /* inta と intb を使った計算 */
      return (inta % 6) - (intb % 6);
}

int main(const int argc, char *argv[]) {
      long n = argc - 1;
      int a[n];
      for (int i = 0; i < n; ++i) {
            a[i] = atoi(argv[1 + i]);
            printf("%d, ", a[i]);
      }
      printf("\n\n");
      qsort(a, n, sizeof(a[0]), order);
      for (int i = 0; i < n; ++i) {
            printf("%d, ", a[i]);
      }
      printf("\n\n");
      return 0;
}
