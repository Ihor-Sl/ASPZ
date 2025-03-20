#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX;

    printf("Attempting to allocate %zu bytes of memory...\n", max_size);

    void *ptr = malloc(max_size);

    if (ptr == NULL) {
        printf("malloc failed: cannot allocate %zu bytes\n", max_size);
    } else {
        printf("malloc succeeded: %zu bytes allocated\n", max_size);
        free(ptr);
    }

    return 0;
}