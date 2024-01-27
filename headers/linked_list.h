#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "hash.h"

typedef struct linked_list_s linked_list;

struct linked_list_s {
    ht_item *item;
    linked_list *next_node;
};

linked_list *allocateNode();                                            // Create a new node for linked list
linked_list *insertNode(linked_list *list, ht_item *new_item);          // Insert a new item to linked list
ht_item *removeHeadLinkedList(linked_list *list);                       // Remove head item from linked list and return it
void freeLinkedList(linked_list *list);                                 // Free linked list
void printLinkedList(linked_list *list);                                // Print all items of linked list

#endif