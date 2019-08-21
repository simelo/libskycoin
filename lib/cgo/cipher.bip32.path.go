package main

import (
	"unsafe"

	"github.com/skycoin/skycoin/src/cipher/bip32"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_bip32_PathNode_Hardened
func SKY_bip32_PathNode_Hardened(_pk *C.bip32__PathNode) (____error_code uint32) {
	pk := (*bip32.PathNode)(unsafe.Pointer(_pk))
	err := pk.Hardened()
	____error_code = 1
	if !err {
		____error_code = 0
	}
	return
}

// nolint megacheck
//export SKY_bip32_ParsePath
func SKY_bip32_ParsePath(_p string, _arg0 *C.bip32__Path) (____error_code uint32) {

	p, err := bip32.ParsePath(_p)
	____error_code = libErrorCode(err)
	if err == nil {
		_arg0 = (*C.bip32__Path)(unsafe.Pointer(p))
	}
	return
}
