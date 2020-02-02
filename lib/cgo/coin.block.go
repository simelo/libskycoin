package main

import (
	"errors"
	"reflect"
	"unsafe"

	cipher "github.com/SkycoinProject/skycoin/src/cipher"
	coin "github.com/SkycoinProject/skycoin/src/coin"
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
func SKY_coin_NewBlock(_prev *C.Block__Handle, _currentTime uint64, _uxHash *C.cipher__SHA256, _txns *C.Transactions__Handle, _calc *C.FeeCalculator, _arg5 *C.Block__Handle) (____error_code uint32) {
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
	calc := func(pTx *coin.Transaction) (uint64, error) {
		var fee C.GoUint64_
		handle := registerTransactionHandle(pTx)
		result := C.callFeeCalculator(_calc, handle, &fee)
		closeHandle(Handle(handle))
		if result == SKY_OK {
			return uint64(fee), nil
		}
		return 0, errors.New("Error calculating fee")
	}
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
func SKY_coin_NewBlockHeader(_prev *C.coin__BlockHeader, _uxHash *C.cipher__SHA256, _currentTime, _fee uint64, _body *C.coin__BlockBody, _arg4 *C.coin__BlockHeader) (____error_code uint32) {
	prev := *(*coin.BlockHeader)(unsafe.Pointer(_prev))
	uxHash := *(*cipher.SHA256)(unsafe.Pointer(_uxHash))
	currentTime := _currentTime
	fee := _fee
	body := *(*coin.BlockBody)(unsafe.Pointer(_body))
	__arg4 := coin.NewBlockHeader(prev, uxHash, currentTime, fee, body)
	*_arg4 = *(*C.coin__BlockHeader)(unsafe.Pointer(&__arg4))
	return
}

//export SKY_coin_BlockHeader_Hash
func SKY_coin_BlockHeader_Hash(_bh C.BlockHeader__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	bh, ok := lookupBlockHeaderHandle(_bh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bh.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockHeader_Bytes
func SKY_coin_BlockHeader_Bytes(_bh *C.coin__BlockHeader, _arg0 *C.GoSlice_) (____error_code uint32) {
	bh := (*coin.BlockHeader)(unsafe.Pointer(_bh))
	__arg0 := bh.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_BlockBody_Hash
func SKY_coin_BlockBody_Hash(_body C.BlockBody__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	body, ok := lookupBlockBodyHandle(_body)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := body.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_BlockBody_Size
func SKY_coin_BlockBody_Size(_bb *C.BlockBody__Handle, _arg0 *uint32) (____error_code uint32) {
	bb, ok := lookupBlockBodyHandle(*_bb)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0, ____return_err := bb.Size()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_BlockBody_Bytes
func SKY_coin_BlockBody_Bytes(_bb C.BlockBody__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	bb, ok := lookupBlockBodyHandle(_bb)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bb.Bytes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_CreateUnspents
func SKY_coin_CreateUnspents(_bh *C.coin__BlockHeader, _txn *C.Transaction__Handle, _arg2 *C.coin__UxArray) (____error_code uint32) {
	bh := *(*coin.BlockHeader)(unsafe.Pointer(_bh))
	__txn, oktxn := lookupTransactionHandle(*_txn)
	if !oktxn {
		____error_code = SKY_BAD_HANDLE
		return
	}
	txn := *__txn
	__arg2 := coin.CreateUnspents(bh, txn)
	copyTocoin_UxArray(reflect.ValueOf(__arg2), _arg2)
	return
}

//export SKY_coin_CreateUnspent
func SKY_coin_CreateUnspent(_bh *C.coin__BlockHeader, _txn *C.Transaction__Handle, _outIndex int, _arg3 *C.coin__UxOut) (____error_code uint32) {
	bh := *(*coin.BlockHeader)(unsafe.Pointer(_bh))
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

// Helpers

//export SKY_coin_GetBlockObject
func SKY_coin_GetBlockObject(_b C.Block__Handle, _p **C.coin__Block) (____error_code uint32) {
	b, ok := lookupBlockHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_p = (*C.coin__Block)(unsafe.Pointer(b))
	}
	return
}

//export SKY_coin_GetBlockBody
func SKY_coin_GetBlockBody(_b C.Block__Handle, _p *C.BlockBody__Handle) (____error_code uint32) {
	b, ok := lookupBlockHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_p = registerBlockBodyHandle(&b.Body)
	}
	return
}

//export SKY_coin_NewEmptyBlock
func SKY_coin_NewEmptyBlock(_txns C.Transactions__Handle, handle *C.Block__Handle) (____error_code uint32) {
	txns, ok := lookupTransactionsHandle(_txns)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	body := coin.BlockBody{
		Transactions: *txns,
	}
	block := coin.Block{
		Body: body,
		Head: coin.BlockHeader{
			Version:  0x02,
			Time:     100,
			BkSeq:    0,
			Fee:      10,
			PrevHash: cipher.SHA256{},
			BodyHash: body.Hash(),
		}}
	*handle = registerBlockHandle(&block)
	return
}

//export SKY_coin_Block_GetBlockHeader
func SKY_coin_Block_GetBlockHeader(_b C.Block__Handle, _bh *C.BlockHeader__Handle) (____error_code uint32) {
	b, ok := lookupBlockHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_bh = registerBlockHeaderHandle(&b.Head)
	}
	return
}

//export SKY_coin_GetBlockHeaderObject
func SKY_coin_GetBlockHeaderObject(_b C.BlockHeader__Handle, _p **C.coin__BlockHeader) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_p = (*C.coin__BlockHeader)(unsafe.Pointer(b))
	}
	return
}

//export SKY_coin_BlockHeader_Time
func SKY_coin_BlockHeader_Time(_b C.BlockHeader__Handle, _arg0 *uint64) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = uint64(b.Time)
	}
	return
}

//export SKY_coin_BlockHeader_BkSeq
func SKY_coin_BlockHeader_BkSeq(_b C.BlockHeader__Handle, _arg0 *uint64) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = uint64(b.BkSeq)
	}
	return
}

