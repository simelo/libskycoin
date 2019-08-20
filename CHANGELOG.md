# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased

### Added

- Added swagger specification for `Skycoin REST API` to v0.27.0
- Added `wallet.collection_wallet`
- Added datatype `CollectionWallet__Handle`
- Added datatype `MetaWallet__Handle`
- Added function `SKY_wallet_CollectionWallet_AddEntry`
- Added function `SKY_wallet_CollectionWallet_GetEntry`
- Added function `SKY_wallet_CollectionWallet_GetAddresses`
- Added function `SKY_wallet_CollectionWallet_GenerateAddresses`
- Added function `SKY_wallet_MetaWallet_IsEncrypted`
- Added function `SKY_wallet_MetaWallet_Label`
- Added function `SKY_wallet_MetaWallet_Filename`
- Added function `SKY_wallet_MetaWallet_Version`
- Added function `SKY_wallet_MetaWallet_Type`
- Added datatype `WalletSeedResponse__Handle`
- Added datatype `Distribution__Handle`
- Added datatype `SKY_params_Distribution_GetMaxCoinSupply`
- Added datatype `SKY_params_Distribution_SetMaxCoinSupply`
- Added datatype `SKY_params_Distribution_GetInitialUnlockedCount`
- Added datatype `SKY_params_Distribution_SetInitialUnlockedCount`
- Added datatype `SKY_params_Distribution_GetUnlockAddressRate`
- Added datatype `SKY_params_Distribution_SetUnlockAddressRate`
- Added datatype `SKY_params_Distribution_GetUnlockTimeInterval`
- Added datatype `SKY_params_Distribution_SetUnlockTimeInterval`
- Added datatype `SKY_params_Distribution_GetAddresses`
- Added datatype `SKY_params_Distribution_SetAddresses`
- Added datatype `SKY_params_Distribution_Validate`
- Added datatype `SKY_params_Distribution_AddressInitialBalance`
- Added datatype `SKY_params_Distribution_UnlockedAddresses`
- Added datatype `SKY_params_Distribution_LockedAddresses`
- Added datatype `SKY_params_Distribution_AddressesDecoded`
- Added datatype `SKY_params_Distribution_UnlockedAddressesDecoded`
- Added datatype `SKY_params_Distribution_LockedAddressesDecoded`
- Added datatype `SKY_params_Distribution_GetMainNetDistribution`
- Added function `SKY_cipher_Sig_String`
- Added function `SKY_cipher_Sig_Null`
- Added function `SKY_cipher_VerifySignatureRecoverPubKey`
- Added datatype `CreateWalletOptionsHandle`
- Added function `SKY_api_Client_CreateWallet`
- Added function `SKY_api_Client_InjectTransactionNoBroadcast`
- Added function `SKY_api_Client_InjectEncodedTransactionNoBroadcast`
- Added function `SKY_api_Client_RecoverWallet`
- Added datatype `CreateWalletOptions__Handle`
- Added datatype `WalletRecoverRequest__Handle`
- Added datatype `PublicKey__Handle`
- Added datatype `PrivateKey__Handle`
- Added datatype `Path`
- Added datatype `PathNode`
- Added function `SKY_bip32_PrivateKey_DeriveSubpath`
- Added function `SKY_bip32_PrivateKey_Publickey`
- Added function `SKY_bip32_PrivateKey_Fingerprint`
- Added function `SKY_bip32_PublicKey_Fingerprint`
- Added function `SKY_bip32_PrivateKey_Identifier`
- Added function `SKY_bip32_PublicKey_Identifier`
- Added function `SKY_bip32_PrivateKey_NewPrivateChildKey`
- Added function `SKY_bip32_PrivateKey_NewPublicChildKey`
- Added function `SKY_bip32_PrivateKey_Serialize`
- Added function `SKY_bip32_PublicKey_Serialize`
- Added function `SKY_bip32_PrivateKey_String`
- Added function `SKY_bip32_PublicKey_String`
- Added function `SKY_bip32_DeserializeEncodedPrivateKey`
- Added function `SKY_bip32_DeserializePrivateKey`
- Added function `SKY_bip32_DeserializeEncodedPublicKey`
- Added function `SKY_bip32_DeserializePublicKey`
- Added function `SKY_bip32_PathNode_Hardened`
- Added function `SKY_bip32_ParsePath`
- Added datatype `bip44_CoinType`
- Added function `SKY_bip44_NewCoin`
- Added datatype `Account__Handle`
- Added datatype `Coin__Handle`
- Added function `SKY_bip44_Coin_Account`
- Added function `SKY_bip44_Account_External`
- Added function `SKY_bip44_Account_Change`
- Added function `SKY_bip44_Account_String`
- Added function `SKY_bip44_Account_GetPrivateKey`
- Added function `SKY_bip32_PrivateKey_GetKey`
- Added function `SKY_bip32_PublicKey_GetKey`
- Added datatype `coin__HashPair`


