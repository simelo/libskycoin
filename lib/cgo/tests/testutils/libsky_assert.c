#include "check.h"
#include "skyassert.h"
#include "skystring.h"
#include <string.h>

GoInt equalSlices(GoSlice* slice1, GoSlice* slice2, int elem_size)
{
    if (slice1->len != slice2->len)
        return 0;
    return (memcmp(slice1->data, slice2->data, slice1->len * elem_size) == 0);
}

GoInt equalSlices_(GoSlice_* slice1, GoSlice_* slice2, int elem_size)
{
    if (slice1->len != slice2->len)
        return 0;
    return (memcmp(slice1->data, slice2->data, slice1->len * elem_size) == 0);
}

GoInt equalTransactions(coin__Transactions* pTxs1, coin__Transactions* pTxs2)
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

GoInt isBitcoinAddressEq(cipher__BitcoinAddress* addr1, cipher__BitcoinAddress* addr2)
{
    return (addr1->Version == addr2->Version && isRipemd160Eq(&addr1->Key, &addr2->Key));
}


GoInt isSecKeyEq(cipher__SecKey* seckey1, cipher__SecKey* seckey2)
{
    return isU8Eq(*seckey1, *seckey2, sizeof(cipher__SecKey));
}

GoInt isSigEq(cipher__Sig* sig1, cipher__Sig* sig2)
{
    return isU8Eq(*sig1, *sig2, sizeof(cipher__Sig));
}

GoInt isSHA256Eq(cipher__SHA256* sh1, cipher__SHA256* sh2)
{
    return isU8Eq(*sh1, *sh2, sizeof(cipher__SHA256));
}

GoInt isGoSliceEq(GoSlice* slice1, GoSlice* slice2)
{
    return (slice1->len == slice2->len) &&
           (memcmp(slice1->data, slice2->data, slice1->len) == 0);
}

GoInt isGoSlice_Eq(GoSlice_* slice1, GoSlice_* slice2)
{
    return (slice1->len == slice2->len) &&
           (memcmp(slice1->data, slice2->data, slice1->len) == 0);
}

GoInt isTransactionsEq(coin__Transactions* x1, coin__Transactions* x2)
{
    return equalTransactions(x1, x2);
}

GoInt isUxOutEq(coin__UxOut* x1, coin__UxOut* x2)
{
    return memcmp(x1, x2, sizeof(coin__UxOut)) == 0;
}

GoInt isTransactionEq(coin__Transaction* x1, coin__Transaction* x2)
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

GoInt isTransactionOutputEq(coin__TransactionOutput* x1, coin__TransactionOutput* x2)
{
    if (x1->Coins != x2->Coins || x1->Hours != x2->Hours) {
        return 0;
    }

    if (!isAddressEq(&x1->Address, &x2->Address))
        return 0;
    return 1;
}

GoInt isUxArrayEq(coin__UxArray* slice1, coin__UxArray* slice2)
{
    return (memcmp(slice1->data, slice2->data, slice1->len) == 0) && ((slice1->len == slice2->len));
}

GoInt isTransactionHandleEq(Transaction__Handle* handle1, Transaction__Handle* handle2)
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

