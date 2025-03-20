#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = realloc(NULL, 100);
    if (ptr == NULL) {
        perror("realloc with NULL");
    } else {
        printf("realloc with NULL succeeded\n");
    }
    
    void *ptr2 = realloc(ptr, 0);
    if (ptr2 == NULL) {
        printf("realloc with size 0 returned NULL\n");
    }

    free(ptr);
    free(ptr2);

    return 0;
}