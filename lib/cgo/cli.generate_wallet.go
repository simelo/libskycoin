package main

import (
	cli "github.com/SkycoinProject/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_cli_MakeAlphanumericSeed
func SKY_cli_MakeAlphanumericSeed(_arg0 *string) (____error_code uint32) {
	*_arg0 = cli.MakeAlphanumericSeed()
	return
}
