#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

typedef struct {
    GoString path;
    GoString privKey;
    GoString pubKey;
    GoString fingerprint;
    GoString identifier;
    GoString chainCode;
    GoString hexPubKey;
    GoString wifPrivKey;
    GoUint32 childNumber;
    GoUint8 depth;
} testChildKey;

typedef struct {
    GoString seed;
    testChildKey children[12];
    GoString privKey;
    GoString pubKey;
    GoString hexPubKey;
    GoString wifPrivKey;
    GoString fingerprint;
    GoString identifier;
    GoString chainCode;
    GoUint32 childNumber;
    GoUint8 depth;
} testMasterKey;


START_TEST(TestBip32TestVectors)
{
}
END_TEST

Suite* cipher_bip32(void)
{
    Suite* s = suite_create("Load cipher.bip32");
    TCase* tc;

    tc = tcase_create("cipher.bip32");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestBip32TestVectors);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}