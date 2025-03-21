#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct sbar {
    int data;
};

int main() {
    size_t initial_size = 1000;
    size_t new_size = 500;

    struct sbar *ptr, *newptr;
    ptr = calloc(1000, sizeof(struct sbar));
    printf("Memory allocated for %zu elements\n", initial_size);

    newptr = realloc(ptr, 500*sizeof(struct sbar));
    printf("Memory reallocated to %zu elements\n", new_size);

    free(newptr);

    return 0;
}