/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

#define APOSTROPHE -58
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // TODO
  return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
  parent = newNode();
  Node* cursor = parent;
  Node* next;
  int count = 1;

  char word[LENGTH + 1];
  FILE* fp;

  if ((fp = fopen(dictionary, "r")) != NULL)
    {
      int i = 0;
      int m; // Track the aphabetical index

      while (fgets(word, sizeof(word), fp) != NULL)
        {
          while (word[i])
            {
              // We'll need to check if the element is in use. NOT NULL
              m = hash(word[i]);
              // If it's an apostrophe then kick it to index 27
              if (m == APOSTROPHE)
                m = 26;
              if (cursor->child[m] == 0)
                {
                  next = newNode();
                  cursor->child[m] = next;
                  cursor = next;
                }
              else
                {
                  cursor = cursor->child[m];
                  i++; // I had forgotten to increment lol...
                  continue;
                }
              // printf("%d ", hash(word[i]));
              if (word[i + 1] == '\n')
                {
                  word[i + 1] = '\0';
                  strncpy(cursor->word, word, LENGTH);
                  printf("%s\n", word);
                  cursor = parent; //rewind back to the root
                  i = 0;
                  break;
                }
              i++;
            }
          count++;
        }
      fclose(fp);
      printf("number of entries %d\n", count);
      return true;
    }
  // TODO
  return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  // TODO
  return 0;
}

void
unloadHelper (Node* node)
{
  for (int i = 0; i < CAPACITY; i++)
    {
      if (node->child[i] != NULL)
        {
          unloadHelper(node->child[i]);
        }
    }
  free(node);
  return;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
  // TODO
  Node* cursor;
  cursor = parent;

  unloadHelper(cursor);

  return false;
}

int
hash (char ch)
{
  int index;
  index = ch - BASE;

  return index;
}

Node*
newNode ()
{
  Node* node = calloc(1, sizeof(Node));

  //for (int i = 0; i < LENGTH; i++)
  //  node->child[i] = NULL;
  return node;
}
