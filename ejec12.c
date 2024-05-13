#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MASTER 0

//calcula fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int a = 0, b = 1, c;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int num_terms;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "Se necesitan al menos 2 procesos para este programa.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == MASTER) {
        scanf("%d", &num_terms);
    }

    MPI_Bcast(&num_terms, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    if (num_terms <= 0) {
        if (rank == MASTER) {
            printf("El número de términos debe ser un entero positivo.\n");
        }
        MPI_Finalize();
        return 1;
    }
    if (rank == MASTER) {
        for (int term = 0; term < num_terms; term++) {
            int fibonacci_term = fibonacci(term);
            printf("%d ", fibonacci_term);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

