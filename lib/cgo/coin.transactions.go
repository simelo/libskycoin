package main

import (
	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	coin "github.com/SkycoinProject/skycoin/src/coin"
	"reflect"
	"unsafe"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfees.h"
*/
import "C"

//export SKY_coin_Transaction_Verify
func SKY_coin_Transaction_Verify(_txn *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	____return_err := txn.Verify()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_VerifyUnsigned
func SKY_coin_Transaction_VerifyUnsigned(_txn *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	____return_err := txn.VerifyUnsigned()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_VerifyInputSignatures
func SKY_coin_Transaction_VerifyInputSignatures(_txn *C.Transaction__Handle, _uxIn *C.coin__UxArray) (____error_code uint32) {
	____error_code = SKY_OK
	__txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn := *__txn
	uxIn := *(*coin.UxArray)(unsafe.Pointer(_uxIn))
	____return_err := txn.VerifyInputSignatures(uxIn)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_VerifyPartialInputSignatures
func SKY_coin_Transaction_VerifyPartialInputSignatures(_txn *C.Transaction__Handle, _uxIn *C.coin__UxArray) (____error_code uint32) {
	____error_code = SKY_OK
	__txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn := *__txn
	uxIn := *(*coin.UxArray)(unsafe.Pointer(_uxIn))
	____return_err := txn.VerifyPartialInputSignatures(uxIn)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_PushInput
func SKY_coin_Transaction_PushInput(_txn *C.Transaction__Handle, _uxOut *C.cipher__SHA256) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	uxOut := *(*cipher.SHA256)(unsafe.Pointer(_uxOut))
	____return_err := txn.PushInput(uxOut)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_TransactionOutput_UxID
func SKY_coin_TransactionOutput_UxID(_txOut *C.coin__TransactionOutput, _txID *C.cipher__SHA256, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	____error_code = SKY_OK
	txOut := *(*coin.TransactionOutput)(unsafe.Pointer(_txOut))
	txID := *(*cipher.SHA256)(unsafe.Pointer(_txID))
	__arg1 := txOut.UxID(txID)
	*_arg1 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg1))
	return
}

//export SKY_coin_Transaction_PushOutput
func SKY_coin_Transaction_PushOutput(_txn *C.Transaction__Handle, _dst *C.cipher__Address, _coins, _hours uint64) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	dst := *(*cipher.Address)(unsafe.Pointer(_dst))
	coins := _coins
	hours := _hours
	____return_err := txn.PushOutput(dst, coins, hours)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_SignInput
func SKY_coin_Transaction_SignInput(_txn *C.Transaction__Handle, _key *C.cipher__SecKey, _index int) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	key := *(*cipher.SecKey)(unsafe.Pointer(_key))
	index := _index
	____return_err := txn.SignInput(key, index)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_SignInputs
func SKY_coin_Transaction_SignInputs(_txn *C.Transaction__Handle, _keys []C.cipher__SecKey) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	keys := *(*[]cipher.SecKey)(unsafe.Pointer(&_keys))
	txn.SignInputs(keys)
	return
}

//export SKY_coin_Transaction_Size
func SKY_coin_Transaction_Size(_txn *C.Transaction__Handle, _arg0 *uint32) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := txn.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_Transaction_IsFullyUnsigned
func SKY_coin_Transaction_IsFullyUnsigned(_txn *C.Transaction__Handle, _arg0 *bool) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.IsFullyUnsigned()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Transaction_IsFullySigned
func SKY_coin_Transaction_IsFullySigned(_txn *C.Transaction__Handle, _arg0 *bool) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.IsFullySigned()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Transaction_Hash
func SKY_coin_Transaction_Hash(_txn *C.Transaction__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_Transaction_SizeHash
func SKY_coin_Transaction_SizeHash(_txn *C.Transaction__Handle, _arg0 *uint32, _arg1 *C.cipher__SHA256) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, __arg1, ____return_err := txn.SizeHash()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
		*_arg1 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg1))
	}
	return
}

//export SKY_coin_Transaction_UpdateHeader
func SKY_coin_Transaction_UpdateHeader(_txn *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	____return_err := txn.UpdateHeader()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_Transaction_HashInner
func SKY_coin_Transaction_HashInner(_txn *C.Transaction__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.HashInner()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_Transaction_MustSerialize
func SKY_coin_Transaction_MustSerialize(_txn *C.Transaction__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.MustSerialize()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_Transaction_Serialize
func SKY_coin_Transaction_Serialize(_txn *C.Transaction__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := txn.Serialize()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	}
	return
}

//export SKY_coin_Transaction_MustSerializeHex
func SKY_coin_Transaction_MustSerializeHex(_txn *C.Transaction__Handle, _arg0 *C.GoString_) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := txn.MustSerializeHex()
	copyString(__arg0, _arg0)
	return
}

//export SKY_coin_Transaction_SerializeHex
func SKY_coin_Transaction_SerializeHex(_txn *C.Transaction__Handle, _arg0 *C.GoString_) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := txn.SerializeHex()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyString(__arg0, _arg0)
	}
	return
}

//export SKY_coin_MustDeserializeTransaction
func SKY_coin_MustDeserializeTransaction(_b []byte, _arg1 *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1 := coin1.MustDeserializeTransaction(b)
	*_arg1 = registerTransactionHandle(&__arg1)
	return
}

