#include "aoc01.h"
#include "utils.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int comp(const void *p1, const void *p2) {
    if (*(int*)p1 > *(int*)p2) return 1;
    else return -1;
}


int aoc1(int argc, char *argv[]) {
    int fptr;
    int size = 5;
    char number[size];

    if (argc != 2) {
        printf("no path provided\n");
        return 1;
    }

    printf("Running task %d with input file %s.\n", 1, argv[1]);
    fptr = open(argv[1], O_RDONLY);

    if (!fptr) {
        printf("fopen\n");
        return 1;
    }

    int lines = count_lines(fptr);
    printf("number of lines: %i\n", lines);
    int list1[lines], list2[lines];

    for (int i = 0; i < lines; i++) {
        read(fptr, number, sizeof(char)*size);
        sscanf(number, "%d", list1+i);
        lseek(fptr, 3, SEEK_CUR);
        read(fptr, number, sizeof(char)*size);
        sscanf(number, "%d", list2+i);
        lseek(fptr, 1, SEEK_CUR);
    }

    close(fptr);

    // PART 1

    qsort(list1, lines, sizeof(int), comp);
    qsort(list2, lines, sizeof(int), comp);

    int sumdiff = 0, diff = 0;

    for (int i = 0; i < lines; i++) {
        diff = list1[i] - list2[i];
        if (diff < 0) diff *= -1;
        sumdiff += diff;
    }

    printf("solution 1: %d\n", sumdiff);

    // PART 2
    
    int simi_score = 0;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {
            if (list1[i] == list2[j]) {
                simi_score += list1[i];
            }
        }
    }
    printf("solution 2: %d\n", simi_score);

    printf("finished...\n");
    return 0;
}
