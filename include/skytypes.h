
#ifndef SKYTYPES_H
#define SKYTYPES_H


#include <inttypes.h>
#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ uintptr_t
#endif

/**
 * Go 8-bit signed integer values.
 */
typedef signed char GoInt8_;
/**
 * Go 8-bit unsigned integer values.
 */
typedef unsigned char GoUint8_;
/**
 * Go 16-bit signed integer values.
 */
typedef short GoInt16_;
/**
 * Go 16-bit unsigned integer values.
 */
typedef unsigned short GoUint16_;
/**
 * Go 32-bit signed integer values.
 */
typedef int GoInt32_;
/**
 * Go 32-bit unsigned integer values.
 */
typedef unsigned int GoUint32_;
/**
 * Go 64-bit signed integer values.
 */
typedef long long GoInt64_;
/**
 * Go 64-bit unsigned integer values.
 */
typedef unsigned long long GoUint64_;
/**
 * Go integer values aligned to the word size of the underlying architecture.
 */
#if __x86_64__ || __ppc64__
typedef GoInt64_ GoInt_;
#else
typedef GoInt32_ GoInt_;
#endif
/**
 * Go unsigned integer values aligned to the word size of the underlying
 * architecture.
 */
#if __x86_64__ || __ppc64__
typedef GoUint64_ GoUint_;
#else
typedef GoUint32_ GoUint_;
#endif
/**
 * Architecture-dependent type representing instances Go `uintptr` type.
 * Used as a generic representation of pointer types.
 */
typedef __SIZE_TYPE__ GoUintptr_;
/**
 * Go single precision 32-bits floating point values.
 */
typedef float GoFloat32_;
/**
 * Go double precision 64-bits floating point values.
 */
typedef double GoFloat64_;
/**
 * Instances of Go `complex` type.
 */
typedef struct {
    float real;
    float imaginary;
} GoComplex64_;
/**
 * Instances of Go `complex` type.
 */
typedef struct {
    double real;
    double imaginary;
} GoComplex128_;
typedef unsigned int BOOL;
typedef unsigned int error;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt._
*/
#if __x86_64__ || __ppc64__
typedef char
    _check_for_64_bit_pointer_matchingGoInt[sizeof(void*) == 64 / 8 ? 1 : -1];
#endif

/**
 * Instances of Go `string` type.
 */
typedef struct {
    const char* p; ///< Pointer to string characters buffer.
    GoInt_ n;      ///< String size not counting trailing `\0` char
                   ///< if at all included.
} GoString_;
/**
 * Instances of Go `map` type.
 */
typedef void* GoMap_;

/**
 * Instances of Go `chan` channel types.
 */
typedef void* GoChan_;

/**
 * Instances of Go interface types.
 */
typedef struct {
    void* t; ///< Pointer to the information of the concrete Go type
             ///< bound to this interface reference.
    void* v; ///< Pointer to the data corresponding to the value
             ///< bound to this interface type.
} GoInterface_;
/**
 * Instances of Go slices
 */
typedef struct {
    void* data;
    GoInt_ len;
    GoInt_ cap;
} GoSlice_;

typedef struct {
    BOOL neg;
    GoSlice_ nat;
} Number;

typedef struct {
    // TODO: stdevEclipse Define Signature
    Number R;
    Number S;
} Signature;

#include "skytypes.gen.h"

/**
 * Internal representation of a Skycoin wallet.
 */
typedef struct {
    GoMap_ Meta;      ///< Records items that are not deterministic, like filename,
                      ///< lable, wallet type, secrets, etc.
    GoSlice_ Entries; ///< Entries field stores the address entries that are
                      ///< deterministically generated from seed.
} Wallet;

typedef GoUint8_ poly1305__Mac[16];
typedef GoUint8_ poly1305__Key[32];

/**
 * Memory handles returned back to the caller and manipulated
 * internally by API functions. Usually used to avoid type dependencies
 * with internal implementation types.
 */
typedef GoInt64_ Handle;

/**
 * Webrpc Client Handle
 */
typedef Handle WebRpcClient__Handle;

/**
 * Wallet Handle
 */
typedef Handle Wallet__Handle;

/**
 * ReadableWallet Handle
 */
typedef Handle ReadableWallet__Handle;

/**
 * ReadableEntry Handle
 */
typedef Handle ReadableEntry__Handle;

/**
 * Options Handle
 */
typedef Handle Options__Handle;

/**
 * Config Handle
 */
typedef Handle Config__Handle;

/**
 * CLI Handle
 */
typedef Handle CLI__Handle;

/**
 * API Client Handle
 */
typedef Handle Client__Handle;

/**
 * Wallet Response Handle
 */
typedef Handle WalletResponse__Handle;

/**
 * Create Transaction Request Handle
 */
typedef Handle CreateTransactionRequest__Handle;


/**
 * Instances of Go `map` type, deal map[string] as handle
 */
typedef Handle GoStringMap_;

/**
 * Wallets Handle, slice of Wallet
 */
typedef Handle Wallets__Handle;

