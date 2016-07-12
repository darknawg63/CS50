#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void display(char* str);
void rotate(char* str, int key);

int
main (int argc, char* argv[])
{
  long int key = -1;
  char* ptr;

  if (argc != 2)
    {
      printf("Usage: %s 'integer value > 0'\n", argv[0]);
      return 1;
    }
  else if (argc == 2)
    key = strtol(argv[1], &ptr, 10);
  string name;
  name = GetString();
  rotate(name, key);
  display(name);
  printf("\n");
  return 0;
}

void
display (char* str)
{
  for (int i = 0, len = strlen(str); i < len; i++)
    printf("%c", str[i]);
}

void
rotate (char* str, int key)
{
  for (int i = 0, len = strlen(str); i < len; i++)
    {
      if (isalpha(str[i]))
        {
          if (isupper(str[i]))
            {
              int base = 65;
              str[i] = ((str[i] - base + key) % 26) + base;
            }
          if (islower(str[i]))
            {
              int base = 97;
              str[i] = ((str[i] - base + key) % 26) + base;
            }
        }
      else
        str[i] = str[i];
    }
}
