#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer[10];

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".out")) {
            printf("Allow read permission for others on %s? (y/n): ", entry->d_name);
            fgets(answer, sizeof(answer), stdin);
            if (answer[0] == 'y' || answer[0] == 'Y') {
                chmod(entry->d_name, S_IRUSR | S_IWUSR | S_IXUSR |
                                      S_IRGRP | S_IXGRP |
                                      S_IROTH | S_IXOTH);
            }
        }
    }

    closedir(dir);
    return 0;
}
