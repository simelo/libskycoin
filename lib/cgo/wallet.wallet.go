package main

import (
	"unsafe"

	wallet "github.com/skycoin/skycoin/src/wallet"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_wallet_NewError
func SKY_wallet_NewError(_err error) (____error_code uint32) {
	err := _err
	____return_err := wallet.NewError(err)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_wallet_NewWallet
func SKY_wallet_NewWallet(_wltName string, _opts C.Options__Handle, _arg2 *C.Wallet__Handle) (____error_code uint32) {
	__opts, okopts := lookupOptionsHandle(_opts)
	if !okopts {
		____error_code = SKY_BAD_HANDLE
		return
	}
	opts := *__opts
	__arg2, ____return_err := wallet.NewWallet(_wltName, opts)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerWalletHandle(__arg2)
	}
	return
}

//export SKY_wallet_Wallet_Lock
func SKY_wallet_Wallet_Lock(_w C.Wallet__Handle, _password []byte, _cryptoType string) (____error_code uint32) {
	w, okw := lookupWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	password := *(*[]byte)(unsafe.Pointer(&_password))
	cryptoType := wallet.CryptoType(_cryptoType)
	____return_err := w.Lock(password, cryptoType)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_wallet_Wallet_Unlock
func SKY_wallet_Wallet_Unlock(_w C.Wallet__Handle, _password []byte, _arg1 *C.Wallet__Handle) (____error_code uint32) {
	w, okw := lookupWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	password := *(*[]byte)(unsafe.Pointer(&_password))
	__arg1, ____return_err := w.Unlock(password)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerWalletHandle(__arg1)
	}
	return
}

//export SKY_wallet_Load
func SKY_wallet_Load(_wltFile string, _arg1 *C.Wallet__Handle) (____error_code uint32) {
	wltFile := _wltFile
	__arg1, ____return_err := wallet.Load(wltFile)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerWalletHandle(__arg1)
	}
	return
}

//export SKY_wallet_Wallet_Save
func SKY_wallet_Wallet_Save(_w C.Wallet__Handle, _dir string) (____error_code uint32) {
	w, okw := lookupWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	dir := _dir
	____return_err := wallet.Save(*w, dir)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
