package main

import (
	"unsafe"

	"github.com/SkycoinProject/skycoin/src/cipher/bip44"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_bip44_NewCoin
func SKY_bip44_NewCoin(_seed []byte, _coinType *C.bip44__CoinType, _arg2 *C.Coin__Handle) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	coinType := *(*bip44.CoinType)(unsafe.Pointer(_coinType))
	__arg2, ____return_err := bip44.NewCoin(seed, coinType)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerCoinHandle(__arg2)
	}
	return
}

//export SKY_bip44_Coin_Account
func SKY_bip44_Coin_Account(_c *C.Coin__Handle, _account uint32, _arg1 *C.Account__Handle) (____error_code uint32) {
	c, okc := lookupCoinHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	account := _account
	__arg1, ____return_err := c.Account(account)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerAccountHandle(__arg1)
	}
	return
}

//export SKY_bip44_Account_External
func SKY_bip44_Account_External(_a *C.Account__Handle, _arg0 *C.PrivateKey__Handle) (____error_code uint32) {
	a, oka := lookupAccountHandle(*_a)
	if !oka {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := a.External()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = registerPrivateKeyHandle(__arg0)
	}
	return
}

//export SKY_bip44_Account_Change
func SKY_bip44_Account_Change(_a *C.Account__Handle, _arg0 *C.PrivateKey__Handle) (____error_code uint32) {
	a, oka := lookupAccountHandle(*_a)
	if !oka {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := a.Change()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = registerPrivateKeyHandle(__arg0)
	}
	return
}
