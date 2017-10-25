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
        return "OK";
    else
        return "ERR";
}

char* request_handler(char* ip, char* req) {
    char** data = split(req, HEADER_SEPERATOR); //TODO: free
    char* command = data[0];

    int is_add_file = (strcmp(command, HEADER_ADD_FILE) == 0);
    if (is_add_file)
        return handle_add_file(ip, data);

    return "BAD COMMMAND";
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
