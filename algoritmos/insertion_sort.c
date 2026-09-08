#include <stdio.h>

void insertion_sort(int *A, int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = A[i];
        j = i - 1;

        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}
