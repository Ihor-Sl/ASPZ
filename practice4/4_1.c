#include <stdio.h>
#include <stdlib.h>

int main() {

    int counter = 1;
    int n = 8;

    void *ptr = NULL;
    while (counter <= 5) {
        if (!ptr)
            ptr = malloc(n);

        for (size_t i = 0; i < n; i++)
        {
            ((int*)ptr)[i] = counter;
        }
        printf("Data: ");
        for (size_t i = 0; i < n; i++)
        {
            printf("%d", ((int*)ptr)[i]);
        }
        printf("\n");

        free(ptr);

        counter++;
    }

    return 0;
}