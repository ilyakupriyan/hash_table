#include <stdio.h>
#include "../headers/hash.h"

int test_table();

int main(void) 
{

    return 0;
}


/*
 * @breaf           Test create and free hash table
 */
int test_table()
{
    hashTable *map = createHashTable(500);
    if (map == NULL)
        return -1;
    
    freeTable(map);

    if (map != NULL)
        return -1;
    
    return 0;
}