package main

import (
	"unsafe"

	"github.com/SkycoinProject/skycoin/src/cli"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_cli_LoadConfig
func SKY_cli_LoadConfig(_arg0 *C.Config__Handle) (____error_code uint32) {
	__arg0, ____return_err := cli.LoadConfig()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = registerConfigHandle(&__arg0)
	}
	return
}

//export SKY_cli_Config_FullDBPath
func SKY_cli_Config_FullDBPath(_c C.Config__Handle, _arg0 *string) (____error_code uint32) {
	__c, okc := lookupConfigHandle(_c)
	if !okc {
		____error_code = SKY_BAD_HANDLE
		return
	}
	c := *__c
	*_arg0 = c.FullDBPath()
	return
}

//export SKY_cli_NewCLI
func SKY_cli_NewCLI(_cfg C.Config__Handle, _arg1 *C.CLI__Handle) (____error_code uint32) {
	__cfg, okcfg := lookupConfigHandle(_cfg)
	if !okcfg {
		____error_code = SKY_BAD_HANDLE
		return
	}
	cfg := *__cfg
	__arg1, ____return_err := cli.NewCLI(cfg)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		if cmd, ok := inplaceCobraCommand(__arg1); ok {
			*_arg1 = registerCLIHandle(cmd)
		} else {
			____error_code = SKY_ERROR
		}
	}
	return
}

//export SKY_cli_NewPasswordReader
func SKY_cli_NewPasswordReader(_password []byte, passwordReader *C.PasswordReader__Handle) {
	password := *(*[]byte)(unsafe.Pointer(&_password))
	pr := cli.NewPasswordReader(password)
	*passwordReader = registerPasswordReaderHandle(&pr)
}

//export SKY_cli_PasswordFromBytes_Password
func SKY_cli_PasswordFromBytes_Password(_p *C.cli__PasswordFromBytes, _arg0 *[]byte) (____error_code uint32) {
	p := *(*cli.PasswordFromBytes)(unsafe.Pointer(_p))
	__arg0, ____return_err := p.Password()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_cli_PasswordFromTerm_Password
func SKY_cli_PasswordFromTerm_Password(_arg0 *[]byte) (____error_code uint32) {
	p := cli.PasswordFromTerm{}
	__arg0, ____return_err := p.Password()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}
