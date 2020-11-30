#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 10000

int array[size];

int partition_m3(int start, int end) {
    int p, i, j, temp;
    int el1, el2, el3;

    el1 = array[start];
    el2 = array[(end - start)/2];
    el3 = array[end];

    if ((el1 <= el2 && el2 <= el3) || (el3 <= el2 && el2 <= el1)) {
        temp = array[start];
        array[start] = array[(end - start)/2];
        array[(end - start)/2] = temp;
    } else if ((el1 <= el3 && el3 <= el2) || (el2 <= el3 && el3 <= el1)) {
        temp = array[start];
        array[start] = array[end];
        array[end] = temp;
    } else if ((el2 <= el1 && el1 <= el3) || (el3 <= el1 && el1 <= el2)) {
        // pivot already at the beginning of the array
    }

    p = array[start];
    i = start + 1;
    for (j = start + 1; j <= end; j++) {
        if (array[j] < p) {
            // swap
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
        }
    }
    // swap array[l] and array[i - 1]
    temp = array[i - 1];
    array[i - 1] = array[start];
    array[start] = temp;

#ifdef DEBUG
    printf("Pivot element %d moved to position %d\n", p, (i - 1));
    printf("\n");
#endif
    return (i - 1);
}

int partition_last(int start, int end) {
    int p, i, j, temp;

    temp = array[start];
    array[start] = array[end];
    array[end] = temp;

    p = array[start];
    i = start + 1;
    for (j = start + 1; j <= end; j++) {
        if (array[j] < p) {
            // swap
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
        }
    }
    // swap array[l] and array[i - 1]
    temp = array[i - 1];
    array[i - 1] = array[start];
    array[start] = temp;

#ifdef DEBUG
    printf("Pivot element %d moved to position %d\n", p, (i - 1));
    printf("\n");
#endif
    return (i - 1);
}

int partition_first(int start, int end) {
    int p, i, j, temp;

    p = array[start];
    i = start + 1;
    for (j = start + 1; j <= end; j++) {
        if (array[j] < p) {
            // swap
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
        }
    }
    // swap array[l] and array[i - 1]
    temp = array[i - 1];
    array[i - 1] = array[start];
    array[start] = temp;

#ifdef DEBUG
    printf("Pivot element %d moved to position %d\n", p, (i - 1));
#endif
    return (i - 1);
}

int sort_and_count(int start, int end) {
    int pivot_pos, n1, n2;

    if (start >= end) return 0;

    pivot_pos = partition_last(start, end);
    n1 = (pivot_pos - 1 - start) + sort_and_count(start, pivot_pos - 1);
    n2 = (end - pivot_pos - 1) + sort_and_count(pivot_pos + 1, end);

    return n1 + n2;
}

int main() {
    int i, j, total;
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("numbers", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        array[i++] = atoi(line);
    }
    fclose(fp);
    printf("\n");

    total = i - 1;
    total += sort_and_count(0, i - 1);
    printf("Total number of comparisons: %d\n", total);

    printf("\nAfter the sort\n");
    for (j = 0; j < i; j++) printf("%d \n", array[j]);
    printf("\n");
    return 0;
}
