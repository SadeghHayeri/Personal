/*
* Author   : zentut.com
* Purpose  : C Linked List file_index Structure
* Copyright: @ zentut.com
* source   : http://www.zentut.com/c-tutorial/c-linked-list/
*/
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    create a new Node
    initialize the file_index and next field

    return the newly created Node
*/
Node* create(int file_index, Node* next, int contributer_id, char* ip, char* port)
{
    Node* new_Node = (Node*)malloc(sizeof(Node));
    if(new_Node == NULL)
    {
        printf("Error creating a new Node.\n");
        exit(0);
    }
    new_Node->file_index = file_index;
    strcpy(new_Node->ip, ip);
    strcpy(new_Node->port, port);
    new_Node->contributer_id = contributer_id;
    new_Node->next = next;

    return new_Node;
}

/*
    add a new Node at the beginning of the list
*/
Node* prepend(Node* head, int file_index, int contributer_id, char* ip, char* port)
{
    Node* new_Node = create(file_index, head, contributer_id, ip, port);
    head = new_Node;
    return head;
}

/*
    traverse the linked list
*/
void traverse(Node* head,callback f)
{
    Node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}
/*
    remove Node from the front of list
*/
Node* remove_front(Node* head)
{
    if(head == NULL)
        return NULL;
    Node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last Node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}

/*
    remove Node from the back of the list
*/
Node* remove_back(Node* head)
{
    if(head == NULL)
        return NULL;

    Node *cursor = head;
    Node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }

    if(back != NULL)
        back->next = NULL;

    /* if this is the last Node in the list*/
    if(cursor == head)
        head = NULL;

    free(cursor);

    return head;
}

/*
    remove a Node from the list
*/
Node* remove_any(Node* head,Node* nd)
{
    if(nd == NULL)
        return NULL;
    /* if the Node is the first Node */
    if(nd == head)
        return remove_front(head);

    /* if the Node is the last Node */
    if(nd->next == NULL)
        return remove_back(head);

    /* if the Node is in the middle */
    Node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        Node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;

}
/*
    display a Node
*/
void display(Node* n)
{
    if(n != NULL)
        printf("%d:%s ", n->file_index, n->port);
}

/*
    Search for a specific Node with input file_index

    return the first matched Node that stores the input file_index,
    otherwise return NULL
*/
Node* search_by_contributer_id(Node* head, int contributer_id)
{

    Node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->file_index == contributer_id)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

/*
    return the number of elements in the list
*/
int get_nodes_count(Node *head)
{
    Node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}
/*
    sort the linked list using insertion sort
*/
Node* insertion_sort(Node* head)
{
    Node *x, *y, *e;

    x = head;
    head = NULL;

    while(x != NULL)
    {
        e = x;
        x = x->next;
        if (head != NULL)
        {
            if(e->file_index > head->file_index)
            {
                y = head;
                while ((y->next != NULL) && (e->file_index> y->next->file_index))
                {
                    y = y->next;
                }
                e->next = y->next;
                y->next = e;
            }
            else
            {
                e->next = head;
                head = e ;
            }
        }
        else
        {
            e->next = NULL;
            head = e ;
        }
    }
    return head;
}