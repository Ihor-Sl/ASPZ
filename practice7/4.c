#include <stdio.h>

#define LINES_PER_PAGE 20
#define LINE_LEN 1024

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            perror("fopen failed");
            continue;
        }

        char line[LINE_LEN];
        int line_count = 0;

        while (fgets(line, LINE_LEN, fp)) {
            printf("%s", line);
            if (++line_count == LINES_PER_PAGE) {
                printf("--More--");
                getchar();
                line_count = 0;
            }
        }

        fclose(fp);
    }

    return 0;
}
