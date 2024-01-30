#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/hash.h"
#include "../headers/linked_list.h"

/*
 * @brief               Create a new node for linked list
 * @return              Pointer to linked list node
 */
linked_list *allocateNode()
{
    linked_list *node = (linked_list *) malloc(sizeof(linked_list *));

    return node;
}

/*
 * @brief               Insert a new item into linked list
 * @param list          Pointer to linked list
 * @param new_item      Item to insert into linked list
 * @return              Pointer to linked list
 */
linked_list *insertLinkedList(linked_list *list, ht_item *new_item)
{
    if (list == NULL) {
        linked_list *head = allocateNode();
        head->item = new_item;
        head->next_node = NULL;

        list = head;

        return list;
    }

    //search tail of linked list
    linked_list *tmp = list;
    while (tmp->next_node != NULL) {
        tmp = tmp->next_node;
    }

    linked_list *node = allocateNode();
    node->next_node = NULL;
    node->item = new_item;

    tmp->next_node = node;

    return list;
}

/*
 * @brief               Remove head item from linked list and return it
 * @param list          Linked list
 * @return              Head item
 */
ht_item *removeHeadLinkedList(linked_list *list)
{
    if (list == NULL) {
        return NULL;
    } else if (!list->next_node) {
        return NULL;
    }

    linked_list *node = list->next_node;
    linked_list *tmp = list;
    
    tmp->next_node = NULL;
    list = node;

    ht_item *item = (ht_item *) malloc(sizeof(ht_item));   
    memcpy(item, tmp->item, sizeof(ht_item));

    freeItem(tmp->item);
    free(tmp);

    return item;
}

/*
 * @brief               Free full linked list
 * @param               Linked list
 */
void freeLinkedList(linked_list *list)
{
    if (!list) {
        return;
    }
    linked_list *tmp = list;
    while (list) {
        tmp = list;
        list = list->next_node;
        freeItem(tmp->item);
        free(tmp);
    }
}