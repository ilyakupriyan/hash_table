#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"

/*
 * @brief               Create an array of linked lists for handling collisions
 * @param table         Hash table
 * @return              Pointer to array of linked lists
 */
linked_list **createBuckets(hashTable *table) 
{
    linked_list **buckets = (linked_list **) calloc(table->size, sizeof(linked_list *));

    for (int iter = 0; iter < table->size; iter++) {
        buckets[iter] = NULL;
    }

    return buckets;
}

/*
 * @brief               Free overflow buckets
 * @param table         Hash table
 */
void freeBuckets(hashTable *table)
{
    linked_list **buckets = table->overflow_buckets;
    
    for (int iter = 0; iter < table->size; iter++) {
        freeLinkedList(buckets[iter]);
    }

    free(buckets);
}

/*
 * @brief               Create hashTable
 * @param ht_size       Max count of item in hash table
 */
hashTable* createHashTable(int ht_size) 
{
    hashTable *table = (hashTable *) malloc(sizeof (hashTable *));
    table->size = ht_size;
    table->count = 0;

    table->overflow_buckets = createBuckets(table);

    return table;
}

/*
 * @brief               Create item of hash table
 * @param key           Key access to value
 * @param value         Value corresponding to the key
 */
ht_item *createItem(char *key, char *value)
{
    ht_item *item = (ht_item *) malloc(sizeof(ht_item *));

    item->key = (char *) malloc(strlen(key) + 1);
    item->value = (char *) malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

/*
 * @brief               Free memory after item in heap
 * @param item              
 */
void freeItem(ht_item *item)
{
    free(item->key);
    free(item->value);

    free(item);
}

/*
 * @brief               Free memory after table in heap
 * @param table         Pointer to hash table
 */
void freeTable(hashTable *table)
{
    freeBuckets(table);
    free(table);
}

/*
 * @brief               Print all items of hash table
 * @param table         Hash table
 */
void print_table(hashTable *table)
{
    puts("\nHash Table");
    puts("------------------");
    for (int iter = 0; iter < table->size; iter++) {
        linked_list *head = table->overflow_buckets[iter];
        
        while (head != NULL) {
            printf ("Index: %d, Key: %s, Value: %s\n", iter, head->item->key, head->item->value);
        }
    }
    puts("------------------");
}

/*
 * @brief               Handle collision at the moment of inserting
 * @param 
 */
void handleCollision(hashTable* table, unsigned long index, ht_item* item)
{
    linked_list *head = table->overflow_buckets[index];

    if (head == NULL) {
        head = allocateNode();
        head->item = item;
    }
    else {
        printf("Insert warning: this key is already exist\n");

        insertLinkedList(table->overflow_buckets[index], item);
    }
}

/*
 * @breaf               Insert key-value pair in hash table                     
 * @param map           Pointer to hash table              
 * @param key           Key access to value
 * @param value         Value corresponding to the key
 */
int insertValue(hashTable *table, const char *key, const char *value)
{
    ht_item *new_item;
    unsigned long index;

    new_item = createItem(key, value);
    index = hashFunction(key);

    handleCollision(table, index, new_item);
    
    return 0;
}

/*
 * @breaf               Search value in hash table via key
 * @param table           Pointer to hash table
 * @param key           Key access to search value
 */
char *searchValue(hashTable *table, const char *key)
{
    unsigned long index = hashFunction(key);
    linked_list *head = table->overflow_buckets[index];

    while (head != NULL) {
        ht_item *item = head->item;

        if (strcmp(item->key, key) != 0) {
            return item->value;
        }

        head = head->next_node;
    }

    return NULL;
}

/*
 * @breaf               Translate key to hash value
 * @param key           Key for translate to the hash value
 */
unsigned long hashFunction (char* key)
{
    unsigned long index = 0;
    __uint8_t iter;

    for (iter = 0; key[iter] != '\0' && iter < MAX_SIZE_KEY; iter++) {
        index += key[iter];
    }

    index += iter;

    return index % MAX_SIZE_MAP;
}
