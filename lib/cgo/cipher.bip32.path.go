package main

import (
	"unsafe"

	"github.com/SkycoinProject/skycoin/src/cipher/bip32"
)

/*

  #include <string.h>
  #include <stdlib.h>
  #include <stdbool.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_bip32_PathNode_Hardened
func SKY_bip32_PathNode_Hardened(_p *C.bip32__PathNode, _arg0 *bool) (____error_code uint32) {
	p := *(*bip32.PathNode)(unsafe.Pointer(_p))
	__arg0 := p.Hardened()
	*_arg0 = __arg0
	return
}

//export SKY_bip32_ParsePath
func SKY_bip32_ParsePath(_p string, _arg1 *C.Path__Handle) (____error_code uint32) {
	p := _p
	__arg1, ____return_err := bip32.ParsePath(p)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPathHandle(__arg1)
	}
	return
}
