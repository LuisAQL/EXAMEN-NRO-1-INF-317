#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int N;

    printf("N: ");
    scanf("%d", &N);

    int** a = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        a[i] = (int*)malloc(N * sizeof(int));
    }

    int* b = (int*)malloc(N * sizeof(int));
    int* c = (int*)malloc(N * sizeof(int));

    printf("Matriz A (%d x %d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Matriz B (%d):\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < N; i++) {
        c[i] = 0;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i] += a[i][j] * b[j];
        }
    }

    printf("Resultado: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    // Liberar la memoria asignada
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
