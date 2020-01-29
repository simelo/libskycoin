package main

import (
	"reflect"
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

//export SKY_bip32_NewError
func SKY_bip32_NewError(_err error) (____error_code uint32) {
	err := _err
	____return_err := bip32.NewError(err)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_bip32_Error_ImpossibleChild
func SKY_bip32_Error_ImpossibleChild(_err *C.bip32__Error, _arg0 *bool) (____error_code uint32) {
	err := *(*bip32.Error)(unsafe.Pointer(_err))
	__arg0 := err.ImpossibleChild()
	*_arg0 = __arg0
	return
}

//export SKY_bip32_NewImpossibleChildError
func SKY_bip32_NewImpossibleChildError(_err error, _childNumber uint32) (____error_code uint32) {
	err := _err
	childNumber := _childNumber
	____return_err := bip32.NewImpossibleChildError(err, childNumber)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_bip32_IsImpossibleChildError
func SKY_bip32_IsImpossibleChildError(_err error, _arg1 *bool) (____error_code uint32) {
	err := _err
	__arg1 := bip32.IsImpossibleChildError(err)
	*_arg1 = __arg1
	return
}

//export SKY_bip32_NewMasterKey
func SKY_bip32_NewMasterKey(_seed []byte, _arg1 *C.PrivateKey__Handle) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	__arg1, ____return_err := bip32.NewMasterKey(seed)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPrivateKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_NewPrivateKeyFromPath
func SKY_bip32_NewPrivateKeyFromPath(_seed []byte, _p string, _arg2 *C.PrivateKey__Handle) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	p := _p
	__arg2, ____return_err := bip32.NewPrivateKeyFromPath(seed, p)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerPrivateKeyHandle(__arg2)
	}
	return
}

//export SKY_bip32_PrivateKey_DeriveSubpath
func SKY_bip32_PrivateKey_DeriveSubpath(_k *C.PrivateKey__Handle, _nodes []C.bip32__PathNode, _arg1 *C.PrivateKey__Handle) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	nodes := *(*[]bip32.PathNode)(unsafe.Pointer(&_nodes))
	__arg1, ____return_err := k.DeriveSubpath(nodes)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPrivateKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_PrivateKey_PublicKey
func SKY_bip32_PrivateKey_PublicKey(_k *C.PrivateKey__Handle, _arg0 *C.PublicKey__Handle) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.PublicKey()
	*_arg0 = registerPublicKeyHandle(__arg0)
	return
}

