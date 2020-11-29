#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 100000

int array[size];
int temp[size];

int count_split_inversions(int start, int end) {
    int i, j, k, split_inversion_count;

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

int sort_and_count(int start, int end) {
    int l, r, s;
    if (start >= end) return 0;

    l = sort_and_count(start, (start + end)/2);
    r = sort_and_count((start + end)/2 + 1, end);
    s = count_split_inversions(start, end);

    return l + r + s;
}

int main() {
    int i, total;
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("numbers", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        array[i++] = atoi(line);
    }

    fclose(fp);

    total = sort_and_count(0, i - 1);

    printf("Number of inversions: %d.\n", total);
    return 0;
}
