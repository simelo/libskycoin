
[](https://user-images.githubusercontent.com/26845312/32426705-d95cb988-c281-11e7-9463-a3fce8076a72.png)

# Skycoin C library

[![Build Status](https://travis-ci.org/skycoin/libskycoin.svg)](https://travis-ci.org/skycoin/libskycoin)

Skycoin C library (a.k.a `libskycoin`) exports the Skycoin API to DApps using the C programming language.
It is also the foundation to build client libraries for other programming languages.

## Links

* [skycoin.net](https://www.skycoin.net)
* [Skycoin Blog](https://www.skycoin.net/blog)
* [Skycoin Docs](https://www.skycoin.net/docs)
* [Skycoin Blockchain Explorer](https://explorer.skycoin.net)
* [Skycoin Development Telegram Channel](https://t.me/skycoindev)
* [Skycoin Github Wiki](https://github.com/skycoin/skycoin/wiki)

## Subprojects

The Skycoin C library is made of the following components

- `lib/cgo`     : C wrappers for the Skycoin core API
- `lib/swig`    : SWIG interfaces to generate wrappers around the Skycoin core API for other programming languages
- `lib/swagger` : Swagger specifications for generating REST API clients
- `lib/curl`    : C REST client for the Skycoin HTTP API. Generated by [openapi-generator](https://github.com/OpenAPITools/openapi-generator). Powered by [libcurl](https://curl.haxx.se/libcurl/c/).

Consult respective `README` files for further details.

<!-- MarkdownTOC levels="1,2,3,4,5" autolink="true" bracket="round" -->
- [Make rules](#make-rules)
- [Development setup](#development-setup)
  - [Running tests](#running-tests)
  - [Releases](#releases)
    - [Update the version](#update-the-version)
    - [Pre-release testing](#pre-release-testing)
    - [Creating release builds](#creating-release-builds)
<!-- /MarkdownTOC -->

## Make Rules

All these make rules require skycoin to be a git submodule of pyskycoin

- `build-libc`
  * Compiles skycoin C language library.
- `test-libc`
  * Compiles skycoin C language library and executes the tests.	
- `build-libc-static`
  * Build libskycoin C static library
- `build-libc-shared`
  * Build libskycoin C shared library

  
## Development setup

  ### Running tests

  ```sh
  $ make test-libc
  ```

  ### Releases

  #### Update the version

  0. If the `master` branch has commits that are not in `develop` (e.g. due to a hotfix applied to `master`), merge `master` into `develop` (and fix any build or test failures)
  0. Switch to a new release branch named `release-X.Y.Z` for preparing the release.
  0. Ensure that the submodule at `gopath/src/github.com/skycoin/skycoin` is in sync with respect to the corresponding tag in https://github.com/skycoin/skycoin repository.
  0. Update `CHANGELOG.md`: move the "unreleased" changes to the version and add the date.
  0. Follow the steps in [pre-release testing](#pre-release-testing)
  0. Make a PR merging the release branch into `master`
  0. Review the PR and merge it
  0. Tag the `master` branch with the version number. Version tags start with `v`, e.g. `v0.20.0`. Sign the tag. If you have your GPG key in github, creating a release on the Github website will automatically tag the release. It can be tagged from the command line with `git tag -as v0.20.0 $COMMIT_ID`, but Github will not recognize it as a "release".
  0. Release builds are created and uploaded by travis. To do it manually, checkout the master branch and follow the [create release builds instructions](#creating-release-builds).

  #### Pre-release testing

  Perform these actions before releasing:

  ```sh
  make check
  ```
## Development

We have two branches: `master` and `develop`.

- `develop` is the default branch and will always have the latest code.
  The submodule at `gopath/src/github.com/skycoin/skycoin` has to be
  in sync with `skycoin/skycoin` `develop` branch.
- `master` will always be equal to the current stable release on the website, and should correspond with the latest release tag.
  The submodule at `gopath/src/github.com/skycoin/skycoin` has to be
  in sync with `skycoin/skycoin` `master` branch.

Separate stable development branches will be created to work on releases for supporting the
most recent stable version of Skycoin. The name of these branches should be the Skycoin
major and minor version numbers followed by `dev` suffix e.g. `0.25dev`.
These branches may be forked out of either `master` or `develop` branches, and 
the submodule at `gopath/src/github.com/skycoin/skycoin` has to be
in sync with the corresponding tag of `skycoin/skycoin` official repository.

Stable development branches are created most of the time for the following reasons:

- A Skycoin release increasing [patch version number](https://semver.org/).
- Enhanced support and bug fixes for a version of PySkycoin compiled against an
  stable version of Skycoin
- Backporting useful features added in `develop`.

### General development guidelines

The following rules are enforced

- Contributions must comply to the development guidelines documented in the [Skycoin wiki](https://github.com/skycoin/skycoin/wiki).
- C / C++ code must comply to the [Bitcoin C coding style](https://github.com/bitcoin/bitcoin/blob/master/doc/developer-notes.md#coding-style-c) (enforced by `clang-format`).

### Lib Curl, a Wrapper for Skycoin Api

This wrapper is Auto generated by openapi-generator directly from `Skycoin Api` code for version v0.25.1.

For further details of usage of `Lib Curl wrapper for Skycoin Api` see [Autogenerated documentation](./lib/curl/README.md)

### Doxygen comment syntax

If you want to continue with `the doxygen way`(we recommend it) of coding and document functions, structs, and functions, you should follow the specifications found in the [Doxygen official site](http://www.doxygen.nl/manual/docblocks.html).

An example of documentation using `doxygen` is the next:

```c
/**
 * Addresses of Bitcoin accounts
 */
typedef struct {
    GoUint8_ Version;      ///< Address version identifier.
                           ///< Used to differentiate testnet
                           ///< vs mainnet addresses, for instance.
    cipher__Ripemd160 Key; ///< Address hash identifier.
} cipher__BitcoinAddress;
```
This code example can be found at `include/cipher.bitcoin.go.h`.

Inside `/* */`  we found struct documentation, meanwhile `//<` symbol is used to describe fields of the struct.

After that, run `make docs` for a new docs generation. You can found the api documentation at `docs/libc` folder.

### Makefile targets:

|Target                        |Help|
| :-------------               | :----------: | 
|test-libc                     |Run tests for libskycoin C client library|
|docs                          |Generate documentation for all libraries|
|docs-libc                     |Generate libskycoin documentation|
|docs-skyapi                   |Generate SkyApi (libcurl) documentation|
|lint                          |Run linters. Use make install-linters first.|
|check                         |Run tests and linters|
|install-linters-Linux         |Install linters on GNU/Linux|
|install-linters-Darwin        |Install linters on Mac OSX|
|install-deps-Linux            |Install deps on GNU/Linux|
|install-deps-Darwin           |Install deps on Mac OSX|
|install-libraries-deps        |Install deps for `lib\curl` wrapper of Skycoin REST API|
|install-linters               |Install linters|
|install-deps-libc-linux       |Install locally dependencies for testing libskycoin|
|install-lib-curl              |Install Sky Api curl based rest wrapper|
|install-deps-libc-osx         |Install locally dependencies for testing libskycoin|
|format                        |Formats the code. Must have goimports installed (use make install-linters).|
|clean-libc                    |Clean files generate by library|
