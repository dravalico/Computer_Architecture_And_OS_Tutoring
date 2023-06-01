#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N_THREADS 3

long x = 3;

void *thread_entry_point(void *arg) {
    int pow = *((int *) arg);
    free(arg);
    long result = x;
    for (int i = 1; i < pow; i++) {
        result *= x;
    }
    return (void *) result;
}

long computeFunctionValue() {
    pthread_t t[N_THREADS];
    for (int i = 0, exponent = 4; i < N_THREADS; i++, exponent--) {
        int *arg = malloc(sizeof(int *));
        if (arg == NULL) {
            perror("malloc()");
            exit(1);
        }

        *arg = exponent;
        if (pthread_create(&t[i], NULL, thread_entry_point, arg) != 0) {
            perror("pthread_create()");
            exit(1);
        }
    }
    void *temp[N_THREADS] = {NULL, NULL, NULL};
    long result = 0;
    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(t[i], &temp[i]) != 0) {
            perror("pthread_join()");
            exit(1);
        }
        if (i == 1) {
            result -= (long) temp[i];
        } else {
            result += (long) temp[i];
        }
    }
    return result;
}

int main() {
    long result = computeFunctionValue();
    printf("computeFunctionValue(%ld) = %ld\n", x, result);
    return 0;
}
