#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define MAX_NUM_49 7
#define MAX_NUM_36 6

void handle_sigxcpu(int sig) {
    printf("CPU limit usage reached\n");
    exit(EXIT_FAILURE);
}

void generate_numbers(int *arr, int size, int max_value) {
    for (int i = 0; i < size; i++) {
        int num;
        int unique;
        do {
            unique = 1;
            num = rand() % max_value + 1;
            for (int j = 0; j < i; j++) {
                if (arr[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        arr[i] = num;
    }
}

int main() {
    signal(SIGXCPU, handle_sigxcpu);

    srand(time(NULL));

    int numbers_49[MAX_NUM_49];
    int numbers_36[MAX_NUM_36];

    generate_numbers(numbers_49, MAX_NUM_49, 49);
    
    generate_numbers(numbers_36, MAX_NUM_36, 36);


    printf("Numbers to 49: ");
    for (int i = 0; i < MAX_NUM_49; i++) {
        printf("%d ", numbers_49[i]);
    }
    printf("\n");

    printf("Numbers to 36: ");
    for (int i = 0; i < MAX_NUM_36; i++) {
        printf("%d ", numbers_36[i]);
    }
    printf("\n");

    return 0;
}
