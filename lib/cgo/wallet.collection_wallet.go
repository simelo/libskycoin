package main

import (
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	wallet "github.com/SkycoinProject/skycoin/src/wallet"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_wallet_CollectionWallet_AddEntry
func SKY_wallet_CollectionWallet_AddEntry(_w C.CollectionWallet__Handle, _entry *C.wallet__Entry) (____error_code uint32) {
	w, okw := lookupCollectionWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	entry := *(*wallet.Entry)(unsafe.Pointer(_entry))
	____return_err := w.AddEntry(entry)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_wallet_CollectionWallet_GetEntry
func SKY_wallet_CollectionWallet_GetEntry(_w C.CollectionWallet__Handle, _a *C.cipher__Address, _arg1 *C.wallet__Entry, _arg2 *bool) (____error_code uint32) {
	w, okw := lookupCollectionWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	a := *(*cipher.Address)(unsafe.Pointer(_a))
	__arg1, __arg2 := w.GetEntry(a)
	*_arg1 = *(*C.wallet__Entry)(unsafe.Pointer(&__arg1))
	*_arg2 = __arg2
	return
}

//export SKY_wallet_CollectionWallet_GetAddresses
func SKY_wallet_CollectionWallet_GetAddresses(_w C.CollectionWallet__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	w, okw := lookupCollectionWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := w.GetAddresses()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_wallet_CollectionWallet_GenerateAddresses
func SKY_wallet_CollectionWallet_GenerateAddresses(_w C.CollectionWallet__Handle, _num uint64, _arg1 *C.GoSlice_) (____error_code uint32) {
	w, okw := lookupCollectionWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	num := _num
	__arg1, ____return_err := w.GenerateAddresses(num)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg1), _arg1)
	}
	return
}

//export SKY_wallet_CollectionWallet_Validate
func SKY_wallet_CollectionWallet_Validate(_w C.CollectionWallet__Handle) (____error_code uint32) {
	w, okw := lookupCollectionWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	____return_err := w.Validate()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
