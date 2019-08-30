#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>
#define MAXBUFFER 1024

typedef struct {
    GoString path;
    GoString privKey;
    GoString pubKey;
    GoString fingerprint;
    GoString identifier;
    GoString chainCode;
    GoString hexPubKey;
    GoString wifPrivKey;
    GoUint32_ childNUmber;
    GoUint8_ depth;
} testChildKey;


typedef struct {
    GoString seed;
    testChildKey children[MAXBUFFER];
    GoString privkey;
    GoString pubKey;
    GoString hexPubKey;
    GoString wifPrivKey;
    GoString fingerprint;
    GoString identifier;
    GoString chainCode;
    GoUint32_ childNUmber;
    GoUint8_ depth;
} testMasterKey;

GoUint32_ testVectorKeyPairs(testMasterKey vector)
{
    // Decode master seed into hex
    GoUint8_ bufferseed[MAXBUFFER];
    GoSlice_ seed = {bufferseed, 0, MAXBUFFER};
    GoUint32_ err = SKY_base58_String2Hex(vector.seed, &seed);
    ck_assert_int_eq(err, SKY_OK);

    // Generate a master private and public key
    PrivateKey__Handle privkey = 0;
    GoSlice sliceseed;
    copyGoSlice_toGoSlice(&sliceseed, &seed, sizeof(seed));
    err = SKY_bip32_NewMasterKey(sliceseed, &privkey);
    ck_assert_int_eq(err, SKY_OK);
    PublicKey__Handle pubkey = 0;
    err = SKY_bip32_PrivateKey_Publickey(privkey, &pubkey);
    ck_assert_int_eq(err, SKY_OK);

    GoUint8 depthPrivKey;
    GoUint8 depthPubKey;
    err = SKY_bip32_PrivateKey_GetDepth(privkey, &depthPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(0, depthPrivKey);
    err = SKY_bip32_PublicKey_GetDepth(pubkey, &depthPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(0, depthPubKey);

    GoUint32 childnumberPrivKey;
    GoUint32 childnumberPubKey;
    err = SKY_bip32_PrivateKey_ChildNumber(privkey, &childnumberPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(0, childnumberPrivKey);
    err = SKY_bip32_PublicKey_ChildNumber(pubkey, &childnumberPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(0, childnumberPubKey);

    GoString stringPrivKey;
    GoString stringPubKey;
    err = SKY_bip32_PrivateKey_String(privkey, &stringPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(isGoStringEq(stringPrivKey, vector.privkey), 0);
    err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(isGoStringEq(stringPubKey, vector.pubKey), 0);

    GoString hexPubKey;
    GoUint8 bufferpubkey[1024];
    GoSlice slicepubkey = {bufferpubkey, 0, 1024};
    err = SKY_bip32_PublicKey_GetKey(pubkey, &slicepubkey);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_base58_Hex2String(slicepubkey, &hexPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_int_eq(isGoStringEq(vector.hexPubKey, hexPubKey), 0);

    cipher__SecKey tempSec;
    GoUint8 bufferprivkey[1024];
    GoSlice sliceprivkey = {bufferprivkey, 0, 1024};
    err = SKY_bip32_PrivateKey_GetKey(privkey, &sliceprivkey);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_cipher_NewSecKey(sliceprivkey, &tempSec);
    ck_assert_int_eq(err, SKY_OK);
    // line 248 bip32_test.go
}

START_TEST(TestBip32TestVectors)
{
}
END_TEST


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
        err = SKY_bip32_PrivateKey_NewPrivateChildKey(key, 0, &key);
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
    tcase_add_test(tc, TestBip32TestVectors);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}