// Problem: In speller we have to implement a spell checker that take a text file and check if
// every word in it is spelled correctly or not in less time.

// The dictionary.c file implements a hash table to load, check, and unload words using linked lists
// for collision handling.
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Struct that represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table (size of hash table)
const int N = 1000;

// Hash table array node
node *table[N];

int count_word = 0;

// Hashes word to a index number
unsigned int hash(const char *word)
{
    int hashed_word_index = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        // find index for each word by multiplying prev hash by 7 and adding current charcter ascii
        hashed_word_index = (hash_value * 7 + tolower(word[i])) % N;
    }
    return hashed_word_index;
}


// Loads each word of dictionary into a new node made at hashed word index of hash array
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        printf("File can't be opened for reading \n");
        return false;
    }

    char word[LENGTH + 1];

    // Read words from dictionary file one by one
    while (fscanf(dictionary_file, "%45s", word) != EOF)
    {
        // Allocate memory for a new node that will store the word
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }
        // Copy the word into the node
        strcpy(newnode->word, word);

        int hashed_word_index = hash(word);

        // Insert node at the head of the linkedlist at hashed word index of hash array
        newnode->next = table[hashed_word_index];
        table[hashed_word_index] = newnode;

        count_word++; // calculating number of words in dictionary
    }

    // Close the dictionary file
    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded
unsigned int size(void)
{
    return count_word;
}

// Check if word is in dictionary or not
bool check(const char *word)
{
    // Get the hash value (index) for the word
    int hashed_word_index = hash(word);

    // Pointer to traverse the linked list at the hash table index
    node *cursor = table[hashed_word_index];

    // Traverse the linked list, checking for the word
    while (cursor != NULL)
    {
        // Compare word case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next; // Move to the next node in the list
    }

    return false;
}


// Unloads dictionary from memory
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Pointer to traverse the linked list at the current index
        node *cursor = table[i];

        // Free each node in the linked list
        while (cursor != NULL)
        {
            node *temp = cursor;   // Temporary pointer to store current node
            cursor = cursor->next; // Move to the next node
            free(temp);            // Free the current node
        }
    }

    return true;
}
