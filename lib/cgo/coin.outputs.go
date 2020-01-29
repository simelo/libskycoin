package main

import (
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

// FIXES: HERE
//export SKY_coin_UxOut_Hash
func SKY_coin_UxOut_Hash(_uo *C.coin__UxOut, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	uo := (*coin.UxOut)(unsafe.Pointer(_uo))
	__arg0 := uo.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_UxOut_SnapshotHash
func SKY_coin_UxOut_SnapshotHash(_uo *C.coin__UxOut, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	uo := (*coin.UxOut)(unsafe.Pointer(_uo))
	__arg0 := uo.SnapshotHash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_UxBody_Hash
func SKY_coin_UxBody_Hash(_ub *C.coin__UxBody, _arg0 *C.cipher__SHA256) (____error_code uint32) {
	ub := (*coin.UxBody)(unsafe.Pointer(_ub))
	__arg0 := ub.Hash()
	*_arg0 = *(*C.cipher__SHA256)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_UxOut_CoinHours
func SKY_coin_UxOut_CoinHours(_uo *C.coin__UxOut, _t uint64, _arg1 *uint64) (____error_code uint32) {
	uo := (*coin.UxOut)(unsafe.Pointer(_uo))
	t := _t
	__arg1, ____return_err := uo.CoinHours(t)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_coin_UxArray_Hashes
func SKY_coin_UxArray_Hashes(_ua *C.coin__UxArray, _arg0 *C.GoSlice_) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	__arg0 := ua.Hashes()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_UxArray_HasDupes
func SKY_coin_UxArray_HasDupes(_ua *C.coin__UxArray, _arg0 *bool) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	__arg0 := ua.HasDupes()
	*_arg0 = __arg0
	return
}

//export SKY_coin_UxArray_Set
func SKY_coin_UxArray_Set(_ua *C.coin__UxArray, _arg0 *C.coin__UxHashSet) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	__arg0 := ua.Set()
	*_arg0 = *(*C.coin__UxHashSet)(unsafe.Pointer(&__arg0))
	return
}

//export SKY_coin_UxArray_Sort
func SKY_coin_UxArray_Sort(_ua *C.coin__UxArray) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	ua.Sort()
	return
}

//export SKY_coin_UxArray_Len
func SKY_coin_UxArray_Len(_ua *C.coin__UxArray, _arg0 *int) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	__arg0 := ua.Len()
	*_arg0 = __arg0
	return
}

//export SKY_coin_UxArray_Less
func SKY_coin_UxArray_Less(_ua *C.coin__UxArray, _i, _j int, _arg1 *bool) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	i := _i
	j := _j
	__arg1 := ua.Less(i, j)
	*_arg1 = __arg1
	return
}

//export SKY_coin_UxArray_Swap
func SKY_coin_UxArray_Swap(_ua *C.coin__UxArray, _i, _j int) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	i := _i
	j := _j
	ua.Swap(i, j)
	return
}

//export SKY_coin_UxArray_Coins
func SKY_coin_UxArray_Coins(_ua *C.coin__UxArray, _arg0 *uint64) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	__arg0, ____return_err := ua.Coins()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_coin_UxArray_CoinHours
func SKY_coin_UxArray_CoinHours(_ua *C.coin__UxArray, _headTime uint64, _arg1 *uint64) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	headTime := _headTime
	__arg1, ____return_err := ua.CoinHours(headTime)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_coin_NewAddressUxOuts
func SKY_coin_NewAddressUxOuts(_uxs *C.coin__UxArray, _arg1 *C.AddressUxOuts__Handle) (____error_code uint32) {
	uxs := *(*coin.UxArray)(unsafe.Pointer(_uxs))
	__arg1 := coin.NewAddressUxOuts(uxs)
	*_arg1 = registerAddressUxOutsHandle(&__arg1)
	return
}

//export SKY_coin_AddressUxOuts_Keys
func SKY_coin_AddressUxOuts_Keys(_auo *C.AddressUxOuts__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	__auo, okauo := lookupAddressUxOutsHandle(*_auo)
	if !okauo {
		____error_code = SKY_BAD_HANDLE
		return
	}
	auo := *__auo
	__arg0 := auo.Keys()
	copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	return
}

//export SKY_coin_AddressUxOuts_Flatten
func SKY_coin_AddressUxOuts_Flatten(_auo *C.AddressUxOuts__Handle, _arg0 *C.coin__UxArray) (____error_code uint32) {
	__auo, okauo := lookupAddressUxOutsHandle(*_auo)
	if !okauo {
		____error_code = SKY_BAD_HANDLE
		return
	}
	auo := *__auo
	__arg0 := auo.Flatten()
	copyToBuffer(reflect.ValueOf(__arg0[:]), unsafe.Pointer(_arg0), uint(SizeofUxArray))
	return
}

