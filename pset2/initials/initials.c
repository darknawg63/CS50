#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void display(int n);
bool is_alpha(int n);
bool is_lower(int n);
void to_upper(int n);

string name;

int
main (void)
{
  name = GetString();
  bool letter = true;

  for ( int i = 0, len = strlen(name); i < len; i++)
    {
      if (!is_alpha(i))
        {
          letter = false;
          continue;
        }
      // if first letter and first letter is small, then caps
      if (i == 0)
        {
          to_upper(i);
          display(i);
        }
      else if (i == 0)
        display(i);
      if (i > 0 && letter == false
          && is_alpha(i))
        {
          to_upper(i);
          letter = true;
          display(i);
        }
    }
  printf("\n");
  return 0;
}

void
display (int n)
{
  printf("%c", name[n]);
}

bool
is_alpha (int n)
{
  if ((name[n] >= 'a' && name[n] <= 'z')
      || (name[n] >= 'A' && name[n] <= 'Z'))
    return true;
  return false;
}

bool
is_lower (int n)
{
     if (name[n] >= 'a' && name[n] <= 'z')
        return true;
     return false;
}

void
to_upper (int n)
{
  if (is_alpha(n) && is_lower(n))
    name[n] = name[n] - abs('a' - 'A');
  else
    name[n] = name[n];
}
