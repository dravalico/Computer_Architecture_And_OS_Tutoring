#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char *str_from_child_a = malloc(sizeof(char) * 100);
    if (str_from_child_a == NULL) {
        perror("malloc()");
        exit(1);
    }
    char *str_from_child_b = malloc(sizeof(char) * 100);
    if (str_from_child_b == NULL) {
        perror("malloc()");
        exit(1);
    }

    int pipe_fd_a[2];
    if (pipe(pipe_fd_a) < 0) {
        perror("pipe()");
        exit(1);
    }

    int pipe_fd_b[2];
    if (pipe(pipe_fd_b) < 0) {
        perror("pipe()");
        exit(1);
    }

    int res;
    pid_t child_b;
    pid_t child_a = fork();
    if (child_a == -1) {
        perror("fork()");
        exit(1);
    } else if (child_a == 0) {
        close(pipe_fd_a[0]);
        char ra[] = "This sentence will be";
        if (write(pipe_fd_a[1], ra, strlen(ra)) < 0) {
            perror("write()");
            exit(1);
        }
        exit(0);
    } else {
        child_b = fork();
        if (child_b == -1) {
            perror("fork()");
            exit(1);
        } else if (child_b == 0) {
            close(pipe_fd_b[0]);
            char rb[] = " completed by child b";
            if (write(pipe_fd_b[1], rb, strlen(rb)) < 0) {
                perror("write()");
                exit(1);
            }
            exit(0);
        }
    }
    if (wait(&child_a) == -1 || wait(&child_b) == -1) {
        perror("wait()");
        exit(1);
    }
    //close(pipe_fd_a[1]);
    for (int i = 0; (res = read(pipe_fd_a[0], &str_from_child_a[i], sizeof(char))) > 0; i++) {
        if (res < 0) {
            perror("read()");
            exit(1);
        }
    }

    printf("C");
    //close(pipe_fd_b[1]);
    for (int i = 0; (res = read(pipe_fd_b[0], &str_from_child_b[i], sizeof(char))) > 0; i++) {
        if (res < 0) {
            perror("read()");
            exit(1);
        }
    }
    printf("%s\n", strcat(str_from_child_a, str_from_child_b));
    free(str_from_child_a);
    free(str_from_child_b);

    return 0;
}
