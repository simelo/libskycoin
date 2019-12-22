package main

import (
	"encoding/hex"
	"reflect"
	"unsafe"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_base58_String2Hex
func SKY_base58_String2Hex(_s string, _arg1 *C.GoSlice_) (____error_code uint32) {
	s := _s
	__arg1, ____return_err := hex.DecodeString(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg1), _arg1)
	}

	return
}

//export SKY_base58_Hex2String
func SKY_base58_Hex2String(_b []byte, _arg1 *C.GoString_) (____error_code uint32) {
	bin := *(*[]byte)(unsafe.Pointer(&_b))
	if bin == nil {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg1 := hex.EncodeToString(bin)
	copyString(__arg1, _arg1)
	return
}
