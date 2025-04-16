#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

int is_user_in_group(const char *target_group) {
    int ngroups = getgroups(0, NULL);
    gid_t *groups = malloc(ngroups * sizeof(gid_t));
    if (!groups) {
        perror("malloc");
        return 0;
    }

    if (getgroups(ngroups, groups) == -1) {
        perror("getgroups");
        free(groups);
        return 0;
    }

    for (int i = 0; i < ngroups; ++i) {
        struct group *gr = getgrgid(groups[i]);
        if (gr && strcmp(gr->gr_name, target_group) == 0) {
            free(groups);
            return 1;
        }
    }

    free(groups);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <target_user> <target_group>\n", argv[0]);
        return 1;
    }

    const char *target_user = argv[1];
    const char *target_group = argv[2];

    int *ptr = malloc(100 * sizeof(int));
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    ptr[0] = 11;

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (!pw) {
        perror("getpwuid");
        free(ptr);
        return 1;
    }

    printf("Running as user: %s (UID: %d)\n", pw->pw_name, uid);

    if (strcmp(pw->pw_name, target_user) == 0 || is_user_in_group(target_group)) {
        printf("Memory NOT freed for user %s or group %s\n", target_user, target_group);
    } else {
        free(ptr);
        printf("Memory freed (user/group do not match)\n");
    }

    return 0;
}
