package main

import (
	cli "github.com/skycoin/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_cli_MakeAlphanumericSeed
func SKY_cli_MakeAlphanumericSeed(_arg0 *C.GoString_) (____error_code uint32) {
	__arg0 := cli.MakeAlphanumericSeed()
	copyString(__arg0, _arg0)
	return
}