//export SKY_coin_BlockHeader_UxHash
func SKY_coin_BlockHeader_UxHash(_b C.BlockHeader__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&b.UxHash))
	}
	return
}

//export SKY_coin_BlockHeader_Fee
func SKY_coin_BlockHeader_Fee(_b C.BlockHeader__Handle, _arg0 *uint64) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = uint64(b.Fee)
	}
	return
}

//export SKY_coin_BlockBody_Transactions
func SKY_coin_BlockBody_Transactions(_bb C.BlockBody__Handle, _arg0 *C.Transactions__Handle) (____error_code uint32) {
	bb, ok := lookupBlockBodyHandle(_bb)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := bb.Transactions
	*_arg0 = registerTransactionsHandle(&__arg0)
	return
}

//export SKY_coin_BlockHeader_SetTime
// nolint megacheck
func SKY_coin_BlockHeader_SetTime(_bh C.BlockHeader__Handle, _arg0 uint64) (____error_code uint32) {

	bh, ok := lookupBlockHeaderHandle(_bh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh.Time = uint64(_arg0)
	_bh = registerBlockHeaderHandle(bh)
	return
}

//export SKY_coin_BlockHeader_SetBkSeq
// nolint megacheck
func SKY_coin_BlockHeader_SetBkSeq(_bh C.BlockHeader__Handle, _arg0 uint64) (____error_code uint32) {

	bh, ok := lookupBlockHeaderHandle(_bh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh.BkSeq = uint64(_arg0)
	_bh = registerBlockHeaderHandle(bh)
	return
}

//export SKY_coin_BlockHeader_SetFee
// nolint megacheck
func SKY_coin_BlockHeader_SetFee(_bh C.BlockHeader__Handle, _arg0 uint64) (____error_code uint32) {

	bh, ok := lookupBlockHeaderHandle(_bh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh.Fee = uint64(_arg0)
	_bh = registerBlockHeaderHandle(bh)
	return
}

//export SKY_coin_BlockHeader_SetVersion
// nolint megacheck
func SKY_coin_BlockHeader_SetVersion(_bh C.BlockHeader__Handle, _arg0 uint32) (____error_code uint32) {

	bh, ok := lookupBlockHeaderHandle(_bh)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	bh.Version = uint32(_arg0)
	_bh = registerBlockHeaderHandle(bh)
	return
}

//export SKY_coin_BlockHeader_Version
func SKY_coin_BlockHeader_Version(_b C.BlockHeader__Handle, _arg0 *uint32) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = uint32(b.Version)
	}
	return
}

//export SKY_coin_BlockHeader_PrevHash
func SKY_coin_BlockHeader_PrevHash(_b C.BlockHeader__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	b, ok := lookupBlockHeaderHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
	} else {
		*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&b.PrevHash))
	}
	return
}

//export SKY_coin_Block_HashBody
func SKY_coin_Block_HashBody(_b C.Block__Handle, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	b, ok := lookupBlockHandle(_b)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__arg0 := b.Body.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}
