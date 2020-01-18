package main

import cli "github.com/SkycoinProject/skycoin/src/cli"

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cli_AddPrivateKey
func SKY_cli_AddPrivateKey(_wlt *C.CollectionWallet__Handle, _key string) (____error_code uint32) {
	wlt, okwlt := lookupCollectionWalletHandle(*_wlt)
	if !okwlt {
		____error_code = SKY_BAD_HANDLE
		return
	}
	key := _key
	____return_err := cli.AddPrivateKey(wlt, key)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_cli_AddPrivateKeyToFile
func SKY_cli_AddPrivateKeyToFile(_walletFile, _key string, _pr *C.PasswordReader__Handle) (____error_code uint32) {
	walletFile := _walletFile
	key := _key
	__pr, okpr := lookupPasswordReaderHandle(*_pr)
	if !okpr {
		____error_code = SKY_BAD_HANDLE
		return
	}
	pr := *__pr
	____return_err := cli.AddPrivateKeyToFile(walletFile, key, pr)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
