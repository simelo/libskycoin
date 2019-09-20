package main

import (
	"reflect"

	"github.com/skycoin/skycoin/src/params"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_params_Distribution_GetMaxCoinSupply
func SKY_params_Distribution_GetMaxCoinSupply(_d C.Distribution__Handle, _arg0 *uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = d.MaxCoinSupply
	return
}

// nolint megacheck
//export SKY_params_Distribution_SetMaxCoinSupply
func SKY_params_Distribution_SetMaxCoinSupply(_d C.Distribution__Handle, _arg0 uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	d.MaxCoinSupply = _arg0
	_d = registerDistributionHandle(d)
	return
}

//export SKY_params_Distribution_GetInitialUnlockedCount
func SKY_params_Distribution_GetInitialUnlockedCount(_d C.Distribution__Handle, _arg0 *uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = d.InitialUnlockedCount
	return
}

// nolint megacheck
//export SKY_params_Distribution_SetInitialUnlockedCount
func SKY_params_Distribution_SetInitialUnlockedCount(_d C.Distribution__Handle, _arg0 uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	d.InitialUnlockedCount = _arg0
	_d = registerDistributionHandle(d)
	return
}

//export SKY_params_Distribution_GetUnlockAddressRate
func SKY_params_Distribution_GetUnlockAddressRate(_d C.Distribution__Handle, _arg0 *uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = d.UnlockAddressRate
	return
}

// nolint megacheck
//export SKY_params_Distribution_SetUnlockAddressRate
func SKY_params_Distribution_SetUnlockAddressRate(_d C.Distribution__Handle, _arg0 uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	d.UnlockAddressRate = _arg0
	_d = registerDistributionHandle(d)
	return
}

//export SKY_params_Distribution_GetUnlockTimeInterval
func SKY_params_Distribution_GetUnlockTimeInterval(_d C.Distribution__Handle, _arg0 *uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = d.UnlockTimeInterval
	return
}

// nolint megacheck
//export SKY_params_Distribution_SetUnlockTimeInterval
func SKY_params_Distribution_SetUnlockTimeInterval(_d C.Distribution__Handle, _arg0 uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	d.UnlockTimeInterval = _arg0
	_d = registerDistributionHandle(d)
	return
}

//export SKY_params_Distribution_GetAddresses
func SKY_params_Distribution_GetAddresses(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := d.Addresses
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

// nolint megacheck
//export SKY_params_Distribution_SetAddresses
func SKY_params_Distribution_SetAddresses(_d C.Distribution__Handle, _arg0 *[]string) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	d.Addresses = *_arg0
	_d = registerDistributionHandle(d)
	return
}

//export SKY_params_Distribution_Validate
func SKY_params_Distribution_Validate(_d C.Distribution__Handle) (____error_code uint32) {

	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	__return_err := d.Validate()
	____error_code = libErrorCode(__return_err)
	return

}

//export SKY_params_Distribution_AddressInitialBalance
func SKY_params_Distribution_AddressInitialBalance(_d C.Distribution__Handle, _arg0 *uint64) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	*_arg0 = d.AddressInitialBalance()
	return
}

//export SKY_params_Distribution_UnlockedAddresses
func SKY_params_Distribution_UnlockedAddresses(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}

	arg0 := d.UnlockedAddresses()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)

	return
}

//export SKY_params_Distribution_LockedAddresses
func SKY_params_Distribution_LockedAddresses(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}

	arg0 := d.LockedAddresses()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_params_Distribution_AddressesDecoded
func SKY_params_Distribution_AddressesDecoded(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := d.AddressesDecoded()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_params_Distribution_UnlockedAddressesDecoded
func SKY_params_Distribution_UnlockedAddressesDecoded(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := d.UnlockedAddressesDecoded()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_params_Distribution_LockedAddressesDecoded
func SKY_params_Distribution_LockedAddressesDecoded(_d C.Distribution__Handle, _arg0 *C.GoSlice_) (____error_code uint32) {
	d, ok := lookupDistributionHandle(_d)
	if !ok {
		____error_code = SKY_BAD_HANDLE
		return
	}
	arg0 := d.LockedAddressesDecoded()
	copyToGoSlice(reflect.ValueOf(arg0), _arg0)
	return
}

//export SKY_params_Distribution_GetMainNetDistribution
func SKY_params_Distribution_GetMainNetDistribution(handle *C.Distribution__Handle) (____error_code uint32) {
	d := params.Distribution{}
	d.MaxCoinSupply = params.MainNetDistribution.MaxCoinSupply
	d.InitialUnlockedCount = params.MainNetDistribution.InitialUnlockedCount
	d.UnlockAddressRate = params.MainNetDistribution.UnlockAddressRate
	d.UnlockTimeInterval = params.MainNetDistribution.UnlockTimeInterval
	d.Addresses = make([]string, 0)
	d.Addresses = append(d.Addresses, params.MainNetDistribution.Addresses...)
	*handle = registerDistributionHandle(&d)
	return
}

//export SKY_params_NewDistribution
func SKY_params_NewDistribution(_d *C.Distribution__Handle) (____error_code uint32) {
	d := params.Distribution{}
	*_d = registerDistributionHandle(&d)
	return
}
