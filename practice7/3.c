#include <stdio.h>
#include <string.h>

#define LINE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp) {
        perror("fopen failed");
        return 1;
    }

    char line[LINE_LEN];
    while (fgets(line, LINE_LEN, fp)) {
        if (strstr(line, argv[1])) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
