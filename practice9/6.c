#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void check_dir(const char *path) {
    printf("\n--- Каталог %s ---\n", path);

    printf("Можна читати: %s\n", access(path, R_OK) == 0 ? "так" : "ні");
    printf("Можна писати: %s\n", access(path, W_OK) == 0 ? "так" : "ні");
    printf("Можна виконати: %s\n", access(path, X_OK) == 0 ? "так" : "ні");

    printf("\n--- Вміст каталогу %s ---\n", path);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s", path);
    system(cmd);
}

int main() {
    check_dir(getenv("HOME"));
    check_dir("/usr/bin");
    check_dir("/etc");

    return 0;
}
