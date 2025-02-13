#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ASCII_SIZE 256

typedef struct
{
    int character;
    int frequency;
} CharFreq;

int compare(const void *a, const void *b)
{
    const CharFreq *cf1 = (const CharFreq *)a;
    const CharFreq *cf2 = (const CharFreq *)b;
    return cf2->frequency - cf1->frequency;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int count[ASCII_SIZE] = {0};
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        count[ch]++;
    }
    fclose(file);

    CharFreq freqArray[ASCII_SIZE];
    int size = 0;
    for (int i = 0; i < ASCII_SIZE; i++)
    {
        if (count[i] > 0)
        {
            freqArray[size].character = i;
            freqArray[size].frequency = count[i];
            size++;
        }
    }

    qsort(freqArray, size, sizeof(CharFreq), compare);

    printf("Character | Frequency\n");
    printf("------------------------\n");
    for (int i = 0; i < size; i++)
    {
        if (isprint(freqArray[i].character))
        {
            printf("    '%c'   |    %d\n", freqArray[i].character, freqArray[i].frequency);
        }
    }

    return EXIT_SUCCESS;
}