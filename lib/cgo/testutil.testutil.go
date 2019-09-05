package main

import (
	"unsafe"

	"github.com/skycoin/skycoin/src/cipher/bip39"
	"github.com/skycoin/skycoin/src/cipher/bip44"
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

//export SKY_testutil_RandXPub
func SKY_testutil_RandXPub(_arg0 *C.PublicKey__Handle) (____error_code uint32) {
	m, _ := bip39.NewDefaultMnemonic()
	s, err := bip39.NewSeed(m, "")
	____error_code = libErrorCode(err)
	if err != nil {
		return
	}

	c, err := bip44.NewCoin(s, bip44.CoinTypeSkycoin)
	____error_code = libErrorCode(err)
	if err != nil {
		return
	}
	x, err := c.Account(0)
	____error_code = libErrorCode(err)
	if err != nil {
		return
	}
	e, err := x.External()
	____error_code = libErrorCode(err)
	if err != nil {
		return
	}
	*_arg0 = registerPublicKeyHandle(e.PublicKey())
	return
}
