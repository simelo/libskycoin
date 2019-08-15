package main

import (
	"reflect"
	"unsafe"

	"github.com/skycoin/skycoin/src/cipher/bip32"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_bip32_NewMasterKey
func SKY_bip32_NewMasterKey(_seed []byte, _pk *C.PrivateKey__Handle) (___error_code uint32) {

	pk, ___return_error := bip32.NewMasterKey(_seed)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_pk = registerPrivateKeyHandle(pk)
	}
	return
}

//export SKY_bip32_NewPrivateKeyFromPath
func SKY_bip32_NewPrivateKeyFromPath(seed []byte, p string, _pk *C.PrivateKey__Handle) (___error_code uint32) {

	pk, ___return_error := bip32.NewPrivateKeyFromPath(seed, p)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_pk = registerPrivateKeyHandle(pk)
	}
	return
}

//export SKY_bip32_PrivateKey_DeriveSubpath
func SKY_bip32_PrivateKey_DeriveSubpath(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_, _pk1 *C.PrivateKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	node := *(*[]bip32.PathNode)(unsafe.Pointer(&_arg0))
	pk1, ____return_err := pk.DeriveSubpath(node)
	___error_code = libErrorCode(____return_err)

	if ____return_err == nil {
		*_pk1 = registerPrivateKeyHandle(pk1)
	}
	return
}

//export SKY_bip32_Private_Publickey
func SKY_bip32_Private_Publickey(_pk C.PrivateKey__Handle, _pp *C.PublicKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	pp := pk.PublicKey()
	*_pp = registerPublicKeyHandle(pp)
	return
}

//export SKY_bip32_Private_Fingerprint
func SKY_bip32_Private_Fingerprint(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Fingerprint()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Private_Identifier
func SKY_bip32_Private_Identifier(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Identifier()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Public_Fingerprint
func SKY_bip32_Public_Fingerprint(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Fingerprint()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Public_Identifier
func SKY_bip32_Public_Identifier(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Identifier()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Private_NewPrivateChildKey
func SKY_bip32_Private_NewPrivateChildKey(_pk C.PrivateKey__Handle, childIdx uint32, _arg0 *C.PrivateKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ___return_error := pk.NewPrivateChildKey(childIdx)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_arg0 = registerPrivateKeyHandle(__arg0)
	}
	return
}

//export SKY_bip32_Private_NewPublicChildKey
func SKY_bip32_Private_NewPublicChildKey(_pk C.PrivateKey__Handle, childIdx uint32, _arg0 *C.PublicKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ___return_error := pk.NewPublicChildKey(childIdx)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_arg0 = registerPublicKeyHandle(__arg0)
	}
	return
}

//export SKY_bip32_Public_NewPublicChildKey
func SKY_bip32_Public_NewPublicChildKey(_pk C.PublicKey__Handle, childIdx uint32, _arg0 *C.PublicKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ___return_error := pk.NewPublicChildKey(childIdx)
	___error_code = libErrorCode(___return_error)
	if ___return_error == nil {
		*_arg0 = registerPublicKeyHandle(__arg0)
	}
	return
}

//export SKY_bip32_Private_Serialize
func SKY_bip32_Private_Serialize(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Serialize()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Public_Serialize
func SKY_bip32_Public_Serialize(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Serialize()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_bip32_Private_String
func SKY_bip32_Private_String(_pk C.PrivateKey__Handle, _arg0 *string) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = pk.String()
	return
}

//export SKY_bip32_Public_String
func SKY_bip32_Public_String(_pk C.PublicKey__Handle, _arg0 *string) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = pk.String()
	return
}

//export SKY_bip32_DeserializeEncodedPrivateKey
func SKY_bip32_DeserializeEncodedPrivateKey(_xprv string, _arg0 *C.PrivateKey__Handle) (___error_code uint32) {
	pk, ___return_err := bip32.DeserializeEncodedPrivateKey(_xprv)
	___error_code = libErrorCode(___return_err)
	if ___return_err == nil {
		*_arg0 = registerPrivateKeyHandle(pk)
	}
	return
}

//export SKY_bip32_DeserializePrivateKey
func SKY_bip32_DeserializePrivateKey(_data []byte, _arg0 *C.PrivateKey__Handle) (___error_code uint32) {

	pk, ___return_err := bip32.DeserializePrivateKey(_data)
	___error_code = libErrorCode(___return_err)
	if ___return_err == nil {
		*_arg0 = registerPrivateKeyHandle(pk)
	}
	return
}

//export SKY_bip32_DeserializeEncodedPublicKey
func SKY_bip32_DeserializeEncodedPublicKey(_xpub string, _arg0 *C.PublicKey__Handle) (___error_code uint32) {
	pk, ___return_err := bip32.DeserializeEncodedPublicKey(_xpub)
	___error_code = libErrorCode(___return_err)
	if ___return_err == nil {
		*_arg0 = registerPublicKeyHandle(pk)
	}
	return
}

//export SKY_bip32_DeserializePublicKey
func SKY_bip32_DeserializePublicKey(_data []byte, _arg0 *C.PublicKey__Handle) (___error_code uint32) {

	pk, ___return_err := bip32.DeserializePublicKey(_data)
	___error_code = libErrorCode(___return_err)
	if ___return_err == nil {
		*_arg0 = registerPublicKeyHandle(pk)
	}
	return
}
