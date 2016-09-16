/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 50
#define CAPACITY 27

// ascii lower case starting index
#define BASE 97


/*
 * Define our custom node for the trie
 */
typedef struct _node
{
  char word[LENGTH + 1];
  struct _node* child[CAPACITY];
} Node;

Node* parent;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Maps the ascii index zero index
 */
int hash(char ch);

void
unloadHelper(Node* node);

/*
 * Helper function for allocation of new nodes
 */
Node* newNode();
#endif // DICTIONARY_H
