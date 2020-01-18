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

//export SKY_cipher_Ripemd160_Set
func SKY_cipher_Ripemd160_Set(_rd *C.cipher__Ripemd160, _b []byte) (____error_code uint32) {
	rd := (*cipher.Ripemd160)(unsafe.Pointer(_rd))
	b := *(*[]byte)(unsafe.Pointer(&_b))
	____return_err := rd.Set(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_Ripemd160FromBytes
func SKY_cipher_Ripemd160FromBytes(_b []byte, _arg1 *C.cipher__Ripemd160) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.Ripemd160FromBytes(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofRipemd160))
	}
	return
}

//export SKY_cipher_HashRipemd160
func SKY_cipher_HashRipemd160(_data []byte, _arg1 *C.cipher__Ripemd160) (____error_code uint32) {
	data := *(*[]byte)(unsafe.Pointer(&_data))
	__arg1 := cipher.HashRipemd160(data)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofRipemd160))
	return
}

//export SKY_cipher_SHA256_Set
func SKY_cipher_SHA256_Set(_g *C.cipher__SHA256, _b []byte) (____error_code uint32) {
	g := (*cipher.SHA256)(unsafe.Pointer(_g))
	b := *(*[]byte)(unsafe.Pointer(&_b))
	____return_err := g.Set(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_SHA256_String
func SKY_cipher_SHA256_String(_g *C.cipher__SHA256, _arg0 *C.GoString_) (____error_code uint32) {
	g := *(*cipher.SHA256)(unsafe.Pointer(_g))
	__arg0 := g.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_SHA256_Hex
func SKY_cipher_SHA256_Hex(_g *C.cipher__SHA256, _arg0 *C.GoString_) (____error_code uint32) {
	g := *(*cipher.SHA256)(unsafe.Pointer(_g))
	__arg0 := g.Hex()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_SHA256_Null
func SKY_cipher_SHA256_Null(_g *C.cipher__SHA256, _arg0 *bool) (____error_code uint32) {
	g := *(*cipher.SHA256)(unsafe.Pointer(_g))
	__arg0 := g.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_SHA256_Xor
func SKY_cipher_SHA256_Xor(_g *C.cipher__SHA256, _b *C.cipher__SHA256, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	g := (*cipher.SHA256)(unsafe.Pointer(_g))
	b := *(*cipher.SHA256)(unsafe.Pointer(_b))
	__arg1 := g.Xor(b)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	return
}

//export SKY_cipher_SHA256FromHex
func SKY_cipher_SHA256FromHex(_hs string, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	hs := _hs
	__arg1, ____return_err := cipher.SHA256FromHex(hs)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	}
	return
}

//export SKY_cipher_SHA256FromBytes
func SKY_cipher_SHA256FromBytes(_b []byte, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.SHA256FromBytes(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	}
	return
}

//export SKY_cipher_SumSHA256
func SKY_cipher_SumSHA256(_b []byte, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1 := cipher.SumSHA256(b)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	return
}

//export SKY_cipher_DoubleSHA256
func SKY_cipher_DoubleSHA256(_b []byte, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1 := cipher.DoubleSHA256(b)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	return
}

//export SKY_cipher_AddSHA256
func SKY_cipher_AddSHA256(_a *C.cipher__SHA256, _b *C.cipher__SHA256, _arg2 *C.cipher__SHA256) (____error_code uint32) {
	a := *(*cipher.SHA256)(unsafe.Pointer(_a))
	b := *(*cipher.SHA256)(unsafe.Pointer(_b))
	__arg2 := cipher.AddSHA256(a, b)
	copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofSHA256))
	return
}

//export SKY_cipher_Merkle
func SKY_cipher_Merkle(_h0 []C.cipher__SHA256, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	h0 := *(*[]cipher.SHA256)(unsafe.Pointer(&_h0))
	__arg1 := cipher.Merkle(h0)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSHA256))
	return
}
