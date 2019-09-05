package main

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_wallet_MetaWallet_IsEncrypted
func SKY_wallet_MetaWallet_IsEncrypted(_w C.MetaWallet__Handle, _arg0 *bool) (____error_code uint32) {
	w, okw := lookupMetaWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := w.IsEncrypted()
	*_arg0 = __arg0
	return
}

//export SKY_wallet_MetaWallet_Label
func SKY_wallet_MetaWallet_Label(_w C.MetaWallet__Handle, _arg0 *string) (____error_code uint32) {
	w, okw := lookupMetaWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = w.Label()
	return
}

//export SKY_wallet_MetaWallet_Filename
func SKY_wallet_MetaWallet_Filename(_w C.MetaWallet__Handle, _arg0 *string) (____error_code uint32) {
	w, okw := lookupMetaWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = w.Filename()
	return
}

//export SKY_wallet_MetaWallet_Version
func SKY_wallet_MetaWallet_Version(_w C.MetaWallet__Handle, _arg0 *string) (____error_code uint32) {
	w, okw := lookupMetaWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = w.Version()

	return
}

//export SKY_wallet_MetaWallet_Type
func SKY_wallet_MetaWallet_Type(_w C.MetaWallet__Handle, _arg0 *string) (____error_code uint32) {
	w, okw := lookupMetaWalletHandle(_w)
	if !okw {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = w.Type()
	return
}
