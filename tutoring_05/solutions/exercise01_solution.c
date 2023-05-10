#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int main() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    pid_t pid_a = fork();
    if (pid_a == -1) {
        perror("fork()");
        exit(1);
    } else if (pid_a == 0) {
        int max_value = array[0];
        for (int i = 1; i < N; i++) {
            if (array[i] > max_value) {
                max_value = array[i];
            }
        }
        printf("[Child1 -> %d] Max value is %d\n", getpid(), max_value);
        exit(0);
    } else {
        pid_t pid_b = fork();
        if (pid_b == -1) {
            perror("fork()");
            exit(1);
        } else if (pid_b == 0) {
            int min_value = array[0];
            for (int i = 1; i < N; i++) {
                if (array[i] < min_value) {
                    min_value = array[i];
                }
            }
            printf("[Child2 -> %d] Min value is %d\n", getpid(), min_value);
            exit(0);
        } else {
            if (wait(&pid_a) == -1 || wait(&pid_b) == -1) {
                perror("wait()");
                exit(1);
            }
            double mean_value = 0;
            for (int i = 0; i < N; i++) {
                mean_value = mean_value + array[i];
            }
            mean_value = mean_value / N;
            printf("[Parent -> %d] Mean value is %f\n", getpid(), mean_value);
        }
    }

    return 0;
}