GoInt isPrivateKeyEq(PrivateKey__Handle handle1, PrivateKey__Handle handle2)
{
    GoUint8 bufferVersion1[1024];
    GoUint8 bufferVersion2[1024];
    GoSlice_ Version1 = {bufferVersion1, 0, 1024};
    GoSlice_ Version2 = {bufferVersion2, 0, 1024};
    GoUint8 bufferParentFingerprint1[1024];
    GoUint8 bufferParentFingerprint2[1024];
    GoSlice_ ParentFingerprint1 = {bufferParentFingerprint1, 0, 1024};
    GoSlice_ ParentFingerprint2 = {bufferParentFingerprint2, 0, 1024};
    GoUint32 childNumber1;
    GoUint32 childNumber2;
    GoUint8 bufferChainCode1[1024];
    GoUint8 bufferChainCode2[1024];
    GoSlice_ ChainCode1 = {bufferChainCode1, 0, 1024};
    GoSlice_ ChainCode2 = {bufferChainCode2, 0, 1024};
    GoUint8 bufferKey1[1024];
    GoUint8 bufferKey2[1024];
    GoSlice_ Key1 = {bufferKey1, 0, 1024};
    GoSlice_ Key2 = {bufferKey2, 0, 1024};
    GoUint8 Depth1;
    GoUint8 Depth2;

    GoUint32 err = SKY_bip32_PrivateKey_GetVersion(handle1, &Version1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_GetVersion(handle2, &Version2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&Version1, &Version2)) {
        printf("Version not equal\n");
        return 0;
    }

    err = SKY_bip32_PrivateKey_GetDepth(handle1, &Depth1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_GetDepth(handle2, &Depth2);
    ck_assert_int_eq(err, SKY_OK);
    if (Depth1 != Depth2) {
        printf("Depth not equal\n");
        return 0;
    }

    err = SKY_bip32_PrivateKey_GetParentFingerprint(handle1, &ParentFingerprint1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_GetParentFingerprint(handle2, &ParentFingerprint2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&ParentFingerprint1, &ParentFingerprint2)) {
        printf("ParentFingerprint not equal\n");
        return 0;
    }

    err = SKY_bip32_PrivateKey_ChildNumber(handle1, &childNumber1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_ChildNumber(handle2, &childNumber2);
    ck_assert_int_eq(err, SKY_OK);
    if (childNumber1 != childNumber2) {
        printf("childNumber not equal\n");
        return 0;
    }

    err = SKY_bip32_PrivateKey_GetChainCode(handle1, &ChainCode1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_GetChainCode(handle2, &ChainCode2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&ChainCode1, &ChainCode2)) {
        printf("ChainCode not equal\n");
        return 0;
    }

    err = SKY_bip32_PrivateKey_GetKey(handle1, &Key1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_GetKey(handle2, &Key2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&Key1, &Key2)) {
        printf("Key not equal\n");
        return 0;
    }

    return 1;
}

GoInt isPublicKeyEq(PublicKey__Handle handle1, PublicKey__Handle handle2)
{
    GoUint8 bufferVersion1[1024];
    GoUint8 bufferVersion2[1024];
    GoSlice_ Version1 = {bufferVersion1, 0, 1024};
    GoSlice_ Version2 = {bufferVersion2, 0, 1024};
    GoUint8 bufferParentFingerprint1[1024];
    GoUint8 bufferParentFingerprint2[1024];
    GoSlice_ ParentFingerprint1 = {bufferParentFingerprint1, 0, 1024};
    GoSlice_ ParentFingerprint2 = {bufferParentFingerprint2, 0, 1024};
    GoUint32 childNumber1;
    GoUint32 childNumber2;
    GoUint8 bufferChainCode1[1024];
    GoUint8 bufferChainCode2[1024];
    GoSlice_ ChainCode1 = {bufferChainCode1, 0, 1024};
    GoSlice_ ChainCode2 = {bufferChainCode2, 0, 1024};
    GoUint8 bufferKey1[1024];
    GoUint8 bufferKey2[1024];
    GoSlice_ Key1 = {bufferKey1, 0, 1024};
    GoSlice_ Key2 = {bufferKey2, 0, 1024};
    GoUint8 Depth1;
    GoUint8 Depth2;

    GoUint32 err = SKY_bip32_PublicKey_GetVersion(handle1, &Version1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetVersion(handle2, &Version2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&Version1, &Version2)) {
        return 0;
    }

    err = SKY_bip32_PublicKey_GetDepth(handle1, &Depth1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetDepth(handle2, &Depth2);
    ck_assert_int_eq(err, SKY_OK);
    if (Depth1 != Depth2) {
        return 0;
    }

    err = SKY_bip32_PublicKey_GetParentFingerprint(handle1, &ParentFingerprint1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetParentFingerprint(handle2, &ParentFingerprint2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&ParentFingerprint1, &ParentFingerprint2)) {
        return 0;
    }

    err = SKY_bip32_PublicKey_ChildNumber(handle1, &childNumber1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_ChildNumber(handle2, &childNumber2);
    ck_assert_int_eq(err, SKY_OK);
    if (childNumber1 != childNumber2) {
        return 0;
    }

    err = SKY_bip32_PublicKey_GetChainCode(handle1, &ChainCode1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetChainCode(handle2, &ChainCode2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&ChainCode1, &ChainCode2)) {
        return 0;
    }

    err = SKY_bip32_PublicKey_GetKey(handle1, &Key1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetKey(handle2, &Key2);
    ck_assert_int_eq(err, SKY_OK);
    if (!isGoSlice_Eq(&Key1, &Key2)) {
        return 0;
    }

    return 1;
}
