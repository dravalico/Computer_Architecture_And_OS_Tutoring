#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define N 10

void signal_handler(int sig) {
    char buf[20] = "[signal_handler]\n";
    write(1, buf, strlen(buf));
}

int main() {
    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        for (int i = 1;; i++) {
            pause();
            printf("[child %d] data=%02d\n", getpid(), i);
            sleep(1);
            if (kill(getppid(), SIGUSR1) == -1) {
                perror("kill");
                exit(1);
            }
        }
    } else {
        for (int i = 1; i <= N; i++) {
            printf("[parent    ] data=%02d\n", i);
            sleep(1);
            if (kill(pid, SIGUSR1) == -1) {
                perror("kill");
                exit(1);
            }
            pause();
        }
        if (kill(pid, SIGINT) == -1) {
            perror("kill");
            exit(1);
        }
        printf("Child %d end\n", wait(NULL));
    }

    return 0;
}
