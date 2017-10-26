#include "mainServerCore.h"

#include "linkedlist.h"
#include "structs.h"

File* init_files_array() {
    File* files = (File*)malloc(MAX_FILE_HANDLER * sizeof(File));
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        memset(files[i].name, '\0', MAX_FILE_NAME);
        strcpy(files[i].name, NOTSET);
    }
    return files;
}

int _add_contributer(Node** contributers_head, int file_index, char ip[IP_LEN], char* port) {

    int file_index_not_exist = (get_node(*contributers_head, file_index) == NULL);
    if(file_index_not_exist) {

        add_node(contributers_head, file_index, ip, port);
        return 1;

    } else {
        return 0;
    }

}

// find file or create new and add a contributer to it
// -1   ERR: file stack is full
// 0    ERR: file_index already exist
// 1    DONE
int add_file_piece(File files[], char file_name[MAX_FILE_NAME], int file_index, char ip[IP_LEN], char* port) {

    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {

        // if file exist -> add
        int is_this_file = (strcmp(files[i].name, file_name) == 0);
        if(is_this_file)
            return _add_contributer(&files[i].contributers_head, file_index, ip, port);

        // if not -> create & add
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block) {
            memset(files[i].name, '\0', MAX_FILE_NAME);
            strcpy(files[i].name, file_name);
            return _add_contributer(&files[i].contributers_head, file_index, ip, port);
        }

    }

    return -1;
}

void print_files(File files[]) {
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block)
            break;

        printf("%lu %s\n", i+1, files[i].name);
    }
}

void print_file_details(File files[], char file_name[MAX_FILE_NAME]) {
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {

        // if file exist -> show
        int is_this_file = (strcmp(files[i].name, file_name) == 0);
        if(is_this_file) {
            printf("%s:\n", file_name);

            Node* curr_contributer = files[i].contributers_head;
            while (curr_contributer != NULL) {
                printf("(%d) %s:%s\n", curr_contributer->file_index, curr_contributer->ip, curr_contributer->port);
                curr_contributer = curr_contributer->next;
            }

            return;
        }

        // if not -> error
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block) {
            printf("Not Found!");
            return;
        }

    }
}
