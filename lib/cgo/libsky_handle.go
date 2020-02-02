package main

/*

  #include <string.h>
  #include <stdlib.h>


  #include "skytypes.h"
*/
import "C"

import (
	"github.com/spf13/cobra"

	"github.com/SkycoinProject/skycoin/src/api"
	"github.com/SkycoinProject/skycoin/src/cipher/bip32"
	"github.com/SkycoinProject/skycoin/src/cipher/bip44"
	"github.com/SkycoinProject/skycoin/src/cli"
	"github.com/SkycoinProject/skycoin/src/coin"
	"github.com/SkycoinProject/skycoin/src/params"
	"github.com/SkycoinProject/skycoin/src/readable"
	"github.com/SkycoinProject/skycoin/src/wallet"
)

type Handle uint64

var (
	handlesCounter uint64 = 0
	handleMap             = make(map[Handle]interface{})
)

func registerHandle(obj interface{}) C.Handle {
	handlesCounter++
	handle := handlesCounter
	handleMap[Handle(handle)] = obj
	return (C.Handle)(handle)
}

func lookupHandle(handle C.Handle) (interface{}, bool) {
	obj, ok := handleMap[Handle(handle)]
	return obj, ok
}

func overwriteHandle(handle C.Handle, obj interface{}) bool {
	_, ok := handleMap[Handle(handle)]
	if ok {
		handleMap[Handle(handle)] = obj
		return true
	}
	return false
}

func registerWalletHandle(obj *wallet.Wallet) C.Wallet__Handle {
	return (C.Wallet__Handle)(registerHandle(obj))
}

func lookupWalletHandle(handle C.Wallet__Handle) (*wallet.Wallet, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*wallet.Wallet); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupCollectionWalletHandle(handle C.Wallet__Handle) (*wallet.CollectionWallet, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*wallet.CollectionWallet); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupMetaWalletHandle(handle C.MetaWallet__Handle) (*wallet.Meta, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*wallet.Meta); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerReadableEntryHandle(obj *wallet.ReadableEntry) C.ReadableEntry__Handle {
	return (C.ReadableEntry__Handle)(registerHandle(obj))
}

func registerOptionsHandle(obj *wallet.Options) C.Options__Handle {
	return (C.Options__Handle)(registerHandle(obj))
}

func lookupOptionsHandle(handle C.Options__Handle) (*wallet.Options, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*wallet.Options); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupConfigHandle(handle C.Config__Handle) (*cli.Config, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*cli.Config); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupCLIHandle(handle C.CLI__Handle) (*cobra.Command, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*cobra.Command); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerClientHandle(obj *api.Client) C.Client__Handle {
	return (C.Client__Handle)(registerHandle(obj))
}

func lookupClientHandle(handle C.Client__Handle) (*api.Client, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.Client); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerWalletsHandle(obj *[]api.WalletResponse) C.Wallets__Handle {
	return (C.Wallets__Handle)(registerHandle(obj))
}

func lookupWalletsHandle(handle C.Wallets__Handle) ([]*api.WalletResponse, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).([]*api.WalletResponse); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerWalletResponseHandle(obj *api.WalletResponse) C.WalletResponse__Handle {
	return (C.WalletResponse__Handle)(registerHandle(obj))
}

func lookupWalletResponseHandle(handle C.WalletResponse__Handle) (*api.WalletResponse, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.WalletResponse); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupCreateTransactionRequestHandle(handle C.CreateTransactionRequest__Handle) (*api.CreateTransactionRequest, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.CreateTransactionRequest); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerPasswordReaderHandle(obj *cli.PasswordReader) C.PasswordReader__Handle {
	return (C.PasswordReader__Handle)(registerHandle(obj))
}

func lookupPasswordReaderHandle(handle C.PasswordReader__Handle) (*cli.PasswordReader, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*cli.PasswordReader); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerTransactionHandle(obj *coin.Transaction) C.Transaction__Handle {
	return (C.Transaction__Handle)(registerHandle(obj))
}

func lookupTransactionHandle(handle C.Transaction__Handle) (*coin.Transaction, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.Transaction); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerTransactionsHandle(obj *coin.Transactions) C.Transactions__Handle {
	return (C.Transactions__Handle)(registerHandle(obj))
}

func lookupTransactionsHandle(handle C.Transactions__Handle) (*coin.Transactions, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.Transactions); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupSortableTransactionsHandle(handle C.SortableTransactions__Handle) (*coin.SortableTransactions, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.SortableTransactions); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerBlockHandle(obj *coin.Block) C.Block__Handle {
	return (C.Block__Handle)(registerHandle(obj))
}

func lookupBlockHandle(handle C.Block__Handle) (*coin.Block, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.Block); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupSignedBlockHandle(handle C.SignedBlock__Handle) (*coin.SignedBlock, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.SignedBlock); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerBlockBodyHandle(obj *coin.BlockBody) C.BlockBody__Handle {
	return (C.BlockBody__Handle)(registerHandle(obj))
}

func lookupBlockBodyHandle(handle C.BlockBody__Handle) (*coin.BlockBody, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.BlockBody); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerCreatedTransactionHandle(obj *api.CreatedTransaction) C.CreatedTransaction__Handle {
	return (C.CreatedTransaction__Handle)(registerHandle(obj))
}

