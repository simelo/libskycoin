package main

import (
	"reflect"
	"unsafe"

	cli "github.com/SkycoinProject/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
  #include "skyfee.h"
*/
import "C"

//export SKY_cli_LoadConfig
func SKY_cli_LoadConfig(_arg0 *C.cli__Config) (____error_code uint32) {
	__arg0, ____return_err := cli.LoadConfig()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = *(*C.cli__Config)(unsafe.Pointer(&__arg0))
	}
	return
}

//export SKY_cli_Config_FullDBPath
func SKY_cli_Config_FullDBPath(_c *C.cli__Config, _arg0 *C.GoString_) (____error_code uint32) {
	c := *(*cli.Config)(unsafe.Pointer(_c))
	__arg0 := c.FullDBPath()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cli_NewCLI
func SKY_cli_NewCLI(_cfg *C.cli__Config, _arg1 *C.CLI__Handle) (____error_code uint32) {
	cfg := *(*cli.Config)(unsafe.Pointer(_cfg))
	__arg1, ____return_err := cli.NewCLI(cfg)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = registerCLIHandle(__arg1)
	}
	return
}

//export SKY_cli_WalletLoadError_Error
func SKY_cli_WalletLoadError_Error(_e *C.cli__WalletLoadError, _arg0 *C.GoString_) (____error_code uint32) {
	e := *(*cli.WalletLoadError)(unsafe.Pointer(_e))
	__arg0 := e.Error()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cli_WalletSaveError_Error
func SKY_cli_WalletSaveError_Error(_e *C.cli__WalletSaveError, _arg0 *C.GoString_) (____error_code uint32) {
	e := *(*cli.WalletSaveError)(unsafe.Pointer(_e))
	__arg0 := e.Error()
	copyString(__arg0, _arg0)
	return
}

//export SKY_cli_PasswordFromBytes_Password
func SKY_cli_PasswordFromBytes_Password(_p *C.cli__PasswordFromBytes, _arg0 *C.GoSlice_) (____error_code uint32) {
	p := *(*cli.PasswordFromBytes)(unsafe.Pointer(_p))
	__arg0, ____return_err := p.Password()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	}
	return
}

//export SKY_cli_PasswordFromTerm_Password
func SKY_cli_PasswordFromTerm_Password(_p *C.cli__PasswordFromTerm, _arg0 *C.GoSlice_) (____error_code uint32) {
	p := *(*cli.PasswordFromTerm)(unsafe.Pointer(_p))
	__arg0, ____return_err := p.Password()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		copyToGoSlice(reflect.ValueOf(__arg0), _arg0)
	}
	return
}

//export SKY_cli_NewPasswordReader
func SKY_cli_NewPasswordReader(_p []byte, _arg1 *C.PasswordReader__Handle) (____error_code uint32) {
	p := *(*[]byte)(unsafe.Pointer(&_p))
	__arg1 := cli.NewPasswordReader(p)
	*_arg1 = registerPasswordReaderHandle(&__arg1)
	return
}
