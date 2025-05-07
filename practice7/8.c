#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer[10];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("Delete %s? (y/n): ", entry->d_name);
            fgets(answer, sizeof(answer), stdin);
            if (answer[0] == 'y' || answer[0] == 'Y') {
                remove(entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
