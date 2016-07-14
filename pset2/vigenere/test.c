// iteration 1: map key's ascii code to alphabetical index where index
// is zero based
// iteration 1: encode message by applying hash
#include <stdio.h>

int
main (void)
{
  const int BASE_LOWER = 97;
  int key = 'b';
  int hash = key - BASE_LOWER;
  char message = 'M';

  printf("ascii code of '%c' is %i\n", key, key);
  printf("alphabetical index of 'a' is %i\n", key - BASE_LOWER);
  printf("Message encrypted is %c\n", message + hash);
  return 0;
}
