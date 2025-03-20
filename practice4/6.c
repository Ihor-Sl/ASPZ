#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = realloc(NULL, 1024);
    printf("realloc(NULL, 1024) = %p\n", ptr);
    free(ptr);

    ptr = malloc(1024);
    void *new_ptr = realloc(ptr, 0);
    printf("realloc(ptr, 0) = %p\n", new_ptr);
    return 0;
}
