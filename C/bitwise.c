#include <stdio.h>

int main(int argc, char* argv[])
{
  char c = 5;

  int i = 0;

  for (i = 7; i >= 0; --i)
    printf("%d", c&0x1<<i ? 1 : 0 );

  printf("\n%d\n", c);

  return 0;
}
