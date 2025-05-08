#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

#define FILENAME "/tmp/original.txt"
#define COPY_FILENAME "/home/admin/copied.txt"

void create_file_as_user(uid_t user_uid) {
    if (setuid(user_uid) != 0) {
        perror("setuid to user");
        exit(1);
    }

    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("create original file");
        exit(1);
    }

    write(fd, "Hello from user!\n", 17);
    close(fd);
    printf("File created by user: %s\n", FILENAME);
}

void copy_file_as_root(const char* src, const char* dest) {
    if (setresuid(0, 0, -1) != 0) {
        perror("setuid to root");
        exit(1);
    }

    char buf[1024];
    int src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("open source file");
        exit(1);
    }

    int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("open dest file");
        close(src_fd);
        exit(1);
    }

    ssize_t n;
    while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
        write(dest_fd, buf, n);
    }

    close(src_fd);
    close(dest_fd);
    printf("File copied to: %s\n", dest);
}

void try_edit_and_delete_as_user(const char* path, uid_t user_uid) {
    if (setuid(user_uid) != 0) {
        perror("setuid to user for edit");
        exit(1);
    }

    printf("Attempting to edit file as user...\n");
    int fd = open(path, O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("edit file");
    } else {
        write(fd, "Trying to edit\n", 15);
        close(fd);
        printf("Edit successful.\n");
    }

    printf("Attempting to delete file as user...\n");
    if (unlink(path) != 0) {
        perror("delete file");
    } else {
        printf("File deleted.\n");
    }
}

int main() {
    struct passwd* pwd = getpwnam("admin");
    if (!pwd) {
        perror("getpwnam");
        exit(1);
    }

    uid_t user_uid = pwd->pw_uid;

    create_file_as_user(user_uid);

    copy_file_as_root(FILENAME, COPY_FILENAME);

    try_edit_and_delete_as_user(COPY_FILENAME, user_uid);

    return 0;
}