//export SKY_coin_DeserializeTransaction
func SKY_coin_DeserializeTransaction(_b []byte, _arg1 *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	b := *(*[]byte)(unsafe.Pointer(&_b))
	__arg1, ____return_err := coin1.DeserializeTransaction(b)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerTransactionHandle(&__arg1)
	}
	return
}

//export SKY_coin_MustDeserializeTransactionHex
func SKY_coin_MustDeserializeTransactionHex(_s string, _arg1 *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	s := _s
	__arg1 := coin1.MustDeserializeTransactionHex(s)
	*_arg1 = registerTransactionHandle(&__arg1)
	return
}

//export SKY_coin_DeserializeTransactionHex
func SKY_coin_DeserializeTransactionHex(_s string, _arg1 *C.Transaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	s := _s
	__arg1, ____return_err := coin1.DeserializeTransactionHex(s)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerTransactionHandle(&__arg1)
	}
	return
}

//export SKY_coin_Transaction_OutputHours
func SKY_coin_Transaction_OutputHours(_txn *C.Transaction__Handle, _arg0 *uint64) (____error_code uint32) {
	____error_code = SKY_OK
	txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := txn.OutputHours()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_Transactions_Fees
func SKY_coin_Transactions_Fees(_txns *C.Transactions__Handle, _calc *C.FeeCalculator__Handle, _arg1 *uint64) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__calc, okcalc := lookupFeeCalculatorHandle(*_calc)
	if !okcalc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	calc := *__calc
	__arg1, ____return_err := txns.Fees(calc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_coin_Transactions_Hashes
func SKY_coin_Transactions_Hashes(_txns *C.Transactions__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__arg0 := txns.Hashes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_Transactions_Size
func SKY_coin_Transactions_Size(_txns *C.Transactions__Handle, _arg0 *uint32) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__arg0, ____return_err := txns.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_Transactions_TruncateBytesTo
func SKY_coin_Transactions_TruncateBytesTo(_txns *C.Transactions__Handle, _size uint32, _arg1 *C.Transactions__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	size := _size
	__arg1, ____return_err := txns.TruncateBytesTo(size)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerTransactionsHandle(&__arg1)
	}
	return
}

//export SKY_coin_SortTransactions
func SKY_coin_SortTransactions(_txns *C.Transactions__Handle, _feeCalc *C.FeeCalculator__Handle, _arg2 *C.Transactions__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__feeCalc, okfeeCalc := lookupFeeCalculatorHandle(*_feeCalc)
	if !okfeeCalc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	feeCalc := *__feeCalc
	__arg2, ____return_err := coin1.SortTransactions(txns, feeCalc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerTransactionsHandle(&__arg2)
	}
	return
}

//export SKY_coin_NewSortableTransactions
func SKY_coin_NewSortableTransactions(_txns *C.Transactions__Handle, _feeCalc *C.FeeCalculator__Handle, _arg2 *C.SortableTransaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__feeCalc, okfeeCalc := lookupFeeCalculatorHandle(*_feeCalc)
	if !okfeeCalc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	feeCalc := *__feeCalc
	__arg2, ____return_err := coin1.NewSortableTransactions(txns, feeCalc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerSortableTransactionHandle(__arg2)
	}
	return
}

//export SKY_coin_SortableTransactions_Sort
func SKY_coin_SortableTransactions_Sort(_txns *C.SortableTransaction__Handle) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupSortableTransactionHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	txns.Sort()
	return
}

//export SKY_coin_SortableTransactions_Len
func SKY_coin_SortableTransactions_Len(_txns *C.SortableTransaction__Handle, _arg0 *int) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupSortableTransactionHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	__arg0 := txns.Len()
	*_arg0 = __arg0
	return
}

//export SKY_coin_SortableTransactions_Less
func SKY_coin_SortableTransactions_Less(_txns *C.SortableTransaction__Handle, _i, _j int, _arg1 *bool) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupSortableTransactionHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	i := _i
	j := _j
	__arg1 := txns.Less(i, j)
	*_arg1 = __arg1
	return
}

//export SKY_coin_SortableTransactions_Swap
func SKY_coin_SortableTransactions_Swap(_txns *C.SortableTransaction__Handle, _i, _j int) (____error_code uint32) {
	____error_code = SKY_OK
	__txns, oktxns := lookupSortableTransactionHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	i := _i
	j := _j
	txns.Swap(i, j)
	return
}

//export SKY_coin_VerifyTransactionCoinsSpending
func SKY_coin_VerifyTransactionCoinsSpending(_uxIn *C.coin__UxArray, _uxOut *C.coin__UxArray) (____error_code uint32) {
	____error_code = SKY_OK
	uxIn := *(*coin.UxArray)(unsafe.Pointer(_uxIn))
	uxOut := *(*coin.UxArray)(unsafe.Pointer(_uxOut))
	____return_err := coin1.VerifyTransactionCoinsSpending(uxIn, uxOut)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_VerifyTransactionHoursSpending
func SKY_coin_VerifyTransactionHoursSpending(_headTime uint64, _uxIn *C.coin__UxArray, _uxOut *C.coin__UxArray) (____error_code uint32) {
	____error_code = SKY_OK
	headTime := _headTime
	uxIn := *(*coin.UxArray)(unsafe.Pointer(_uxIn))
	uxOut := *(*coin.UxArray)(unsafe.Pointer(_uxOut))
	____return_err := coin1.VerifyTransactionHoursSpending(headTime, uxIn, uxOut)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}
