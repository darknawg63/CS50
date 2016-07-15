// vigenere.c
//
// iteration 0: map characters to key
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define RANGE 26

void rotate(char* str, char* key, int range);
void display(char* str);

int
main (int argc, char* argv[])
{
  string key;

  if (argc == 2)
    key = argv[1];
  else
    {
      printf("usage: %s <key>\n", argv[0]);
      return 1;
    }
  // check if key contains a numeric char
  for (int i = 0, len_k = strlen(key); i < len_k; i++)
    if (isdigit(key[i]))
      {
        printf("usage: %s <key>\n", argv[0]);
        return 1;
      }
  string message;
  message = GetString();
  rotate(message, key, RANGE);
  return 0;
}

void
rotate (char* str, char* key, int range)
{
  const int BASE_LOWER = 97;
  const int BASE_UPPER = 65;
  int hash;
  int k = 0;
  int s = 0;
  int len_k = strlen(key);
  int len_s = strlen(str);

  for (s = 0; s < len_s; s++)
    {
      if (isalpha(str[s]))
        {
          if (islower(key[k]))
            // key gives us the ascii position. Subtracting lower boundery
            // gives us its alphabetical zero based index which tells us
            // exactly how many places to shift a letter over.
            hash = key[k] - BASE_LOWER;
          else if (isupper(key[k]))
            hash = key[k] - BASE_UPPER;
          if (isupper(str[s]))
            // adding BASE_UPPER converts back to the ascii representation
            printf("%c", (str[s] - BASE_UPPER + hash) % range + BASE_UPPER);
          if (islower(str[s]))
            printf("%c", (str[s] - BASE_LOWER + hash) % range + BASE_LOWER);
          k++;
          if (k == len_k)
            k = 0;
        }
      else
        printf("%c", str[s]);
    }

  printf ("\n");
}
