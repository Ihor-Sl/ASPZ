#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    const int size = 10000000;
    char *buffer = malloc(size);
    memset(buffer, 'A', size);

    ssize_t count = write(pipefd[1], buffer, size);

    if (count == -1) {
        perror("write");
    } else if (count < size) {
        printf("Partial write occurred! Requested: %d, Written: %zd\n", size, count);
    } else {
        printf("All bytes written successfully.\n");
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
