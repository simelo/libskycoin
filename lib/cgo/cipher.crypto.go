package main

import (
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
)

/*

  #include <string.h>
  #include <stdlib.h>
  #include <stdbool.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cipher_RandByte
func SKY_cipher_RandByte(_n int, _arg1 *C.GoSlice_) (____error_code uint32) {
	n := _n
	__arg1 := cipher.RandByte(n)
	copyToGoSlice(reflect.ValueOf(__arg1), _arg1)
	return
}

//export SKY_cipher_NewPubKey
func SKY_cipher_NewPubKey(_b []byte, _arg1 *C.cipher__PubKey) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.NewPubKey(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofPubKey))
	}
	return
}

//export SKY_cipher_PubKeyFromHex
func SKY_cipher_PubKeyFromHex(_s string, _arg1 *C.cipher__PubKey) (____error_code uint32) {
	s := _s
	__arg1, ____return_err := cipher.PubKeyFromHex(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofPubKey))
	}
	return
}

//export SKY_cipher_PubKeyFromSecKey
func SKY_cipher_PubKeyFromSecKey(_seckey *C.cipher__SecKey, _arg1 *C.cipher__PubKey) (____error_code uint32) {
	seckey := *(*cipher.SecKey)(unsafe.Pointer(_seckey))
	__arg1, ____return_err := cipher.PubKeyFromSecKey(seckey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofPubKey))
	}
	return
}

//export SKY_cipher_PubKeyFromSig
func SKY_cipher_PubKeyFromSig(_sig *C.cipher__Sig, _hash *C.cipher__SHA256, _arg2 *C.cipher__PubKey) (____error_code uint32) {
	sig := *(*cipher.Sig)(unsafe.Pointer(_sig))
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	__arg2, ____return_err := cipher.PubKeyFromSig(sig, hash)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofPubKey))
	}
	return
}

//export SKY_cipher_PubKey_Verify
func SKY_cipher_PubKey_Verify(_pk *C.cipher__PubKey) (____error_code uint32) {
	pk := *(*cipher.PubKey)(unsafe.Pointer(_pk))
	____return_err := pk.Verify()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_PubKey_Hex
func SKY_cipher_PubKey_Hex(_pk *C.cipher__PubKey, _arg0 *C.GoString_) (____error_code uint32) {
	pk := *(*cipher.PubKey)(unsafe.Pointer(_pk))
	__arg0 := pk.Hex()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_PubKey_Null
func SKY_cipher_PubKey_Null(_pk *C.cipher__PubKey, _arg0 *bool) (____error_code uint32) {
	pk := *(*cipher.PubKey)(unsafe.Pointer(_pk))
	__arg0 := pk.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_NewSecKey
func SKY_cipher_NewSecKey(_b []byte, _arg1 *C.cipher__SecKey) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.NewSecKey(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSecKey))
	}
	return
}

//export SKY_cipher_SecKeyFromHex
func SKY_cipher_SecKeyFromHex(_s string, _arg1 *C.cipher__SecKey) (____error_code uint32) {
	s := _s
	__arg1, ____return_err := cipher.SecKeyFromHex(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSecKey))
	}
	return
}

//export SKY_cipher_SecKey_Verify
func SKY_cipher_SecKey_Verify(_sk *C.cipher__SecKey) (____error_code uint32) {
	sk := *(*cipher.SecKey)(unsafe.Pointer(_sk))
	____return_err := sk.Verify()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_SecKey_Hex
func SKY_cipher_SecKey_Hex(_sk *C.cipher__SecKey, _arg0 *C.GoString_) (____error_code uint32) {
	sk := *(*cipher.SecKey)(unsafe.Pointer(_sk))
	__arg0 := sk.Hex()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_SecKey_Null
func SKY_cipher_SecKey_Null(_sk *C.cipher__SecKey, _arg0 *bool) (____error_code uint32) {
	sk := *(*cipher.SecKey)(unsafe.Pointer(_sk))
	__arg0 := sk.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_ECDH
func SKY_cipher_ECDH(_pub *C.cipher__PubKey, _sec *C.cipher__SecKey, _arg2 *C.GoSlice_) (____error_code uint32) {
	pub := *(*cipher.PubKey)(unsafe.Pointer(_pub))
	sec := *(*cipher.SecKey)(unsafe.Pointer(_sec))
	__arg2, ____return_err := cipher.ECDH(pub, sec)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg2), _arg2)
	}
	return
}

//export SKY_cipher_NewSig
func SKY_cipher_NewSig(_b []byte, _arg1 *C.cipher__Sig) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.NewSig(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSig))
	}
	return
}

//export SKY_cipher_SigFromHex
func SKY_cipher_SigFromHex(_s string, _arg1 *C.cipher__Sig) (____error_code uint32) {
	s := _s
	__arg1, ____return_err := cipher.SigFromHex(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSig))
	}
	return
}

//export SKY_cipher_Sig_String
func SKY_cipher_Sig_String(_s *C.cipher__Sig, _arg0 *C.GoString_) (____error_code uint32) {
	s := *(*cipher.Sig)(unsafe.Pointer(_s))
	__arg0 := s.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_Sig_Null
func SKY_cipher_Sig_Null(_s *C.cipher__Sig, _arg0 *bool) (____error_code uint32) {
	s := *(*cipher.Sig)(unsafe.Pointer(_s))
	__arg0 := s.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_Sig_Hex
func SKY_cipher_Sig_Hex(_s *C.cipher__Sig, _arg0 *C.GoString_) (____error_code uint32) {
	s := *(*cipher.Sig)(unsafe.Pointer(_s))
	__arg0 := s.Hex()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_SignHash
func SKY_cipher_SignHash(_hash *C.cipher__SHA256, _sec *C.cipher__SecKey, _arg2 *C.cipher__Sig) (____error_code uint32) {
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	sec := *(*cipher.SecKey)(unsafe.Pointer(_sec))
	__arg2, ____return_err := cipher.SignHash(hash, sec)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofSig))
	}
	return
}

//export SKY_cipher_VerifyAddressSignedHash
func SKY_cipher_VerifyAddressSignedHash(_address *C.cipher__Address, _sig *C.cipher__Sig, _hash *C.cipher__SHA256) (____error_code uint32) {
	address := *inplaceAddress(_address)
	sig := *(*cipher.Sig)(unsafe.Pointer(_sig))
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	____return_err := cipher.VerifyAddressSignedHash(address, sig, hash)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_VerifyPubKeySignedHash
func SKY_cipher_VerifyPubKeySignedHash(_pubkey *C.cipher__PubKey, _sig *C.cipher__Sig, _hash *C.cipher__SHA256) (____error_code uint32) {
	pubkey := *(*cipher.PubKey)(unsafe.Pointer(_pubkey))
	sig := *(*cipher.Sig)(unsafe.Pointer(_sig))
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	____return_err := cipher.VerifyPubKeySignedHash(pubkey, sig, hash)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_VerifySignatureRecoverPubKey
func SKY_cipher_VerifySignatureRecoverPubKey(_sig *C.cipher__Sig, _hash *C.cipher__SHA256) (____error_code uint32) {
	sig := *(*cipher.Sig)(unsafe.Pointer(_sig))
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	____return_err := cipher.VerifySignatureRecoverPubKey(sig, hash)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_GenerateKeyPair
func SKY_cipher_GenerateKeyPair(_arg0 *C.cipher__PubKey, _arg1 *C.cipher__SecKey) (____error_code uint32) {
	__arg0, __arg1 := cipher.GenerateKeyPair()
	copyToBuffer(reflect.ValueOf(__arg0[:]), unsafe.Pointer(_arg0), uint(SizeofPubKey))
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSecKey))
	return
}

//export SKY_cipher_GenerateDeterministicKeyPair
func SKY_cipher_GenerateDeterministicKeyPair(_seed []byte, _arg1 *C.cipher__PubKey, _arg2 *C.cipher__SecKey) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	__arg1, __arg2, ____return_err := cipher.GenerateDeterministicKeyPair(seed)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofPubKey))
		copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofSecKey))
	}
	return
}

//export SKY_cipher_DeterministicKeyPairIterator
func SKY_cipher_DeterministicKeyPairIterator(_seed []byte, _arg1 *C.GoSlice_, _arg2 *C.cipher__PubKey, _arg3 *C.cipher__SecKey) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	__arg1, __arg2, __arg3, ____return_err := cipher.DeterministicKeyPairIterator(seed)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg1), _arg1)
		copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofPubKey))
		copyToBuffer(reflect.ValueOf(__arg3[:]), unsafe.Pointer(_arg3), uint(SizeofSecKey))
	}
	return
}

//export SKY_cipher_GenerateDeterministicKeyPairs
func SKY_cipher_GenerateDeterministicKeyPairs(_seed []byte, _n int, _arg2 *C.GoSlice_) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	n := _n
	__arg2, ____return_err := cipher.GenerateDeterministicKeyPairs(seed, n)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg2), _arg2)
	}
	return
}

//export SKY_cipher_GenerateDeterministicKeyPairsSeed
func SKY_cipher_GenerateDeterministicKeyPairsSeed(_seed []byte, _n int, _arg2 *C.GoSlice_, _arg3 *C.GoSlice_) (____error_code uint32) {
	seed := *(*[]byte)(unsafe.Pointer(&_seed))
	n := _n
	__arg2, __arg3, ____return_err := cipher.GenerateDeterministicKeyPairsSeed(seed, n)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg2), _arg2)
		copyToGoSlice(reflect.ValueOf(__arg3), _arg3)
	}
	return
}

//export SKY_cipher_CheckSecKey
func SKY_cipher_CheckSecKey(_seckey *C.cipher__SecKey) (____error_code uint32) {
	seckey := *(*cipher.SecKey)(unsafe.Pointer(_seckey))
	____return_err := cipher.CheckSecKey(seckey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_CheckSecKeyHash
func SKY_cipher_CheckSecKeyHash(_seckey *C.cipher__SecKey, _hash *C.cipher__SHA256) (____error_code uint32) {
	seckey := *(*cipher.SecKey)(unsafe.Pointer(_seckey))
	hash := *(*cipher.SHA256)(unsafe.Pointer(_hash))
	____return_err := cipher.CheckSecKeyHash(seckey, hash)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
