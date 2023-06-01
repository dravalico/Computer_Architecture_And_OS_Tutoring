#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N_CHAR 6
#define N_CHILDREN 15
#define SIZE (N_CHAR*N_CHILDREN)

char *create_shared_memory(int size) {
    key_t key;
    int shm_id;
    char *data;
    int shm_size = sizeof(char) * size;

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

    data = (char *) shmat(shm_id, (void *) 0, 0);
    if (data == (char *) -1) {
        perror("shmat()");
        exit(1);
    }
    return data;
}

int main() {
    char *data = create_shared_memory(SIZE);
    pid_t pids[N_CHILDREN];

    for (int i = 0, offset; i < N_CHILDREN; i++) {
        pids[i] = fork();
        switch (pids[i]) {
            case -1:
                perror("fork()");
                exit(1);
            case 0:
                offset = i * SIZE / N_CHILDREN;
                char to_write = (char) ('a' + i);
                for (int j = 0; j < N_CHAR; j++) {
                    data[offset + j] = to_write;
                }
                printf("[child %04d] wrote '%c' from %d\n", getpid(), *(data + offset), offset);
                if (shmdt(data) == -1) {
                    perror("shmdt()");
                    exit(1);
                }
                exit(0);
        }
    }

    for(int i = 0; i < N_CHILDREN; i++) {
        if (wait(&pids[i]) == -1) {
            perror("wait()");
            exit(1);
        }
    }

    for (int i = 0; i < SIZE; i += 1) {
        printf("%c", data[i]);
    }
    if (shmdt(data) == -1) {
        perror("shmdt()");
        exit(1);
    }

    return 0;
}
