#include <stdio.h>
#include <stdlib.h>

int main() {
    int ret = system("sudo cat /etc/shadow");
    if (ret != 0) {
        fprintf(stderr, "Не вдалося прочитати /etc/shadow. Перевірте права.\n");
    }
    return ret;
}
