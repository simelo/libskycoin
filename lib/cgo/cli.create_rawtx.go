package main

import (
	"unsafe"

	"github.com/skycoin/skycoin/src/transaction"

	cipher "github.com/skycoin/skycoin/src/cipher"
	cli "github.com/skycoin/skycoin/src/cli"
	coin "github.com/skycoin/skycoin/src/coin"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

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
