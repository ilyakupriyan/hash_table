#ifndef HASH_H
#define HASH_H

#include "linked_list.h"

#define MAX_SIZE_KEY 256
#define MAX_SIZE_MAP 500

typedef struct ht_item ht_item;
typedef struct table hashTable;

//Node of hash map
struct ht_item {
    char *key;
    char *value;
};

//Hash map
struct table {
    linked_list **overflow_buckets;
    int size;
    int count;
};

int         insertValue(hashTable*map, const char *key, const char *value);     //  insert key-value pair in hash table
int         removeValue(hashTable *map, const char *value);                     //  remove value located in hash table
char *      searchValue(hashTable *map, const char *key);                       //  get value located in hash table

hashTable * createHashTable(int size);                                          //  create hash table
void        freeTable(hashTable *map);                                          //  remove hash table
void        freeItem(ht_item *item);                                            //  free item 
void        print_table(hashTable *map);                                        //  show the full hash table

#endif