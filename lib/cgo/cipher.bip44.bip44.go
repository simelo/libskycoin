package main

import (
	"github.com/skycoin/skycoin/src/cipher/bip44"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_bip44_NewCoin
func SKY_bip44_NewCoin(_seed []byte, _coinType uint32, _arg0 *C.Coin__Handle) (___err_code uint32) {
	__arg0, ___return_err := bip44.NewCoin(_seed, bip44.CoinType(_coinType))
	___err_code = libErrorCode(___return_err)
	if ___return_err == nil {
		*_arg0 = registerCoinHandle(__arg0)
	}
	return
}

//export SKY_bip44_Coin_Account
func SKY_bip44_Coin_Account(_c C.Coin__Handle, account uint32, _arg0 *C.Account__Handle) (___err_code uint32) {
	c, okc := lookupCoinHandle(_c)
	if !okc {
		___err_code = SKY_BAD_HANDLE
		return
	}
	ac, err := c.Account(account)
	___err_code = libErrorCode(err)
	if err == nil {
		*_arg0 = registerAccountHandle(ac)
	}
	return
}

//export SKY_bip44_Account_External
func SKY_bip44_Account_External(_a C.Account__Handle, _arg0 *C.PrivateKey__Handle) (___err_code uint32) {
	a, oka := lookupAccountHandle(_a)
	if !oka {
		___err_code = SKY_BAD_HANDLE
		return
	}

	p, __return_err := a.External()
	___err_code = libErrorCode(__return_err)
	if __return_err == nil {
		*_arg0 = registerPrivateKeyHandle(p)

	}
	return
}

//export SKY_bip44_Account_Change
func SKY_bip44_Account_Change(_a C.Account__Handle, _arg0 *C.PrivateKey__Handle) (___err_code uint32) {
	a, oka := lookupAccountHandle(_a)
	if !oka {
		___err_code = SKY_BAD_HANDLE
		return
	}

	p, __return_err := a.Change()
	___err_code = libErrorCode(__return_err)
	if __return_err == nil {
		*_arg0 = registerPrivateKeyHandle(p)

	}
	return
}

//export SKY_bip44_Account_String
func SKY_bip44_Account_String(_a C.Account__Handle, _arg0 *string) (___err_code uint32) {

	a, oka := lookupAccountHandle(_a)
	if !oka {

		___err_code = SKY_BAD_HANDLE
		return
	}

	*_arg0 = a.String()
	return
}

//export SKY_bip44_Account_GetPrivateKey
func SKY_bip44_Account_GetPrivateKey(_a C.Account__Handle, _arg0 *C.PrivateKey__Handle) (___err_code uint32) {

	a, oka := lookupAccountHandle(_a)
	if !oka {

		___err_code = SKY_BAD_HANDLE
		return
	}

	*_arg0 = registerPrivateKeyHandle(a.PrivateKey)
	return
}
