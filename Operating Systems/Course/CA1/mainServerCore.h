#ifndef MAIN_SERVER_CORE
#define MAIN_SERVER_CORE

#include "linkedlist.h"
#include "structs.h"

File* init_files_array();

int _add_contributer(Node** contributers_head, int file_index, char ip[IP_LEN], char* port);

// find file or create new and add a contributer to it
// -1   ERR: file stack is full
// 0    ERR: file_index already exist
// 1    DONE
int add_file_piece(File files[], char file_name[MAX_FILE_NAME], int file_index, char ip[IP_LEN], char* port);

void print_files(File files[]);

void print_file_details(File files[], char file_name[MAX_FILE_NAME]);

#endif
