#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    for (int i = 0; i < 10; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
        }

        if (pid == 0) {
            printf("Child process ID: %d\n", getpid());
            sleep(3);
            return 0;
        }
    }

    for (int i = 0; i < 10; i++) {
        wait(NULL);
    }

    return 0;
}