#include <stdio.h>

void merge(int dst[], int a[], long l, int b[], long m) {
    long i = 0, j = 0, t = 0;
    while (i < l || j < m) {
        if (i == l)
        	dst[t++] = b[j++];
        else if (j == m)
        	dst[t++] = a[i++];
        else if (a[i] < b[j])
        	dst[t++] = a[i++];
        else
        	dst[t++] = b[j++];
    }
}

int main(void) {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = 6;
    int i;

    printf("Before: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int tmp[n];
    for (long l = 1; l < n; l <<= 1) {
        for (long i = 0; i < n; i += l << 1) {
            long m = (i + l < n) ? i + l : n;
            long r = (i + (l << 1) < n) ? i + (l << 1) : n;
            merge(tmp + i, arr + i, m - i, arr + m, r - m);
        }
        for (long i = 0; i < n; ++i)
        	arr[i] = tmp[i];
    }

    printf("After: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
