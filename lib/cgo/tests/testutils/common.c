#include "common.h"

#include <string.h>
#include <stdio.h>

int MEMPOOLIDX = 0;
void *MEMPOOL[1024 * 256];

GoInt_ isU8Eq(unsigned char p1[], unsigned char p2[], size_t len) {

  if (strncmp(p1, p2, len) == 0) {

    return 1;
  }
  printf("p1 %s\n", p1);
  printf("p2 %s\n", p2);
  return 0;
}

void * registerMemCleanup(void *p) {
  int i;
  for (i = 0; i < MEMPOOLIDX; i++) {
    if(MEMPOOL[i] == NULL){
      MEMPOOL[i] = p;
      return p;
    }
  }
  MEMPOOL[MEMPOOLIDX++] = p;
  return p;
}
