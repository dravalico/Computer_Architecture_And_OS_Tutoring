#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_THREADS 4
#define ARRAY_SIZE 9000000
#define ITERATIONS (ARRAY_SIZE / N_THREADS)

int global_sum = 0;
int shared_array[ARRAY_SIZE];
pthread_mutex_t sum_mutex;

void *thread_entry_point(void *arg) {
    int id = *((int *) arg);
    int start = id * ITERATIONS;
    int end = start + ITERATIONS;
    printf("[thread %d] work on iterations %d to %d\n", id, start, end - 1);
    for (int i = start; i < end; i++) {
        pthread_mutex_lock(&sum_mutex);
        global_sum = global_sum + shared_array[i];
        pthread_mutex_unlock(&sum_mutex);
    }
    printf("[thread %d] finished the job\n", id);
    pthread_exit(NULL);
}

int main() {
    int i, threads_ids[N_THREADS];
    pthread_t threads[N_THREADS];
    srand(time(NULL));
    for (i = 0; i < ARRAY_SIZE; i++) {
        shared_array[i] = rand() % 10;
    }
    pthread_mutex_init(&sum_mutex, NULL);
    for (i = 0; i < N_THREADS; i++) {
        threads_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_entry_point, (void *) &threads_ids[i]);
    }
    for (i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    int sum = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        sum = sum + shared_array[i];
    }
    printf("\nSum computed by main = %d\n", sum);
    printf("Sum computed by threads = %d\n", global_sum);
    printf("main_sum %s", sum == global_sum ? "== global_sum\n" : "!= global_sum\n");
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit(NULL);
}