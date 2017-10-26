#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

void add_node(Node** head, int file_index, int id, char* ip, char* port);
// int delete_node(node* head, char* ip)
Node* get_node(Node* head, int file_index);
int get_nodes_count(Node* head);

int remove_node_with_id(Node** head, int id);

void print_list(Node* head);
#endif
