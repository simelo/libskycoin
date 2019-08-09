package main

import (
	"unsafe"

	wallet "github.com/skycoin/skycoin/src/wallet"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_wallet_NewReadableEntry
func SKY_wallet_NewReadableEntry(_coinType string, _walletType string, _w *C.wallet__Entry, _arg1 *C.ReadableEntry__Handle) (____error_code uint32) {
	coinType := wallet.CoinType(_coinType)
	w := *(*wallet.Entry)(unsafe.Pointer(_w))
	__arg1 := wallet.NewReadableEntry(coinType, _walletType, w)
	*_arg1 = registerReadableEntryHandle(&__arg1)
	return
}
