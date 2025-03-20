#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    size_t allocated = 0;
    size_t block_size = 1024 * 1024 * 1024;
    while (1) {
        void *ptr = malloc(block_size);
        if (ptr == NULL) {
            perror("malloc");
            break;
        }
        memset(ptr, 0, block_size);
        allocated += block_size;
        printf("Allocated: %zu MB\n", allocated / (1024 * 1024));
    }
    return 0;
}