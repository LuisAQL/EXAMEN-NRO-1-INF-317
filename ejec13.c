#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_TERMS 1000

//fibonacci
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

struct ThreadArgs {
    int start;
    int end;
    int* results;
};
void* fibonacci_rango(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    for (int i = args->start; i < args->end; i++) {
        args->results[i] = fibonacci(i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs args[NUM_THREADS];
    int resultados[NUM_TERMS];
    int terms_per_thread = NUM_TERMS / NUM_THREADS;

    //crear hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = i * terms_per_thread;
        args[i].end = (i + 1) * terms_per_thread;
        args[i].results = resultados;
        pthread_create(&threads[i], NULL, fibonacci_rango, (void*)&args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < NUM_TERMS; i++) {
        printf("%d ", resultados[i]);
    }
    printf("\n");

    return 0;
}

