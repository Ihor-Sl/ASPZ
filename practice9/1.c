#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":");
        char *uid_str = strtok(NULL, ":");
        int uid = atoi(uid_str);

        if (uid >= 1000 && uid != getuid()) {
            printf("User: %s UID: %d\n", username, uid);
        }
    }

    pclose(fp);
    return 0;
}
