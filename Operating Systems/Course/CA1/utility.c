#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char** split(char* string, char* delim) {
    int size = strlen(string);
    char** split = (char**)malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        if (i == 0)
            split[i] = strtok(string, delim);
        else
            split[i] = strtok(NULL, delim);
    }

    return split;
}

void print(char* msg) {
    write(0, msg, strlen(msg));
}
