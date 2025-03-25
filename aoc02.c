#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


/**
 * @param fd File Descripter of the input file.
 * @param list Pointer to the list of number in the report (line in the file).
 * @return Lenght of the list.
**/
int get_next_number(int fd, int *list) {
    char buf;
    char number[2];  // Numbers in the report seem to not exeed two digits.
    int i = 0; /**< Numbers of read digits of current number. */
    int j = 0; /**< Number of numbers read from report */

    while (1) {
        read(fd, &buf, sizeof(char));
        if ( buf == '\n' ) {
            sscanf(&buf, "%d", list+j); 
            i = 0;
            j++;
            break;
        } else if ( buf == ' ' ) {
            // bearbeiten
            i = 0;
            j++;
        } else {
            number[i] = buf;
            i++;
        }
    }
    // sscanf(number, "%d", list1+i);
    return j;
}

int main(int argc, char *argv[]) {
    int fd;

    if (argc != 2) {
        printf("no path provided\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (!fd) {
        printf("fopen\n");
        return 1;
    }


    close(fd);

    printf("finished...");
    return 0;
}
