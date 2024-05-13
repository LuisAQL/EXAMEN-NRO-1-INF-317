#include <stdio.h>
#include <omp.h>

#define N 10 //N Serie
#define M 4  //N de vectores y procesadores

int main() {
    int series[M][N]; //matriz
    int i, j;

    #pragma omp parallel num_threads(M) private(i, j)
    {
        int id = omp_get_thread_num(); 

        for (i = 0; i < N; i++) {
            series[id][i] = (id * N * 2) + (i * 2) + 2;
        }
    }

    printf("Series generadas:\n");
    for (i = 0; i < M; i++) {
        printf("Vector %d: ", i + 1);
        for (j = 0; j < N; j++) {
            printf("%d ", series[i][j]);
        }
        printf("\n");
    }

    return 0;
}

