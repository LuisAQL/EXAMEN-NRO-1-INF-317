#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 4   //N Serie
#define N 10  //N de vectores y procesadores

//estructura
struct ThreadArgs {
    int serie[N];
    int inicio; //primer termino
};

void *generar_serie(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

    for (int i = 0; i < N; i++) {
        args->serie[i] = args->inicio + i * 2;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[M];
    struct ThreadArgs args[M];

    //crear y ejecutar los hilos
    for (int i = 0; i < M; i++) {
        args[i].inicio = 2 + i * 2 * N; // Calcular el primer término de la serie para este hilo
        pthread_create(&threads[i], NULL, generar_serie, (void *)&args[i]);
    }

    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < M; i++) {
        printf("Serie %d: ", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d ", args[i].serie[j]);
        }
        printf("\n");
    }

    return 0;
}

