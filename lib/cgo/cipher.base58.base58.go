package main

import (
	"encoding/hex"
	"unsafe"

	"github.com/skycoin/skycoin/src/cipher/base58"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_base58_Hex2Base58
func SKY_base58_Hex2Base58(_val []byte, _arg1 *string) (____error_code uint32) {
	val := *(*[]byte)(unsafe.Pointer(&_val))
	*_arg1 = string(base58.Encode(val))
	return
}

//export SKY_base58_Encode
func SKY_base58_Encode(_bin []byte, _arg1 *string) (____error_code uint32) {
	bin := *(*[]byte)(unsafe.Pointer(&_bin))
	*_arg1 = base58.Encode(bin)

	return
}

//export SKY_base58_Decode
func SKY_base58_Decode(_s string, _arg1 *[]byte) (____error_code uint32) {
	s := _s
	__arg1, ____return_err := base58.Decode(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}

	return
}

//export SKY_base58_String2Hex
func SKY_base58_String2Hex(_s string, _arg1 *[]byte) (____error_code uint32) {
	__arg1, ____return_err := hex.DecodeString(_s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}

	return
}

//export SKY_base58_Hex2String
func SKY_base58_Hex2String(_b []byte, _arg1 *string) (____error_code uint32) {
	bin := *(*[]byte)(unsafe.Pointer(&_b))
	*_arg1 = hex.EncodeToString(bin)
	return
}
