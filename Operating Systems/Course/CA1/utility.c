#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <math.h>

#include "structs.h"

char** split(char* string, char* delim) {
    int size = strlen(string);

    char* string_tmp = (char*)malloc(size * sizeof(char));
    memcpy(string_tmp, string, size);

    char** split = (char**)malloc(MAX_SPLIT_BOX * sizeof(char*));

    for (int i = 0; i < size; i++) {
        if (i == 0)
            split[i] = strtok(string_tmp, delim);
        else
            split[i] = strtok(NULL, delim);
    }

    free(string_tmp);
    return split;
}

void print(char* msg) {
    write(0, msg, strlen(msg));
}

int num_len(int number) {
    return floor(log10(abs(number))) + 1;
}
