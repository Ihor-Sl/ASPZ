#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void recursive_function(int depth) {
    char buffer[10000];
    printf("Recursion depth: %d\n", depth);
    recursive_function(depth + 1);
}

int main() {
    struct rlimit limit;

    getrlimit(RLIMIT_STACK, &limit);
    printf("Stack size limit: %ld bytes\n", limit.rlim_cur);

    recursive_function(1);

    return 0;
}