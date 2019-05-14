#include "common.h"

#include <stddef.h>

int isU8Eq(unsigned char p1[], unsigned char p2[], int len)
{
  size_t i;
   for (i= 0; i < len; i++) {
    if (p1[i] != p2[i])
    {
      return 0;
    }
  }

  return 1;
} 
