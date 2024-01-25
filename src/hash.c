#include <stdio.h>
#include <string.h>
#include "../headers/hash.h"

/*
 * @brief               Create hashTable
 * @param ht_size       Max count of item in hash table
 */
hashTable* createHashTable(int ht_size) 
{
    hashTable *table = (hashTable *) malloc(sizeof (hashTable *));
    table->size = ht_size;
    table->count = 0;

    table->items = (ht_item**) calloc (ht_size, sizeof(ht_item));

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
    for (int iter = 0; iter < table->size; iter++)
    {
        ht_item *item = table->items[iter];

        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

/*
 * @breaf               Insert key-value pair in hash table                     
 * @param map           Pointer to hash table              
 * @param key           Key access to value
 * @param value         Value corresponding to the key
 */
int insertValue(hashTable *map, const char *key, const char *value)
{
    ht_item *new_item;
    unsigned long index;

    new_item = createItem(key, value);

    index = hashFunction(key);

    ht_item *curr_item = map->items[index];

    //Checking an existing item
    if (curr_item != NULL) {

        printf ("Insert error: this key is already exist\n");
        return -1;
    }

    map->items[index] = new_item;
    map->count++;

    return 0;
}

char *getValue(hashTable *map, const char *key)
{
    unsigned long index = hashFunction(key);

    
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


