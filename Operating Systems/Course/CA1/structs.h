#ifndef STRUCTS_H
#define STRUCTS_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define MAX_FILE_NAME 50
#define MAX_FILE_HANDLER 10
#define NOTSET "NOT_SET"
#define NOT_FOUND "NOT_FOUND"
#define OK_MESSAGE "OK"
#define ERROR_MESSAGE "ERR"
#define BAD_COMMAND "BAD_COMMAND"
#define IP_LEN 22   // worst case: ::ffff:255.255.255.255
#define PORT_LEN 15   // worst case: 60000
#define MAX_RANDOM_PORT 60000
#define RANDOM_PORT_OFFSET 1000

#define MAX_DATA_SIZE 700
#define CHUNK_SIZE 500

#define HEADER_ADD_FILE "ADD_FILE"
#define HEADER_GET_CHUNK_COUNT "GET_CHUNK_COUNT"
#define HEADER_GET_CHUNK "GET_CHUNK"
#define HEADER_GET_COUNTRIBUTERS "GET_COUNTRIBUTERS"
#define DATA_MARKER "DATA"
#define HEADER_SEPERATOR "<*>"
#define HEADER_SUB_SEPERATOR "<|>"


#define BACKLOG 10     // how many pending connections queue will hold

typedef struct Node {
	int contributer_id;
    int file_index;
    char ip[IP_LEN];
    char port[PORT_LEN];

    struct Node *next;
} Node;

typedef struct file {
    char name[MAX_FILE_NAME];
    Node* contributers_head;
} File;

#endif
