#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;

    void *ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc failed: cannot allocate %zu bytes\n", (size_t) num);
    } else {
        printf("malloc succeeded: %zu bytes allocated\n", (size_t) num);
        free(ptr);
    }

    return 0;
}