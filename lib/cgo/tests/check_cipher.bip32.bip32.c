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
    GoUint32 childNUmber;
    GoUint8 depth;
    GoUint32 depthNumber;
} testMasterKey;


void assertPrivateKeySerialization(PrivateKey__Handle key, GoString expected)
{
    GoSlice expectedBytes;
    GoUint32 err = SKY_base58_Decode(expected, &expectedBytes);
    ck_assert_int_eq(SKY_OK, err);
    GoSlice serialized;
    err = SKY_bip32_PrivateKey_Serialize(key, &serialized);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoSliceEq(&expectedBytes, &serialized));
    PrivateKey__Handle key2 = 0;
    err = SKY_bip32_DeserializePrivateKey(serialized, &key2);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPrivateKeyEq(key, key2));
    PrivateKey__Handle key3 = 0;
    err = SKY_bip32_DeserializeEncodedPrivateKey(expected, &key3);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPrivateKeyEq(key2, key3));
}

void assertPublicKeySerialization(PublicKey__Handle key, GoString expected)
{
    GoSlice expectedBytes;
    GoUint32 err = SKY_base58_Decode(expected, &expectedBytes);
    ck_assert_int_eq(SKY_OK, err);
    GoSlice serialized;
    err = SKY_bip32_PublicKey_Serialize(key, &serialized);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoSliceEq(&expectedBytes, &serialized));
    PublicKey__Handle key2 = 0;
    err = SKY_bip32_DeserializePublicKey(serialized, &key2);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPublicKeyEq(key, key2));
    PublicKey__Handle key3 = 0;
    err = SKY_bip32_DeserializeEncodedPublicKey(expected, &key3);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPublicKeyEq(key2, key3));
}

