#include "structs.h"
#include "utility.h"
#include "network.h"
#include "mainServerCore.h"

#include <unistd.h> // atoi

File* FILES;

char* handle_add_file(char* ip, char** data) {
    char* name = data[1];
    char* port = data[3];
    int part_num = atoi(data[2]);

    int status = add_file_piece(FILES, name, part_num, ip, port);
    if (status == 1)
        return OK_MESSAGE;
    else
        return ERROR_MESSAGE;
}

char* handle_get_countributers(char* ip, char** data) {
    char* name = data[1];

    for (size_t i = 0; i < MAX_FILE_HANDLER; i++) {
        int is_this_file = (strcmp(name, FILES[i].name) == 0);
        if (is_this_file) {

            char* response = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
            memset(response, '\0', MAX_DATA_SIZE);
            char* end_char = response;

            Node* contributers_head = FILES[i].contributers_head;

            int nodes_count = get_nodes_count(contributers_head);
            sprintf(end_char, "%d", nodes_count);
            end_char += num_len(nodes_count);

            Node* curr_contributers = contributers_head;
            for (size_t i = 0; i < nodes_count; i++) {
                strcpy(end_char, HEADER_SEPERATOR);
                end_char += strlen(HEADER_SEPERATOR);

                int file_index = curr_contributers->file_index;
                char* ip = curr_contributers->ip;
                char* port = curr_contributers->port;

                sprintf(end_char, "%d", file_index);
                end_char += num_len(file_index);

                strcpy(end_char, HEADER_SUB_SEPERATOR);
                end_char += strlen(HEADER_SUB_SEPERATOR);

                strcpy(end_char, ip);
                end_char += strlen(ip);

                strcpy(end_char, HEADER_SUB_SEPERATOR);
                end_char += strlen(HEADER_SUB_SEPERATOR);

                strcpy(end_char, port);
                end_char += strlen(port);
            }

            return response;
        }
    }
    return NOT_FOUND;
}

char* request_handler(char* ip, char* req) {


    printf("------1\n");
    char** data = split(req, HEADER_SEPERATOR); //TODO: free

    for (int i = 0; i < strlen(data[0]); ++i)
    {
        printf("%d -> %c\n", data[0][i], data[0][i]);
    }

    printf("------2\n");

    for (int i = 0; i < strlen(data[1]); ++i)
    {
        printf("%d -> %c\n", data[1][i], data[1][i]);
    }

     printf("------3\n");

    char* command = data[0];

    int is_add_file = (strcmp(command, HEADER_ADD_FILE) == 0);
    if (is_add_file)
        return handle_add_file(ip, data);

    int is_get_countributers = (strcmp(command, HEADER_GET_COUNTRIBUTERS) == 0);
    if (is_get_countributers)
        return handle_get_countributers(ip, data);

    return BAD_COMMAND;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: ./mainServer port\n");
        exit(1);
    }
    char* listener_port = argv[1];

    FILES = init_files_array();

    int listener = create_listener_fd(listener_port);
    listen_to_clients(listener, listener_port, request_handler);

    return 0;
}
