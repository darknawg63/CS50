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
#define LAST_ELEMENT 26

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // TODO
  Node* cursor;
  cursor = parent;

  int i = 0;
  int m;

  while (word[i])
    {
      m = hash(tolower(word[i]));

      if (cursor->child[m] == NULL)
        return false;
      // If we've been able to traverse to the end then this is a word in the dictionary
      if (cursor->child[m] != NULL && word[i + 1] == '\0' && cursor->child[m]->is_word == true)
        return true;

      if (cursor->child[m] != NULL)
        {
          cursor = cursor->child[m];
          i++;
          continue;
        }
      i++;
    }

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

  char ch;
  FILE* fp;

  if ((fp = fopen(dictionary, "r")) != NULL)
    {
      int m; // Track the aphabetical index
      count = 1;

      do
        {
          ch = fgetc(fp);
          m = hash(ch);

          if( feof(fp) )
            {
              break ;
            }
          if (ch == '\n')
            {
              cursor->is_word = true;
              cursor = parent; //rewind back to the root
              count++;
              continue;
            }
          if (cursor->child[m] == NULL)
            {
              next = newNode();
              cursor->child[m] = next;
              cursor = next;
            }
          else
            {
              cursor = cursor->child[m];
            }
        } while (1);

      fclose(fp);
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
  if (count > 0)
    return count;
  return 0;
}

int
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
  return 1;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
  // TODO
  Node* cursor;
  cursor = parent;

  if (unloadHelper(cursor))
    return true;

  return false;
}

int
hash (char ch)
{
  int index;
  index = ch - BASE;

  if (index == APOSTROPHE)
    return LAST_ELEMENT;

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
