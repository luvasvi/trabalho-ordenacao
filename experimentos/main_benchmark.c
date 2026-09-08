#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================================
   1. QUICKSORT (Obrigatório - Partição de Hoare com pivô central)
   ========================================================================= */
void quicksort_rec(int *A, int esq, int dir) {
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

    if (esq < j) quicksort_rec(A, esq, j);
    if (i < dir) quicksort_rec(A, i, dir);
}

void quicksort(int *A, int n) {
    if (n > 1) {
        quicksort_rec(A, 0, n - 1);
    }
}

/* =========================================================================
   2. MERGE SORT (Algoritmo 2 - Buffer auxiliar único para alta performance)
   ========================================================================= */
void merge(int *A, int esq, int meio, int dir, int *temp) {
    int i = esq;
    int j = meio + 1;
    int k = esq;

    while (i <= meio && j <= dir) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
        }
    }

    while (i <= meio) temp[k++] = A[i++];
    while (j <= dir)  temp[k++] = A[j++];

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

/* =========================================================================
   3. INSERTION SORT (Algoritmo 3 - In-place elementar)
   ========================================================================= */
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

/* =========================================================================
   GERADORES DE VETOR (Conforme Parte IV do roteiro da disciplina)
   ========================================================================= */
void gerar_aleatorio(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 10);
    }
}

void gerar_ordenado(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void gerar_inverso(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

/* =========================================================================
   MEDIÇÃO DE TEMPO
   ========================================================================= */
double medir_tempo_ms(void (*algoritmo)(int*, int), int *A, int n) {
    clock_t inicio = clock();
    algoritmo(A, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
}

/* =========================================================================
   FLUXO PRINCIPAL DE EXECUÇÃO
   ========================================================================= */
int main() {
    srand(42); /* Semente fixa para reproducibilidade dos experimentos */

    int tamanhos[] = {100, 1000, 10000, 100000};
    int total_tamanhos = 4;

    const char *nomes_algoritmos[] = {"Quicksort", "Merge Sort", "Insertion Sort"};
    void (*algoritmos[])(int*, int) = {quicksort, merge_sort, insertion_sort};

    const char *tipos_entrada[] = {"Aleatória", "Ordenada", "Inversa"};
    void (*geradores[])(int*, int) = {gerar_aleatorio, gerar_ordenado, gerar_inverso};

    /* Abertura do arquivo CSV para exportação dos resultados */
    FILE *fp = fopen("resultados.csv", "w");
    if (fp != NULL) {
        fprintf(fp, "Algoritmo,Entrada,100,1000,10000,100000,Unidade\n");
    }

    printf("=======================================================================================\n");
    printf("                  BENCHMARK DE ALGORITMOS DE ORDENACAO (TEMPOS EM MS)                  \n");
    printf("=======================================================================================\n");
    printf("%-16s | %-11s | %-9s | %-9s | %-9s | %-9s\n", 
           "Algoritmo", "Entrada", "100", "1.000", "10.000", "100.000");
    printf("---------------------------------------------------------------------------------------\n");

    for (int a = 0; a < 3; a++) {
        for (int e = 0; e < 3; e++) {
            printf("%-16s | %-11s | ", nomes_algoritmos[a], tipos_entrada[e]);
            if (fp != NULL) {
                fprintf(fp, "%s,%s", nomes_algoritmos[a], tipos_entrada[e]);
            }

            for (int t = 0; t < total_tamanhos; t++) {
                int n = tamanhos[t];

                /* Conforme item 6 do roteiro: interrupção de casos com tempo excessivo (O(n²)) */
                if (a == 2 && n == 100000 && e != 1) {
                    printf("%-9s | ", "TIMEOUT*");
                    if (fp != NULL) fprintf(fp, ",TIMEOUT");
                    continue;
                }

                int *vetor = (int *)malloc(n * sizeof(int));
                if (vetor == NULL) {
                    fprintf(stderr, "\nErro de alocacao de memoria para n = %d\n", n);
                    return 1;
                }

                geradores[e](vetor, n);
                double tempo_ms = medir_tempo_ms(algoritmos[a], vetor, n);

                printf("%-9.3f | ", tempo_ms);
                if (fp != NULL) {
                    fprintf(fp, ",%.3f", tempo_ms);
                }

                free(vetor);
            }
            printf("\n");
            if (fp != NULL) {
                fprintf(fp, ",ms\n");
            }
        }
        printf("---------------------------------------------------------------------------------------\n");
    }

    if (fp != NULL) {
        fclose(fp);
        printf("\n[SUCESSO] Dados exportados com exito para o arquivo 'resultados.csv'.\n");
    }

    printf("* TIMEOUT: Teste interrompido conforme previsto no roteiro (complexidade O(n^2)).\n");
    return 0;
}
