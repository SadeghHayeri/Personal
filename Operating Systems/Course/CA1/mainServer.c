#include "structs.h"
#include "utility.h"
#include "network.h"
#include "mainServerCore.h"

#include <unistd.h> // atoi

File* FILES;

char* handle_add_file(int id, char* ip, Split_data data) {
    char* name = data[1];
    char* port = data[3];
    int part_num = atoi(data[2]);

    int status = add_file_piece(FILES, name, part_num, id, ip, port);
    if (status == 0)
        return OK_MESSAGE;
    else
        return ERROR_MESSAGE;
}

char* handle_get_countributers(char* ip, Split_data data) {
    char* name = data[1];

    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        int is_this_file = (strcmp(name, FILES[i].name) == 0);
        if (is_this_file) {

            char* response = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
            memset(response, '\0', MAX_DATA_SIZE);

            Node* contributers_head = FILES[i].contributers_head;

            int nodes_count = get_nodes_count(contributers_head);
            char nodes_count_string[MAX_DATA_SIZE];
            num_to_string(nodes_count, nodes_count_string);

            strcat(response, nodes_count_string);

            Node* curr_contributers = contributers_head;
            for (size_t i = 0; i < nodes_count; i++) {
                strcat(response, HEADER_SEPARATOR);

                int file_index = curr_contributers->file_index;
                char file_index_string[MAX_DATA_SIZE];
                num_to_string(file_index, file_index_string);

                char* ip = curr_contributers->ip;
                char* port = curr_contributers->port;

                strcat(response, file_index_string);
                strcat(response, HEADER_SUB_SEPARATOR);
                strcat(response, ip);
                strcat(response, HEADER_SUB_SEPARATOR);
                strcat(response, port);

                curr_contributers = curr_contributers->next;
            }

            return response;
        }
    }
    return NOT_FOUND;
}

char* request_handler(int id, char* ip, char* req) {
    Split_data data;
    split(req, data, HEADER_SEPARATOR);
    char* command = data[0];

    int is_add_file = (strcmp(command, HEADER_ADD_FILE) == 0);
    if (is_add_file)
        return handle_add_file(id, ip, data);

    int is_get_countributers = (strcmp(command, HEADER_GET_COUNTRIBUTERS) == 0);
    if (is_get_countributers)
        return handle_get_countributers(ip, data);

    return BAD_COMMAND;
}

void disconnect_handler(int id) {
    int result = remove_file_piece(FILES, id);
    if(result == 0) {
        printf("File Removed: %d\n", id);
    }
}

// void disconnect

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: ./mainServer port\n");
        exit(1);
    }
    char* listener_port = argv[1];

    FILES = init_files_array();

    int listener = create_listener_fd(listener_port);
    listen_to_clients(listener, listener_port, request_handler, disconnect_handler);
    
    return 0;
}
