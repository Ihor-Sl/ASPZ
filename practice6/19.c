#include <stdio.h>
#include <string.h>

static void* uar(void) {
    char name[32];

    memset(name, 0, 32);
    strncpy(name, "Welcome to Linux Sys Soft", 26);

    return name;
}

int main() {

    char* str = (char*) uar();
    printf("res: %s\n", str);

    return 0;
}