#include "mainServerCore.h"
#include "logger.h"
#include "linkedlist.h"
#include "structs.h"

#include <unistd.h>

File* init_files_array() {
    File* files = (File*)malloc(MAX_FILE_HANDLER * sizeof(File));
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        memset(files[i].name, '\0', MAX_FILE_NAME);
        strcpy(files[i].name, NOTSET);
    }
    return files;
}

int _add_contributer(Node** contributers_head, int file_index, int id, char ip[IP_LEN], char* port) {
    *contributers_head = prepend(*contributers_head, file_index, id, ip, port);
    *contributers_head = insertion_sort(*contributers_head);

    return 0; //TODO: handle exist!
}

// find file or create new and add a contributer to it
// 2   ERR: file stack is full
// 1    ERR: file_index already exist
// 0    DONE
int add_file_piece(File files[], char file_name[MAX_FILE_NAME], int file_index, int id, char ip[IP_LEN], char* port) {

    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {

        // if file exist -> add
        int is_this_file = (strcmp(files[i].name, file_name) == 0);
        if(is_this_file)
            return _add_contributer(&files[i].contributers_head, file_index, id, ip, port);

        // if not -> create & add
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block) {
            memset(files[i].name, '\0', MAX_FILE_NAME);
            strcpy(files[i].name, file_name);
            return _add_contributer(&files[i].contributers_head, file_index, id, ip, port);
        }

    }

    return -1;
}

int remove_file_piece(File files[], int id) {
    for (int i = 0; i < MAX_FILE_HANDLER; ++i) {
        Node* target_node = search_by_contributer_id(files[i].contributers_head, id);
        if(target_node != NULL) {
            files[i].contributers_head = remove_any(files[i].contributers_head, target_node);
            return 0;
        }
    }
    return 1;
}

void print_files(File files[]) {
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block)
            break;

        logger("%lu %s\n", i+1, files[i].name);
    }
}

void print_file_details(File files[], char file_name[MAX_FILE_NAME]) {
    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {

        // if file exist -> show
        int is_this_file = (strcmp(files[i].name, file_name) == 0);
        if(is_this_file) {
            logger("%s:\n", file_name);

            Node* curr_contributer = files[i].contributers_head;
            while (curr_contributer != NULL) {
                logger("(%d) %s:%s\n", curr_contributer->file_index, curr_contributer->ip, curr_contributer->port);
                curr_contributer = curr_contributer->next;
            }

            return;
        }

        // if not -> error
        int is_empty_block = (strcmp(files[i].name, NOTSET) == 0);
        if(is_empty_block) {
            error("Not Found!");
            return;
        }

    }
}
