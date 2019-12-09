package main

import (
	"crypto/rand"
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	"github.com/SkycoinProject/skycoin/src/cipher/bip39"
	"github.com/SkycoinProject/skycoin/src/cipher/bip44"
	testutil "github.com/SkycoinProject/skycoin/src/testutil"
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

// RandBytes returns n random bytes
func SKY_testutil_RandBytes(n int, _arg0 *C.GoSlice_) (____error_code uint32) {
	b := make([]byte, n)
	_, err := rand.Read(b)
	if err != nil {
		____error_code = SKY_BAD_HANDLE
		return
	}
	copyToGoSlice(reflect.ValueOf(b), _arg0)
	return
}

//export SKY_testutil_RandSHA256
func SKY_testutil_RandSHA256(_arg0 *C.cipher__SHA256) (____error_code uint32) {
	b := make([]byte, 128)
	_, err := rand.Read(b)
	if err != nil {
		____error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := cipher.SumSHA256(b)
	copyToBuffer(reflect.ValueOf(arg0[:]), unsafe.Pointer(_arg0), uint(SizeofSHA256))
	return
}

//export SKY_testutil_RandXPub
func SKY_testutil_RandXPub(_arg0 *C.PublicKey__Handle) (____error_code uint32) {
	m, err := bip39.NewDefaultMnemonic()
	____error_code = libErrorCode(err)
	if err != nil {
		return
	}
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
