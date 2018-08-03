/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Wei-Chien Hsu
 * Date: 8/02/2018
 */

#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    /* Load the first word into key pointer */
    char *word = nextWord(file);
    /* Loop through whole dicitionary */
    while(word != NULL) {
        /* Put the single word into the Map */
        hashMapPut(map, word, 0);
        /* Free the address stored the previous word for the next word */
        free(word);
        /* Points to the next Word */
        word = nextWord(file);
    }
}

/**
 * LevenshteinDistance function
 * the function calculates the levenshtein distance between two strings
 * and returns the value.
 * @param char *s1 
 * @param char *s2
 * @return int
 */

/* Define a minimun function to get the minimun value of three */
#define minimum(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int LevenshteinDistance(char *s1, char *s2) {
    int x, y;
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    /* Allocate a integer matrix row for the string2 and col for the string1 */
    int matrix[s2_len + 1][s1_len + 1];
    /* Init the (0, 0) index in the matrix as 0 */
    matrix[0][0] = 0;

    /* Init the first row from 0 to the length of string1 */
    for(x = 1; x <= s2_len; x++) 
        matrix[x][0] = matrix[x - 1][0] + 1;
    /* Init the first column from 0 to the length of string2*/
    for(y = 1; y <= s1_len; y++)
        matrix[0][y] = matrix[0][y - 1] + 1;

    /* Start from (1, 1) to treverse the whole matrix */
    for(x = 1; x <= s2_len; x++)
        for(y = 1; y <= s1_len; y++)
            /* Deletion, Insertion and Substitution */
            matrix[x][y] = minimum(matrix[x - 1][y] + 1, 
                                   matrix[x][y - 1] + 1,
                                   matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));
    return matrix[s2_len][s1_len];
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
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        char originalInputBuffer[256];
        strcpy(originalInputBuffer, inputBuffer);

        /* Convert the input characters to lowercase */
        for(int i = 0; inputBuffer[i]; i++) {
            inputBuffer[i] = tolower(inputBuffer[i]);
        }
        /* Variable to stop the program and recognize if we found the target key */
        int found = 0;

        /*  create 5 best candidates */
        char *matches[5];
        for(int i = 0; i < 5; i++) {
            matches[i] = malloc(sizeof(char) * 257);
            assert(matches[i] != 0);
        }
        /* Create a distances array for holding the Levenshtein Distance */
        /* Init them as 0, and will put the new Distince by calling another function */
        int distances[5] = {0, 0, 0, 0, 0};
        for(int i = 0; i < map -> capacity; i++) {
            /* A Hash Link pointer points to single link in our table (value in dictionary) */
            HashLink *link = map -> table[i];
            if(link != NULL) {
                while(link != NULL) {
                    if(strcmp(inputBuffer, link -> key) == 0) {
                        printf("The inputted word %s is spelled correctly \n", originalInputBuffer);
                        link = NULL; /* Stop the */
                        found = 1;
                    }
                    /* Current Key did not match the user input */
                    /* Need to calculate Levenshtein Distance to see */
                    /* If it would be added into our distances array */
                    else {
                        /* Calculate the level of differences between  */
                        int distance = LevenshteinDistance(inputBuffer, link -> key);
                        for(int j = 0; j < 5; j++) {
                            /* Update the distances array if the current 
                            distance if larger than new get one or equal to 0  */
                            if((distances[j] > distance) || distances[j] == 0) {
                                distances[j] = distance;
                                /* Copy the current key (value in dictionary) into match array */
                                strcpy(matches[j], link -> key);
                                /* Since we have updated both arrays, 
                                stop finding the next position in the array */
                                break;
                            }
                        }
                        /* Find the next key in the Link */
                        link = link -> next;
                    }
                }
            }
            /* If we found the value during traves the map */
            /* Then we could jump out the for loop and free the matches pointers */
            else if(found) {
                break;
            }
        } /* The end of searching in the dictionary */

        /* Still not found the matched key */
        if(!found) {
            printf("The inputted word %s is spelled incorrectly. \n", originalInputBuffer);
            /* Print out 5 most possible results */
            for(int i = 0; i < 5; i++)
                printf("Did you mean \"%s\"? \n", matches[i]);
        }

        for(int i = 0; i < 5; i++) {
            free(matches[i]);
        }
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}