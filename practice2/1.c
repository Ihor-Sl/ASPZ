#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    time_t max;
    if (sizeof(time_t) == 4) {
        max = (time_t) INT_MAX;
    } else if (sizeof(time_t) == 8) {
        max = (time_t) LLONG_MAX;
    }
    printf("Maximum time: %li\n", max);
    printf("ctime max: %s\n", ctime(&max));
    max++;
    printf("ctime max+1: %s\n", ctime(&max));

    return 0;
}