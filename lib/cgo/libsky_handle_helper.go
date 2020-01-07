package main

import (
	"encoding/json"
	"errors"
	"path/filepath"
	"reflect"
	"strconv"
	"unsafe"

	api "github.com/SkycoinProject/skycoin/src/api"
	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	coin "github.com/SkycoinProject/skycoin/src/coin"
	"github.com/SkycoinProject/skycoin/src/daemon"
	"github.com/SkycoinProject/skycoin/src/readable"
)

/*

  #include <string.h>
  #include <stdlib.h>


  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_JsonEncode_Handle
func SKY_JsonEncode_Handle(handle C.Handle, json_string *C.GoString_) uint32 {
	obj, ok := lookupHandle(handle)
	if ok {
		jsonBytes, err := json.Marshal(obj)
		if err == nil {
			copyString(string(jsonBytes), json_string)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Progress_GetCurrent
func SKY_Handle_Progress_GetCurrent(handle C.Handle, current *uint64) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*daemon.BlockchainProgress); isOK {
			*current = obj.Current
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Block_GetHeadSeq
func SKY_Handle_Block_GetHeadSeq(handle C.Handle, seq *uint64) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.Block); isOK {
			*seq = obj.Head.BkSeq
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Block_GetHeadHash
func SKY_Handle_Block_GetHeadHash(handle C.Handle, hash *C.GoString_) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.Block); isOK {
			copyString(obj.Head.Hash, hash)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Block_GetPreviousBlockHash
func SKY_Handle_Block_GetPreviousBlockHash(handle C.Handle, hash *C.GoString_) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.Block); isOK {
			copyString(obj.Head.PreviousHash, hash)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Blocks_GetAt
func SKY_Handle_Blocks_GetAt(handle C.Handle,
	index uint64, blockHandle *C.Handle) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.Blocks); isOK {
			*blockHandle = registerHandle(&obj.Blocks[index])
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Blocks_GetCount
func SKY_Handle_Blocks_GetCount(handle C.Handle,
	count *uint64) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.Blocks); isOK {
			*count = uint64(len(obj.Blocks))
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_Handle_Connections_GetCount
func SKY_Handle_Connections_GetCount(handle C.Handle,
	count *uint64) uint32 {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.Connections); isOK {
			*count = uint64(len(obj.Connections))
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_Client_GetWalletDir
func SKY_api_Handle_Client_GetWalletDir(handle C.Client__Handle, walletDir *C.GoString_) uint32 {
	client, ok := lookupClientHandle(handle)
	if ok {
		wf, err := client.WalletFolderName()
		if err == nil {
			copyString(wf.Address, walletDir)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_Client_GetWalletFileName
func SKY_api_Handle_Client_GetWalletFileName(handle C.WalletResponse__Handle,
	walletFileName *C.GoString_) uint32 {
	w, ok := lookupWalletResponseHandle(handle)
	if ok {
		copyString(w.Meta.Filename, walletFileName)
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_Client_GetWalletLabel
func SKY_api_Handle_Client_GetWalletLabel(handle C.WalletResponse__Handle,
	walletLabel *C.GoString_) uint32 {
	w, ok := lookupWalletResponseHandle(handle)
	if ok {
		copyString(w.Meta.Label, walletLabel)
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_Client_GetWalletFullPath
func SKY_api_Handle_Client_GetWalletFullPath(
	clientHandle C.Client__Handle,
	walletHandle C.WalletResponse__Handle,
	fullPath *C.GoString_) uint32 {
	client, ok := lookupClientHandle(clientHandle)
	if ok {
		wf, err := client.WalletFolderName()
		if err == nil {
			w, okw := lookupWalletResponseHandle(walletHandle)
			if okw {
				walletPath := filepath.Join(wf.Address, w.Meta.Filename)
				copyString(walletPath, fullPath)
				return SKY_OK
			}
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_Client_GetWalletResponseEntriesCount
func SKY_api_Handle_Client_GetWalletResponseEntriesCount(
	handle C.WalletResponse__Handle,
	count *uint32) uint32 {
	w, ok := lookupWalletResponseHandle(handle)
	if ok {
		*count = uint32(len(w.Entries))
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_WalletResponseGetEntry
func SKY_api_Handle_WalletResponseGetEntry(handle C.WalletResponse__Handle,
	index uint32,
	address *C.GoString_,
	pubkey *C.GoString_) uint32 {
	w, ok := lookupWalletResponseHandle(handle)
	if ok {
		if index < uint32(len(w.Entries)) {
			copyString(w.Entries[index].Address, address)
			copyString(w.Entries[index].Public, pubkey)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_WalletResponseIsEncrypted
func SKY_api_Handle_WalletResponseIsEncrypted(
	handle C.WalletResponse__Handle,
	isEncrypted *bool) uint32 {
	w, ok := lookupWalletResponseHandle(handle)
	if ok {
		*isEncrypted = w.Meta.Encrypted
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_WalletsResponseGetCount
func SKY_api_Handle_WalletsResponseGetCount(
	handle C.Wallets__Handle,
	count *uint32) uint32 {
	w, ok := lookupWalletsHandle(handle)
	if ok {
		*count = uint32(len(w))
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_WalletsResponseGetAt
func SKY_api_Handle_WalletsResponseGetAt(
	walletsHandle C.Wallets__Handle,
	index uint32,
	walletHandle *C.WalletResponse__Handle) uint32 {
	w, ok := lookupWalletsHandle(walletsHandle)
	if ok {
		if index < uint32(len(w)) {
			*walletHandle = registerWalletResponseHandle(w[index])
		}
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_GetWalletFolderAddress
func SKY_api_Handle_GetWalletFolderAddress(
	folderHandle C.Handle,
	address *C.GoString_) uint32 {
	obj, ok := lookupHandle(folderHandle)
	if ok {
		if obj, isOK := (obj).(*api.WalletFolder); isOK {
			copyString(obj.Address, address)
			return SKY_OK
		}
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_GetWalletSeed
func SKY_api_Handle_GetWalletSeed(handle C.MetaWallet__Handle,
	seed *C.GoString_) uint32 {
	w, ok := lookupMetaWalletHandle(handle)
	if ok {
		copyString(w.Seed(), seed)
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_GetWalletLastSeed
func SKY_api_Handle_GetWalletLastSeed(handle C.MetaWallet__Handle,
	lastSeed *C.GoString_) uint32 {
	w, ok := lookupMetaWalletHandle(handle)
	if ok {
		copyString(w.LastSeed(), lastSeed)
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

//export SKY_api_Handle_GetBuildInfoData
func SKY_api_Handle_GetBuildInfoData(handle C.BuildInfo_Handle,
	version *C.GoString_, commit *C.GoString_, branch *C.GoString_) uint32 {
	bi, ok := lookupBuildInfoHandle(handle)
	if ok {
		copyString(bi.Version, version)
		copyString(bi.Commit, commit)
		copyString(bi.Branch, branch)
		return SKY_OK
	}
	return SKY_BAD_HANDLE
}

// Transactions

//export SKY_coin_Create_Transaction
func SKY_coin_Create_Transaction(handle *C.Transaction__Handle) (____error_code uint32) {
	tx := coin.Transaction{}
	*handle = registerTransactionHandle(&tx)
	return
}

//export SKY_coin_Transaction_Copy
func SKY_coin_Transaction_Copy(handle C.Transaction__Handle, handle2 *C.Transaction__Handle) (____error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	ntx := coin.Transaction{}
	ntx.Length = tx.Length
	ntx.Type = tx.Type
	ntx.InnerHash = tx.InnerHash
	ntx.Sigs = make([]cipher.Sig, 0)
	ntx.Sigs = append(ntx.Sigs, tx.Sigs...)
	ntx.In = make([]cipher.SHA256, 0)
	ntx.In = append(ntx.In, tx.In...)
	ntx.Out = make([]coin.TransactionOutput, 0)
	ntx.Out = append(ntx.Out, tx.Out...)
	*handle2 = registerTransactionHandle(&ntx)
	return
}

//export SKY_coin_Transaction_ResetInputs
func SKY_coin_Transaction_ResetInputs(handle C.Transaction__Handle, count int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn.In = make([]cipher.SHA256, count)
	return
}

//export SKY_coin_Transaction_GetInputsCount
func SKY_coin_Transaction_GetInputsCount(handle C.Transaction__Handle, length *int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*length = len(txn.In)
	return
}

//export SKY_coin_Transaction_GetInputAt
func SKY_coin_Transaction_GetInputAt(handle C.Transaction__Handle, i int, input *C.cipher__SHA256) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.In) {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*input = *(*C.cipher__SHA256)(unsafe.Pointer(&txn.In[i]))
	return
}

//export SKY_coin_Transaction_SetInputAt
func SKY_coin_Transaction_SetInputAt(handle C.Transaction__Handle, i int, input *C.cipher__SHA256) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.In) {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*(*C.cipher__SHA256)(unsafe.Pointer(&txn.In[i])) = *input
	return
}

//export SKY_coin_Transaction_GetOutputsCount
func SKY_coin_Transaction_GetOutputsCount(handle C.Transaction__Handle, length *int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*length = len(txn.Out)
	return
}

//export SKY_coin_Transaction_GetOutputAt
func SKY_coin_Transaction_GetOutputAt(handle C.Transaction__Handle, i int, output *C.coin__TransactionOutput) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.Out) {
		____error_code = SKY_ERROR
		return
	}
	*output = *(*C.coin__TransactionOutput)(unsafe.Pointer(&txn.Out[i]))
	return
}

//export SKY_coin_Transaction_SetOutputAt
func SKY_coin_Transaction_SetOutputAt(handle C.Transaction__Handle, i int, output *C.coin__TransactionOutput) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.Out) {
		____error_code = SKY_ERROR
		return
	}
	*(*C.coin__TransactionOutput)(unsafe.Pointer(&txn.Out[i])) = *output
	return
}

//export SKY_coin_Transaction_GetSignaturesCount
func SKY_coin_Transaction_GetSignaturesCount(handle C.Transaction__Handle, length *int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*length = len(txn.Sigs)
	return
}

//export SKY_coin_Transaction_GetSignatureAt
func SKY_coin_Transaction_GetSignatureAt(handle C.Transaction__Handle, i int, sig *C.cipher__Sig) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.Sigs) {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*sig = *(*C.cipher__Sig)(unsafe.Pointer(&txn.Sigs[i]))
	return
}

//export SKY_coin_Transaction_SetSignatureAt
func SKY_coin_Transaction_SetSignatureAt(handle C.Transaction__Handle, i int, sig *C.cipher__Sig) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if i >= len(txn.Sigs) {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*(*C.cipher__Sig)(unsafe.Pointer(&txn.Sigs[i])) = *sig
	return
}

//export SKY_coin_Transaction_PushSignature
func SKY_coin_Transaction_PushSignature(handle C.Transaction__Handle, _sig *C.cipher__Sig) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	sig := *(*cipher.Sig)(unsafe.Pointer(_sig))
	txn.Sigs = append(txn.Sigs, sig)
	return
}

//export SKY_coin_Transaction_ResetOutputs
func SKY_coin_Transaction_ResetOutputs(handle C.Transaction__Handle, count int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn.Out = make([]coin.TransactionOutput, count)
	return
}

//export SKY_coin_Transaction_ResetSignatures
func SKY_coin_Transaction_ResetSignatures(handle C.Transaction__Handle, count int) (____error_code uint32) {
	txn, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn.Sigs = make([]cipher.Sig, count)
	return
}

//export SKY_coin_GetTransactionObject
func SKY_coin_GetTransactionObject(handle C.Transaction__Handle, _pptx **C.coin__Transaction) (____error_code uint32) {
	ptx, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_pptx = (*C.coin__Transaction)(unsafe.Pointer(ptx))
	}
	return
}

//export SKY_coin_Transaction_GetLength
func SKY_coin_Transaction_GetLength(handle C.Transaction__Handle, _arg0 *uint32) (____error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}

	*_arg0 = tx.Length

	return
}

//export SKY_coin_Transaction_GetType
func SKY_coin_Transaction_GetType(handle C.Transaction__Handle, _arg0 *uint8) (____error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}

	*_arg0 = tx.Type
	return
}

//export SKY_coin_Transaction_GetInnerHash
func SKY_coin_Transaction_GetInnerHash(handle C.Transaction__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}

	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&tx.InnerHash))
	return
}

//export SKY_coin_Transaction_GetSigs
func SKY_coin_Transaction_GetSigs(handle C.Transaction__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		___error_code = SKY_BAD_HANDLE
		return
	}

	copyToGoSlice(reflect.ValueOf(tx.Sigs), _arg0)
	return
}

//export SKY_coin_Transaction_GetIn
func SKY_coin_Transaction_GetIn(handle C.Transaction__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		___error_code = SKY_BAD_HANDLE
		return
	}

	copyToGoSlice(reflect.ValueOf(tx.In), _arg0)
	return
}

//export SKY_coin_Transaction_GetOut
func SKY_coin_Transaction_GetOut(handle C.Transaction__Handle, _arg0 *C.GoSlice_) (___error_code uint32) {
	tx, ok := lookupTransactionHandle(handle)
	if !ok {
		___error_code = SKY_BAD_HANDLE
		return
	}

	copyToGoSlice(reflect.ValueOf(tx.Out), _arg0)
	return
}

//export SKY_coin_Transaction_SetInnerHash
func SKY_coin_Transaction_SetInnerHash(handle *C.Transaction__Handle, _sha *C.cipher__SHA256) (___error_code uint32) {
	tx, ok := lookupTransactionHandle(*handle)
	if !ok {
		___error_code = SKY_BAD_HANDLE
		return
	}
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_sha))
	tx.InnerHash = uxHash
	return
}

//export SKY_coin_Create_Transactions
func SKY_coin_Create_Transactions(handle *C.Transactions__Handle) (____error_code uint32) {
	txs := make(coin.Transactions, 0)
	*handle = registerTransactionsHandle(&txs)
	return SKY_OK
}

//export SKY_coin_Transactions_Length
func SKY_coin_Transactions_Length(handle C.Transactions__Handle, _length *int) (____error_code uint32) {
	txns, ok := lookupTransactionsHandle(handle)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_length = len(*txns)
	return
}

//export SKY_coin_Transactions_Add
func SKY_coin_Transactions_Add(tsh C.Transactions__Handle, th C.Transaction__Handle) (____error_code uint32) {
	txns, ok := lookupTransactionsHandle(tsh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	tx, okt := lookupTransactionHandle(th)
	if !okt {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*txns = append(*txns, *tx)
	result := overwriteHandle(tsh, txns)
	if !result {
		____error_code = SKY_ERROR
	}
	return
}

//export SKY_coin_Transactions_Fees
func SKY_coin_Transactions_Fees(tsh C.Transactions__Handle, pFeeCalc *C.FeeCalculator, _result *uint64) (____error_code uint32) {
	feeCalc := func(pTx *coin.Transaction) (uint64, error) {
		var fee C.GoUint64_
		handle := registerTransactionHandle(pTx)
		result := C.callFeeCalculator(pFeeCalc, handle, &fee)
		closeHandle(Handle(handle))
		if result == SKY_OK {
			return uint64(fee), nil
		} else {
			return 0, errors.New("Error calculating fee")
		}
	}
	txns, ok := lookupTransactionsHandle(tsh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	result, err := txns.Fees(feeCalc)
	if err != nil {
		____error_code = SKY_ERROR
	} else {
		*_result = result
	}
	return
}

//export SKY_coin_Transactions_GetAt
func SKY_coin_Transactions_GetAt(tsh C.Transactions__Handle, n int, th *C.Transaction__Handle) (____error_code uint32) {
	txns, ok := lookupTransactionsHandle(tsh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	if n >= len(*txns) {
		____error_code = SKY_ERROR
		return
	}
	tx := (*txns)[n]
	*th = registerTransactionHandle(&tx)
	return
}

//export SKY_coin_SortTransactions
func SKY_coin_SortTransactions(tsh C.Transactions__Handle, pFeeCalc *C.FeeCalculator, ptsh *C.Transactions__Handle) (____error_code uint32) {
	feeCalc := func(pTx *coin.Transaction) (uint64, error) {
		var fee C.GoUint64_
		handle := registerTransactionHandle(pTx)
		errorcode := C.callFeeCalculator(pFeeCalc, handle, &fee)
		closeHandle(Handle(handle))
		if errorcode != SKY_OK {
			if err, exists := codeToErrorMap[uint32(errorcode)]; exists {
				return 0, err
			}
			return 0, errors.New("C fee calculator failed code=" + strconv.Itoa(int(errorcode)))
		}
		return uint64(fee), nil
	}
	txns, ok := lookupTransactionsHandle(tsh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	sorted, ____return_err := coin.SortTransactions(*txns, feeCalc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*ptsh = registerTransactionsHandle(&sorted)
	}
	return
}

//export SKY_coin_NewSortableTransactions
func SKY_coin_NewSortableTransactions(tsh C.Transactions__Handle, pFeeCalc *C.FeeCalculator, ptsh *C.SortableTransactions_Handle) (____error_code uint32) {
	feeCalc := func(pTx *coin.Transaction) (uint64, error) {
		var fee C.GoUint64_
		handle := registerTransactionHandle(pTx)
		result := C.callFeeCalculator(pFeeCalc, handle, &fee)
		closeHandle(Handle(handle))
		if result == SKY_OK {
			return uint64(fee), nil
		} else {
			return 0, errors.New("Error calculating fee")
		}
	}
	txns, ok := lookupTransactionsHandle(tsh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	sorted, ____return_err := coin.NewSortableTransactions(*txns, feeCalc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*ptsh = registerSortableTransactiontHandle(sorted)
	}
	return
}
