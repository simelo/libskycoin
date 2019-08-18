#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

START_TEST(TestMaxChildDepthError)
{
    GoUint8 bufferTemp[1024];
    GoSlice tmp = {bufferTemp, 0, 32};
    randBytes(&tmp, 32);
    PrivateKey__Handle key = 0;
    GoUint32 err = SKY_bip32_NewMasterKey(tmp, &key);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 reached = 0;
    for (size_t i = 0; i < 256; i++) {
        err = SKY_bip32_Private_NewPrivateChildKey(key, 0, &key);
        switch (i) {
        case 255:
            ck_assert_int_eq(err, SKY_ErrMaxDepthReached);
            reached = 1;
            break;

        default:
            ck_assert_int_eq(err, SKY_OK);
            break;
        }
    }
    ck_assert(reached == 1);
}
END_TEST

Suite* cipher_bip32(void)
{
    Suite* s = suite_create("Load cipher.bip32");
    TCase* tc;

    tc = tcase_create("cipher.bip32");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestMaxChildDepthError);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}