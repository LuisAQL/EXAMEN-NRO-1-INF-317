#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10 //N Serie
#define M 4  //N de vectores y procesadores

int main(int argc, char *argv[]) {
    int numprocs, myid, i, j;
    int series[M][N]; //matriz

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (numprocs != M) {
        printf("Este programa debe ejecutarse con exactamente %d procesos.\n", M);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    //MPI genera su parte de la serie
    for (i = 0; i < N; i++) {
        series[myid][i] = (myid * N * 2) + (i * 2) + 2;
    }

    printf("Proceso %d: ", myid);
    for (j = 0; j < N; j++) {
        printf("%d ", series[myid][j]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

