#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
    void *ptr = malloc(1024);
    if (!ptr) return 1;

    void *new_ptr = realloc(ptr, (size_t) LLONG_MAX);
    if (!new_ptr) {
        printf("Memory reallocation failed\n");
    } else {
        ptr = new_ptr;
    }

    free(ptr);

    return 0;
}
