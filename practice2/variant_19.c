#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void check_elf_dependencies(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "readelf -d %s", filename);
    system(command);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }

    check_elf_dependencies(argv[1]);
    return 0;
}