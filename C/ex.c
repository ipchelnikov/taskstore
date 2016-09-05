#include <stdio.h>

void main()
{
  short a[5] = {1,2,3,4,5};
  char* b = a;
 
  printf("%d %d \n", b[0], b[5]); // in case of littel endian (Linuz for example), the result will be 1 0
                                  // short = 2 bytes, chat = 1 byte. 
                                  // Printing the left part of the first element in the array
                                  // and the right part of third element
}