void testVectorKeyPairs(testMasterKey vector)
{
    // Decode master seed into hex
    GoUint8 bufferseed[MAXBUFFER];
    GoSlice seed = {bufferseed, 0, MAXBUFFER};
    GoUint32 err = SKY_base58_String2Hex(vector.seed, &seed);
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
    ck_assert(isGoStringEq(stringPrivKey, vector.privkey));
    err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoStringEq(stringPubKey, vector.pubKey));

    GoString hexPubKey;
    GoUint8 bufferpubkey[MAXBUFFER];
    GoSlice slicepubkey = {bufferpubkey, 0, MAXBUFFER};
    err = SKY_bip32_PublicKey_GetKey(pubkey, &slicepubkey);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_base58_Hex2String(slicepubkey, &hexPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoStringEq(vector.hexPubKey, hexPubKey));

    cipher__SecKey tempSec;
    GoUint8 bufferprivkey[MAXBUFFER];
    GoSlice sliceprivkey = {bufferprivkey, 0, MAXBUFFER};
    err = SKY_bip32_PrivateKey_GetKey(privkey, &sliceprivkey);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_cipher_NewSecKey(sliceprivkey, &tempSec);
    ck_assert_int_eq(err, SKY_OK);
    GoString wif;
    SKY_cipher_BitcoinWalletImportFormatFromSeckey(&tempSec, &wif);
    ck_assert(isGoStringEq(wif, vector.wifPrivKey));

    GoUint8 bufferprivChainCode[MAXBUFFER];
    GoUint8 bufferpubChainCode[MAXBUFFER];
    GoSlice privChainCode = {bufferprivChainCode, 0, MAXBUFFER};
    GoSlice pubChainCode = {bufferpubChainCode, 0, MAXBUFFER};
    err = SKY_bip32_PrivateKey_GetChainCode(privkey, &privChainCode);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_GetChainCode(pubkey, &pubChainCode);
    ck_assert_int_eq(SKY_OK, err);
    GoString priv_ChainCode = {bufferprivChainCode, 0};
    GoString pub_ChainCode = {bufferpubChainCode, 0};
    err = SKY_base58_Hex2String(privChainCode, &priv_ChainCode);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoStringEq(vector.chainCode, priv_ChainCode));
    err = SKY_base58_Hex2String(pubChainCode, &pub_ChainCode);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoStringEq(vector.chainCode, pub_ChainCode));

    GoUint8 bufferprivFringerprint[MAXBUFFER];
    GoUint8 bufferpubFringerprint[MAXBUFFER];
    GoSlice privFringerprint = {bufferprivFringerprint, 0, MAXBUFFER};
    GoSlice pubFringerprint = {bufferpubFringerprint, 0, MAXBUFFER};
    GoString priv_Fringerprint;
    GoString pub_Fringerprint;
    err = SKY_bip32_PrivateKey_Fingerprint(privkey, &privFringerprint);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_Fingerprint(pubkey, &pubFringerprint);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_base58_Hex2String(privFringerprint, &priv_Fringerprint);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_base58_Hex2String(pubFringerprint, &pub_Fringerprint);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoStringEq(vector.fingerprint, priv_Fringerprint));
    ck_assert(isGoStringEq(vector.fingerprint, pub_Fringerprint));

    GoUint8 bufferprivIdentifier[1024];
    GoUint8 bufferpubIdentifier[1024];
    GoSlice privIdentifier = {bufferprivIdentifier, 0, 1024};
    GoSlice pubIdentifier = {bufferpubIdentifier, 0, 1024};
    GoString priv_Identifier = {bufferprivIdentifier, 0};
    GoString pub_Identifier = {bufferpubIdentifier, 0};
    err = SKY_bip32_PrivateKey_Identifier(privkey, &privIdentifier);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_Identifier(pubkey, &pubIdentifier);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_base58_Hex2String(privIdentifier, &priv_Identifier);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_base58_Hex2String(pubIdentifier, &pub_Identifier);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoStringEq(vector.identifier, priv_Identifier));
    ck_assert(isGoStringEq(vector.identifier, pub_Identifier));

    GoUint8 privDepth;
    GoUint8 pubDepth;
    err = SKY_bip32_PrivateKey_GetDepth(privkey, &privDepth);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_GetDepth(pubkey, &pubDepth);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert_int_eq(vector.depth, privDepth);
    ck_assert_int_eq(vector.depth, pubDepth);

    GoUint32 privchildNumber;
    GoUint32 pubchildNumber;
    err = SKY_bip32_PrivateKey_ChildNumber(privkey, &privchildNumber);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_ChildNumber(pubkey, &pubchildNumber);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert_int_eq(vector.childNUmber, privchildNumber);
    ck_assert_int_eq(vector.childNUmber, pubchildNumber);

    // line 302 bip32_test.go
    // Serialize and deserialize both keys and ensure they're the same
    assertPrivateKeySerialization(privkey, vector.privkey);
    assertPublicKeySerialization(pubkey, vector.pubKey);

    GoSlice b58pk;
    err = SKY_base58_Decode(vector.privkey, &b58pk);
    ck_assert_int_eq(SKY_OK, err);
    PrivateKey__Handle privKey2 = 0;
    err = SKY_bip32_DeserializePrivateKey(b58pk, &privKey2);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPrivateKeyEq(privkey, privKey2));

    // Test that DeserializeEncodedPrivateKey
    // is equivalent to DeserializePrivateKey(base58.Decode(key))
    PrivateKey__Handle privKey3 = 0;
    err = SKY_bip32_DeserializeEncodedPrivateKey(vector.privkey, &privKey3);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isPrivateKeyEq(privKey2, privKey3));

    // Iterate over the entire child chain and test the given keys
    for (size_t i = 0; i < vector.depthNumber; i++) {
        testChildKey tck = vector.children[i];
        privkey = 0;
        err = SKY_bip32_NewPrivateKeyFromPath(seed, tck.path, &privkey);
        ck_assert_int_eq(SKY_OK, err);

        // Get this private key's public key
        pubkey = 0;
        err = SKY_bip32_PrivateKey_Publickey(privkey, &pubkey);
        ck_assert_int_eq(SKY_OK, err);

        // Test DeserializePrivateKey
        GoSlice ppk;
        err = SKY_base58_Decode(tck.privKey, &ppk);
        ck_assert_int_eq(SKY_OK, err);
        PrivateKey__Handle xx = 0;
        err = SKY_bip32_DeserializePrivateKey(ppk, &xx);
        ck_assert_int_eq(SKY_OK, err);

        ck_assert(isPrivateKeyEq(xx, privkey));

        err = SKY_bip32_PrivateKey_String(privkey, &stringPrivKey);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isGoStringEq(stringPrivKey, tck.privKey));
        err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isGoStringEq(stringPubKey, tck.pubKey));


        err = SKY_bip32_PrivateKey_GetChainCode(privkey, &privChainCode);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_GetChainCode(pubkey, &pubChainCode);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(privChainCode, &priv_ChainCode);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoStringEq(tck.chainCode, priv_ChainCode));
        err = SKY_base58_Hex2String(pubChainCode, &pub_ChainCode);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoStringEq(tck.chainCode, pub_ChainCode));

        err = SKY_bip32_PrivateKey_Fingerprint(privkey, &privFringerprint);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_Fingerprint(pubkey, &pubFringerprint);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(privFringerprint, &priv_Fringerprint);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(pubFringerprint, &pub_Fringerprint);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoStringEq(tck.fingerprint, priv_Fringerprint));
        ck_assert(isGoStringEq(tck.fingerprint, pub_Fringerprint));

        err = SKY_bip32_PrivateKey_Identifier(privkey, &privIdentifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_Identifier(pubkey, &pubIdentifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(privIdentifier, &priv_Identifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(pubIdentifier, &pub_Identifier);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoStringEq(tck.identifier, priv_Identifier));
        ck_assert(isGoStringEq(tck.identifier, pub_Identifier));

        err = SKY_bip32_PrivateKey_GetDepth(privkey, &privDepth);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_GetDepth(pubkey, &pubDepth);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert_int_eq(tck.depth, privDepth);
        ck_assert_int_eq(tck.depth, pubDepth);

        err = SKY_bip32_PrivateKey_ChildNumber(privkey, &privchildNumber);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_ChildNumber(pubkey, &pubchildNumber);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert_int_eq(tck.childNUmber, privchildNumber);
        ck_assert_int_eq(tck.childNUmber, pubchildNumber);

        // Serialize and deserialize both keys and ensure they're the same
        assertPrivateKeySerialization(privkey, tck.privKey);
        assertPublicKeySerialization(pubkey, tck.pubKey);
    }
}

