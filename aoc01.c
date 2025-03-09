#include <stdio.h>
#include <unistd.h>

int count_lines(FILE *fp) {
    char ch;
    int lines = 0;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    rewind(fp);

    return lines;
}

int main(int argc, char *argv[]) {
    printf("hello\n");
    FILE *fptr;
    int size = 5;
    char number[size];

    if (argc != 2) {
        printf("no path provided\n");
        return 1;
    }

    fptr = fopen(argv[1], "r");

    if (!fptr) {
        printf("fopen\n");
        return 1;
    }

    int lines = count_lines(fptr);
    int list1[lines], list2[lines];

    for (int i = 0; i < lines; i++) {
        fread(number, sizeof(char), size, fptr);
/*     https://stackoverflow.com/questions/3420629/what-is-the-difference-between-sscanf-or-atoi-to-convert-a-string-to-an-integer */
    }

    fclose(fptr);
    return 0;
}
