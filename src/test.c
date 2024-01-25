#include <stdio.h>
#include <string.h>
#include "../headers/hash.h"

int test_table();
int test_insert();

int main(void) 
{
    int test_create, test_insert_search;

    test_create = test_table();
    if (test_create == -1) {
        printf ("Error create: hash table was not create or freed\n");
        return -1;
    }

    test_insert_search = test_insert();
    if (test_insert_search == -1) {
        printf("Error insert: value was not inserted to hash table\n");
        return -1;
    }

    return 0;
}


/*
 * @breaf           Test create and free hash table
 */
int test_table()
{
    hashTable *map = createHashTable(MAX_SIZE_MAP);
    if (map == NULL)
        return -1;
    
    freeTable(map);

    if (map != NULL)
        return -1;
    
    return 0;
}

/*
 * @breif           Test insert function to hash table
 */
int test_insert()
{
    hashTable *map = createHashTable(200);
    const char *key = "Willie";
    const char *value = "Street legacy";

    insertValue(map, key, value);

    char *check_value = searchValue(map, key);
    if (strcmp(check_value, value) == 0) {
        freeTable(map);
        return -1;
    }

    return 0;
}