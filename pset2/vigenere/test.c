// iteration 1: map key's ascii code to alphabetical index where index
// is zero based
#include <stdio.h>

int
main (void)
{
  const int BASE_LOWER = 97;
  int ch = 'a';

  printf("ascii code of 'a' is %i\n", ch);
  printf("alphabetical index of 'a' is %i\n", ch - BASE_LOWER);
  return 0;
}
