package main

import (
	"unsafe"

	cli "github.com/SkycoinProject/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cli_CheckWalletBalance
func SKY_cli_CheckWalletBalance(_c *C.GetOutputser__Handle, _walletFile string, _arg2 *C.BalanceResult__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	walletFile := _walletFile
	__arg2, ____return_err := cli.CheckWalletBalance(c, walletFile)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerBalanceResultHandle(__arg2)
	}
	return
}

//export SKY_cli_GetBalanceOfAddresses
func SKY_cli_GetBalanceOfAddresses(_c *C.GetOutputser__Handle, _addrs []string, _arg2 *C.BalanceResult__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	addrs := *(*[]string)(unsafe.Pointer(&_addrs))
	__arg2, ____return_err := cli.GetBalanceOfAddresses(c, addrs)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerBalanceResultHandle(__arg2)
	}
	return
}
