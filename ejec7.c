#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 1000000

double calculate_pi(int num_points, unsigned int seed) {
    int points_inside_circle = 0;
    for (int i = 0; i < num_points; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            points_inside_circle++;
        }
    }
    return 4.0 * points_inside_circle;
}

int main() {
    unsigned int seed = omp_get_thread_num(); 
    int num_threads = omp_get_max_threads();
    int total_points = NUM_POINTS;
    int points_per_thread = total_points / num_threads;

    double pi_estimate = 0.0;

    #pragma omp parallel reduction(+:pi_estimate)
    {
        int thread_num = omp_get_thread_num();
        int start = thread_num * points_per_thread;
        int end = start + points_per_thread;

        if (thread_num == num_threads - 1) {
            end += total_points % num_threads;
        }

        double local_pi_estimate = calculate_pi(end - start, seed + thread_num);
        pi_estimate += local_pi_estimate;
    }

    pi_estimate /= total_points;
    printf("Estimated value of PI is: %f\n", pi_estimate);

    return 0;
}

