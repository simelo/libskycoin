# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c

# Utility rule file for ExperimentalTest.

CMakeFiles/ExperimentalTest:
	/opt/cmake/bin/ctest -D ExperimentalTest

ExperimentalTest: CMakeFiles/ExperimentalTest
ExperimentalTest: CMakeFiles/ExperimentalTest.dir/build.make
.PHONY : ExperimentalTest

# Rule to build all files generated by this target.
CMakeFiles/ExperimentalTest.dir/build: ExperimentalTest
.PHONY : CMakeFiles/ExperimentalTest.dir/build

CMakeFiles/ExperimentalTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExperimentalTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExperimentalTest.dir/clean

CMakeFiles/ExperimentalTest.dir/depend:
	cd /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c /home/maceo/goeg/src/github.com/skycoin/libskycoin/lib/curl/c/CMakeFiles/ExperimentalTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExperimentalTest.dir/depend

