#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char fullpath[1024];

    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        printf("%s\n", fullpath);

        struct stat info;
        if (stat(fullpath, &info) == 0 && S_ISDIR(info.st_mode)) {
            list_files(fullpath);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
