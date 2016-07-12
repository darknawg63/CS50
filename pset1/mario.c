// mario.c
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10
#define NOINPUT 4
#define MIN 0
#define MAX 23

int GetInt (char str[], long int* int_, int capacity);
void PrintSpace();
void PrintHash();

long int height;
int hash = 2;
int space;

int
main (void)
{
  int noinput = 0;
  char buf[CAPACITY];
  while (noinput < NOINPUT)
    {
      printf("height: ");
      noinput = GetInt(buf, &height, CAPACITY);
      if (height > MIN && height <= MAX)
        {
          for (int i = 0; i < height; i++)
            {
              PrintSpace();
              PrintHash();
            }
        }
      if (height > MAX)
        noinput = 0;
      if (height < MIN)
        noinput = -1;
    }
  return 0;
}

int
GetInt (char str[], long int* int_, int capacity)
{
  char ch;
  char* p;
  int i;
  int in_buffer;
  i = 0;
  in_buffer = 1;
  while (in_buffer)
    {
      ch = getchar();
      if ((ch == '\n') || (ch == EOF))
        {
          in_buffer = 0;
        }
      else
        if (i < capacity - 1)
          {
            str[i] = ch;
            i++;
          }
    }
  str[i] = '\0';
  *int_ = strtol(str, &p, 10);
  if (str[0] != '\n' && i != 0 && (*p == '\n' || *p == '\0'))
    // return 7 for valid input
    return i - i + 6;
  else
    {
      // return 1 for no input, enter pressed
      if (i == 0)
        return i - i + 1;
      // return 2 for invalid input
      if (i > 0)
        return i - i + 2;
    }
  return i;
}

void
PrintSpace ()
{
  space = height - hash + 1;
  for (int i = 0; i < space; i++)
    printf(" ");
  space--;
}

void
PrintHash ()
{
  for (int i = 0; i < hash; i++)
    printf("#");
  hash++;
  printf("\n");
}
