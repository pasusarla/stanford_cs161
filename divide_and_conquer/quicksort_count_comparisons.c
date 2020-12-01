#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG 0
#define size 100000

int array[size];
int partition_strategy = 0;

void swap(int x, int y) {
    int temp;

    temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}

void set_pivot(int start, int end) {
    int el1, el2, el3;

    switch (partition_strategy) {
        case 0:
            break;
        case 1: 
            swap(start, end);
            break;
        case 2:
            el1 = array[start];
            el2 = array[(end - start)/2];
            el3 = array[end];

            if ((el1 <= el2 && el2 <= el3) || (el3 <= el2 && el2 <= el1)) swap(start, (end - start)/2);
            else if ((el1 <= el3 && el3 <= el2) || (el2 <= el3 && el3 <= el1)) swap(start, end);
            else if ((el2 <= el1 && el1 <= el3) || (el3 <= el1 && el1 <= el2)) { /* pivot already at the beginning of the array */ }

            break;
        default:
            break;
    }
}

int partition(int start, int end) {
    int p, i, j;

    p = array[start];
    i = start + 1;
    for (j = start + 1; j <= end; j++) if (array[j] < p) swap(j, i++);
    swap(i - 1, start);

#ifdef DEBUG
#if (DEBUG == 1)
    printf("Pivot element %d moved to position %d\n", p, (i - 1));
    printf("\n");
#endif
#endif

    return (i - 1);
}

int sort_and_count(int start, int end) {
    int pivot_pos;
    unsigned long long n1, n2;

    if (start >= end) return 0;

    set_pivot(start, end);
    pivot_pos = partition(start, end);
    n1 = (pivot_pos - 1 - start) + sort_and_count(start, pivot_pos - 1);
    n2 = (end - pivot_pos - 1) + sort_and_count(pivot_pos + 1, end);

    return n1 + n2;
}

int main(int argc, char **argv) {
    int i, j;
    unsigned long long total;
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *filename;

    if (argc == 2) {
        partition_strategy = atoi(argv[1]);
    }

    if (argc == 3) {
        partition_strategy = atoi(argv[1]);
        filename = (char *)malloc(sizeof(char) * strlen(argv[2]));
        filename = argv[2];
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
#if (DEBUG == 1)
            printf("%s", line);
#endif
#endif
            array[i++] = atoi(line);
        }
        fclose(fp);
#ifdef DEBUG
#if (DEBUG == 1)
        printf("\n");
#endif
#endif
    }

    total = i - 1;
    total += sort_and_count(0, i - 1);
    printf("Total number of comparisons: %Lu\n", total);

#ifdef DEBUG
#if (DEBUG == 0)
    printf("\nAfter the sort\n");
    for (j = 0; j < i; j++) printf("%d \n", array[j]);
    printf("\n");
#endif
#endif

    return 0;
}
