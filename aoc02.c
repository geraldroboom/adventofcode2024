#include "aoc02.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * @param fd File Descripter of the input file.
 * @param list Pointer to the list of number in the report (line in the file).
 * @return Lenght of the list.
**/
int read_report(int fd, int *len, int *list) {
    char buf;
    char number[2];  // Numbers in the report seem to not exeed two digits.
    int i = 0; /**< Numbers of read digits of current number. */
    *len = 0; /**< Number of numbers read from report */

    while (1) {
        read(fd, &buf, sizeof(char));

        if (buf == 'E') {
            return 0;
        } else if ( buf == '\n' ) {
            sscanf(number, "%d", list+(*len)); 
            number[0] = ' ';
            number[1] = ' ';
            i = 0;
            (*len)++;
            break;
        } else if ( buf == ' ' ) {
            sscanf(number, "%d", list+(*len));
            number[0] = ' ';
            number[1] = ' ';
            i = 0;
            (*len)++;
        } else {
            number[i] = buf;
            i++;
        }
    }
    // for (int k = 0; k< *len; k++) printf("%d ", list[k]);
    // printf("\n");
    return 1;
}

/**
 * @return Returns 1 if the report is save and returns 0 if the report is unsave.
**/
int scan_report(int len, int report[]) {
    int direction_up = 1; // if up == 1, if down == 0
    int diff;

    // set direction
    diff = report[0] - report[1];
    if (diff > 0) direction_up = 0;

    if (abs(diff) < 1 || abs(diff) > 3) return 0;

    for(int i = 1; i<len-1; i++) {
        diff = report[i] - report[i+1];
        if ((diff > 0) == direction_up) return 0;

        if (abs(diff) < 1 || abs(diff) > 3) return 0;
    }
    return 1;
}

int scan_report_dampner(int len, int report[]) {
    int report_cp[len];
    if(scan_report(len, report)) return 1;
    for ( int i = 0; i< len; i++) {
        memcpy(report_cp, report, sizeof(int)*len);
        remove_element_i(report_cp, i, len);
        if(scan_report(len-1, report_cp)) return 1;
    }
    return 0;
    
    // int direction_up = 1; // if up == 1, if down == 0
    // int diff;
    // // int dampner = 1;
    // int report_cp1[len];
    // int report_cp2[len];
    // memcpy(report_cp1, report, sizeof(int));
    // memcpy(report_cp2, report, sizeof(int));
    //
    // // set direction
    // diff = report[0] - report[1];
    // if (diff > 0) direction_up = 0;
    //
    // remove_element_i(report_cp1, 0, len);
    // remove_element_i(report_cp2, 1, len);
    // if(scan_report(len-1, report_cp1) || scan_report(len-1, report_cp2)) return 1;
    // memcpy(report_cp1, report, sizeof(int));
    // memcpy(report_cp2, report, sizeof(int));
    //
    // if (abs(diff) < 1 || abs(diff) > 3) {
    //     remove_element_i(report_cp1, 0, len);
    //     remove_element_i(report_cp2, 1, len);
    //     if(scan_report(len-1, report_cp1) || scan_report(len-1, report_cp2)) return 1;
    //     else return 0;
    // }
    //
    // for(int i = 1; i<len-1; i++) {
    //     diff = report[i] - report[i+1];
    //     if (((diff > 0) == direction_up) || (abs(diff) < 1 || abs(diff) > 3)) {
    //         remove_element_i(report_cp1, i, len);
    //         remove_element_i(report_cp2, i+1, len);
    //         if(scan_report(len-1, report_cp1) || scan_report(len-1, report_cp2)) return 1;
    //         else return 0;
    //     }
    // }
    // return 1;
}

int aoc2(int argc, char *argv[]) {
    int fd;
    int num_save_reports = 0;
    int num_save_reports_dampener = 0;
    int report[16];
    int len_report;

    if (argc != 2) {
        printf("ERROR: no path provided\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (!fd) {
        printf("ERROR: fopen\n");
        return 1;
    }

    while(read_report(fd, &len_report, report)) {
        if(scan_report(len_report, report)) num_save_reports++;  // Part 1
        if(scan_report_dampner(len_report, report)) num_save_reports_dampener++;  // Part 2
    }

    close(fd);

    printf("number of save reports is %d\n", num_save_reports);
    printf("number of save reports with dampener is %d\n", num_save_reports_dampener);
    printf("finished...\n");
    return 0;
}