//export SKY_coin_AddressUxOuts_Sub
func SKY_coin_AddressUxOuts_Sub(_auo *C.AddressUxOuts__Handle, _other *C.AddressUxOuts__Handle, _arg1 *C.AddressUxOuts__Handle) (____error_code uint32) {
	__auo, okauo := lookupAddressUxOutsHandle(*_auo)
	if !okauo {
		____error_code = SKY_BAD_HANDLE
		return
	}
	auo := *__auo
	__other, okother := lookupAddressUxOutsHandle(*_other)
	if !okother {
		____error_code = SKY_BAD_HANDLE
		return
	}
	other := *__other
	__arg1 := auo.Sub(other)
	*_arg1 = registerAddressUxOutsHandle(&__arg1)
	return
}

//export SKY_coin_AddressUxOuts_Add
func SKY_coin_AddressUxOuts_Add(_auo *C.AddressUxOuts__Handle, _other *C.AddressUxOuts__Handle, _arg1 *C.AddressUxOuts__Handle) (____error_code uint32) {
	__auo, okauo := lookupAddressUxOutsHandle(*_auo)
	if !okauo {
		____error_code = SKY_BAD_HANDLE
		return
	}
	auo := *__auo
	__other, okother := lookupAddressUxOutsHandle(*_other)
	if !okother {
		____error_code = SKY_BAD_HANDLE
		return
	}
	other := *__other
	__arg1 := auo.Add(other)
	*_arg1 = registerAddressUxOutsHandle(&__arg1)
	return
}

//export SKY_coin_UxArray_Sub
func SKY_coin_UxArray_Sub(_ua *C.coin__UxArray, _other *C.coin__UxArray, _arg1 *C.coin__UxArray) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	other := *(*coin.UxArray)(unsafe.Pointer(_other))
	__arg1 := ua.Sub(other)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofUxArray))
	return
}

//export SKY_coin_UxArray_Add
func SKY_coin_UxArray_Add(_ua *C.coin__UxArray, _other *C.coin__UxArray, _arg1 *C.coin__UxArray) (____error_code uint32) {
	ua := *(*coin.UxArray)(unsafe.Pointer(_ua))
	other := *(*coin.UxArray)(unsafe.Pointer(_other))
	__arg1 := ua.Add(other)
	copyToBuffer(reflect.ValueOf(__arg1[:]), unsafe.Pointer(_arg1), uint(SizeofUxArray))
	return
}

// Helpers

//export SKY_coin_AddressUxOuts_Get
func SKY_coin_AddressUxOuts_Get(handle C.AddressUxOuts__Handle, _key *C.cipher__Address, _uxOuts *C.coin__UxArray) (____error_code uint32) {
	a, ok := lookupAddressUxOutHandle(handle)
	if ok {
		key := *(*cipher.Address)(unsafe.Pointer(_key))
		uxOuts, found := (*a)[key]
		if found {
			copyTocoin_UxArray(reflect.ValueOf(uxOuts), _uxOuts)
			____error_code = SKY_OK
		}
	} else {
		____error_code = SKY_BAD_HANDLE
	}
	return
}

//export SKY_coin_AddressUxOuts_HasKey
func SKY_coin_AddressUxOuts_HasKey(handle C.AddressUxOuts__Handle, _key *C.cipher__Address, _hasKey *bool) (____error_code uint32) {
	a, ok := lookupAddressUxOutHandle(handle)
	if ok {
		key := *(*cipher.Address)(unsafe.Pointer(_key))
		_, found := (*a)[key]
		*_hasKey = found
		____error_code = SKY_OK
	} else {
		____error_code = SKY_BAD_HANDLE
	}
	return
}

//export SKY_coin_AddressUxOuts_GetOutputLength
func SKY_coin_AddressUxOuts_GetOutputLength(handle C.AddressUxOuts__Handle, _key *C.cipher__Address, _length *int) (____error_code uint32) {
	a, ok := lookupAddressUxOutHandle(handle)
	if ok {
		key := *(*cipher.Address)(unsafe.Pointer(_key))
		uxOuts, found := (*a)[key]
		if found {
			*_length = len(uxOuts)
			____error_code = SKY_OK
		}
	} else {
		____error_code = SKY_BAD_HANDLE
	}
	return
}

//export SKY_coin_AddressUxOuts_Length
func SKY_coin_AddressUxOuts_Length(handle C.AddressUxOuts__Handle, _length *int) (____error_code uint32) {
	a, ok := lookupAddressUxOutHandle(handle)
	if ok {
		*_length = len(*a)
		____error_code = SKY_OK
	} else {
		____error_code = SKY_BAD_HANDLE
	}
	return
}

//export SKY_coin_AddressUxOuts_Set
func SKY_coin_AddressUxOuts_Set(handle C.AddressUxOuts__Handle, _key *C.cipher__Address, _uxOuts *C.coin__UxArray) (____error_code uint32) {
	a, ok := lookupAddressUxOutHandle(handle)
	if ok {
		key := *(*cipher.Address)(unsafe.Pointer(_key))
		//Copy the slice because it is going to be kept
		//We can't hold memory allocated outside Go
		tempUxOuts := *(*coin.UxArray)(unsafe.Pointer(_uxOuts))
		uxOuts := make(coin.UxArray, 0, len(tempUxOuts))

		uxOuts = append(uxOuts, tempUxOuts...)
		(*a)[key] = uxOuts
		____error_code = SKY_OK
	} else {
		____error_code = SKY_BAD_HANDLE
	}
	return
}