/**
 * CollectionWallets Handle, slice of Wallet
 */
typedef Handle CollectionWallet__Handle;

/**
 * MetaWallet__Handle Handle, slice of Wallet
 */
typedef Handle MetaWallet__Handle;

/**
 * MetaWallet__Handle Handle, slice of Wallet
 */
typedef Handle WalletSeedResponse__Handle;

/**
 * Distribution__Handle Handle, struct param.distribution
 */
typedef Handle Distribution__Handle;

/**
 * CreateWalletOptions__Handle Handle, struct api.CreateWalletOptions
 */
typedef Handle CreateWalletOptions__Handle;

/**
 * WalletRecoverRequest__Handle Handle, struct api.WalletRecoverRequest
 */
typedef Handle WalletRecoverRequest__Handle;

/**
 * PublicKey__Handle Handle, struct bip32.Publickey
 */
typedef Handle PublicKey__Handle;

/**
 * PrivateKey__Handle Handle, struct bip32.Privatekey
 */
typedef Handle PrivateKey__Handle;

/**
 * Path__Handle Handle, struct bip32.Path
 */
typedef Handle Path__Handle;

/**
 * Coin__Handle Handle, struct bip44.Coin
 */
typedef Handle Coin__Handle;

/**
 * Account__Handle Handle, struct bip44.Account
 */
typedef Handle Account__Handle;

/**
 * GetOutputser__Handle Handle, interface cli.GetOutputser
 */

typedef Handle GetOutputser__Handle;

/**
 * Memory handle for internal object retrieving password to read
 * encrypted wallets.
 */
typedef Handle PasswordReader__Handle;

/**
 * Memory handle to perform Skycoin RPC API calls
 * encrypted wallets.
 */
typedef Handle WebRpcClient__Handle;

/**
 * Memory handle providing access to wallet data
 */
typedef Handle Wallet__Handle;

/**
 * Memory handle Options Handle
 */
typedef Handle Options__Handle;

/**
 * Memory handle to access to Skycoin CLI configuration
 */
typedef Handle Config__Handle;
/**
 * Memory handle to access to coin.Transaction
 */
typedef Handle Transaction__Handle;

/**
 * Memory handle to access to coin.Transactions
 */
typedef Handle Transactions__Handle;

/**
 * Memory handle to access to api.CreatedTransaction
 */
typedef Handle CreatedTransaction__Handle;

/**
 * Memory handle to access to api.CreatedTransactionOutput
 */
typedef Handle CreatedTransactionOutput__Handle;

/**
 * Memory handle to access to api.CreatedTransactionInput
 */
typedef Handle CreatedTransactionInput__Handle;

/**
 * Memory handle to access to api.CreateTransactionResponse
 */
typedef Handle CreateTransactionResponse__Handle;

/**
 * Memory handle to access to coin.Block
 */
typedef Handle Block__Handle;

/**
 * Memory handle to access to coin.SignedBlock
 */
typedef Handle SignedBlock__Handle;

/**
 * Memory handle to access to coin.BlockBody
 */
typedef Handle BlockBody__Handle;

/**
 * Memory handle to access to coin.BlockHeader
 */
typedef Handle BlockHeader__Handle;
/**
 * Memory handle to access to cli.BalanceResult
 */

typedef Handle BalanceResult_Handle;

/**
 * Memory handle to access to api.SpendResult
 */

typedef Handle SpendResult_Handle;

/**
 * Memory handle to access to coin.Transactions
 */

typedef Handle TransactionResult_Handle;

/**
 * Memory handle to access to coin.SortableTransactions
 */

typedef Handle SortableTransactions_Handle;

/**
 * Memory handle to access to wallet.Notes
 */

/**
 * Memory handle to access to wallet.ReadableNotes
 */

typedef Handle WalletReadableNotes_Handle;

/**
 * Memory handle to access to webrpc.OutputsResult
 */

typedef Handle OutputsResult_Handle;

/**
 * Memory handle to access to webrpc.StatusResult
 */

typedef Handle StatusResult_Handle;

/**
 * Memory handle to access to coin.AddressUxOuts
 */

typedef Handle AddressUxOuts_Handle;

/**
 * Memory handle to access to readable.BuildInfo (BuildInfo)
 */

typedef Handle BuildInfo_Handle;

/**
 * Memory handle to access to readable.UnspentOutputsSummary
 * (UnspentOutputsSummary)
 */

typedef Handle ReadableUnspentOutputsSummary_Handle;

/**
 * Memory handle for hash (ripemd160.digest)
 */

typedef Handle Hash_Handle;

/**
 * Handle for Number type
 */

typedef Handle Number_Handle;

/**
 * Handle for Signature type
 */

typedef Handle Signature_Handle;
/**
 * Handle for readable.UnspentOutputsSummary
 * */
typedef Handle UnspentOutputsSummary_Handle;

typedef GoUint32_ (*FeeCalcFunc)(Transaction__Handle handle, GoUint64_* pFee, void* context);

typedef struct {
    FeeCalcFunc callback;
    void* context;
} FeeCalculator;

#endif
