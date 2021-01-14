package main

import file "github.com/SkycoinProject/skycoin/src/util/file"

/*

  #include <string.h>
  #include <stdlib.h>

  #include "skytypes.h"
*/
import "C"

//export SKY_file_InitDataDir
func SKY_file_InitDataDir(_dir string, _arg1 *string) (____error_code uint32) {
	dir := _dir
	__arg1, ____return_err := file.InitDataDir(dir)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg1 = __arg1
	}
	return
}

//export SKY_file_UserHome
func SKY_file_UserHome(_arg0 *string) (____error_code uint32) {
	*_arg0 = file.UserHome()
	return
}

//export SKY_file_ResolveResourceDirectory
func SKY_file_ResolveResourceDirectory(_path string, _arg1 *string) (____error_code uint32) {
	path := _path
	*_arg1 = file.ResolveResourceDirectory(path)
	return
}

//export SKY_file_DetermineResourcePath
func SKY_file_DetermineResourcePath(_staticDir string, _resourceDir string, _devDir string, _arg3 *string) (____error_code uint32) {
	staticDir := _staticDir
	resourceDir := _resourceDir
	devDir := _devDir
	__arg3, ____return_err := file.DetermineResourcePath(staticDir, resourceDir, devDir)
	____error_code = libErrorCode(____return_err)
	if ____return_err == nil {
		*_arg3 = __arg3
	}
	return
}
