package main

import (
	src "github.com/SkycoinProject/skycoin/src/"
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

//export SKY_coin_SignedBlock_VerifySignature
func SKY_coin_SignedBlock_VerifySignature(_b *C.coin__SignedBlock, _pubkey *C.cipher__PubKey) (____error_code uint32) {
	b := *(*src.SignedBlock)(unsafe.Pointer(_b))
	pubkey := *(*cipher.PubKey)(unsafe.Pointer(_pubkey))
	____return_err := b.VerifySignature(pubkey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_NewBlock
func SKY_coin_NewBlock(_prev *C.coin__Block, _currentTime uint64, _uxHash *C.cipher__SHA256, _txns *C.Transactions__Handle, _calc *C.FeeCalculator__Handle, _arg5 *C.coin__Block) (____error_code uint32) {
	prev := *(*src.Block)(unsafe.Pointer(_prev))
	currentTime := _currentTime
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_uxHash))
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
	__arg5, ____return_err := coin.NewBlock(prev, currentTime, uxHash, txns, calc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg5 = *(*C.coin__Block)(unsafe.Pointer(__arg5))
	}
	return
}

//export SKY_coin_NewGenesisBlock
func SKY_coin_NewGenesisBlock(_genesisAddr *C.cipher__Address, _genesisCoins, _timestamp uint64, _arg2 *C.coin__Block) (____error_code uint32) {
	genesisAddr := *(*cipher.Address)(unsafe.Pointer(_genesisAddr))
	genesisCoins := _genesisCoins
	timestamp := _timestamp
	__arg2, ____return_err := coin.NewGenesisBlock(genesisAddr, genesisCoins, timestamp)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = *(*C.coin__Block)(unsafe.Pointer(__arg2))
	}
	return
}

//export SKY_coin_Block_HashHeader
func SKY_coin_Block_HashHeader(_b *C.coin__Block, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	b := *(*src.Block)(unsafe.Pointer(_b))
	__arg0 := b.HashHeader()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_Block_Time
func SKY_coin_Block_Time(_b *C.coin__Block, _arg0 *uint64) (____error_code uint32) {
	b := *(*src.Block)(unsafe.Pointer(_b))
	__arg0 := b.Time()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Block_Seq
func SKY_coin_Block_Seq(_b *C.coin__Block, _arg0 *uint64) (____error_code uint32) {
	b := *(*src.Block)(unsafe.Pointer(_b))
	__arg0 := b.Seq()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Block_Size
func SKY_coin_Block_Size(_b *C.coin__Block, _arg0 *uint32) (____error_code uint32) {
	b := *(*src.Block)(unsafe.Pointer(_b))
	__arg0, ____return_err := b.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_NewBlockHeader
func SKY_coin_NewBlockHeader(_prev *C.coin__BlockHeader, _uxHash *C.cipher__SHA256, _currentTime, _fee uint64, _body *C.coin__BlockBody, _arg4 *C.coin__BlockHeader) (____error_code uint32) {
	prev := *(*src.BlockHeader)(unsafe.Pointer(_prev))
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_uxHash))
	currentTime := _currentTime
	fee := _fee
	body := *(*src.BlockBody)(unsafe.Pointer(_body))
	__arg4 := coin.NewBlockHeader(prev, uxHash, currentTime, fee, body)
	*_arg4 = *(*C.coin__BlockHeader)(unsafe.Pointer(&__arg4))
	return
}

//export SKY_coin_BlockHeader_Hash
func SKY_coin_BlockHeader_Hash(_bh *C.coin__BlockHeader, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	bh := (*src.BlockHeader)(unsafe.Pointer(_bh))
	__arg0 := bh.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockHeader_Bytes
func SKY_coin_BlockHeader_Bytes(_bh *C.coin__BlockHeader, _arg0 *C.GoSlice_) (____error_code uint32) {
	bh := (*src.BlockHeader)(unsafe.Pointer(_bh))
	__arg0 := bh.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_BlockBody_Hash
func SKY_coin_BlockBody_Hash(_bb *C.coin__BlockBody, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	bb := *(*src.BlockBody)(unsafe.Pointer(_bb))
	__arg0 := bb.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockBody_Size
func SKY_coin_BlockBody_Size(_bb *C.coin__BlockBody, _arg0 *uint32) (____error_code uint32) {
	bb := *(*src.BlockBody)(unsafe.Pointer(_bb))
	__arg0, ____return_err := bb.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_BlockBody_Bytes
func SKY_coin_BlockBody_Bytes(_bb *C.coin__BlockBody, _arg0 *C.GoSlice_) (____error_code uint32) {
	bb := (*src.BlockBody)(unsafe.Pointer(_bb))
	__arg0 := bb.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_CreateUnspents
func SKY_coin_CreateUnspents(_bh *C.coin__BlockHeader, _txn *C.Transaction__Handle, _arg2 *C.coin__UxArray) (____error_code uint32) {
	bh := *(*src.BlockHeader)(unsafe.Pointer(_bh))
	__txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn := *__txn
	__arg2 := coin.CreateUnspents(bh, txn)
	copyToBuffer(reflect.ValueOf(__arg2[:]), unsafe.Pointer(_arg2), uint(SizeofUxArray))
	return
}

//export SKY_coin_CreateUnspent
func SKY_coin_CreateUnspent(_bh *C.coin__BlockHeader, _txn *C.Transaction__Handle, _outIndex int, _arg3 *C.coin__UxOut) (____error_code uint32) {
	bh := *(*src.BlockHeader)(unsafe.Pointer(_bh))
	__txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn := *__txn
	outIndex := _outIndex
	__arg3, ____return_err := coin.CreateUnspent(bh, txn, outIndex)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg3 = *(*C.coin__UxOut)(unsafe.Pointer(&__arg3))
	}
	return
}
