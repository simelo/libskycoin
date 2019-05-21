#include "common.h"

#include <string.h>
#include <stdio.h>

#include "libskycoin.h"
#include "skyerrors.h"

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

// FIXME this should be documented as memory initializer
// a better approach can be follow the RAII pattern instead of using the
// registerMemCleanup
int copyGoSlice_toGoSlice(GoSlice* pdest, GoSlice_* psource, int elem_size){
  pdest->len = psource->len;
  pdest->cap = psource->cap;
  pdest->data = calloc(psource->cap, elem_size);
  registerMemCleanup(pdest->data);
  memcpy(pdest->data, psource->data, psource->len * elem_size);
  return SKY_OK;
}