func lookupCreatedTransactionHandle(handle C.CreatedTransaction__Handle) (*api.CreatedTransaction, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.CreatedTransaction); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerCreatedTransactionOutputHandle(obj *api.CreatedTransactionOutput) C.CreatedTransactionOutput__Handle {
	return (C.CreatedTransactionOutput__Handle)(registerHandle(obj))
}

func registerCreatedTransactionInputHandle(obj *api.CreatedTransactionInput) C.CreatedTransactionInput__Handle {
	return (C.CreatedTransactionInput__Handle)(registerHandle(obj))
}

func registerCreateTransactionResponseHandle(obj *api.CreateTransactionResponse) C.CreateTransactionResponse__Handle {
	return (C.CreateTransactionResponse__Handle)(registerHandle(obj))
}

func registerBalanceResultHandle(obj *cli.BalanceResult) C.BalanceResult__Handle {
	return (C.BalanceResult__Handle)(registerHandle(obj))
}

func registerSortableTransactiontHandle(obj *coin.SortableTransactions) C.SortableTransactions__Handle {
	return (C.SortableTransactions__Handle)(registerHandle(obj))
}

func lookupAddressUxOutHandle(handle C.AddressUxOuts__Handle) (*coin.AddressUxOuts, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.AddressUxOuts); isOK {
			return obj, true
		}
	}
	return nil, false
}

func closeHandle(handle Handle) {
	delete(handleMap, handle)
}

//export SKY_handle_close
func SKY_handle_close(handle C.Handle) {
	closeHandle(Handle(handle))
}

//export SKY_handle_copy
func SKY_handle_copy(handle C.Handle, copy *C.Handle) uint32 {
	obj, ok := lookupHandle(handle)
	if ok {
		*copy = registerHandle(obj)
		return SKY_OK
	} else {
		return SKY_BAD_HANDLE
	}
}

func registerBuildInfoHandle(obj *readable.BuildInfo) C.BuildInfo__Handle {
	return (C.BuildInfo__Handle)(registerHandle(obj))
}

func lookupBuildInfoHandle(handle C.BuildInfo__Handle) (*readable.BuildInfo, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*readable.BuildInfo); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerBlockHeaderHandle(obj *coin.BlockHeader) C.BlockHeader__Handle {
	return (C.BlockHeader__Handle)(registerHandle(obj))
}

func lookupBlockHeaderHandle(handle C.BlockHeader__Handle) (*coin.BlockHeader, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.BlockHeader); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerWalletSeedResponseHandle(obj *api.WalletSeedResponse) C.WalletSeedResponse__Handle {
	return (C.WalletResponse__Handle)(registerHandle(obj))
}

func registerDistributionHandle(obj *params.Distribution) C.Distribution__Handle {
	return (C.Distribution__Handle)(registerHandle(obj))
}

func lookupDistributionHandle(handle C.Distribution__Handle) (*params.Distribution, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*params.Distribution); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupCreateWalletOptionsHandle(handle C.CreateWalletOptions__Handle) (*api.CreateWalletOptions, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.CreateWalletOptions); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupWalletRecoverRequestHandle(handle C.WalletRecoverRequest__Handle) (*api.WalletRecoverRequest, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*api.WalletRecoverRequest); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerPublicKeyHandle(obj *bip32.PublicKey) C.PublicKey__Handle {
	return (C.PublicKey__Handle)(registerHandle(obj))
}

func lookupPublicKeyHandle(handle C.PublicKey__Handle) (*bip32.PublicKey, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*bip32.PublicKey); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerPrivateKeyHandle(obj *bip32.PrivateKey) C.PrivateKey__Handle {
	return (C.PublicKey__Handle)(registerHandle(obj))
}

func lookupPrivateKeyHandle(handle C.PrivateKey__Handle) (*bip32.PrivateKey, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*bip32.PrivateKey); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerPathHandle(obj *bip32.Path) C.Path__Handle {
	return (C.Path__Handle)(registerHandle(obj))
}

func lookupPathHandle(handle C.Path__Handle) (*bip32.Path, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*bip32.Path); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerCoinHandle(obj *bip44.Coin) C.Coin__Handle {
	return (C.Coin__Handle)(registerHandle(obj))
}

func lookupCoinHandle(handle C.Coin__Handle) (*bip44.Coin, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*bip44.Coin); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerAccountHandle(obj *bip44.Account) C.Account__Handle {
	return (C.Account__Handle)(registerHandle(obj))
}

func lookupAccountHandle(handle C.Account__Handle) (*bip44.Account, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*bip44.Account); isOK {
			return obj, true
		}
	}
	return nil, false
}

func lookupGetOutputserHandle(handle C.GetOutputser__Handle) (*cli.GetOutputser, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*cli.GetOutputser); isOK {
			return obj, true
		}
	}
	return nil, false
}

func registerUnspentOutputsSummaryHandle(obj *readable.UnspentOutputsSummary) C.UnspentOutputsSummary__Handle {
	return (C.UnspentOutputsSummary__Handle)(registerHandle(obj))
}

func registerAddressUxOutsHandle(obj *coin.AddressUxOuts) C.AddressUxOuts__Handle {
	return (C.AddressUxOuts__Handle)(registerHandle(obj))
}

func lookupAddressUxOutsHandle(handle C.AddressUxOuts__Handle) (*coin.AddressUxOuts, bool) {
	obj, ok := lookupHandle(C.Handle(handle))
	if ok {
		if obj, isOK := (obj).(*coin.AddressUxOuts); isOK {
			return obj, true
		}
	}
	return nil, false
}
