#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char *dirs[1024];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode) &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            dirs[count++] = strdup(entry->d_name);
        }
    }

    qsort(dirs, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        puts(dirs[i]);
        free(dirs[i]);
    }

    closedir(dir);
    return 0;
}
