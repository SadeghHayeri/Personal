#ifndef _MYLOGGER_H_
#define _MYLOGGER_H_

#include <stdio.h>
#include "structs.h"

#define logger(format, ...) \
    do { \
        char str[MAX_LOG_SIZE];\
        sprintf(str, format, ##__VA_ARGS__);\
        write(STDOUT, "> ", 3);\
        write(STDOUT, str, strlen(str));\
        write(STDOUT, "\n", 2);\
    } while(0)

#define error(format, ...) \
    do { \
        char str[MAX_LOG_SIZE];\
        sprintf(str, format, ##__VA_ARGS__);\
        write(STDERR, "Err: ", 6);\
        write(STDERR, str, strlen(str));\
        write(STDERR, "\n", 2);\
    } while(0)

#endif