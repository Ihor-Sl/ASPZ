#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char *buffer = malloc(1024 * 1024 * 1024);
    memset(buffer, 'A', 1024 * 1024 * 1024);

    while (1) {
        ssize_t bytes_written = write(fd, buffer, 1024 * 1024 * 1024);
        if (bytes_written < 0) {
            perror("write");
            printf("errno: %d (%s)\n", errno, strerror(errno));
            break;
        }
    }

    close(fd);
    free(buffer);
    return 0;
}
