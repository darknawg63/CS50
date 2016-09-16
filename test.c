#include <stdio.h>

int
main (void)
{
  char cat[] = {'c', 'a', 's', '\0'};
  char tac[] = {'c', 'a', 't', '\0'};

  if (cat > tac)
    puts("yes");
  return 0;
}
