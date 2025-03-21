#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct sbar {
    int data;
};

int main() {

    struct sbar *ptr, *newptr;
    ptr = calloc(1000, sizeof(struct sbar));
    printf("Memory allocated for %zu elements\n", 1000);

    newptr = realloc(ptr, 500*sizeof(struct sbar));
    printf("Memory reallocated to %zu elements\n", 500);

    free(newptr);

    return 0;
}