#include "aoc03.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int aoc3(int argc, char *argv[]) {
    FILE* fptr;
    char buf;
    int rtn1 = 1;
    int rtn2 = 1;

    if (argc != 2) {
        printf("ERROR: no path provided\n");
        return 1;
    }

    fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
        printf("ERROR: fopen\n");
        return 1;
    }

    int num1, num2, sum = 0;

    do {
        rtn1 = fscanf(fptr, "mul(%d,%d%c", &num1, &num2, &buf); 
        if(rtn1 == EOF) { 
            printf("EOF or ERROR\n");
            break;
        } else if(rtn1 == 3 && buf == ')') {
            if ( ( num1 > 999 || num1 < 0) || ( num2 > 999 || num2 < 0)) printf("EEEEEE");
            sum += num1 * num2;
            printf("%d:: + %d * %d = %d\n", rtn1, num1, num2, sum);
        }
        else rtn2 = fread(&buf, sizeof(char), 1, fptr);

    } while(rtn1 != EOF && rtn2 != 0);

    fclose(fptr);

    printf("sum = %d\n", sum);
    printf("finished...\n");
    return 0;
}
