#include "common.h"

#include <string.h>
#include <stdio.h>

GoInt_ isU8Eq(unsigned char p1[], unsigned char p2[], size_t len) {

  if (strncmp(p1, p2, len) == 0) {

    return 1;
  }
  printf("p1 %s\n", p1);
  printf("p2 %s\n", p2);
  return 0;
}
