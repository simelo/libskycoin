package main

import iputil "github.com/skycoin/skycoin/src/util/iputil"

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_iputil_LocalhostIP
func SKY_iputil_LocalhostIP(_arg0 *string) (____error_code uint32) {
	__arg0, ____return_err := iputil.LocalhostIP()
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg0 = __arg0
	}
	return
}

//export SKY_iputil_IsLocalhost
func SKY_iputil_IsLocalhost(_addr string, _arg1 *bool) (____error_code uint32) {
	addr := _addr
	__arg1 := iputil.IsLocalhost(addr)
	*_arg1 = __arg1
	return
}

//export SKY_iputil_SplitAddr
func SKY_iputil_SplitAddr(_addr string, _arg1 *string, _arg2 *uint16) (____error_code uint32) {
	addr := _addr
	__arg1, __arg2, ____return_err := iputil.SplitAddr(addr)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
		*_arg2 = __arg2
	}
	return
}