### Removed

- Removed function `SKY_wallet_Wallet_AddEntry`
- Removed function `SKY_wallet_Wallet_GetEntry`
- Removed function `SKY_wallet_Wallet_GetAddresses`
- Removed function `SKY_wallet_Wallet_GenerateAddresses`
- Removed function `SKY_wallet_Wallet_IsEncrypted`
- Removed function `SKY_wallet_Wallet_Label`
- Removed function `SKY_wallet_Wallet_File`
- Removed function `SKY_wallet_Wallet_Version`
- Removed function `SKY_wallet_Wallet_Type`
- Removed function `SKY_cli_Config_FullWalletPath`
- Removed function `SKY_api_Client_CreateUnencryptedWallet`
- Removed function `SKY_api_Client_CreateEncryptedWallet`
- Removed function `SKY_cli_GenerateWallet`
- Removed function `SKY_params_GetDistributionAddresses`
- Removed function `SKY_params_GetUnlockedDistributionAddresses`
- Removed function `SKY_params_GetLockedDistributionAddresses`
- Removed function `SKY_wallet_LoadReadableWallet`
- Removed function `SKY_wallet_ReadableWallet_Save`
- Removed function `SKY_wallet_ReadableWallet_Load`
- Removed function `SKY_wallet_ReadableWallet_Erase`
- Removed function `SKY_api_Handle_GetWalletMeta`
- Removed function `SKY_api_Handle_GetWalletEntriesCount`
- Removed function `SKY_api_Handle_WalletGetEntry`
- Removed function `SKY_api_Handle_WalletResponseGetCryptoType`

### Changed

- Update `lib/curl` to v0.27.0
- Update submodule to `skycoin == 0.27.0`
- Change datatype `SKY_cli_AddPrivateKey`
- Change datatype `SKY_api_Client_WalletSeed`
- Rename function `SKY_wallet_Wallet_Lock` => `SKY_wallet_Lock`
- Rename function `SKY_wallet_Wallet_Unlock` => `SKY_wallet_Unlock`

## [0.26.0] - 2019-07-12

### Added

- Added datatype `api__TransactionInput`
- Added datatype `transaction__UxBalance`
- Added function `SKY_transaction_NewUxBalances`,
- Added function `SKY_transaction_DistributeCoinHoursProportional`, `SKY_transaction_DistributeSpendHours`
- Added funcion `SKY_coin_VerifyInputSignatures`
- Added funcion `SKY_coin_BlockHeader_SetTime`
- Added funcion `SKY_coin_BlockHeader_SetBkSeq`
- Added funcion `SKY_coin_BlockHeader_SetFee`
- Added funcion `SKY_coin_BlockHeader_SetVersion`
- Added funcion `SKY_coin_BlockHeader_Version`
- Added funcion `SKY_coin_BlockHeader_PrevHash`
- Support for this new functions in `skyapi`:
  - Add POST /api/v2/wallet/transaction/sign to sign an unsigned transaction with a wallet
  - Add POST /api/v2/transaction to create an unsigned transaction from addresses or unspent outputs without a wallet
  - Add /api/v2/data APIs for transaction notes and generic key-value storage.
  - Update /metrics endpoint to add metrics from /health: unspent_outputs, unconfirmed_txns, time_since_last_block_seconds, open_connections, outgoing_connections, incoming_connections, start_at, uptime_seconds, last_block_seq.

