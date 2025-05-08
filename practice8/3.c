#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void generate_reverse_sorted(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = size - i;
}

void generate_same_elements(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 42;
}

void generate_sorted(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = i;
}

void generate_random(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % size;
}

bool is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

void test_sort(void (*gen)(int*, int), int size, const char *test_name) {
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    gen(arr, size);
    
    clock_t start = clock();
    qsort(arr, size, sizeof(int), cmp);
    clock_t end = clock();
    
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    bool sorted = is_sorted(arr, size);
    
    printf("%-20s | Time: %-8.5f sec | %s\n", 
           test_name, elapsed, sorted ? "PASS" : "FAIL");
    
    free(arr);
}

int main() {
    const int size = 10000000;
    srand(time(NULL));

    test_sort(generate_reverse_sorted, size, "Reverse sorted");
    test_sort(generate_reverse_sorted, size, "Reverse sorted");
    test_sort(generate_reverse_sorted, size, "Reverse sorted");
    test_sort(generate_same_elements, size, "All equal");
    test_sort(generate_same_elements, size, "All equal");
    test_sort(generate_same_elements, size, "All equal");
    test_sort(generate_sorted, size, "Already sorted");
    test_sort(generate_sorted, size, "Already sorted");
    test_sort(generate_sorted, size, "Already sorted");
    test_sort(generate_random, size, "Random data");
    test_sort(generate_random, size, "Random data");
    test_sort(generate_random, size, "Random data");
    
    return 0;
}