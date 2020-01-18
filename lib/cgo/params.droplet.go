package main

import params "github.com/SkycoinProject/skycoin/src/params"

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_params_DropletPrecisionToDivisor
func SKY_params_DropletPrecisionToDivisor(_precision uint8, _arg1 *uint64) (____error_code uint32) {
	precision := _precision
	__arg1 := params.DropletPrecisionToDivisor(precision)
	*_arg1 = __arg1
	return
}

//export SKY_params_DropletPrecisionCheck
func SKY_params_DropletPrecisionCheck(_precision uint8, _amount uint64) (____error_code uint32) {
	precision := _precision
	amount := _amount
	____return_err := params.DropletPrecisionCheck(precision, amount)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
