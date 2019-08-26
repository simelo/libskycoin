#include "check.h"
#include "skyassert.h"
#include "skystring.h"
#include <string.h>

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
