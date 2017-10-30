#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include <math.h>

#include "structs.h"

void split(char* str, char sp[MAX_DATA_SIZE][MAX_DATA_SIZE], char* delim) {
    memset(sp, 0, MAX_DATA_SIZE * MAX_DATA_SIZE);
    int i = 0;
    char* start = str;
    char* end = strstr(start, delim);


    while(end != NULL) {
        memcpy(sp[i], start, end - start);

        start = end+strlen(delim);

        end = strstr(start, delim);
        i++;
    }
    memcpy(sp[i], start, (str + strlen(str)) - start);
}

void print(char* msg) {
    write(0, msg, strlen(msg));
}

int num_len(int number) {
    return floor(log10(abs(number))) + 1;
}

long get_file_size(int file_fd) {
    struct stat buf;
    fstat(file_fd, &buf);
    return buf.st_size;
}

// https://en.wikibooks.org/wiki/C_Programming/stdlib.h/itoa
void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void num_to_string(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void process(int x, int all) {
    int p = ((float)x / all) * PROCESS_SIZE;

    write(STDOUT, "\r", 2);
    for (int i = 0; i < PROCESS_SIZE; ++i)
        write(STDOUT, " ", 1);
    write(STDOUT, "\r[", 2);
    for (int i = 0; i < PROCESS_SIZE; ++i) {
        if(i <= p+1)
            write(STDOUT, "=", 1);
        else
            write(STDOUT, "-", 1);
    }
    write(STDOUT, "]", 1);
}
