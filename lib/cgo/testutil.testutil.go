package main

import (
	"unsafe"

	testutil "github.com/skycoin/skycoin/src/testutil"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_testutil_MakeAddress
func SKY_testutil_MakeAddress(_arg0 *C.cipher__Address) (____error_code uint32) {
	__arg0 := testutil.MakeAddress()
	*_arg0 = *(*C.cipher__Address)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_testutil_MakePubKey
func SKY_testutil_MakePubKey(_arg0 *C.cipher__PubKey) (____error_code uint32) {
	__arg0 := testutil.MakePubKey()
	*_arg0 = *(*C.cipher__PubKey)(unsafe.Pointer(&__arg0))
	return
}

