package main

import (
	"reflect"
	"unsafe"

	"github.com/SkycoinProject/skycoin/src/cipher/base58"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_base58_NewAlphabet
func SKY_base58_NewAlphabet(_s string, _arg1 *C.base58__Alphabet) (____error_code uint32) {
	____error_code = 0
	s := _s
	__arg1 := base58.NewAlphabet(s)
	*_arg1 = *(*C.base58__Alphabet)(unsafe.Pointer(__arg1))
	return
}

//export SKY_base58_Encode
func SKY_base58_Encode(_bin []byte, _arg1 *C.GoString_) (____error_code uint32) {
	____error_code = 0
	bin := *(*[]byte)(unsafe.Pointer(&_bin))
	__arg1 := base58.Encode(bin)
	copyString(__arg1, _arg1)
	return
}

//export SKY_base58_Decode
func SKY_base58_Decode(_str string, _arg1 *C.GoSlice_) (____error_code uint32) {
	____error_code = 0
	str := _str
	__arg1, ____return_err := base58.Decode(str)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg1), _arg1)
	}
	return
}
