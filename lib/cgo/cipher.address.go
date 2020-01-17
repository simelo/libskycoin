package main

import (
	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	"reflect"
	"unsafe"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cipher_PubKeyRipemd160
func SKY_cipher_PubKeyRipemd160(_pubKey *C.cipher__PubKey, _arg1 *C.cipher__Ripemd160) (____error_code uint32) {
	pubKey := *(*cipher.PubKey)(unsafe.Pointer(_pubKey))
	__arg1 := cipher.PubKeyRipemd160(pubKey)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofRipemd160))
	return
}

//export SKY_cipher_AddressFromPubKey
func SKY_cipher_AddressFromPubKey(_pubKey *C.cipher__PubKey, _arg1 *C.cipher__Address) (____error_code uint32) {
	pubKey := *(*cipher.PubKey)(unsafe.Pointer(_pubKey))
	__arg1 := cipher.AddressFromPubKey(pubKey)
	*_arg1 = *(*C.cipher__Address)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_cipher_AddressFromSecKey
func SKY_cipher_AddressFromSecKey(_secKey *C.cipher__SecKey, _arg1 *C.cipher__Address) (____error_code uint32) {
	secKey := *(*cipher.SecKey)(unsafe.Pointer(_secKey))
	__arg1, ____return_err := cipher.AddressFromSecKey(secKey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__Address)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_DecodeBase58Address
func SKY_cipher_DecodeBase58Address(_addr string, _arg1 *C.cipher__Address) (____error_code uint32) {
	addr := _addr
	__arg1, ____return_err := cipher.DecodeBase58Address(addr)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__Address)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_AddressFromBytes
func SKY_cipher_AddressFromBytes(_b []byte, _arg1 *C.cipher__Address) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.AddressFromBytes(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__Address)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_Address_Null
func SKY_cipher_Address_Null(_addr *C.cipher__Address, _arg0 *bool) (____error_code uint32) {
	addr := *inplaceAddress(_addr)
	__arg0 := addr.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_Address_Bytes
func SKY_cipher_Address_Bytes(_addr *C.cipher__Address, _arg0 *C.GoSlice_) (____error_code uint32) {
	addr := *inplaceAddress(_addr)
	__arg0 := addr.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_cipher_Address_Verify
func SKY_cipher_Address_Verify(_addr *C.cipher__Address, _pubKey *C.cipher__PubKey) (____error_code uint32) {
	addr := *inplaceAddress(_addr)
	pubKey := *(*cipher.PubKey)(unsafe.Pointer(_pubKey))
	____return_err := addr.Verify(pubKey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_Address_String
func SKY_cipher_Address_String(_addr *C.cipher__Address, _arg0 *C.GoString_) (____error_code uint32) {
	addr := *inplaceAddress(_addr)
	__arg0 := addr.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_Address_Checksum
func SKY_cipher_Address_Checksum(_addr *C.cipher__Address, _arg0 *C.cipher__Checksum) (____error_code uint32) {
	addr := *inplaceAddress(_addr)
	__arg0 := addr.Checksum()
	*_arg0 = *(*C.cipher__Checksum)(unsafe.Pointer(&__arg0))
	return
}