### Changed

- Support for this changed functions in `skyapi`:
  - Add /api/v1/resendUnconfirmedTxns to the WALLET API set
  - In POST /api/v1/wallet/transaction, moved wallet parameters to the top level of the object
  - POST /api/v2/wallet/seed/verify returns an error if the seed's checksum is invalid
  - Increase the detail of error messages for invalid seeds sent to POST /api/v2/wallet/seed/verify

### Removed

- Removed symbolic links from vendor
- Removed function `SKY_webrpc_NewClient`, `SKY_webrpc_Client_CSRF`, `SKY_webrpc_Client_InjectTransaction`, `SKY_webrpc_Client_GetStatus`,`SKY_webrpc_Client_GetTransactionByID`, `SKY_webrpc_Client_GetAddressUxOuts`, `SKY_webrpc_Client_GetBlocksInRange`, `SKY_webrpc_Client_GetBlocksBySeq` and `SKY_webrpc_Client_GetLastBlocks`.
- Removed datatype `wallet__UxBalance`
- Removed fuction `SKY_cipher_VerifySignedHash`
- Removed fuction `SKY_bip39_MnemonicToByteArray`
- Removed fuction `SKY_api_Client_Spend`, `SKY_api_Client_AddressTransactions`
- Removed fuction `SKY_coin_Block_PreHashHeader`, `SKY_coin_Block_String` and `SKY_coin_BlockHeader_String`.
- Removed functions exported for `coin.math`
- Removed function `SKY_coin_Transaction_TxID`
- Removed function `SKY_wallet_DistributeSpendHours`
- Removed function `SKY_wallet_DistributeCoinHoursProportional`
- Removed function `SKY_wallet_NewUxBalances`
- Removed support for next functions in `skyapi`:
  - /api/v1/explorer/address endpoint (use GET /api/v1/transactions?verbose=1 instead). See https://github.com/skycoin/skycoin/blob/develop/src/api/README.md#migrating-from--api-v1-explorer-address
  - The unversioned REST API (the -enable-unversioned-api is removed, prefix your API requests with /api/v1 if they don't have an /api/vx prefix already). See https://github.com/skycoin/skycoin/blob/develop/src/api/README.md#migrating-from-the-unversioned-api
  - /api/v1/wallet/spend endpoint (use POST /api/v1/wallet/transaction followed by POST /api/v1/injectTransaction instead). See https://github.com/skycoin/skycoin/blob/develop/src/api/README.md#migrating-from--api-v1-spend

## [0.25.1] - 2019-06-30

### Added

- Be able to set a build type for lib curl.
- Export functions in Skycoin 0.25.1 core API's
- `skyapi` C client for Skycoin node REST at `lib/curl`.
- Support for building `libskycoin` on ARM and 32 / 64 bits.

### Fixed

- `/api/v1/health` will return correct build info when running Docker containers based on `skycoin/skycoin` mainnet image.

### Changed

- Adapt `libskycoin` after switching `skycoin-cli` from `urfave/cli` to `spf13/cobra`.

### Removed

- Delete function `SKY_base58_String2Hex`

## [0.25.0] - 2018-12-19

### Added

- Export functions in Skycoin 0.25.0 core API's
- Coinhour burn factor when creating transactions can be configured at runtime with `USER_BURN_FACTOR` envvar
- Max transaction size when creating transactions can be configured at runtime with `USER_MAX_TXN_SIZE` envvar
- Max decimals allowed when creating transactions can be configured at runtime with `USER_MAX_DECIMALS` envvar
- Complete support for `cipher` package in `libskycoin` C API.
- Add `coin`, `wallet`, `util/droplet` and `util/fee` methods as part of `libskycoin` C API
- Add `util/droplet` and `util/fee` API's as part of `libskycoin`
- Implement SWIG interfaces in order to generate client libraries for multiple programming languages
