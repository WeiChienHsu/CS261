/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Wei-Chien Hsu
 * Date: 7/31/2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key); /* Copy key into link -> key */
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL; 
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    /* Create a temporary pointer to the current and next Link */
    struct HashLink *currentLink;
    struct HashLink *nextLink;

    /* Traverse whole buckets of the map */
    for(int i = 0; i < map -> capacity; i++) {
        /* Get each Linked List in the Hash Table */
        currentLink = map ->table[i];
        /* Loop through the linked list in the specific bucket */
        while(currentLink != NULL) {
            /* Copy the next Link */
            nextLink = currentLink -> next;
            /* Delete the current Link included free the memory */
            hashLinkDelete(currentLink);
            /* Move forward current Link by assigning the stored next Link */
            currentLink = nextLink;
        }
        /* Set the current bucket to NULL */
        map -> table[i] = NULL;
    }
    /* Free the table and reset the value of size and capacity to 0 */
    free(map -> table);
    map -> size = 0;
    map -> capacity = 0;

}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    /* Hashing our key and mod it by the capcaity of Hash Map to get HashIndex */
    int hashIndex = HASH_FUNCTION(key) % map -> capacity;
    /* Modify the hashIndex to make it positive */
    if(hashIndex < 0) hashIndex += map -> capacity;
    /* Set up a temporary pointer points to the HashLink stored in the hashIndex in bucket */
    struct HashLink *temp = map -> table[hashIndex];

    while(temp != NULL) {
        /* Check each key of hashLink to find the same key */
        if(strcmp(temp -> key, key) == 0) {
            /* Return the pointer pointed to the value */
            return &(temp -> value);
        }
        /* Traverse whole Hash List */
        temp = temp -> next;
    }
    /* Do not find the target key */
    return NULL; 
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    /* Stored the old Table and old capacity inorder to re-assign elements and free the memory  */
    HashLink **oldTable = map -> table;
    int oldCapacity = map -> capacity;

    /* Create a larger Hash Table */
    hashMapInit(map, capacity);

    struct HashLink *current;
    struct HashLink *last;

    for(int i = 0; i < oldCapacity; i++) {

        current = oldTable[i];

        while(current != NULL) {
            /* Assign the old elements into the new Table */
            hashMapPut(map, current -> key, current -> value);
            last = current;
            current = current -> next;
            hashLinkDelete(last);
        }
    }
    free(oldTable);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    /* Check the Load Factor before adding new element */
    if(hashMapTableLoad(map) >= MAX_TABLE_LOAD) {
        resizeTable(map, 2 * map -> capacity);
    }

    int hashIndex = HASH_FUNCTION(key) % map -> capacity;

    if(hashIndex < 0 ) hashIndex += map -> capacity;

    if(hashMapContainsKey(map, key)) {
    /* Key has already been in the hash Map */
        /* Use a temporary pointer to store the Hash Link we would like to modify */
        struct HashLink *temp = map -> table[hashIndex];
        /* Loop through the Hash Link */
        while(temp != NULL) {
            /* Check if the key passed in was in the current List */
            if(strcmp(temp -> key, key) == 0) {
                /* Update the value */
                temp -> value = value;
                break;
            }
            /* Move forward */
            temp = temp -> next;
        }
    }
    /* Key was not in the Hash Map, need to create a new Link */
    else {
        /* Create a new link with the passed key and value */
        HashLink *link = hashLinkNew(key, value, map -> table[hashIndex]);
        /* add the new Link into the bucket */
        map -> table[hashIndex] = link;
        /* Increment the size by 1 */
        map -> size++;
    } 
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return 0;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return 0;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    return 0;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    return 0;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // FIXME: implement

   
}