//export SKY_bip32_PrivateKey_Fingerprint
func SKY_bip32_PrivateKey_Fingerprint(_k *C.PrivateKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Fingerprint()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_Identifier
func SKY_bip32_PrivateKey_Identifier(_k *C.PrivateKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Identifier()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_Fingerprint
func SKY_bip32_PublicKey_Fingerprint(_k *C.PublicKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPublicKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Fingerprint()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_Identifier
func SKY_bip32_PublicKey_Identifier(_k *C.PublicKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPublicKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Identifier()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_NewPrivateChildKey
func SKY_bip32_PrivateKey_NewPrivateChildKey(_k *C.PrivateKey__Handle, _childIdx uint32, _arg1 *C.PrivateKey__Handle) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	childIdx := _childIdx
	__arg1, ____return_err := k.NewPrivateChildKey(childIdx)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPrivateKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_PrivateKey_NewPublicChildKey
func SKY_bip32_PrivateKey_NewPublicChildKey(_k *C.PrivateKey__Handle, _childIdx uint32, _arg1 *C.PublicKey__Handle) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	childIdx := _childIdx
	__arg1, ____return_err := k.NewPublicChildKey(childIdx)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPublicKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_PublicKey_NewPublicChildKey
func SKY_bip32_PublicKey_NewPublicChildKey(_k *C.PublicKey__Handle, _childIdx uint32, _arg1 *C.PublicKey__Handle) (____error_code uint32) {
	k, okk := lookupPublicKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	childIdx := _childIdx
	__arg1, ____return_err := k.NewPublicChildKey(childIdx)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPublicKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_PrivateKey_Serialize
func SKY_bip32_PrivateKey_Serialize(_k *C.PrivateKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Serialize()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_Serialize
func SKY_bip32_PublicKey_Serialize(_k *C.PublicKey__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	k, okk := lookupPublicKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.Serialize()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_String
func SKY_bip32_PrivateKey_String(_k *C.PrivateKey__Handle, _arg0 *C.GoString_) (____error_code uint32) {
	k, okk := lookupPrivateKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_bip32_PublicKey_String
func SKY_bip32_PublicKey_String(_k *C.PublicKey__Handle, _arg0 *C.GoString_) (____error_code uint32) {
	k, okk := lookupPublicKeyHandle(*_k)
	if !okk {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := k.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_bip32_DeserializeEncodedPrivateKey
func SKY_bip32_DeserializeEncodedPrivateKey(_xprv string, _arg1 *C.PrivateKey__Handle) (____error_code uint32) {
	xprv := _xprv
	__arg1, ____return_err := bip32.DeserializeEncodedPrivateKey(xprv)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPrivateKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_DeserializePrivateKey
func SKY_bip32_DeserializePrivateKey(_data []byte, _arg1 *C.PrivateKey__Handle) (____error_code uint32) {
	data := *(*[]byte)(unsafe.Pointer(&_data))
	__arg1, ____return_err := bip32.DeserializePrivateKey(data)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPrivateKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_DeserializeEncodedPublicKey
func SKY_bip32_DeserializeEncodedPublicKey(_xpub string, _arg1 *C.PublicKey__Handle) (____error_code uint32) {
	xpub := _xpub
	__arg1, ____return_err := bip32.DeserializeEncodedPublicKey(xpub)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPublicKeyHandle(__arg1)
	}
	return
}

//export SKY_bip32_DeserializePublicKey
func SKY_bip32_DeserializePublicKey(_data []byte, _arg1 *C.PublicKey__Handle) (____error_code uint32) {
	data := *(*[]byte)(unsafe.Pointer(&_data))
	__arg1, ____return_err := bip32.DeserializePublicKey(data)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerPublicKeyHandle(__arg1)
	}
	return
}

// Helpers

//export SKY_bip32_PrivateKey_GetKey
func SKY_bip32_PrivateKey_GetKey(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := pk.Key
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_GetKey
func SKY_bip32_PublicKey_GetKey(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := pk.Key
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_GetDepth
func SKY_bip32_PrivateKey_GetDepth(_pk C.PrivateKey__Handle, _arg0 *byte) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Depth
	*_arg0 = arg0
	return
}

//export SKY_bip32_PublicKey_GetDepth
func SKY_bip32_PublicKey_GetDepth(_pk C.PublicKey__Handle, _arg0 *byte) (___error_code uint32) {
	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := pk.Depth
	*_arg0 = arg0
	return
}

//export SKY_bip32_PrivateKey_ChildNumber
func SKY_bip32_PrivateKey_ChildNumber(_pk C.PrivateKey__Handle, _arg0 *uint32) (___error_code uint32) {

	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.ChildNumber()
	*_arg0 = uint32(__arg0)
	return
}

//export SKY_bip32_PublicKey_ChildNumber
func SKY_bip32_PublicKey_ChildNumber(_pk C.PublicKey__Handle, _arg0 *uint32) (___error_code uint32) {

	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := uint32(pk.ChildNumber())
	*_arg0 = __arg0
	return
}

//export SKY_bip32_PrivateKey_GetChainCode
func SKY_bip32_PrivateKey_GetChainCode(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.ChainCode
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_GetChainCode
func SKY_bip32_PublicKey_GetChainCode(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.ChainCode
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_GetVersion
func SKY_bip32_PrivateKey_GetVersion(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.Version
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_GetVersion
func SKY_bip32_PublicKey_GetVersion(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	copyToGoSlice(reflect.ValueOf(pk.Version), _arg0)
	return
}

//export SKY_bip32_PrivateKey_GetParentFingerprint
func SKY_bip32_PrivateKey_GetParentFingerprint(_pk C.PrivateKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPrivateKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.ParentFingerprint
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PublicKey_GetParentFingerprint
func SKY_bip32_PublicKey_GetParentFingerprint(_pk C.PublicKey__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {

	pk, okpk := lookupPublicKeyHandle(_pk)

	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	__arg0 := pk.ParentFingerprint
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_bip32_PrivateKey_Publickey
func SKY_bip32_PrivateKey_Publickey(_pk C.PrivateKey__Handle, _pp *C.PublicKey__Handle) (___error_code uint32) {
	pk, okpk := lookupPrivateKeyHandle(_pk)
	if !okpk {
		___error_code = SKY_BAD_HANDLE
		return
	}

	pp := pk.PublicKey()
	*_pp = registerPublicKeyHandle(pp)
	return
}