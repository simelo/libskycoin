package main

import (
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	cli "github.com/SkycoinProject/skycoin/src/cli"
	coin "github.com/SkycoinProject/skycoin/src/coin"
	transaction "github.com/SkycoinProject/skycoin/src/transaction"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cli_CreateRawTxnFromWallet
func SKY_cli_CreateRawTxnFromWallet(_c *C.GetOutputser__Handle, _walletFile, _chgAddr string, _toAddrs []C.cli__SendAmount, _pr *C.PasswordReader__Handle, _distParams *C.Distribution__Handle, _arg5 *C.Transaction__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	walletFile := _walletFile
	chgAddr := _chgAddr
	toAddrs := *(*[]cli.SendAmount)(unsafe.Pointer(&_toAddrs))
	__pr, okpr := lookupPasswordReaderHandle(*_pr)
	if !okpr {
		____error_code = SKY_BAD_HANDLE
		return
	}
	pr := *__pr
	__distParams, okdistParams := lookupDistributionHandle(*_distParams)
	if !okdistParams {
		____error_code = SKY_BAD_HANDLE
		return
	}
	distParams := *__distParams
	__arg5, ____return_err := cli.CreateRawTxnFromWallet(c, walletFile, chgAddr, toAddrs, pr, distParams)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg5 = registerTransactionHandle(__arg5)
	}
	return
}

//export SKY_cli_CreateRawTxnFromAddress
func SKY_cli_CreateRawTxnFromAddress(_c *C.GetOutputser__Handle, _addr, _walletFile, _chgAddr string, _toAddrs []C.cli__SendAmount, _pr *C.PasswordReader__Handle, _distParams *C.Distribution__Handle, _arg5 *C.Transaction__Handle) (____error_code uint32) {
	__c, okc := lookupGetOutputserHandle(*_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	addr := _addr
	walletFile := _walletFile
	chgAddr := _chgAddr
	toAddrs := *(*[]cli.SendAmount)(unsafe.Pointer(&_toAddrs))
	__pr, okpr := lookupPasswordReaderHandle(*_pr)
	if !okpr {
		____error_code = SKY_BAD_HANDLE
		return
	}
	pr := *__pr
	__distParams, okdistParams := lookupDistributionHandle(*_distParams)
	if !okdistParams {
		____error_code = SKY_BAD_HANDLE
		return
	}
	distParams := *__distParams
	__arg5, ____return_err := cli.CreateRawTxnFromAddress(c, addr, walletFile, chgAddr, toAddrs, pr, distParams)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg5 = registerTransactionHandle(__arg5)
	}
	return
}

//export SKY_cli_CreateRawTxn
func SKY_cli_CreateRawTxn(_c *C.GetOutputser__Handle, _wlt *C.Wallet__Handle, _inAddrs []string, _chgAddr string, _toAddrs []C.cli__SendAmount, _password []byte, _distParams *C.Distribution__Handle, _arg7 *C.Transaction__Handle) (____error_code uint32) {
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
	inAddrs := *(*[]string)(unsafe.Pointer(&_inAddrs))
	chgAddr := _chgAddr
	toAddrs := *(*[]cli.SendAmount)(unsafe.Pointer(&_toAddrs))
	password := *(*[]byte)(unsafe.Pointer(&_password))
	__distParams, okdistParams := lookupDistributionHandle(*_distParams)
	if !okdistParams {
		____error_code = SKY_BAD_HANDLE
		return
	}
	distParams := *__distParams
	__arg7, ____return_err := cli.CreateRawTxn(c, wlt, inAddrs, chgAddr, toAddrs, password, distParams)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg7 = registerTransactionHandle(__arg7)
	}
	return
}

//export SKY_cli_NewTransaction
func SKY_cli_NewTransaction(_utxos []C.transaction__UxBalance, _keys []C.cipher__SecKey, _outs []C.coin__TransactionOutput, _arg3 *C.Transaction__Handle) (____error_code uint32) {
	utxos := *(*[]transaction.UxBalance)(unsafe.Pointer(&_utxos))
	keys := *(*[]cipher.SecKey)(unsafe.Pointer(&_keys))
	outs := *(*[]coin.TransactionOutput)(unsafe.Pointer(&_outs))
	__arg3, ____return_err := cli.NewTransaction(utxos, keys, outs)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg3 = registerTransactionHandle(__arg3)
	}
	return
}
