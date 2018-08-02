/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Wei-Chien Hsu
 * Date: 8/01/2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
//Fix me: Do the necessary change to make the implementation //case-insensitive  
   while (1) 
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')  
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            /* A: 65, B:66, Z:90, a:97, b:98, z:122 */
            /* Convert Uppercase to the Lowercase */
            if(c >= 'A' && c <= 'Z'){
                c += 32;
            }

            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    /* Open a file by calling fopen() and use a pointer for hold the file */
    FILE *inputFile = fopen(fileName, "r");

    if(!inputFile) {
        printf("ERROR: Can not open the input file. \n");
    }
    /* Load the first word into key pointer */
    char *key = nextWord(inputFile);

    /* Loop through the file to update keys counted in the Map  */
    while(key != 0) {
        printf(" %s", key);
        /* Check if the key is in the map or not */
        if(hashMapContainsKey(map, key) == 0) {
            /* Create a new key into the Map */
            hashMapPut(map, key, 1);
        } 
        else {
            /* Increment the value of the key by 1 */
            (*hashMapGet(map, key))++;
        }
        /* Free the memory space that stored the previous key */
        free(key);
        /* Get new key stored in different address for this key pointer */
        key = nextWord(inputFile);
    }

    fclose(inputFile);
    printf("\n");
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}