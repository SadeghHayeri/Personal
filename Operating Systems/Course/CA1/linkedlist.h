#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

typedef struct Node {
	int contributer_id;
    int file_index;
    char ip[IP_LEN];
    char port[PORT_LEN];

    struct Node *next;
} Node;
 
typedef void (*callback)(Node* file_index);

Node* create(int file_index, Node* next, int contributer_id, char* ip, char* port);
Node* prepend(Node* head, int file_index, int contributer_id, char* ip, char* port);
void traverse(Node* head, callback f);
Node* remove_front(Node* head);
Node* remove_back(Node* head);
Node* remove_any(Node* head, Node* nd);
void display(Node* n);
Node* search_by_contributer_id(Node* head, int contributer_id);
void dispose(Node *head);
int count(Node *head);
Node* insertion_sort(Node* head);
Node* reverse(Node* head);

#endif
