#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct sbar {
    int data;
};

int main() {
    size_t initial_size = 1000;
    size_t new_size = 500;

    struct sbar *ptr = calloc(initial_size, sizeof(struct sbar));
    if (ptr == NULL) {
        perror("calloc failed");
        return 1;
    }
    printf("Memory allocated for %zu elements\n", initial_size);

    struct sbar *newptr = reallocarray(ptr, new_size, sizeof(struct sbar));
    if (newptr == NULL) {
        perror("reallocarray failed");
        free(ptr);
        return 1;
    }
    printf("Memory reallocated to %zu elements\n", new_size);

    free(newptr);

    return 0;
}