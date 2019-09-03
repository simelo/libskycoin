#ifndef LIBSKY_ASSERT_H
#define LIBSKY_ASSERT_H

#include "libskycoin.h"
#include "skyerrors.h"

extern GoInt isAddressEq(cipher__Address* addr1, cipher__Address* addr2);

extern GoInt isAddressEqPtr(cipher__Address addr1, cipher__Address addr2);

extern GoInt isBitcoinAddressEq(cipher__BitcoinAddress* addr1, cipher__BitcoinAddress* addr2);

extern GoInt isPubKeyEq(cipher__PubKey* pubkey1, cipher__PubKey* pubkey2);

extern GoInt isSigEq(cipher__Sig* sig1, cipher__Sig* sig2);

extern GoInt isSecKeyEq(cipher__SecKey* seckey1, cipher__SecKey* seckey2);

extern GoInt isSHA256Eq(cipher__SHA256* sh1, cipher__SHA256* sh2);

extern GoInt isRipemd160Eq(cipher__Ripemd160* rip1, cipher__Ripemd160* rip2);

extern GoInt isU8Eq(unsigned char p1[], unsigned char p2[], size_t len);

extern GoInt isGoSliceEq(GoSlice* slice1, GoSlice* slice2);

extern GoInt isGoSlice_Eq(GoSlice_* slice1, GoSlice_* slice2);

extern GoInt isUxOutEq(coin__UxOut* x1, coin__UxOut* x2);

extern GoInt isUxArrayEq(coin__UxArray* slice1, coin__UxArray* slice2);

extern GoInt isTransactionEq(coin__Transaction* x1, coin__Transaction* x2);

extern GoInt isTransactionHandleEq(Transaction__Handle* handle1, Transaction__Handle* handle2);

extern GoInt isTransactionsEq(coin__Transactions* x1, coin__Transactions* x2);

extern GoInt isTransactionOutputEq(coin__TransactionOutput* x1, coin__TransactionOutput* x2);

extern GoInt isGoStringEq(GoString string1, GoString string2);

extern GoInt isGoString_Eq(GoString_ string1, GoString_ string2);

extern GoInt isPrivateKeyEq(PrivateKey__Handle handle1, PrivateKey__Handle handle2);
extern GoInt isPublicKeyEq(PublicKey__Handle handle1, PublicKey__Handle handle2);

#endif // LIBSKY_ASSERT_H
