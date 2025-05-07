#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[256];

    fp = popen("who | more", "r");

    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}
