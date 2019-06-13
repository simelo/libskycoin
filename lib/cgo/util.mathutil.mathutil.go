package main

import (
	mathutil "github.com/skycoin/skycoin/src/util/mathutil"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_util_AddUint64
func SKY_util_AddUint64(_a, _b uint64, _arg1 *uint64) (____error_code uint32) {
	a := _a
	b := _b
	__arg1, ____return_err := mathutil.AddUint64(a, b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_util_Uint64ToInt64
func SKY_util_Uint64ToInt64(_a uint64, _arg1 *int64) (____error_code uint32) {
	a := _a
	__arg1, ____return_err := mathutil.Uint64ToInt64(a)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_util_Int64ToUint64
func SKY_util_Int64ToUint64(_a int64, _arg1 *uint64) (____error_code uint32) {
	a := _a
	__arg1, ____return_err := mathutil.Int64ToUint64(a)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_util_IntToUint32
func SKY_util_IntToUint32(_a int, _arg1 *uint32) (____error_code uint32) {
	a := _a
	__arg1, ____return_err := mathutil.IntToUint32(a)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}
