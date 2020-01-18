package main

import cli "github.com/SkycoinProject/skycoin/src/cli"

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cli_GetWalletOutputsFromFile
func SKY_cli_GetWalletOutputsFromFile(_c *C.GetOutputser__Handle, _walletFile string, _arg2 *C.UnspentOutputsSummary__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	walletFile := _walletFile
	__arg2, ____return_err := cli.GetWalletOutputsFromFile(c, walletFile)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerUnspentOutputsSummaryHandle(__arg2)
	}
	return
}

//export SKY_cli_GetWalletOutputs
func SKY_cli_GetWalletOutputs(_c *C.GetOutputser__Handle, _wlt *C.Wallet__Handle, _arg2 *C.UnspentOutputsSummary__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	__wlt, okwlt := lookupWalletHandle(*_wlt)
	if !okwlt {
		____error_code = SKY_BAD_HANDLE
		return
	}
	wlt := *__wlt
	__arg2, ____return_err := cli.GetWalletOutputs(c, wlt)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerUnspentOutputsSummaryHandle(__arg2)
	}
	return
}
