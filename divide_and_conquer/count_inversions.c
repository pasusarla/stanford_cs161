#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#define size 100000

int array[size];
int temp[size];

unsigned long long count_split_inversions(int start, int end) {
    int i, j, k;
    unsigned long long split_inversion_count;

    split_inversion_count = 0;
    for (i = start, j = (start + end)/2 + 1, k = start; i <= (start + end)/2 && j <= end; k++) {
        if (array[i] <= array[j]) temp[k] = array[i++];
        else {
            temp[k] = array[j++];
            split_inversion_count += (start + end)/2 - i + 1;
#ifdef DEBUG
            printf("Start: %d, end: %d\n", start, end);
            printf("i: %d, j: %d, k: %d\n", i, j, k);
            printf("Incrementing split inversion count: %d from the right is less than %d elements from the left.\n", temp[k], (start + end)/2 - i + 1);
            printf("Local inversion count (running): %d\n", split_inversion_count);
#endif
        }
    }

    while (i <= (start + end)/2) temp[k++] = array[i++];
    while (j <= end) temp[k++] = array[j++];

    for (i = start; i <= end; i++) array[i] = temp[i];

    return split_inversion_count;
}

unsigned long long sort_and_count(int start, int end) {
    unsigned long long l, r, s;

    if (start >= end) return 0;

    l = sort_and_count(start, (start + end)/2);
    r = sort_and_count((start + end)/2 + 1, end);
    s = count_split_inversions(start, end);

    return l + r + s;
}

int main(int argc, char **argv) {
    int i;
    unsigned long long total;
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *filename;

    if (argc == 2) {
        filename = (char *)malloc(sizeof(char) * strlen(argv[1]));
        filename = argv[1];
    } else {
        filename = (char *)malloc(sizeof(char) * 8);
        filename = "numbers";
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        array[0] = 1;
        array[1] = 3;
        array[2] = 5;
        array[3] = 2;
        array[4] = 4;
        array[5] = 6;
        i = 6;
    } else {
        i = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
#ifdef DEBUG
            printf("Retrieved line of length %zu:\n", read);
            printf("%s", line);
#endif
            array[i++] = atoi(line);
        }

        fclose(fp);
    }

    total = sort_and_count(0, i - 1);
    printf("Number of inversions: %Lu.\n", total);

    return 0;
}
