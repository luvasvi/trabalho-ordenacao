#include <stdio.h>
#include <stdlib.h>

void merge(int *A, int esq, int meio, int dir, int *temp) {
    int i = esq;
    int j = meio + 1;
    int k = esq;

    while (i <= meio && j <= dir) {
        if (A[i] <= A[j]) { // O operador <= preserva a estabilidade
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
        }
    }

    while (i <= meio) {
        temp[k++] = A[i++];
    }

    while (j <= dir) {
        temp[k++] = A[j++];
    }

    for (i = esq; i <= dir; i++) {
        A[i] = temp[i];
    }
}

void merge_sort_rec(int *A, int esq, int dir, int *temp) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        merge_sort_rec(A, esq, meio, temp);
        merge_sort_rec(A, meio + 1, dir, temp);
        merge(A, esq, meio, dir, temp);
    }
}

void merge_sort(int *A, int n) {
    if (n <= 1) return;
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp != NULL) {
        merge_sort_rec(A, 0, n - 1, temp);
        free(temp);
    }
}
