#include <stdio.h>
#include <stdlib.h>

int global_var = 42;
static int static_var = 100;

void recursive_function(int depth) {
    int local_array[1000];
    printf("Recursion depth: %d, stack top near %p\n", depth, &local_array);
    
    if (depth < 5) {
        recursive_function(depth + 1);
    }
}

int main() {
    int stack_var;
    int *heap_var1 = (int *)malloc(sizeof(int) * 100);
    int *heap_var2 = (int *)malloc(sizeof(int) * 100);
    char *text_segment = (char *)main;

    printf("Stack top is near: %p\n", &stack_var);
    printf("Heap var 1 (malloc) is near: %p\n", heap_var1);
    printf("Heap var 2 (malloc) is near: %p\n", heap_var2);
    printf("Data segment (global_var) is near: %p\n", &global_var);
    printf("Data segment (static_var) is near: %p\n", &static_var);
    printf("Text segment (main function) is near: %p\n", text_segment);

    recursive_function(1);

    free(heap_var1);
    free(heap_var2);
    return 0;
}
