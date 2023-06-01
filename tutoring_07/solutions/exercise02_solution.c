#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_EXCHANGES 10

volatile sig_atomic_t parent_sig;
volatile sig_atomic_t child_sig;

void signal_handler_parent(int sig) {
    parent_sig = 1;
}

void signal_handler_child(int sig) {
    child_sig = 1;
}

int main() {
    srand(time(NULL));
    int i = rand() % 2;
    if (i) {
        parent_sig = 1;
        child_sig = 0;
    } else {
        parent_sig = 0;
        child_sig = 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork()");
        exit(1);
    } else if (pid == 0) {
        if (signal(SIGUSR1, signal_handler_child) == SIG_ERR) {
            perror("signal()");
            exit(1);
        }
        for (;;) {
            while (child_sig != 1) {
                sleep(1);
            }
            printf("Ping!\n");
            sleep(1);
            child_sig = 0;
            kill(getppid(), SIGUSR1);
        }
    } else {
        if (signal(SIGUSR1, signal_handler_parent) == SIG_ERR) {
            perror("signal()");
            exit(1);
        }
        sleep(1);
        for (int exchange = 0; exchange < MAX_EXCHANGES; exchange++) {
            while (parent_sig != 1) {
                sleep(1);
            }
            printf("\tPong!\n");
            sleep(1);
            parent_sig = 0;
            kill(pid, SIGUSR1);
        }
        kill(pid, SIGINT);
        if (wait(&pid) == -1) {
            perror("wait()");
            exit(1);
        }
    }
    printf("Game finished!\n");

    return 0;
}