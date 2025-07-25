#include "utils.h"
#include <unistd.h>


// @param int fp, counts the lines in the file referenced by fp.
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

int remove_element_i(int *list, int index, int len) {
    for( int i = index; i < len-1; i++) {
        list[i] = list[i+1];
    }
    return 0;
}
