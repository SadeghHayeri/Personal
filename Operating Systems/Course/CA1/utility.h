#ifndef UTILITY_H
#define UTILITY_H

#include "structs.h"

void split(char* str, char sp[MAX_DATA_SIZE][MAX_DATA_SIZE], char* delim);
void print(char* msg);
int num_len(int number);
long get_file_size(int file_fd);
void reverse_string(char s[]);
void num_to_string(int n, char s[]);
void process(int x, int all);

#endif
