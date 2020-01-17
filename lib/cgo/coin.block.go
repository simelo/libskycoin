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
  #include "skyfee.h"
*/
import "C"

//export SKY_coin_SignedBlock_VerifySignature
func SKY_coin_SignedBlock_VerifySignature(_b *C.SignedBlock__Handle, _pubkey *C.cipher__PubKey) (____error_code uint32) {
	__b, okb := lookupSignedBlockHandle(*_b)
	if !okb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	b := *__b
	pubkey := *(*cipher.PubKey)(unsafe.Pointer(_pubkey))
	____return_err := b.VerifySignature(pubkey)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
	}
	return
}

//export SKY_coin_NewBlock
func SKY_coin_NewBlock(_prev *C.Block__Handle, _currentTime uint64, _uxHash *C.cipher__SHA256, _txns *C.Transactions__Handle, _calc *C.coin__FeeCalculator, _arg5 *C.Block__Handle) (____error_code uint32) {
	__prev, okprev := lookupBlockHandle(*_prev)
	if !okprev {
		____error_code = SKY_BAD_HANDLE
		return
	}
	prev := *__prev
	currentTime := _currentTime
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_uxHash))
	__txns, oktxns := lookupTransactionsHandle(*_txns)
	if !oktxns {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txns := *__txns
	calc := *(*coin.FeeCalculator)(unsafe.Pointer(_calc))
	__arg5, ____return_err := coin.NewBlock(prev, currentTime, uxHash, txns, calc)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg5 = registerBlockHandle(__arg5)
	}
	return
}

//export SKY_coin_NewGenesisBlock
func SKY_coin_NewGenesisBlock(_genesisAddr *C.cipher__Address, _genesisCoins, _timestamp uint64, _arg2 *C.Block__Handle) (____error_code uint32) {
	genesisAddr := *(*cipher.Address)(unsafe.Pointer(_genesisAddr))
	genesisCoins := _genesisCoins
	timestamp := _timestamp
	__arg2, ____return_err := coin.NewGenesisBlock(genesisAddr, genesisCoins, timestamp)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg2 = registerBlockHandle(__arg2)
	}
	return
}

//export SKY_coin_Block_HashHeader
func SKY_coin_Block_HashHeader(_b *C.Block__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	__b, okb := lookupBlockHandle(*_b)
	if !okb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	b := *__b
	__arg0 := b.HashHeader()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_Block_Time
func SKY_coin_Block_Time(_b *C.Block__Handle, _arg0 *uint64) (____error_code uint32) {
	__b, okb := lookupBlockHandle(*_b)
	if !okb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	b := *__b
	__arg0 := b.Time()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Block_Seq
func SKY_coin_Block_Seq(_b *C.Block__Handle, _arg0 *uint64) (____error_code uint32) {
	__b, okb := lookupBlockHandle(*_b)
	if !okb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	b := *__b
	__arg0 := b.Seq()
	*_arg0 = __arg0
	return
}

//export SKY_coin_Block_Size
func SKY_coin_Block_Size(_b *C.Block__Handle, _arg0 *uint32) (____error_code uint32) {
	__b, okb := lookupBlockHandle(*_b)
	if !okb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	b := *__b
	__arg0, ____return_err := b.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_NewBlockHeader
func SKY_coin_NewBlockHeader(_prev *C.BlockHeader__Handle, _uxHash *C.cipher__SHA256, _currentTime, _fee uint64, _body *C.BlockBody__Handle, _arg4 *C.BlockHeader__Handle) (____error_code uint32) {
	__prev, okprev := lookupBlockHeaderHandle(*_prev)
	if !okprev {
		____error_code = SKY_BAD_HANDLE
		return
	}
	prev := *__prev
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_uxHash))
	currentTime := _currentTime
	fee := _fee
	__body, okbody := lookupBlockBodyHandle(*_body)
	if !okbody {
		____error_code = SKY_BAD_HANDLE
		return
	}
	body := *__body
	__arg4 := coin.NewBlockHeader(prev, uxHash, currentTime, fee, body)
	*_arg4 = registerBlockHeaderHandle(&__arg4)
	return
}

//export SKY_coin_BlockHeader_Hash
func SKY_coin_BlockHeader_Hash(_bh *C.BlockHeader__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	bh, okbh := lookupBlockHeaderHandle(*_bh)
	if !okbh {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bh.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockHeader_Bytes
func SKY_coin_BlockHeader_Bytes(_bh *C.BlockHeader__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	bh, okbh := lookupBlockHeaderHandle(*_bh)
	if !okbh {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bh.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_BlockBody_Hash
func SKY_coin_BlockBody_Hash(_bb *C.BlockBody__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	__bb, okbb := lookupBlockBodyHandle(*_bb)
	if !okbb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bb := *__bb
	__arg0 := bb.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockBody_Size
func SKY_coin_BlockBody_Size(_bb *C.BlockBody__Handle, _arg0 *uint32) (____error_code uint32) {
	__bb, okbb := lookupBlockBodyHandle(*_bb)
	if !okbb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bb := *__bb
	__arg0, ____return_err := bb.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_BlockBody_Bytes
func SKY_coin_BlockBody_Bytes(_bb *C.BlockBody__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	bb, okbb := lookupBlockBodyHandle(*_bb)
	if !okbb {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bb.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_CreateUnspents
func SKY_coin_CreateUnspents(_bh *C.BlockHeader__Handle, _txn *C.Transaction__Handle, _arg2 *C.coin__UxArray) (____error_code uint32) {
	__bh, okbh := lookupBlockHeaderHandle(*_bh)
	if !okbh {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh := *__bh
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
func SKY_coin_CreateUnspent(_bh *C.BlockHeader__Handle, _txn *C.Transaction__Handle, _outIndex int, _arg3 *C.coin__UxOut) (____error_code uint32) {
	__bh, okbh := lookupBlockHeaderHandle(*_bh)
	if !okbh {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh := *__bh
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
