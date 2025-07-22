#include "aoc01.h"
#include "aoc02.h"
#include <stdio.h>

#define TASK 1

int task;
char *argv_new[8];

int main(int argc, char *argv[]) {

    if (argc == 2) {
        task = TASK;
        argv_new[0] = argv[0];
        argv_new[1] = argv[1];
    }
    else if (argc == 3) {
        sscanf(argv[1], "%d", &task);
        argv_new[0] = argv[0];
        argv_new[1] = argv[2];
    }
    else {
        printf("args incorrect!");
        return 1;
    }

    printf("Running task %d with input file %s.\n", task, argv_new[1]);

    switch (task) {
        case 1:
            aoc1(2, argv_new);
        case 2:
            aoc2(2, argv_new);
    
    }
    return 0;
}
