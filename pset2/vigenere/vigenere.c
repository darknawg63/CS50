// vigenere.c
//
// iteration 0: map characters to key
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int
main (void)
{
  string message = "Meet me at the park at eleven am";
  string key = "bacon";

  for (int i = 0, j = 0, ilen = strlen(message),
       jlen = strlen(key); i < ilen; i++)
    {
      if (isalpha(message[i]))
        {
          if (j == jlen)
            j = 0;
          printf ("%c", key[j]);
          j++;
        }
      else
        printf ("%c", message[i]);
    }

  printf ("\n");
  return 0;
}
