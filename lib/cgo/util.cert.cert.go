package main

import (
	cert "github.com/skycoin/skycoin/src/util/certutil"
)

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_certutil_NewTLSCertPair
func SKY_certutil_NewTLSCertPair(organization string, validUntil string, extraHosts []string, _cert *[]byte, _key *[]byte) (____error_code uint32) {
	____time_validUntil, ____return_err := parseTimeValue(validUntil)
	if ____return_err == nil {
		cert, key, ____return_err := cert.NewTLSCertPair(organization, ____time_validUntil, extraHosts)
		if ____return_err == nil {
			*_cert = cert
			*_key = key
		}
	}
	____error_code = libErrorCode(____return_err)
	return
}