START_TEST(TestBip32TestVectors)
{
    testMasterKey vector1;
    vector1.seed.p = "000102030405060708090a0b0c0d0e0f";
    vector1.seed.n = 32;
    vector1.privkey.p = "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi";
    vector1.privkey.n = 111;
    vector1.pubKey.p = "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8";
    vector1.pubKey.n = 111;
    vector1.hexPubKey.p = "0339a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2";
    vector1.hexPubKey.n = 66;
    vector1.wifPrivKey.p = "L52XzL2cMkHxqxBXRyEpnPQZGUs3uKiL3R11XbAdHigRzDozKZeW";
    vector1.wifPrivKey.n = 52;
    vector1.fingerprint.p = "3442193e";
    vector1.fingerprint.n = 8;
    vector1.identifier.p = "3442193e1bb70916e914552172cd4e2dbc9df811";
    vector1.identifier.n = 40;
    vector1.chainCode.p = "873dff81c02f525623fd1fe5167eac3a55a049de3d314bb42ee227ffed37d508";
    vector1.chainCode.n = 64;
    vector1.childNUmber = 0;
    vector1.depth = 0;
    vector1.depthNumber = 1;
    vector1.children[0].path.p = "m/0'";
    vector1.children[0].path.n = 4;
    vector1.children[0].privKey.p = "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7";
    vector1.children[0].privKey.n = 111;
    vector1.children[0].pubKey.p = "xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw";
    vector1.children[0].pubKey.n = 111;
    vector1.children[0].fingerprint.p = "5c1bd648";
    vector1.children[0].fingerprint.n = 8;
    vector1.children[0].identifier.p = "5c1bd648ed23aa5fd50ba52b2457c11e9e80a6a7";
    vector1.children[0].identifier.n = 40;
    vector1.children[0].chainCode.p = "47fdacbd0f1097043b78c63c20c34ef4ed9a111d980047ad16282c7ae6236141";
    vector1.children[0].chainCode.n = 64;
    vector1.children[0].hexPubKey.p = "035a784662a4a20a65bf6aab9ae98a6c068a81c52e4b032c0fb5400c706cfccc56";
    vector1.children[0].hexPubKey.n = 66;
    vector1.children[0].wifPrivKey.p = "L5BmPijJjrKbiUfG4zbiFKNqkvuJ8usooJmzuD7Z8dkRoTThYnAT";
    vector1.children[0].wifPrivKey.n = 52;
    vector1.children[0].childNUmber = 2147483648;
    vector1.children[0].depth = 1;
    


    testVectorKeyPairs(vector1);
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
    // tcase_add_test(tc, TestMaxChildDepthError);
    tcase_add_test(tc, TestBip32TestVectors);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}