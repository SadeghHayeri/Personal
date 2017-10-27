#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
