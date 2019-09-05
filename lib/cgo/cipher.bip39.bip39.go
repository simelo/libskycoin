package main

import (
	"unsafe"

	"github.com/skycoin/skycoin/src/cipher/bip39"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_bip39_NewDefaultMnemomic
func SKY_bip39_NewDefaultMnemomic(_arg0 *string) (____error_code uint32) {
	__arg0, ____return_err := bip39.NewDefaultMnemonic()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_bip39_NewEntropy
func SKY_bip39_NewEntropy(_bitSize int, _arg1 *[]byte) (____error_code uint32) {
	bitSize := _bitSize
	__arg1, ____return_err := bip39.NewEntropy(bitSize)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_bip39_NewMnemonic
func SKY_bip39_NewMnemonic(_entropy []byte, _arg1 *string) (____error_code uint32) {
	entropy := *(*[]byte)(unsafe.Pointer(&_entropy))
	__arg1, ____return_err := bip39.NewMnemonic(entropy)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_bip39_ValidateMnemonic
func SKY_bip39_ValidateMnemonic(_mnemonic string) (____error_code uint32) {
	mnemonic := _mnemonic
	____return_err := bip39.ValidateMnemonic(mnemonic)
	____error_code = libErrorCode(____return_err)
	return
}

//export SKY_bip39_NewSeed
func SKY_bip39_NewSeed(_mnemonic string, _password string, _arg1 *[]byte) (____error_code uint32) {
	mnemonic := _mnemonic
	password := _password
	__arg1, ____return_err := bip39.NewSeed(mnemonic, password)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}
