#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

#define MAX_ROLLS 1000
#define FILE_NAME "dice_rolls.txt"

void handle_sigxfsz(int signum) {
    printf("File size limit reached. Stopping write operation.\n");
    exit(EXIT_FAILURE);
}

int main() {
    signal(SIGXFSZ, handle_sigxfsz);

    struct rlimit lim;

    if (getrlimit(RLIMIT_FSIZE, &lim) != 0) {
        perror("Failed to get file size limit");
        return 1;
    }

    printf("Current file size limit: soft = %ld, hard = %ld\n",
           (long)lim.rlim_cur, (long)lim.rlim_max);

    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("Cannot open file");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < MAX_ROLLS; i++) {
        if (fprintf(file, "%d\n", rand() % 6 + 1) < 0) {
            perror("Error writing to file");
            break;
        }
    }

    fclose(file);

    return 0;
}