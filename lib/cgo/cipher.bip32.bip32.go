package main

import (
	"github.com/skycoin/skycoin/src/cipher/bip32"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_bip32_NewMasterKey
func SKY_bip32_NewMasterKey(_seed []byte, _pk *C.PrivateKey__Handle) (___error_code uint32) {

	pk, ___return_error := bip32.NewMasterKey(_seed)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_pk = registerPrivateKeyHandle(pk)
	}
	return
}

//export SKY_bip32_NewPrivateKeyFromPath
func SKY_bip32_NewPrivateKeyFromPath(seed []byte, p string, _pk *C.PrivateKey__Handle) (___error_code uint32) {

	pk, ___return_error := bip32.NewPrivateKeyFromPath(seed, p)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_pk = registerPrivateKeyHandle(pk)
	}
	return
}


