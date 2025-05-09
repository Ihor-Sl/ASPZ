#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *filename = "/tmp/testfile";

    FILE *f = fopen(filename, "w");
    fprintf(f, "Це створено звичайним користувачем.\n");
    fclose(f);

    printf("Копіюємо файл у /home/admin/testfile_copy як root...\n");
    system("sudo cp /tmp/testfile /home/admin/testfile_copy");

    printf("Намагаємось змінити файл...\n");
    FILE *f2 = fopen("/home/admin/testfile_copy", "a");
    if (f2) {
        fprintf(f2, "Додаємо щось...\n");
        fclose(f2);
        printf("Успішно змінили.\n");
    } else {
        perror("fopen");
    }

    printf("Намагаємось видалити файл...\n");
    int del = system("rm /home/admin/testfile_copy");
    if (del != 0) {
        printf("Не вдалося видалити (ймовірно, немає прав).\n");
    }

    return 0;
}
