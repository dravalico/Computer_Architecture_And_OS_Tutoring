#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_CHILDREN 40

int *create_shared_memory(int size) {
    key_t key;
    int shm_id;
    int *data;
    int shm_size = sizeof(int) * size;

    key = ftok(".", 'r');
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }

    shm_id = shmget(key, shm_size, 0644 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget()");
        exit(1);
    }

    data = (int *) shmat(shm_id, (void *) 0, 0);
    if (data == (int *) -1) {
        perror("shmat()");
        exit(1);
    }
    return data;
}

int fibonacci(int n) {
    switch (n) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int *data = create_shared_memory(N_CHILDREN);
    int pids[N_CHILDREN];
    for (int i = 0; i < N_CHILDREN; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork()");
            exit(1);
        } else if (pids[i] == 0) {
            data[i] = fibonacci(i);
            if (shmdt(data) == -1) {
                perror("shmdt()");
                exit(1);
            }
            exit(0);
        }
    }

    for (int i = 0; i < N_CHILDREN; i++) {
        if (wait(&pids[i]) == -1) {
            perror("wait()");
            exit(1);
        }
    }
    for (int j = 0; j < N_CHILDREN; j++) {
        printf("fibonacci(%d) = %d\n", j, data[j]);
    }
    if (shmdt(data) == -1) {
        perror("shmdt()");
        exit(1);
    }

    return 0;
}
