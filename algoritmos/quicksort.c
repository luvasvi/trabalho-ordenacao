#include <stdio.h>

void quicksort(int *A, int esq, int dir) {
    int i = esq;
    int j = dir;
    int pivo = A[(esq + dir) / 2];
    int aux;

    while (i <= j) {
        while (A[i] < pivo) i++;
        while (A[j] > pivo) j--;
        
        if (i <= j) {
            aux = A[i];
            A[i] = A[j];
            A[j] = aux;
            i++;
            j--;
        }
    }

    if (esq < j) quicksort(A, esq, j);
    if (i < dir) quicksort(A, i, dir);
}

void quicksort_sort(int *A, int n) {
    if (n > 1) {
        quicksort(A, 0, n - 1);
    }
}
