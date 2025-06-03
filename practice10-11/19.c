#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int count = 0;

    while (1) {
        pid_t pid = fork();

        if (pid < 0) {
            break;
        } else if (pid == 0) {
            while (1) pause();
        } else {
            count++;
        }
    }

    printf("Кількість успішно створених процесів: %d\n", count);
    return 0;
}
