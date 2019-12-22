package main

import (
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_cipher_BitcoinPubKeyRipemd160
func SKY_cipher_BitcoinPubKeyRipemd160(_pubKey *C.cipher__PubKey, _arg1 *C.cipher__Ripemd160) (____error_code uint32) {
	____error_code = 0
	pubKey := *(*cipher.PubKey)(unsafe.Pointer(_pubKey))
	__arg1 := cipher.BitcoinPubKeyRipemd160(pubKey)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofRipemd160))
	return
}

//export SKY_cipher_BitcoinAddressFromPubKey
func SKY_cipher_BitcoinAddressFromPubKey(_pubKey *C.cipher__PubKey, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	pubKey := *(*cipher.PubKey)(unsafe.Pointer(_pubKey))
	__arg1 := cipher.BitcoinAddressFromPubKey(pubKey)
	*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_cipher_BitcoinAddressFromSecKey
func SKY_cipher_BitcoinAddressFromSecKey(_secKey *C.cipher__SecKey, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	secKey := *(*cipher.SecKey)(unsafe.Pointer(_secKey))
	__arg1, ____return_err := cipher.BitcoinAddressFromSecKey(secKey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_MustBitcoinAddressFromSecKey
func SKY_cipher_MustBitcoinAddressFromSecKey(_secKey *C.cipher__SecKey, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	secKey := *(*cipher.SecKey)(unsafe.Pointer(_secKey))
	__arg1 := cipher.MustBitcoinAddressFromSecKey(secKey)
	*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_cipher_DecodeBase58BitcoinAddress
func SKY_cipher_DecodeBase58BitcoinAddress(_addr string, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	addr := _addr
	__arg1, ____return_err := cipher.DecodeBase58BitcoinAddress(addr)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_MustDecodeBase58BitcoinAddress
func SKY_cipher_MustDecodeBase58BitcoinAddress(_addr string, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	addr := _addr
	__arg1 := cipher.MustDecodeBase58BitcoinAddress(addr)
	*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_cipher_BitcoinAddressFromBytes
func SKY_cipher_BitcoinAddressFromBytes(_b []byte, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := cipher.BitcoinAddressFromBytes(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_cipher_MustBitcoinAddressFromBytes
func SKY_cipher_MustBitcoinAddressFromBytes(_b []byte, _arg1 *C.cipher__BitcoinAddress) (____error_code uint32) {
	____error_code = 0
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1 := cipher.MustBitcoinAddressFromBytes(b)
	*_arg1 = *(*C.cipher__BitcoinAddress)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_cipher_BitcoinAddress_Null
func SKY_cipher_BitcoinAddress_Null(_addr *C.cipher__BitcoinAddress, _arg0 *bool) (____error_code uint32) {
	____error_code = 0
	addr := *(*cipher.BitcoinAddress)(unsafe.Pointer(_addr))
	__arg0 := addr.Null()
	*_arg0 = __arg0
	return
}

//export SKY_cipher_BitcoinAddress_Bytes
func SKY_cipher_BitcoinAddress_Bytes(_addr *C.cipher__BitcoinAddress, _arg0 *C.GoSlice_) (____error_code uint32) {
	____error_code = 0
	addr := *(*cipher.BitcoinAddress)(unsafe.Pointer(_addr))
	__arg0 := addr.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_cipher_BitcoinAddress_Verify
func SKY_cipher_BitcoinAddress_Verify(_addr *C.cipher__BitcoinAddress, _key *C.cipher__PubKey) (____error_code uint32) {
	____error_code = 0
	addr := *(*cipher.BitcoinAddress)(unsafe.Pointer(_addr))
	key := *(*cipher.PubKey)(unsafe.Pointer(_key))
	____return_err := addr.Verify(key)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cipher_BitcoinAddress_String
func SKY_cipher_BitcoinAddress_String(_addr *C.cipher__BitcoinAddress, _arg0 *C.GoString_) (____error_code uint32) {
	____error_code = 0
	addr := *(*cipher.BitcoinAddress)(unsafe.Pointer(_addr))
	__arg0 := addr.String()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cipher_BitcoinAddress_Checksum
func SKY_cipher_BitcoinAddress_Checksum(_addr *C.cipher__BitcoinAddress, _arg0 *C.cipher__Checksum) (____error_code uint32) {
	____error_code = 0
	addr := *(*cipher.BitcoinAddress)(unsafe.Pointer(_addr))
	__arg0 := addr.Checksum()
	*_arg0 = *(*C.cipher__Checksum)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_cipher_BitcoinWalletImportFormatFromSeckey
func SKY_cipher_BitcoinWalletImportFormatFromSeckey(_seckey *C.cipher__SecKey, _arg1 *C.GoString_) (____error_code uint32) {
	____error_code = 0
	seckey := *(*cipher.SecKey)(unsafe.Pointer(_seckey))
	__arg1 := cipher.BitcoinWalletImportFormatFromSeckey(seckey)
	copyString(__arg1, _arg1)
	return
}

//export SKY_cipher_SecKeyFromBitcoinWalletImportFormat
func SKY_cipher_SecKeyFromBitcoinWalletImportFormat(_input string, _arg1 *C.cipher__SecKey) (____error_code uint32) {
	____error_code = 0
	input := _input
	__arg1, ____return_err := cipher.SecKeyFromBitcoinWalletImportFormat(input)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSecKey))
	}
	return
}

//export SKY_cipher_MustSecKeyFromBitcoinWalletImportFormat
func SKY_cipher_MustSecKeyFromBitcoinWalletImportFormat(_input string, _arg1 *C.cipher__SecKey) (____error_code uint32) {
	____error_code = 0
	input := _input
	__arg1 := cipher.MustSecKeyFromBitcoinWalletImportFormat(input)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofSecKey))
	return
}
