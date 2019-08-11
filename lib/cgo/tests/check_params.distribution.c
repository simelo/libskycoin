#include "libskycoin.h"
#include "skyassert.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>


START_TEST(TestDistributionAddressArrays)
{
    GoUint8_ bufferunlocked[1024];
    GoUint8_ bufferlocked[1024];
    Strings__Handle address = 0;
    Strings__Handle unlocked = 0;
    Strings__Handle locked = 0;
    Distribution__Handle dist = 0;
    SKY_params_NewDistribution(&dist);
    GoUint32_ err = SKY_params_Distribution_GetMainNetDistribution(&dist);
    ck_assert_msg(err == SKY_OK, "%X", err);
    err = SKY_params_Distribution_GetAddresses(dist, &address);
    ck_assert_msg(err == SKY_OK, "%X", err);
    GoUint32 count = 0;
    err = SKY_Handle_Strings_GetCount(address, &count);
    ck_assert_msg(err == SKY_OK, "%X", err);
    ck_assert(count == 100);
    GoUint8_ bufferAddr[1024];
    GoString_ addr = {bufferAddr, 0};
    err = SKY_params_Distribution_UnlockedAddresses(dist, &unlocked);
    ck_assert_msg(err == SKY_OK, "%X", err);
    GoUint32 countUnlock;
    err = SKY_Handle_Strings_GetCount(unlocked, &countUnlock);
    ck_assert_msg(err == SKY_OK, "%X", err);
    ck_assert(countUnlock == 25);
    err = SKY_params_Distribution_LockedAddresses(dist, &locked);
    ck_assert_msg(err == SKY_OK, "%X", err);
    GoUint32 countLock;
    err = SKY_Handle_Strings_GetCount(locked, &countLock);
    ck_assert_msg(err == SKY_OK, "%X", err);
    ck_assert(countLock == 75);

    int i, j, k;
    int notfound;

    for (i = 0; i < countUnlock; ++i) {
        GoUint8_ bufferi[1024];
        GoString_ iStr = {bufferi, 0, 1024};
        err = SKY_Handle_Strings_GetAt(unlocked, i, &iStr);
        ck_assert_msg(err == SKY_OK, "%X", err);
        // Check no duplicate address in unlocked addresses
        for (j = i + 1; j < countUnlock; ++j) {
            GoUint8_ bufferj[1024];
            GoString_ jStr = {bufferj, 0, 1024};
            err = SKY_Handle_Strings_GetAt(unlocked, j, &jStr);
            ck_assert_msg(err == SKY_OK, "%X", err);
            ck_assert_str_ne((char*)iStr.p, (char*)jStr.p);
        }
        GoUint8_ bufferAll[1024];
        GoString_ kStr = {bufferAll, 0, 1024};
        err = SKY_Handle_Strings_GetAt(address, i, &kStr);
        ck_assert_msg(err == SKY_OK, "%X", err);
        // Check unlocked address in set of all addresses
        for (k = 0, notfound = 1; notfound && (k < count); ++k) {
            notfound = strcmp(iStr.p, kStr.p);
        }
        ck_assert(notfound == 0);
    }

    for (i = 0; i < countLock; ++i) {
        GoUint8_ bufferi[1024];
        GoString_ iStr = {bufferi, 0, 1024};
        err = SKY_Handle_Strings_GetAt(locked, i, &iStr);
        ck_assert_msg(err == SKY_OK, "%X", err);
        // Check no duplicate address in locked addresses
        for (j = i + 1; j < countLock; ++j) {
            GoUint8_ bufferj[1024];
            GoString_ jStr = {bufferj, 0, 1024};
            err = SKY_Handle_Strings_GetAt(locked, j, &jStr);
            ck_assert_msg(err == SKY_OK, "%X", err);
            ck_assert_str_ne((char*)iStr.p, (char*)jStr.p);
        }

        // Check locked address in set of all addresses
        for (k = 0, notfound = 1; notfound && (k < count); ++k) {
            GoUint8_ bufferAll[1024];
            GoString_ kStr = {bufferAll, 0, 1024};
            err = SKY_Handle_Strings_GetAt(address, k, &kStr);
            ck_assert_msg(err == SKY_OK, "%X", err);
            notfound = strcmp(iStr.p, kStr.p);
        }
        ck_assert_int_eq(notfound, 0);
    }
}
END_TEST

Suite* param_distribution(void)
{
    Suite* s = suite_create("Load param.Distribution");
    TCase* tc;

    tc = tcase_create("params.distribution");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestDistributionAddressArrays);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);
    return s;
}