#include <stdio.h>

int main ()
{
  FILE *fp;
  char c;
  //int n = 0;

  fp = fopen("dictionaries/large","r");
  if(fp == NULL) 
    {
      perror("Error in opening file");
      return(-1);
    }
  do
    {
      c = fgetc(fp);
      if(c == '\n')
        puts("__");
      if( feof(fp) )
        {
          break ;
        }
      printf("%c", c);
    } while (1);

  fclose(fp);
  return(0);
}
