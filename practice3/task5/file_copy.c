#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <signal.h>
#include <unistd.h>

#define MAX_FILE_SIZE 4

volatile sig_atomic_t file_size_exceeded = 0;

void handle_sigxfsz(int signum) {
    printf("Reached file size limit\n");
    exit(EXIT_FAILURE);
}

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_error("Program need two arguments");
    }

    signal(SIGXFSZ, handle_sigxfsz);

    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    FILE *src = fopen(source_file, "rb");
    if (!src) {
        fprintf(stderr, "Cannot open file %s for reading: %s\n", source_file, strerror(errno));
        exit(EXIT_FAILURE);
    }

    FILE *dst = fopen(destination_file, "wb");
    if (!dst) {
        fclose(src);
        fprintf(stderr, "Cannot open file %s for writing: %s\n", destination_file, strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct rlimit file_size_limit;
    file_size_limit.rlim_cur = MAX_FILE_SIZE;
    file_size_limit.rlim_max = MAX_FILE_SIZE;
    if (setrlimit(RLIMIT_FSIZE, &file_size_limit) == -1) {
        fclose(src);
        fclose(dst);
        print_error("Failed to set file size limit");
    }

    char buffer[1024];
    size_t bytes_read, bytes_written;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, dst);
        if (bytes_written != bytes_read) {
            fclose(src);
            fclose(dst);
            print_error("Failed to write to destination file");
        }
    }

    if (ferror(src)) {
        fclose(src);
        fclose(dst);
        print_error("Error reading source file");
    }

    fclose(src);
    fclose(dst);

    printf("File copied successfully from %s to %s\n", source_file, destination_file);
    return 0;
}