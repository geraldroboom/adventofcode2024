#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int count_lines(int fp) {
    char ch;
    int nbytes = sizeof(ch);
    int rtn;
    int lines = 0;

    while (1) {
        rtn = read(fp, &ch, nbytes);
        if (rtn < nbytes) break;
        if (ch == '\n') lines++;
        // printf("%i\n", lines);
    }
    lseek(fp, 0, SEEK_SET);
    return lines;
}

int main(int argc, char *argv[]) {
    int fptr;
    int size = 5;
    char number[size];

    if (argc != 2) {
        printf("no path provided\n");
        return 1;
    }

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
    printf("finished...\n");
    return 0;
}
