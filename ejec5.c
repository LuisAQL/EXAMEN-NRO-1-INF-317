#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int N;
    int rank, size;

    MPI_Init(&argc, &argv); //inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    
    if (rank == 0) {

        printf("N: ");
        scanf("%d", &N);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *a = (int*)malloc(N * N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));
    int *local_a = (int*)malloc(N * (N/size) * sizeof(int));
    int *local_c = (int*)malloc((N/size) * sizeof(int));

    if (rank == 0) {
        printf("Matriz A (%d x %d):\n", N, N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &a[i * N + j]);
            }
        }

        printf("Matriz B (%d):\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &b[i]);
        }
    }

    MPI_Bcast(b, N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(a, N * (N/size), MPI_INT, local_a, N * (N/size), MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N/size; i++) {
        local_c[i] = 0;
    }

    for (int i = 0; i < N/size; i++) {
        for (int j = 0; j < N; j++) {
            local_c[i] += local_a[i * N + j] * b[j];
        }
    }


    MPI_Gather(local_c, N/size, MPI_INT, c, N/size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultado:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", c[i]);
        }
        printf("\n");
    }

    //liberar la memoria 
    free(a);
    free(b);
    free(c);
    free(local_a);
    free(local_c);

    MPI_Finalize();

    return 0;
}
