#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

void handle_sigusr1(int sig) {
    printf("Child: received SIGUSR1\n");
    kill(getppid(), SIGUSR2);
}

void handle_sigusr2(int sig) {
    printf("Parent: received SIGUSR2\n");
}

int main() {
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        while (1) {
            pause();
        }
    } else {
        sleep(1);

        printf("Parent: sending SIGUSR1 to child\n");
        kill(child_pid, SIGUSR1);

        pause();

        kill(child_pid, SIGTERM);
        wait(NULL);
    }

    return 0;
}
