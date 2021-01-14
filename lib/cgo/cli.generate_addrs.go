package main

import (
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	cli "github.com/SkycoinProject/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_cli_GenerateAddressesInFile
func SKY_cli_GenerateAddressesInFile(_walletFile string, _num uint64, pwd C.PasswordReader__Handle, _arg3 *C.GoSlice_) (____error_code uint32) {
	walletFile := _walletFile
	num := _num
	pr, okc := lookupPasswordReaderHandle(pwd)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg3, ____return_err := cli.GenerateAddressesInFile(walletFile, num, *pr)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg3), _arg3)
	}
	return
}

//export SKY_cli_FormatAddressesAsJSON
func SKY_cli_FormatAddressesAsJSON(_addrs []C.cipher__Address, _arg1 *string) (____error_code uint32) {
	addrs := *(*[]cipher.Address)(unsafe.Pointer(&_addrs))
	__addrs := toAddresserArray(addrs)
	__arg1, ____return_err := cli.FormatAddressesAsJSON(__addrs)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_cli_FormatAddressesAsJoinedArray
func SKY_cli_FormatAddressesAsJoinedArray(_addrs []C.cipher__Address, _arg1 *string) (____error_code uint32) {
	addrs := *(*[]cipher.Address)(unsafe.Pointer(&_addrs))
	__addrs := toAddresserArray(addrs)
	__arg1 := cli.FormatAddressesAsJoinedArray(__addrs)
	*_arg1 = __arg1
	return
}

//export SKY_cli_AddressesToStrings
func SKY_cli_AddressesToStrings(_addrs []C.cipher__Address, _arg1 *[]string) (____error_code uint32) {
	addrs := *(*[]cipher.Address)(unsafe.Pointer(&_addrs))
	__addrs := toAddresserArray(addrs)
	*_arg1 = cli.AddressesToStrings(__addrs)

	return
}
