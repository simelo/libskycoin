
#include "check.h"
#include "skyassert.h"
#include "skystring.h"
#include <string.h>


GoInt_ equalSlices(GoSlice* slice1, GoSlice* slice2, int elem_size)
{
    if (slice1->len != slice2->len)
        return 0;
    return (memcmp(slice1->data, slice2->data, slice1->len * elem_size) == 0);
}

GoInt_ equalSlices_(GoSlice_* slice1, GoSlice_* slice2, int elem_size)
{
    if (slice1->len != slice2->len)
        return 0;
    return (memcmp(slice1->data, slice2->data, slice1->len * elem_size) == 0);
}

GoInt_ equalTransactions(coin__Transactions* pTxs1, coin__Transactions* pTxs2)
{
    if (pTxs1->len != pTxs2->len)
        return 0;
    coin__Transaction* pTx1 = pTxs1->data;
    coin__Transaction* pTx2 = pTxs2->data;
    int i;
    for (i = 0; i < pTxs1->len; i++) {
        if (!isTransactionEq(pTx1, pTx2))
            return 0;
        pTx1++;
        pTx2++;
    }
    return 1;
}

GoInt_ isAddressEq(cipher__Address* addr1, cipher__Address* addr2)
{
    return (addr1->Version == addr2->Version && isRipemd160Eq(&addr1->Key, &addr2->Key));
}

GoInt_ isBitcoinAddressEq(cipher__BitcoinAddress* addr1, cipher__BitcoinAddress* addr2)
{
    return (addr1->Version == addr2->Version && isRipemd160Eq(&addr1->Key, &addr2->Key));
}

GoInt_ isGoStringEq(GoString string1, GoString string2)
{
    return (string1.n == string2.n) &&
           (strcmp(string1.p, string2.p) == 0);
}

GoInt_ isGoString_Eq(GoString_ string1, GoString_ string2)
{
    return (string1.n == string2.n) &&
           (strcmp(string1.p, string2.p) == 0);
}

GoInt_ isSecKeyEq(cipher__SecKey* seckey1, cipher__SecKey* seckey2)
{
    return isU8Eq(*seckey1, *seckey2, sizeof(cipher__SecKey));
}

GoInt_ isPubKeyEq(cipher__PubKey* pubkey1, cipher__PubKey* pubkey2)
{
    return isU8Eq(*pubkey1, *pubkey2, sizeof(cipher__PubKey));
}

GoInt_ isSigEq(cipher__Sig* sig1, cipher__Sig* sig2)
{
    return isU8Eq(*sig1, *sig2, sizeof(cipher__Sig));
}

GoInt_ isU8Eq(GoUint8_ p1[], GoUint8_ p2[], size_t len)
{
    for (GoInt i = 0; i < len; i++) {
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}

GoInt_ isSHA256Eq(cipher__SHA256* sh1, cipher__SHA256* sh2)
{
    return isU8Eq(*sh1, *sh2, sizeof(cipher__SHA256));
}

GoInt_ isGoSliceEq(GoSlice* slice1, GoSlice* slice2)
{
    return (slice1->len == slice2->len) &&
           (memcmp(slice1->data, slice2->data, slice1->len) == 0);
}

GoInt_ isGoSlice_Eq(GoSlice_* slice1, GoSlice_* slice2)
{
    return (slice1->len == slice2->len) &&
           (memcmp(slice1->data, slice2->data, slice1->len) == 0);
}

GoInt_ isTransactionsEq(coin__Transactions* x1, coin__Transactions* x2)
{
    return equalTransactions(x1, x2);
}

GoInt_ isUxOutEq(coin__UxOut* x1, coin__UxOut* x2)
{
    return memcmp(x1, x2, sizeof(coin__UxOut)) == 0;
}

GoInt_ isTransactionEq(coin__Transaction* x1, coin__Transaction* x2)
{
    if (x1->Length != x2->Length || x1->Type != x2->Type) {
        return 0;
    }
    if (!isSHA256Eq(&x1->InnerHash, &x2->InnerHash))
        return 0;
    if (!equalSlices_(&x1->Sigs, &x2->Sigs, sizeof(cipher__Sig)))
        return 0;
    if (!equalSlices_(&x1->In, &x2->In, sizeof(cipher__SHA256)))
        return 0;
    if (!equalSlices_(&x1->Out, &x2->Out, sizeof(coin__TransactionOutput)))
        return 0;
    return 1;
}

GoInt_ isTransactionOutputEq(coin__TransactionOutput* x1, coin__TransactionOutput* x2)
{
    if (x1->Coins != x2->Coins || x1->Hours != x2->Hours) {
        return 0;
    }

    if (!isAddressEq(&x1->Address, &x2->Address))
        return 0;
    return 1;
}

GoInt_ isUxArrayEq(coin__UxArray* slice1, coin__UxArray* slice2)
{
    return (memcmp(slice1->data, slice2->data, slice1->len) == 0) && ((slice1->len == slice2->len));
}

GoInt_ isRipemd160Eq(cipher__Ripemd160* rip1, cipher__Ripemd160* rip2)
{
    return isU8Eq(*rip1, *rip2, sizeof(cipher__Ripemd160));
}

GoInt_ isTransactionHandleEq(Transaction__Handle* handle1, Transaction__Handle* handle2)
{
    GoUint32 len1 = 0;
    GoUint32 len2 = 0;
    GoUint8 type1 = 0;
    GoUint8 type2 = 0;
    cipher__SHA256 sha1 = "";
    cipher__SHA256 sha2 = "";
    GoUint8 bufferP1[1024];
    GoUint8 bufferP2[1024];
    GoSlice_ p1 = {bufferP1, 0, 1024};
    GoSlice_ p2 = {bufferP2, 0, 1024};

    GoUint32 err = SKY_coin_Transaction_GetLength(*handle1, &len1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetLength(*handle2, &len2);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetType(*handle1, &type1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetType(*handle2, &type2);
    ck_assert_int_eq(err, SKY_OK);

    if (len1 != len2 || type1 != type2) {
        return 0;
    }
    err = SKY_coin_Transaction_GetInnerHash(*handle1, &sha1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetInnerHash(*handle2, &sha2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isSHA256Eq(&sha1, &sha2))
        return 0;

    err = SKY_coin_Transaction_GetSigs(*handle1, &p1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetSigs(*handle2, &p2);
    ck_assert_int_eq(err, SKY_OK);
    if (!equalSlices_(&p1, &p2, sizeof(cipher__Sig)))
        return 0;
    err = SKY_coin_Transaction_GetIn(*handle1, &p1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetIn(*handle2, &p2);
    ck_assert_int_eq(err, SKY_OK);
    if (!equalSlices_(&p1, &p2, sizeof(cipher__SHA256)))
        return 0;
    err = SKY_coin_Transaction_GetOut(*handle1, &p1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_coin_Transaction_GetOut(*handle2, &p2);
    ck_assert_int_eq(err, SKY_OK);
    if (!equalSlices_(&p1, &p2, sizeof(coin__TransactionOutput)))
        return 0;
    return 1;
}