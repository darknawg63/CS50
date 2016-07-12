#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CAPACITY 12
#define NOINPUT 4

int GetFloat (char str[], float* flt_, int capacity);

int quarter = 25;
int dime = 10;
int nickel = 5;
int penny = 1;
int counter = 0;

int
main (void)
{
  char buf[CAPACITY];
  float dollars;
  int input = 0;

  while (input < NOINPUT)
    {
      printf("Yo! How much change owed? ");
      input = GetFloat(buf, &dollars, CAPACITY);

      dollars = dollars*100;
      int balance = round(dollars);
      if (balance < 0)
        {
          input = 0;
          continue;
        }
      while (balance >= quarter)
        {
          balance = balance - quarter;
          counter++;
        }
      while (balance >= dime)
        {
          balance = balance - dime;
          counter++;
        }
      while (balance >= nickel)
        {
          balance = balance - nickel;
          counter++;
        }
      while (balance >= penny)
        {
          balance = balance - penny;
          counter++;
        }
    }
  printf("%d\n", counter);
  return 0;
}

int
GetFloat (char str[], float* flt_, int capacity)
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

  // The specs required that the input be of type float :)
  *flt_ = strtof(str, &p);

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
