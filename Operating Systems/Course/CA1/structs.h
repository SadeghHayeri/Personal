#ifndef STRUCTS_H
#define STRUCTS_H

// I/O file descriptors
#define STDIN 0
#define STDOUT 1
#define STDERR 2

// MainServer file handler
#define MAX_FILE_NAME 50
#define MAX_FILE_HANDLER 10

// Address info
#define IP_LEN 22   // worst case: ::ffff:255.255.255.255
#define PORT_LEN 15   // worst case: 60000
#define MAX_RANDOM_PORT 60000
#define RANDOM_PORT_OFFSET 1000

// Configs
#define MAX_DATA_SIZE 700
#define CHUNK_SIZE 500
#define BACKLOG 10     // how many pending connections queue will hold


/////////////////////// API ////////////////////////
// Separators
#define HEADER_SEPERATOR "<*>"
#define HEADER_SUB_SEPERATOR "<|>"

// Client Requests
#define HEADER_GET_CHUNK_COUNT "GET_CHUNK_COUNT"
#define HEADER_GET_CHUNK "GET_CHUNK"
#define HEADER_GET_COUNTRIBUTERS "GET_COUNTRIBUTERS"

// Server Requests
#define HEADER_ADD_FILE "ADD_FILE"

// Server Responses
#define DATA_MARKER "DATA"

// MainServer Responses
#define OK_MESSAGE "OK"
#define ERROR_MESSAGE "ERR"
#define BAD_COMMAND "BAD_COMMAND"
#define NOTSET "NOT_SET"
#define NOT_FOUND "NOT_FOUND"
////////////////////////////////////////////////////

typedef struct Node {
	int contributer_id;
    int file_index;
    char ip[IP_LEN];
    char port[PORT_LEN];

    struct Node *next;
} Node;

typedef struct File {
    char name[MAX_FILE_NAME];
    Node* contributers_head;
} File;

#endif
