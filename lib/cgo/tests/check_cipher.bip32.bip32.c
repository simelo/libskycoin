#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>
#define MAXBUFFER 1024
#define FirstHardenedChild 0x80000000

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
    GoUint8 bufferexpectedBytes[1024];
    GoSlice expectedBytes = {bufferexpectedBytes, 0, 1024};
    GoUint32 err = SKY_base58_Decode(expected, &expectedBytes);
    ck_assert_int_eq(SKY_OK, err);
    GoUint8 bufferserialized[1024];
    GoSlice serialized = {bufferserialized, 0, 1024};
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
    GoUint8 bufferexpectedBytes[1024];
    GoSlice expectedBytes = {bufferexpectedBytes, 0, 1024};
    GoUint32 err = SKY_base58_Decode(expected, &expectedBytes);
    ck_assert_int_eq(SKY_OK, err);
    GoUint8 bufferserialized[1024];
    GoSlice serialized = {bufferserialized, 0, 1024};
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
    GoSlice_ seed = {bufferseed, 0, MAXBUFFER};
    GoUint32 err = SKY_base58_String2Hex(vector.seed, &seed);
    ck_assert_int_eq(err, SKY_OK);

    // Generate a master private and public key
    PrivateKey__Handle privkey = 0;
    GoUint8 buffersliceseed[1024];
    GoSlice sliceseed = {buffersliceseed, 0, 1024};
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
    err = SKY_bip32_PublicKey_GetDepth(pubkey, &depthPubKey);
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

    GoUint8 bufferstringPrivKey[1024];
    GoUint8 bufferstringPubKey[1024];
    GoString_ stringPrivKey = {bufferstringPrivKey, 0};
    GoString_ stringPubKey = {bufferstringPubKey, 0};
    err = SKY_bip32_PrivateKey_String(privkey, &stringPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoString_toGoStringEq(stringPrivKey, vector.privkey));
    err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoString_toGoStringEq(stringPubKey, vector.pubKey));

    GoUint8 bufferhexPubKey[1024];
    GoString_ hexPubKey = {bufferhexPubKey, 0};
    GoUint8 bufferpubkey[MAXBUFFER];
    GoSlice_ slicepubkey_tmp = {bufferpubkey, 0, MAXBUFFER};
    err = SKY_bip32_PublicKey_GetKey(pubkey, &slicepubkey_tmp);
    ck_assert_int_eq(err, SKY_OK);
    GoSlice slicepubkey;
    copyGoSlice_toGoSlice(&slicepubkey, &slicepubkey_tmp, slicepubkey_tmp.len);
    err = SKY_base58_Hex2String(slicepubkey, &hexPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoString_toGoStringEq(hexPubKey, vector.hexPubKey));

    cipher__SecKey tempSec;
    GoUint8 bufferprivkey[MAXBUFFER];
    GoSlice_ sliceprivkey_tmp = {bufferprivkey, 0, MAXBUFFER};
    err = SKY_bip32_PrivateKey_GetKey(privkey, &sliceprivkey_tmp);
    ck_assert_int_eq(err, SKY_OK);
    GoSlice sliceprivkey;
    copyGoSlice_toGoSlice(&sliceprivkey, &sliceprivkey_tmp, sliceprivkey_tmp.len);
    err = SKY_cipher_NewSecKey(sliceprivkey, &tempSec);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferwif[1024];
    GoString_ wif = {bufferwif, 0};
    SKY_cipher_BitcoinWalletImportFormatFromSeckey(&tempSec, &wif);
    ck_assert(isGoString_toGoStringEq(wif, vector.wifPrivKey));

    GoUint8 bufferprivChainCode[MAXBUFFER];
    GoUint8 bufferpubChainCode[MAXBUFFER];
    GoSlice_ privChainCode_tmp = {bufferprivChainCode, 0, MAXBUFFER};
    GoSlice_ pubChainCode_tmp = {bufferpubChainCode, 0, MAXBUFFER};
    err = SKY_bip32_PrivateKey_GetChainCode(privkey, &privChainCode_tmp);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_GetChainCode(pubkey, &pubChainCode_tmp);
    ck_assert_int_eq(SKY_OK, err);
    GoString_ priv_ChainCode = {bufferprivChainCode, 0};
    GoString_ pub_ChainCode = {bufferpubChainCode, 0};
    GoSlice privChainCode;
    GoSlice pubChainCode;
    copyGoSlice_toGoSlice(&privChainCode, &privChainCode_tmp, privChainCode_tmp.len);
    err = SKY_base58_Hex2String(privChainCode, &priv_ChainCode);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoString_toGoStringEq(priv_ChainCode, vector.chainCode));
    copyGoSlice_toGoSlice(&pubChainCode, &pubChainCode_tmp, pubChainCode_tmp.len);
    err = SKY_base58_Hex2String(pubChainCode, &pub_ChainCode);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoString_toGoStringEq(pub_ChainCode, vector.chainCode));

    GoUint8 bufferprivFringerprint[MAXBUFFER];
    GoUint8 bufferpubFringerprint[MAXBUFFER];
    GoSlice_ privFringerprint_tmp = {bufferprivFringerprint, 0, MAXBUFFER};
    GoSlice_ pubFringerprint_tmp = {bufferpubFringerprint, 0, MAXBUFFER};
    GoUint8 bufferpriv_Fringerprint[MAXBUFFER];
    GoString priv_Fringerprint = {bufferpriv_Fringerprint, 0};
    GoUint8 bufferpub_Fringerprint[MAXBUFFER];
    GoString pub_Fringerprint = {bufferpub_Fringerprint, 0};
    err = SKY_bip32_PrivateKey_Fingerprint(privkey, &privFringerprint_tmp);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_Fingerprint(pubkey, &pubFringerprint_tmp);
    ck_assert_int_eq(SKY_OK, err);
    GoSlice privFringerprint;
    copyGoSlice_toGoSlice(&privFringerprint, &privFringerprint_tmp, privFringerprint_tmp.len);
    GoSlice pubFringerprint;

    GoString_ priv_Fringerprint_tmp;
    GoString_ pub_Fringerprint_tmp;
    err = SKY_base58_Hex2String(privFringerprint, &priv_Fringerprint_tmp);
    ck_assert_int_eq(SKY_OK, err);
    copyGoSlice_toGoSlice(&pubFringerprint, &pubFringerprint_tmp, pubFringerprint_tmp.len);
    err = SKY_base58_Hex2String(pubFringerprint, &pub_Fringerprint_tmp);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoString_toGoStringEq(priv_Fringerprint_tmp, vector.fingerprint));
    ck_assert(isGoString_toGoStringEq(pub_Fringerprint_tmp, vector.fingerprint));

    GoSlice_ privIdentifier_tmp;
    GoSlice_ pubIdentifier_tmp;
    GoString_ priv_Identifier;
    GoString_ pub_Identifier;
    err = SKY_bip32_PrivateKey_Identifier(privkey, &privIdentifier_tmp);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_bip32_PublicKey_Identifier(pubkey, &pubIdentifier_tmp);
    ck_assert_int_eq(SKY_OK, err);
    GoSlice privIdentifier;
    GoSlice pubIdentifier;
    copyGoSlice_toGoSlice(&privIdentifier, &privIdentifier_tmp, privIdentifier_tmp.len);
    copyGoSlice_toGoSlice(&pubIdentifier, &pubIdentifier_tmp, pubIdentifier_tmp.len);
    err = SKY_base58_Hex2String(privIdentifier, &priv_Identifier);
    ck_assert_int_eq(SKY_OK, err);
    err = SKY_base58_Hex2String(pubIdentifier, &pub_Identifier);
    ck_assert_int_eq(SKY_OK, err);
    ck_assert(isGoString_toGoStringEq(priv_Identifier, vector.identifier));
    ck_assert(isGoString_toGoStringEq(pub_Identifier, vector.identifier));

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

    // Serialize and deserialize both keys and ensure they're the same
    assertPrivateKeySerialization(privkey, vector.privkey);
    assertPublicKeySerialization(pubkey, vector.pubKey);

    GoSlice_ b58pk_tmp;
    err = SKY_base58_Decode(vector.privkey, &b58pk_tmp);
    ck_assert_int_eq(SKY_OK, err);
    PrivateKey__Handle privKey2 = 0;
    GoSlice b58pk;
    copyGoSlice_toGoSlice(&b58pk, &b58pk_tmp, b58pk_tmp.len);
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
        printf("Iter %d\n", i);
        testChildKey tck = vector.children[i];
        privkey = 0;
        err = SKY_bip32_NewPrivateKeyFromPath(sliceseed, tck.path, &privkey);
        ck_assert_int_eq(SKY_OK, err);

        // Get this private key's public key
        pubkey = 0;
        err = SKY_bip32_PrivateKey_Publickey(privkey, &pubkey);
        ck_assert_int_eq(SKY_OK, err);

        // Test DeserializePrivateKey
        GoUint8 bufferppk[MAXBUFFER];
        GoSlice_ ppk_tmp = {bufferppk, 0, MAXBUFFER};
        err = SKY_base58_Decode(tck.privKey, &ppk_tmp);
        ck_assert_int_eq(SKY_OK, err);
        PrivateKey__Handle xx = 0;
        GoSlice ppk;
        copyGoSlice_toGoSlice(&ppk, &ppk_tmp, ppk_tmp.len);
        err = SKY_bip32_DeserializePrivateKey(ppk, &xx);
        ck_assert_int_eq(SKY_OK, err);

        ck_assert(isPrivateKeyEq(xx, privkey));

        err = SKY_bip32_PrivateKey_String(privkey, &stringPrivKey);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isGoString_toGoStringEq(stringPrivKey, tck.privKey));
        err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isGoString_toGoStringEq(stringPubKey, tck.pubKey));

        err = SKY_bip32_PrivateKey_GetChainCode(privkey, &privChainCode);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_GetChainCode(pubkey, &pubChainCode);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(privChainCode, &priv_ChainCode);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoString_toGoStringEq(priv_ChainCode, tck.chainCode));
        err = SKY_base58_Hex2String(pubChainCode, &pub_ChainCode);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoString_toGoStringEq(pub_ChainCode, tck.chainCode));

        GoSlice_ privFringerprint_tmp;
        err = SKY_bip32_PrivateKey_Fingerprint(privkey, &privFringerprint_tmp);
        ck_assert_int_eq(SKY_OK, err);
        GoSlice_ pubFringerprint_tmp;
        err = SKY_bip32_PublicKey_Fingerprint(pubkey, &pubFringerprint_tmp);
        ck_assert_int_eq(SKY_OK, err);
        copyGoSlice_toGoSlice(&privFringerprint, &privFringerprint_tmp, privFringerprint_tmp.len);
        err = SKY_base58_Hex2String(privFringerprint, &priv_Fringerprint_tmp);
        ck_assert_int_eq(SKY_OK, err);
        copyGoSlice_toGoSlice(&pubFringerprint, &pubFringerprint_tmp, pubFringerprint_tmp.len);
        err = SKY_base58_Hex2String(pubFringerprint, &pub_Fringerprint_tmp);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoString_toGoStringEq(pub_Fringerprint_tmp, tck.fingerprint));
        ck_assert(isGoString_toGoStringEq(pub_Fringerprint_tmp, tck.fingerprint));

        err = SKY_bip32_PrivateKey_Identifier(privkey, &privIdentifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_bip32_PublicKey_Identifier(pubkey, &pubIdentifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(privIdentifier, &priv_Identifier);
        ck_assert_int_eq(SKY_OK, err);
        err = SKY_base58_Hex2String(pubIdentifier, &pub_Identifier);
        ck_assert_int_eq(SKY_OK, err);
        ck_assert(isGoString_toGoStringEq(priv_Identifier, tck.identifier));
        ck_assert(isGoString_toGoStringEq(pub_Identifier, tck.identifier));

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
    vector1.depthNumber = 5;
    // 0
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
    // 1
    vector1.children[1].path.p = "m/0'/1";
    vector1.children[1].path.n = 6;
    vector1.children[1].privKey.p = "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs";
    vector1.children[1].privKey.n = 111;
    vector1.children[1].pubKey.p = "xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ";
    vector1.children[1].pubKey.n = 111;
    vector1.children[1].fingerprint.p = "bef5a2f9";
    vector1.children[1].fingerprint.n = 8;
    vector1.children[1].identifier.p = "bef5a2f9a56a94aab12459f72ad9cf8cf19c7bbe";
    vector1.children[1].identifier.n = 40;
    vector1.children[1].chainCode.p = "2a7857631386ba23dacac34180dd1983734e444fdbf774041578e9b6adb37c19";
    vector1.children[1].chainCode.n = 64;
    vector1.children[1].hexPubKey.p = "03501e454bf00751f24b1b489aa925215d66af2234e3891c3b21a52bedb3cd711c";
    vector1.children[1].hexPubKey.n = 66;
    vector1.children[1].wifPrivKey.p = "KyFAjQ5rgrKvhXvNMtFB5PCSKUYD1yyPEe3xr3T34TZSUHycXtMM";
    vector1.children[1].wifPrivKey.n = 52;
    vector1.children[1].childNUmber = 1;
    vector1.children[1].depth = 2;
    // 2
    vector1.children[2].path.p = "m/0'/1/2'";
    vector1.children[2].path.n = 9;
    vector1.children[2].privKey.p = "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM";
    vector1.children[2].privKey.n = 111;
    vector1.children[2].pubKey.p = "xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5";
    vector1.children[2].pubKey.n = 111;
    vector1.children[2].fingerprint.p = "ee7ab90c";
    vector1.children[2].fingerprint.n = 8;
    vector1.children[2].identifier.p = "ee7ab90cde56a8c0e2bb086ac49748b8db9dce72";
    vector1.children[2].identifier.n = 40;
    vector1.children[2].chainCode.p = "04466b9cc8e161e966409ca52986c584f07e9dc81f735db683c3ff6ec7b1503f";
    vector1.children[2].chainCode.n = 64;
    vector1.children[2].hexPubKey.p = "0357bfe1e341d01c69fe5654309956cbea516822fba8a601743a012a7896ee8dc2";
    vector1.children[2].hexPubKey.n = 66;
    vector1.children[2].wifPrivKey.p = "L43t3od1Gh7Lj55Bzjj1xDAgJDcL7YFo2nEcNaMGiyRZS1CidBVU";
    vector1.children[2].wifPrivKey.n = 52;
    vector1.children[2].childNUmber = 2 + FirstHardenedChild;
    vector1.children[2].depth = 3;
    // 3
    vector1.children[3].path.p = "m/0'/1/2'/2";
    vector1.children[3].path.n = 11;
    vector1.children[3].privKey.p = "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334";
    vector1.children[3].privKey.n = 111;
    vector1.children[3].pubKey.p = "xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV";
    vector1.children[3].pubKey.n = 111;
    vector1.children[3].fingerprint.p = "d880d7d8";
    vector1.children[3].fingerprint.n = 8;
    vector1.children[3].identifier.p = "d880d7d893848509a62d8fb74e32148dac68412f";
    vector1.children[3].identifier.n = 40;
    vector1.children[3].chainCode.p = "cfb71883f01676f587d023cc53a35bc7f88f724b1f8c2892ac1275ac822a3edd";
    vector1.children[3].chainCode.n = 64;
    vector1.children[3].hexPubKey.p = "02e8445082a72f29b75ca48748a914df60622a609cacfce8ed0e35804560741d29";
    vector1.children[3].hexPubKey.n = 66;
    vector1.children[3].wifPrivKey.p = "KwjQsVuMjbCP2Zmr3VaFaStav7NvevwjvvkqrWd5Qmh1XVnCteBR";
    vector1.children[3].wifPrivKey.n = 52;
    vector1.children[3].childNUmber = 2;
    vector1.children[3].depth = 4;
    // 4
    vector1.children[4].path.p = "m/0'/1/2'/2/1000000000";
    vector1.children[4].path.n = 22;
    vector1.children[4].privKey.p = "xprvA41z7zogVVwxVSgdKUHDy1SKmdb533PjDz7J6N6mV6uS3ze1ai8FHa8kmHScGpWmj4WggLyQjgPie1rFSruoUihUZREPSL39UNdE3BBDu76";
    vector1.children[4].privKey.n = 111;
    vector1.children[4].pubKey.p = "xpub6H1LXWLaKsWFhvm6RVpEL9P4KfRZSW7abD2ttkWP3SSQvnyA8FSVqNTEcYFgJS2UaFcxupHiYkro49S8yGasTvXEYBVPamhGW6cFJodrTHy";
    vector1.children[4].pubKey.n = 111;
    vector1.children[4].fingerprint.p = "d69aa102";
    vector1.children[4].fingerprint.n = 8;
    vector1.children[4].identifier.p = "d69aa102255fed74378278c7812701ea641fdf32";
    vector1.children[4].identifier.n = 40;
    vector1.children[4].chainCode.p = "c783e67b921d2beb8f6b389cc646d7263b4145701dadd2161548a8b078e65e9e";
    vector1.children[4].chainCode.n = 64;
    vector1.children[4].hexPubKey.p = "022a471424da5e657499d1ff51cb43c47481a03b1e77f951fe64cec9f5a48f7011";
    vector1.children[4].hexPubKey.n = 66;
    vector1.children[4].wifPrivKey.p = "Kybw8izYevo5xMh1TK7aUr7jHFCxXS1zv8p3oqFz3o2zFbhRXHYs";
    vector1.children[4].wifPrivKey.n = 52;
    vector1.children[4].childNUmber = 1000000000;
    vector1.children[4].depth = 5;
    // vector 2
    testMasterKey vector2;
    vector2.seed.p = "fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542";
    vector2.seed.n = 128;
    vector2.privkey.p = "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U";
    vector2.privkey.n = 111;
    vector2.pubKey.p = "xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJY47LJhkJ8UB7WEGuduB";
    vector2.pubKey.n = 111;
    vector2.hexPubKey.p = "03cbcaa9c98c877a26977d00825c956a238e8dddfbd322cce4f74b0b5bd6ace4a7";
    vector2.hexPubKey.n = 66;
    vector2.wifPrivKey.p = "KyjXhyHF9wTphBkfpxjL8hkDXDUSbE3tKANT94kXSyh6vn6nKaoy";
    vector2.wifPrivKey.n = 52;
    vector2.fingerprint.p = "bd16bee5";
    vector2.fingerprint.n = 8;
    vector2.identifier.p = "bd16bee53961a47d6ad888e29545434a89bdfe95";
    vector2.identifier.n = 40;
    vector2.chainCode.p = "60499f801b896d83179a4374aeb7822aaeaceaa0db1f85ee3e904c4defbd9689";
    vector2.chainCode.n = 64;
    vector2.childNUmber = 0;
    vector2.depth = 0;
    vector2.depthNumber = 5;
    // 0
    vector2.children[0].path.p = "m/0";
    vector2.children[0].path.n = 3;
    vector2.children[0].privKey.p = "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt";
    vector2.children[0].privKey.n = 111;
    vector2.children[0].pubKey.p = "xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH";
    vector2.children[0].pubKey.n = 111;
    vector2.children[0].fingerprint.p = "5a61ff8e";
    vector2.children[0].fingerprint.n = 8;
    vector2.children[0].identifier.p = "5a61ff8eb7aaca3010db97ebda76121610b78096";
    vector2.children[0].identifier.n = 40;
    vector2.children[0].chainCode.p = "f0909affaa7ee7abe5dd4e100598d4dc53cd709d5a5c2cac40e7412f232f7c9c";
    vector2.children[0].chainCode.n = 64;
    vector2.children[0].hexPubKey.p = "02fc9e5af0ac8d9b3cecfe2a888e2117ba3d089d8585886c9c826b6b22a98d12ea";
    vector2.children[0].hexPubKey.n = 66;
    vector2.children[0].wifPrivKey.p = "L2ysLrR6KMSAtx7uPqmYpoTeiRzydXBattRXjXz5GDFPrdfPzKbj";
    vector2.children[0].wifPrivKey.n = 52;
    vector2.children[0].childNUmber = 0;
    vector2.children[0].depth = 1;
    // 1
    vector2.children[1].path.p = "m/0/2147483647'";
    vector2.children[1].path.n = 15;
    vector2.children[1].privKey.p = "xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9";
    vector2.children[1].privKey.n = 111;
    vector2.children[1].pubKey.p = "xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaDMBU4Zn9h8LZNnBC5y4a";
    vector2.children[1].pubKey.n = 111;
    vector2.children[1].fingerprint.p = "d8ab4937";
    vector2.children[1].fingerprint.n = 8;
    vector2.children[1].identifier.p = "d8ab493736da02f11ed682f88339e720fb0379d1";
    vector2.children[1].identifier.n = 40;
    vector2.children[1].chainCode.p = "be17a268474a6bb9c61e1d720cf6215e2a88c5406c4aee7b38547f585c9a37d9";
    vector2.children[1].chainCode.n = 64;
    vector2.children[1].hexPubKey.p = "03c01e7425647bdefa82b12d9bad5e3e6865bee0502694b94ca58b666abc0a5c3b";
    vector2.children[1].hexPubKey.n = 66;
    vector2.children[1].wifPrivKey.p = "L1m5VpbXmMp57P3knskwhoMTLdhAAaXiHvnGLMribbfwzVRpz2Sr";
    vector2.children[1].wifPrivKey.n = 52;
    vector2.children[1].childNUmber = 2147483647 + FirstHardenedChild;
    vector2.children[1].depth = 2;
    // 2
    vector2.children[2].path.p = "m/0/2147483647'/1";
    vector2.children[2].path.n = 17;
    vector2.children[2].privKey.p = "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef";
    vector2.children[2].privKey.n = 111;
    vector2.children[2].pubKey.p = "xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon";
    vector2.children[2].pubKey.n = 111;
    vector2.children[2].fingerprint.p = "78412e3a";
    vector2.children[2].fingerprint.n = 8;
    vector2.children[2].identifier.p = "78412e3a2296a40de124307b6485bd19833e2e34";
    vector2.children[2].identifier.n = 40;
    vector2.children[2].chainCode.p = "f366f48f1ea9f2d1d3fe958c95ca84ea18e4c4ddb9366c336c927eb246fb38cb";
    vector2.children[2].chainCode.n = 64;
    vector2.children[2].hexPubKey.p = "03a7d1d856deb74c508e05031f9895dab54626251b3806e16b4bd12e781a7df5b9";
    vector2.children[2].hexPubKey.n = 66;
    vector2.children[2].wifPrivKey.p = "KzyzXnznxSv249b4KuNkBwowaN3akiNeEHy5FWoPCJpStZbEKXN2";
    vector2.children[2].wifPrivKey.n = 52;
    vector2.children[2].childNUmber = 1;
    vector2.children[2].depth = 3;
    // 3
    vector2.children[3].path.p = "m/0/2147483647'/1/2147483646'";
    vector2.children[3].path.n = 29;
    vector2.children[3].privKey.p = "xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc";
    vector2.children[3].privKey.n = 111;
    vector2.children[3].pubKey.p = "xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRjaDMzQLcgJvLJuZZvRcEL";
    vector2.children[3].pubKey.n = 111;
    vector2.children[3].fingerprint.p = "31a507b8";
    vector2.children[3].fingerprint.n = 8;
    vector2.children[3].identifier.p = "31a507b815593dfc51ffc7245ae7e5aee304246e";
    vector2.children[3].identifier.n = 40;
    vector2.children[3].chainCode.p = "637807030d55d01f9a0cb3a7839515d796bd07706386a6eddf06cc29a65a0e29";
    vector2.children[3].chainCode.n = 64;
    vector2.children[3].hexPubKey.p = "02d2b36900396c9282fa14628566582f206a5dd0bcc8d5e892611806cafb0301f0";
    vector2.children[3].hexPubKey.n = 66;
    vector2.children[3].wifPrivKey.p = "L5KhaMvPYRW1ZoFmRjUtxxPypQ94m6BcDrPhqArhggdaTbbAFJEF";
    vector2.children[3].wifPrivKey.n = 52;
    vector2.children[3].childNUmber = 2147483646 + FirstHardenedChild;
    vector2.children[3].depth = 4;
    // 4
    vector2.children[4].path.p = "m/0/2147483647'/1/2147483646'/2";
    vector2.children[4].path.n = 31;
    vector2.children[4].privKey.p = "xprvA2nrNbFZABcdryreWet9Ea4LvTJcGsqrMzxHx98MMrotbir7yrKCEXw7nadnHM8Dq38EGfSh6dqA9QWTyefMLEcBYJUuekgW4BYPJcr9E7j";
    vector2.children[4].privKey.n = 111;
    vector2.children[4].pubKey.p = "xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9rXpVGyy3bdW6EEgAtqt";
    vector2.children[4].pubKey.n = 111;
    vector2.children[4].fingerprint.p = "26132fdb";
    vector2.children[4].fingerprint.n = 8;
    vector2.children[4].identifier.p = "26132fdbe7bf89cbc64cf8dafa3f9f88b8666220";
    vector2.children[4].identifier.n = 40;
    vector2.children[4].chainCode.p = "9452b549be8cea3ecb7a84bec10dcfd94afe4d129ebfd3b3cb58eedf394ed271";
    vector2.children[4].chainCode.n = 64;
    vector2.children[4].hexPubKey.p = "024d902e1a2fc7a8755ab5b694c575fce742c48d9ff192e63df5193e4c7afe1f9c";
    vector2.children[4].hexPubKey.n = 66;
    vector2.children[4].wifPrivKey.p = "L3WAYNAZPxx1fr7KCz7GN9nD5qMBnNiqEJNJMU1z9MMaannAt4aK";
    vector2.children[4].wifPrivKey.n = 52;
    vector2.children[4].childNUmber = 2;
    vector2.children[4].depth = 5;

    // Vector 3
    testMasterKey vector3;
    vector3.seed.p = "4b381541583be4423346c643850da4b320e46a87ae3d2a4e6da11eba819cd4acba45d239319ac14f863b8d5ab5a0d0c64d2e8a1e7d1457df2e5a3c51c73235be";
    vector3.seed.n = 128;
    vector3.privkey.p = "xprv9s21ZrQH143K25QhxbucbDDuQ4naNntJRi4KUfWT7xo4EKsHt2QJDu7KXp1A3u7Bi1j8ph3EGsZ9Xvz9dGuVrtHHs7pXeTzjuxBrCmmhgC6";
    vector3.privkey.n = 111;
    vector3.pubKey.p = "xpub661MyMwAqRbcEZVB4dScxMAdx6d4nFc9nvyvH3v4gJL378CSRZiYmhRoP7mBy6gSPSCYk6SzXPTf3ND1cZAceL7SfJ1Z3GC8vBgp2epUt13";
    vector3.pubKey.n = 111;
    vector3.hexPubKey.p = "03683af1ba5743bdfc798cf814efeeab2735ec52d95eced528e692b8e34c4e5669";
    vector3.hexPubKey.n = 66;
    vector3.wifPrivKey.p = "KwFPqAq9SKx1sPg15Qk56mqkHwrfGPuywtLUxoWPkiTSBoxCs8am";
    vector3.wifPrivKey.n = 52;
    vector3.fingerprint.p = "41d63b50";
    vector3.fingerprint.n = 8;
    vector3.identifier.p = "41d63b50d8dd5e730cdf4c79a56fc929a757c548";
    vector3.identifier.n = 40;
    vector3.chainCode.p = "01d28a3e53cffa419ec122c968b3259e16b65076495494d97cae10bbfec3c36f";
    vector3.chainCode.n = 64;
    vector3.childNUmber = 0;
    vector3.depth = 0;
    vector3.depthNumber = 1;
    // 0
    vector3.children[0].path.p = "m/0'";
    vector3.children[0].path.n = 4;
    vector3.children[0].privKey.p = "xprv9uPDJpEQgRQfDcW7BkF7eTya6RPxXeJCqCJGHuCJ4GiRVLzkTXBAJMu2qaMWPrS7AANYqdq6vcBcBUdJCVVFceUvJFjaPdGZ2y9WACViL4L";
    vector3.children[0].privKey.n = 111;
    vector3.children[0].pubKey.p = "xpub68NZiKmJWnxxS6aaHmn81bvJeTESw724CRDs6HbuccFQN9Ku14VQrADWgqbhhTHBaohPX4CjNLf9fq9MYo6oDaPPLPxSb7gwQN3ih19Zm4Y";
    vector3.children[0].pubKey.n = 111;
    vector3.children[0].fingerprint.p = "c61368bb";
    vector3.children[0].fingerprint.n = 8;
    vector3.children[0].identifier.p = "c61368bb50e066acd95bd04a0b23d3837fb75698";
    vector3.children[0].identifier.n = 40;
    vector3.children[0].chainCode.p = "e5fea12a97b927fc9dc3d2cb0d1ea1cf50aa5a1fdc1f933e8906bb38df3377bd";
    vector3.children[0].chainCode.n = 64;
    vector3.children[0].hexPubKey.p = "027c3591221e28939e45f8ea297d62c3640ebb09d7058b01d09c963d984a40ad49";
    vector3.children[0].hexPubKey.n = 66;
    vector3.children[0].wifPrivKey.p = "L3z3MSqZtDQ1FPHKi7oWf1nc9rMEGFtZUDCoFa7n4F695g5qZiSu";
    vector3.children[0].wifPrivKey.n = 52;
    vector3.children[0].childNUmber = FirstHardenedChild;
    vector3.children[0].depth = 1;

    testMasterKey vector4;
    vector4.seed.p = "d13de7bd1e54422d1a3b3b699a27fb460de2849e7e66a005c647e8e4a54075cb";
    vector4.seed.n = 64;
    vector4.privkey.p = "xprv9s21ZrQH143K3zWpEJm5QtHFh93eNJrNbNqzqLN5XoE9MvC7gs5TmBFaL2PpaXpDc8FBYVe5EChc73ApjSQ5fWsXS7auHy1MmG6hdpywE1q";
    vector4.privkey.n = 111;
    vector4.pubKey.p = "xpub661MyMwAqRbcGUbHLLJ5n2DzFAt8mmaDxbmbdimh68m8EiXGEQPiJya4BJat5yMzy4e68VSUoLGCu5uvzf8dUoGvwuJsLE6F1cibmWsxFNn";
    vector4.pubKey.n = 111;
    vector4.hexPubKey.p = "0298ccc720d5dea817c7077605263bae52bca083cf8888fee77ff4c1b4797ee180";
    vector4.hexPubKey.n = 66;
    vector4.wifPrivKey.p = "KwDiCU5bs8xQwsRgxjhkcJcVuR7NE4Mei8X9uSAVviVTE7JmMoS6";
    vector4.wifPrivKey.n = 52;
    vector4.fingerprint.p = "1a87677b";
    vector4.fingerprint.n = 8;
    vector4.identifier.p = "1a87677be6f73cc9655e8b4c5d2fd0aeeb1b23c7";
    vector4.identifier.n = 40;
    vector4.chainCode.p = "c23ab32b36ddff49fae350a1bed8ec6b4d9fc252238dd789b7273ba4416054eb";
    vector4.chainCode.n = 64;
    vector4.childNUmber = 0;
    vector4.depth = 0;
    vector4.depthNumber = 0;
    // 0
    vector4.children[0].path.p = "m/44'/0'/0'/0/0'";
    vector4.children[0].path.n = 16;
    vector4.children[0].privKey.p = "xprvA3cqPFaMpr7n1wRh6BPtYfwdYRoKCaPzgDdQnUmgMrz1WxWNEW3EmbBr9ieh9BJAsRGKFPLvotb4p4Aq79jddUVKPVJt7exVzLHcv777JVf";
    vector4.children[0].privKey.n = 111;
    vector4.children[0].pubKey.p = "xpub6GcBnm7FfDg5ERWACCvtuotN6Tdoc37r3SZ1asBHvCWzPkqWn3MVKPWKzy6GsfmdMUGanR3D12dH1cp5tJauuubwc4FAJDn67SH2uUjwAT1";
    vector4.children[0].pubKey.n = 111;
    vector4.children[0].fingerprint.p = "e371d69b";
    vector4.children[0].fingerprint.n = 8;
    vector4.children[0].identifier.p = "e371d69b5dae6eacee832a130ee9f55545275a09";
    vector4.children[0].identifier.n = 40;
    vector4.children[0].chainCode.p = "ca27553aa89617e982e621637d6478f564b32738f8bbe2e48d0a58a8e0f6da40";
    vector4.children[0].chainCode.n = 64;
    vector4.children[0].hexPubKey.p = "027c3591221e28939e45f8ea297d62c3640ebb09d7058b01d09c963d984a40ad49";
    vector4.children[0].hexPubKey.n = 66;
    vector4.children[0].wifPrivKey.p = "L3z3MSqZtDQ1FPHKi7oWf1nc9rMEGFtZUDCoFa7n4F695g5qZiSu";
    vector4.children[0].wifPrivKey.n = 52;
    vector4.children[0].childNUmber = FirstHardenedChild;
    vector4.children[0].depth = 5;

    printf("Vector 1\n");
    testVectorKeyPairs(vector1);
    printf("Vector 2\n");
    testVectorKeyPairs(vector2);
    printf("Vector 3\n");
    testVectorKeyPairs(vector3);
    printf("Vector 4\n");
    testVectorKeyPairs(vector4);
}
END_TEST

START_TEST(TestParentPublicChildDerivation)
{
    GoSlice_ extendedMasterPublicBytes_tmp;
    GoString tmp_str = {"xpub6DxSCdWu6jKqr4isjo7bsPeDD6s3J4YVQV1JSHZg12Eagdqnf7XX4fxqyW2sLhUoFWutL7tAELU2LiGZrEXtjVbvYptvTX5Eoa4Mamdjm9u", 111};
    GoUint32 err = SKY_base58_Decode(tmp_str, &extendedMasterPublicBytes_tmp);
    ck_assert_int_eq(err, SKY_OK);

    PublicKey__Handle extendedMasterPublic = 0;
    GoSlice extendedMasterPublicBytes;
    copyGoSlice_toGoSlice(&extendedMasterPublicBytes, &extendedMasterPublicBytes_tmp, extendedMasterPublicBytes_tmp.len);
    err = SKY_bip32_DeserializePublicKey(extendedMasterPublicBytes, &extendedMasterPublic);
    ck_assert_int_eq(err, SKY_OK);

    GoSlice extendedMasterPrivateBytes_tmp;
    tmp_str.p = "xprv9zy5o7z1GMmYdaeQdmabWFhUf52Ytbpe3G5hduA4SghboqWe7aDGWseN8BJy1GU72wPjkCbBE1hvbXYqpCecAYdaivxjNnBoSNxwYD4wHpW";
    tmp_str.n = 111;
    err = SKY_base58_Decode(tmp_str, &extendedMasterPrivateBytes_tmp);
    ck_assert_int_eq(err, SKY_OK);

    PrivateKey__Handle extendedMasterPrivate = 0;
    GoSlice extendedMasterPrivateBytes;
    copyGoSlice_toGoSlice(&extendedMasterPrivateBytes, &extendedMasterPrivateBytes_tmp, extendedMasterPrivateBytes_tmp.len);
    err = SKY_bip32_DeserializePrivateKey(extendedMasterPrivateBytes, &extendedMasterPrivate);
    ck_assert_int_eq(err, SKY_OK);

    testChildKey expectedChildren[MAXBUFFER];
    // 0
    expectedChildren[0].path.p = "m/0";
    expectedChildren[0].path.n = 3;
    expectedChildren[0].hexPubKey.p = "0243187e1a2ba9ba824f5f81090650c8f4faa82b7baf93060d10b81f4b705afd46";
    expectedChildren[0].hexPubKey.n = 66;
    expectedChildren[0].wifPrivKey.p = "KyNPkzzaQ9xa7d2iFacTBgjP4rM3SydTzUZW7uwDh6raePWRJkeM";
    expectedChildren[0].wifPrivKey.n = 52;
    // 1
    expectedChildren[1].path.p = "m/1";
    expectedChildren[1].path.n = 3;
    expectedChildren[1].hexPubKey.p = "023790d11eb715c4320d8e31fba3a09b700051dc2cdbcce03f44b11c274d1e220b";
    expectedChildren[1].hexPubKey.n = 66;
    expectedChildren[1].wifPrivKey.p = "KwVyk5XXaamsPPiGLHciv6AjhUV88CM7xTto7sRMCEy12GfwZzZQ";
    expectedChildren[1].wifPrivKey.n = 52;
    // 2
    expectedChildren[2].path.p = "m/2";
    expectedChildren[2].path.n = 3;
    expectedChildren[2].hexPubKey.p = "0302c5749c3c75cea234878ae3f4d8f65b75d584bcd7ed0943b016d6f6b59a2bad";
    expectedChildren[2].hexPubKey.n = 66;
    expectedChildren[2].wifPrivKey.p = "L1o7CpgTjkcBYmbeuNigVpypgJ9GKq87WNqz8QDjWMqdKVKFf826";
    expectedChildren[2].wifPrivKey.n = 52;
    // 3
    expectedChildren[3].path.p = "m/3";
    expectedChildren[3].path.n = 3;
    expectedChildren[3].hexPubKey.p = "03f0440c94e5b14ea5b15875934597afff541bec287c6e65dc1102cafc07f69699";
    expectedChildren[3].hexPubKey.n = 66;
    expectedChildren[3].wifPrivKey.p = "KzmYqf8WSUNzf2LhAWJjxv7pYX34XhFeLLxSoaSD8y9weJ4j6Z7q";
    expectedChildren[3].wifPrivKey.n = 52;
    // 4
    expectedChildren[4].path.p = "m/4";
    expectedChildren[4].path.n = 3;
    expectedChildren[4].hexPubKey.p = "026419d0d8996707605508ac44c5871edc7fe206a79ef615b74f2eea09c5852e2b";
    expectedChildren[4].hexPubKey.n = 66;
    expectedChildren[4].wifPrivKey.p = "KzezMKd7Yc4jwJd6ASji2DwXX8jB8XwNTggLoAJU78zPAfXhzRLD";
    expectedChildren[4].wifPrivKey.n = 52;
    // 5
    expectedChildren[5].path.p = "m/5";
    expectedChildren[5].path.n = 3;
    expectedChildren[5].hexPubKey.p = "02f63c6f195eea98bdb163c4a094260dea71d264b21234bed4df3899236e6c2298";
    expectedChildren[5].hexPubKey.n = 66;
    expectedChildren[5].wifPrivKey.p = "Kwxik5cHiQCZYy5g9gdfQmr7c3ivLDhFjpSF7McHKHeox6iu6MjL";
    expectedChildren[5].wifPrivKey.n = 52;
    // 6
    expectedChildren[6].path.p = "m/6";
    expectedChildren[6].path.n = 3;
    expectedChildren[6].hexPubKey.p = "02d74709cd522081064858f393d009ead5a0ecd43ede3a1f57befcc942025cb5f9";
    expectedChildren[6].hexPubKey.n = 66;
    expectedChildren[6].wifPrivKey.p = "KwGhZYHovZoczyfupFRgZcr2xz1nHTSKx79uZuWhuzDSU7L7LrxE";
    expectedChildren[6].wifPrivKey.n = 52;
    // 7
    expectedChildren[7].path.p = "m/7";
    expectedChildren[7].path.n = 3;
    expectedChildren[7].hexPubKey.p = "03e54bb92630c943d38bbd8a4a2e65fca7605e672d30a0e545a7198cbb60729ceb";
    expectedChildren[7].hexPubKey.n = 66;
    expectedChildren[7].wifPrivKey.p = "L4iGJ3JCfnMU1ia2bMQeF88hs6tkkS9QrmLbWPsj1ULHrUJid4KT";
    expectedChildren[7].wifPrivKey.n = 52;
    // 8
    expectedChildren[8].path.p = "m/8";
    expectedChildren[8].path.n = 3;
    expectedChildren[8].hexPubKey.p = "027e9d5acd14d39c4938697fba388cd2e8f31fc1c5dc02fafb93a10a280de85199";
    expectedChildren[8].hexPubKey.n = 66;
    expectedChildren[8].wifPrivKey.p = "L3xfynMTDMR8vs6G5VxxjoKLBQyihvtcBHF4KHY5wvFMwevLjZKU";
    expectedChildren[8].wifPrivKey.n = 52;
    // 9
    expectedChildren[9].path.p = "m/9";
    expectedChildren[9].path.n = 3;
    expectedChildren[9].hexPubKey.p = "02a167a9f0d57468fb6abf2f3f7967e2cadf574314753a06a9ef29bc76c54638d2";
    expectedChildren[9].hexPubKey.n = 66;
    expectedChildren[9].wifPrivKey.p = "KxiUV7CcdCuF3bLajqaP6qMFERQFvzsRj9aeCCf3TNWXioLwwJAm";
    expectedChildren[9].wifPrivKey.n = 52;
    // 10
    expectedChildren[10].path.p = "m/100";
    expectedChildren[10].path.n = 5;
    expectedChildren[10].hexPubKey.p = "020db9ba00ddf68428e3f5bfe54252bbcd75b21e42f51bf3bfc4172bf0e5fa7905";
    expectedChildren[10].hexPubKey.n = 66;
    expectedChildren[10].wifPrivKey.p = "L5ipKgExgKZYaxsQPEmyjrhoSepoxuSAxSWgK1GX5kaTUN3zGCU7";
    expectedChildren[10].wifPrivKey.n = 52;
    // 11
    expectedChildren[11].path.p = "m/101";
    expectedChildren[11].path.n = 5;
    expectedChildren[11].hexPubKey.p = "0299e3790956570737d6164e6fcda5a3daa304065ca95ba46bc73d436b84f34d46";
    expectedChildren[11].hexPubKey.n = 66;
    expectedChildren[11].wifPrivKey.p = "L1iUjHWpYSead5vYZycMdMzCZDFQzveG3S6NviAi5BvvGdnuQbi6";
    expectedChildren[11].wifPrivKey.n = 52;
    // 12
    expectedChildren[12].path.p = "m/102";
    expectedChildren[12].path.n = 5;
    expectedChildren[12].hexPubKey.p = "0202e0732c4c5d2b1036af173640e01957998cfd4f9cdaefab6ffe76eb869e2c59";
    expectedChildren[12].hexPubKey.n = 66;
    expectedChildren[12].wifPrivKey.p = "KybjnK4e985dgzxL5pgXTfq8YFagG8gB9HWAjLimagR4pdodCSNo";
    expectedChildren[12].wifPrivKey.n = 52;
    // 13
    expectedChildren[13].path.p = "m/103";
    expectedChildren[13].path.n = 5;
    expectedChildren[13].hexPubKey.p = "03d050adbd996c0c5d737ff638402dfbb8c08e451fef10e6d62fb57887c1ac6cb2";
    expectedChildren[13].hexPubKey.n = 66;
    expectedChildren[13].wifPrivKey.p = "Kx9bf5cyf29fp7uuMVnqn47692xRwXStVmnL75w9i1sLQDjbFHP5";
    expectedChildren[13].wifPrivKey.n = 52;
    // 14
    expectedChildren[14].path.p = "m/104";
    expectedChildren[14].path.n = 5;
    expectedChildren[14].hexPubKey.p = "038d466399e2d68b4b16043ad4d88893b3b2f84fc443368729a973df1e66f4f530";
    expectedChildren[14].hexPubKey.n = 66;
    expectedChildren[14].wifPrivKey.p = "L5myg7MNjKHcgVMS9ytmHgBftiWAi1awGpeC6p9dygsEQV9ZRvpz";
    expectedChildren[14].wifPrivKey.n = 52;
    // 15
    expectedChildren[15].path.p = "m/105";
    expectedChildren[15].path.n = 5;
    expectedChildren[15].hexPubKey.p = "034811e2f0c8c50440c08c2c9799b99c911c036e877e8325386ff61723ae3ffdce";
    expectedChildren[15].hexPubKey.n = 66;
    expectedChildren[15].wifPrivKey.p = "L1KHrLBPhaJnvysjKUYk5QwkyWDb6uHgDM8EmE4eKtfqyJ13a7HC";
    expectedChildren[15].wifPrivKey.n = 52;
    // 16
    expectedChildren[16].path.p = "m/106";
    expectedChildren[16].path.n = 5;
    expectedChildren[16].hexPubKey.p = "026339fd5842921888e711a6ba9104a5f0c94cc0569855273cf5faefdfbcd3cc29";
    expectedChildren[16].hexPubKey.n = 66;
    expectedChildren[16].wifPrivKey.p = "Kz4WPV43po7LRkatwHf9YGknGZRYfvo7TkvojinzxoFRXRYXyfDn";
    expectedChildren[16].wifPrivKey.n = 52;
    // 17
    expectedChildren[17].path.p = "m/107";
    expectedChildren[17].path.n = 5;
    expectedChildren[17].hexPubKey.p = "02833705c1069fab2aa92c6b0dac27807290d72e9f52378d493ac44849ca003b22";
    expectedChildren[17].hexPubKey.n = 66;
    expectedChildren[17].wifPrivKey.p = "L3PxeN4w336kTk1becdFsAnR8ihh8SeMYXRHEzSmRNQTjtmcUjr9";
    expectedChildren[17].wifPrivKey.n = 52;
    // 18
    expectedChildren[18].path.p = "m/108";
    expectedChildren[18].path.n = 5;
    expectedChildren[18].hexPubKey.p = "032d2639bde1eb7bdf8444bd4f6cc26a9d1bdecd8ea15fac3b992c3da68d9d1df5";
    expectedChildren[18].hexPubKey.n = 66;
    expectedChildren[18].wifPrivKey.p = "L2wf8FYiA888qrhDzHkFkZ3ZRBntysjtJa1QfcxE1eFiyDUZBRSi";
    expectedChildren[18].wifPrivKey.n = 52;
    // 19
    expectedChildren[19].path.p = "m/109";
    expectedChildren[19].path.n = 5;
    expectedChildren[19].hexPubKey.p = "02479c6d4a64b93a2f4343aa862c938fbc658c99219dd7bebb4830307cbd76c9e9";
    expectedChildren[19].hexPubKey.n = 66;
    expectedChildren[19].wifPrivKey.p = "L5A5hcupWnYTNJTLTWDDfWyb3hnrJgdDgyN7c4PuF17bsY1tNjxS";
    expectedChildren[19].wifPrivKey.n = 52;

    for (size_t i = 0; i < 20; i++) {
        testChildKey child = expectedChildren[i];
        Path__Handle path;
        err = SKY_bip32_ParsePath(child.path, &path);
        ck_assert_int_eq(err, SKY_OK);
        GoInt len;
        err = SKY_bip32_Path_Count(path, &len);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert_int_eq(len, 2);

        PublicKey__Handle pubKey = 0;
        bip32__PathNode element_tmp;
        err = SKY_bip32_Path_GetElements(path, 1, &element_tmp);
        ck_assert_int_eq(err, SKY_OK);
        err = SKY_bip32_PublicKey_NewPublicChildKey(extendedMasterPublic, element_tmp.ChildNumber, &pubKey);
        ck_assert_int_eq(err, SKY_OK);
        GoSlice_ pubkey_key_tmp;
        err = SKY_bip32_PublicKey_GetKey(pubKey, &pubkey_key_tmp);
        ck_assert_int_eq(err, SKY_OK);

        GoString_ pubkey_hexpubkey;
        GoSlice pubkey_key;
        copyGoSlice_toGoSlice(&pubkey_key, &pubkey_key_tmp, pubkey_key_tmp.len);
        err = SKY_base58_Hex2String(pubkey_key, &pubkey_hexpubkey);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isGoString_toGoStringEq(pubkey_hexpubkey, child.hexPubKey));

        PublicKey__Handle pubKey2 = 0;
        err = SKY_bip32_PrivateKey_NewPublicChildKey(extendedMasterPrivate, element_tmp.ChildNumber, &pubKey2);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isPublicKeyEq(pubKey, pubKey2));

        PrivateKey__Handle privKey = 0;
        err = SKY_bip32_PrivateKey_NewPrivateChildKey(extendedMasterPrivate, element_tmp.ChildNumber, &privKey);
        ck_assert_int_eq(err, SKY_OK);

        cipher__SecKey expectedPrivKey;
        err = SKY_cipher_SecKeyFromBitcoinWalletImportFormat(child.wifPrivKey, &expectedPrivKey);
        ck_assert_int_eq(err, SKY_OK);

        PublicKey__Handle pubKey3 = 0;
        err = SKY_bip32_PrivateKey_Publickey(privKey, &pubKey3);
        ck_assert_int_eq(err, SKY_OK);
        ck_assert(isPublicKeyEq(pubKey, pubKey3));
    }
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

typedef struct {
    GoUint32 err;
    GoString base58;
} tests_Struct;


START_TEST(TestDeserializePrivateInvalidStrings)
{
    tests_Struct tests[MAXBUFFER];
    // 0
    tests[0].err = SKY_ErrSerializedKeyWrongSize;
    tests[0].base58.p = "xprv9s21ZrQH143K4YUcKrp6cVxQaX59ZFkN6MFdeZjt8CHVYNs55xxQSvZpHWfojWMv6zgjmzopCyWPSFAnV4RU33J4pwCcnhsB4R4mPEnTsM";
    tests[0].base58.n = 110;
    // 1
    tests[1].err = SKY_bip32_ErrInvalidChecksum;
    tests[1].base58.p = "xprv9s21ZrQH143K3YSbAXLMPCzJso5QAarQksAGc5rQCyZCBfw4Rj2PqVLFNgezSBhktYkiL3Ta2stLPDF9yZtLMaxk6Spiqh3DNFG8p8MVeEc";
    tests[1].base58.n = 111;
    // 2
    tests[2].err = SKY_ErrInvalidPrivateKeyVersion;
    tests[2].base58.p = "xpub6DxSCdWu6jKqr4isjo7bsPeDD6s3J4YVQV1JSHZg12Eagdqnf7XX4fxqyW2sLhUoFWutL7tAELU2LiGZrEXtjVbvYptvTX5Eoa4Mamdjm9u";
    tests[2].base58.n = 111;
    // 3
    tests[3].err = SKY_ErrInvalidKeyVersion;
    tests[3].base58.p = "8FH81Rao5EgGmdScoN66TJAHsQP7phEMeyMTku9NBJd7hXgaj3HTvSNjqJjoqBpxdbuushwPEM5otvxXt2p9dcw33AqNKzZEPMqGHmz7Dpayi6Vb";
    tests[3].base58.n = 112;
    // 4
    tests[4].err = SKY_bip32_ErrInvalidChecksum;
    tests[4].base58.p = "xprvQQQQQQQQQQQQQQQQCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334";
    tests[4].base58.n = 111;
    // 5
    tests[5].err = SKY_ErrSerializedKeyWrongSize;
    tests[5].base58.p = "HAsbc6CgKmTYEQg2CTz7m5STEPAB";
    tests[5].base58.n = 28;
    // 6
    tests[6].err = SKY_ErrInvalidFingerprint;
    tests[6].base58.p = "xprv9tnJFvAXAXPfPnMTKfwpwnkty7MzJwELVgp4NTBquaKXy4RndyfJJCJJf7zNaVpBpzrwVRutZNLRCVLEcZHcvuCNG3zGbGBcZn57FbNnmSP";
    tests[6].base58.n = 111;
    // 7
    tests[7].err = SKY_ErrInvalidPrivateKey;
    tests[7].base58.p = "xprv9s21ZrQH143K3yLysFvsu3n1dMwhNusmNHr7xArzAeCc7MQYqDBBStmqnZq6WLi668siBBNs3SjiyaexduHu9sXT9ixTsqptL67ADqcaBdm";
    tests[7].base58.n = 111;
    // 8
    tests[8].err = SKY_ErrInvalidChildNumber;
    tests[8].base58.p = "xprv9s21ZrQYdgnodnKW4Drm1Qg7poU6Gf2WUDsjPxvYiK7iLBMrsjbnF1wsZZQgmXNeMSG3s7jmHk1b3JrzhG5w8mwXGxqFxfrweico7k8DtxR";
    tests[8].base58.n = 111;
    // 9
    tests[9].err = SKY_ErrInvalidKeyVersion;
    tests[9].base58.p = "1111111111111adADjFaSNPxwXqLjHLj4mBfYxuewDPbw9hEj1uaXCzMxRPXDFF3cUoezTFYom4sEmEVSQmENPPR315cFk9YUFVek73wE9";
    tests[9].base58.n = 106;
    // 10
    tests[10].err = SKY_ErrSerializedKeyWrongSize;
    tests[10].base58.p = "9XpNiB4DberdMn4jZiMhNGtuZUd7xUrCEGw4MG967zsVNvUKBEC9XLrmVmFasanWGp15zXfTNw4vW4KdvUAynEwyKjdho9QdLMPA2H5uyt";
    tests[10].base58.n = 106;
    // 11
    tests[11].err = SKY_ErrSerializedKeyWrongSize;
    tests[11].base58.p = "7JJikZQ2NUXjSAnAF2SjFYE3KXbnnVxzRBNddFE1DjbDEHVGEJzYC7zqSgPoauBJS3cWmZwsER94oYSFrW9vZ4Ch5FtGeifdzmtS3FGYDB1vxFZsYKgMc";
    tests[11].base58.n = 117;

    for (size_t i = 0; i < 12; i++) {
        tests_Struct test = tests[i];
        GoUint8 bufferb[MAXBUFFER];
        GoSlice_ b_tmp = {bufferb, 0, MAXBUFFER};
        GoUint32 err = SKY_base58_Decode(test.base58, &b_tmp);
        ck_assert_int_eq(err, SKY_OK);

        PrivateKey__Handle rest_priv = 0;
        GoSlice b;
        copyGoSlice_toGoSlice(&b, &b_tmp, b_tmp.len);
        err = SKY_bip32_DeserializePrivateKey(b, &rest_priv);
        ck_assert_int_eq(err, test.err);
    }
}
END_TEST

START_TEST(TestDeserializePublicInvalidStrings)
{
    tests_Struct tests[MAXBUFFER];
    // 0
    tests[0].err = SKY_ErrSerializedKeyWrongSize;
    tests[0].base58.p = "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet888";
    tests[0].base58.n = 113;
    // 1
    tests[1].err = SKY_bip32_ErrInvalidChecksum;
    tests[1].base58.p = "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W11GMcet8";
    tests[1].base58.n = 111;
    // 2
    tests[2].err = SKY_ErrInvalidPublicKeyVersion;
    tests[2].base58.p = "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7";
    tests[2].base58.n = 111;
    // 3
    tests[3].err = SKY_ErrInvalidFingerprint;
    tests[3].base58.p = "xpub67tVq9SuNQCfm2PXBqjGRAtNZ935kx2uHJaURePth4JBpMfEy6jum7Euj7FTpbs7fnjhfZcNEktCucWHcJf74dbKLKNSTZCQozdDVwvkJhs";
    tests[3].base58.n = 111;
    // 4
    tests[4].err = SKY_ErrInvalidChildNumber;
    tests[4].base58.p = "xpub661MyMwTWkfYZq6BEh3ywGVXFvNj5hhzmWMhFBHSqmub31B1LZ9wbJ3DEYXZ8bHXGqnHKfepTud5a2XxGdnnePzZa2m2DyzTnFGBUXtaf9M";
    tests[4].base58.n = 111;
    // 5
    tests[5].err = SKY_ErrInvalidPublicKey;
    tests[5].base58.p = "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gYymDsxxRe3WWeZQ7TadaLSdKUffezzczTCpB8j3JP96UwE2n6w1";
    tests[5].base58.n = 111;
    // 6
    tests[6].err = SKY_ErrInvalidKeyVersion;
    tests[6].base58.p = "8FH81Rao5EgGmdScoN66TJAHsQP7phEMeyMTku9NBJd7hXgaj3HTvSNjqJjoqBpxdbuushwPEM5otvxXt2p9dcw33AqNKzZEPMqGHmz7Dpayi6Vb";
    tests[6].base58.n = 112;
    // 7
    tests[7].err = SKY_ErrInvalidKeyVersion;
    tests[7].base58.p = "1111111111111adADjFaSNPxwXqLjHLj4mBfYxuewDPbw9hEj1uaXCzMxRPXDFF3cUoezTFYom4sEmEVSQmENPPR315cFk9YUFVek73wE9";
    tests[7].base58.n = 106;
    // 8
    tests[8].err = SKY_ErrSerializedKeyWrongSize;
    tests[8].base58.p = "7JJikZQ2NUXjSAnAF2SjFYE3KXbnnVxzRBNddFE1DjbDEHVGEJzYC7zqSgPoauBJS3cWmZwsER94oYSFrW9vZ4Ch5FtGeifdzmtS3FGYDB1vxFZsYKgMc";
    tests[8].base58.n = 117;

    for (size_t i = 0; i < 9; i++) {
        tests_Struct test = tests[i];
        GoUint8 bufferb[MAXBUFFER];
        GoSlice_ b_tmp = {bufferb, 0, MAXBUFFER};
        GoUint32 err = SKY_base58_Decode(test.base58, &b_tmp);
        ck_assert_msg(err == SKY_OK, " Iter %d", i);

        PublicKey__Handle rest_pub = 0;
        GoSlice b;
        copyGoSlice_toGoSlice(&b, &b_tmp, b_tmp.len);
        err = SKY_bip32_DeserializePublicKey(b, &rest_pub);
        ck_assert_msg(err == test.err, "Iter %d", i);
    }
}
END_TEST

START_TEST(TestCantCreateHardenedPublicChild)
{
    GoUint8 bufferb[MAXBUFFER];
    GoSlice b = {bufferb, 0, MAXBUFFER};
    randBytes(&b, 32);
    PrivateKey__Handle key = 0;
    GoUint32 err = SKY_bip32_NewMasterKey(b, &key);
    ck_assert(err == SKY_OK);

    // Test that it works for private keys
    PrivateKey__Handle priv_temp = 0;
    err = SKY_bip32_PrivateKey_NewPrivateChildKey(key, FirstHardenedChild - 1, &priv_temp);
    ck_assert(err == SKY_OK);
    err = SKY_bip32_PrivateKey_NewPrivateChildKey(key, FirstHardenedChild, &priv_temp);
    ck_assert(err == SKY_OK);
    err = SKY_bip32_PrivateKey_NewPrivateChildKey(key, FirstHardenedChild + 1, &priv_temp);
    ck_assert(err == SKY_OK);

    // Test that it throws an error for public keys if hardened
    PublicKey__Handle pubkey = 0;
    err = SKY_bip32_PrivateKey_Publickey(key, &pubkey);
    ck_assert(err == SKY_OK);

    PublicKey__Handle pub_temp = 0;
    err = SKY_bip32_PublicKey_NewPublicChildKey(pubkey, FirstHardenedChild - 1, &pub_temp);
    ck_assert(err == SKY_OK);
    err = SKY_bip32_PublicKey_NewPublicChildKey(pubkey, FirstHardenedChild, &pub_temp);
    ck_assert_int_eq(err, SKY_ErrHardenedChildPublicKey);
    err = SKY_bip32_PublicKey_NewPublicChildKey(pubkey, FirstHardenedChild + 1, &pub_temp);
    ck_assert_int_eq(err, SKY_ErrHardenedChildPublicKey);
}
END_TEST

typedef struct
{
    GoString seed;
    GoString path;
    GoString key;
    GoUint32 err;
} cases_Str;


START_TEST(TestNewPrivateKeyFromPath)
{
    cases_Str cases[MAXBUFFER];
    // 0
    cases[0].seed.p = "6162636465666768696A6B6C6D6E6F707172737475767778797A";
    cases[0].seed.n = 52;
    cases[0].path.p = "m";
    cases[0].path.n = 1;
    cases[0].key.p = "xprv9s21ZrQH143K3GfuLFf1UxUB4GzmFav1hrzTG1bPorBTejryu4YfYVxZn6LNmwfvsi6uj1Wyv9vLDPsfKDuuqwEqYier1ZsbgWVd9NCieNv";
    cases[0].key.n = 111;
    cases[0].err = SKY_OK;
    // 1
    cases[1].seed.p = "6162636465666768696A6B6C6D6E6F707172737475767778797A";
    cases[1].seed.n = 52;
    cases[1].path.p = "m/1'";
    cases[1].path.n = 4;
    cases[1].key.p = "xprv9uWf8oyvCHcAUg3kSjSroz67s7M3qJRWmNcdVwYGf91GFsaAatsVVp1bjH7z3WiWevqB7WK92B415oBwcahjoMvvb4mopPyqZUDeVW4168c";
    cases[1].key.n = 111;
    cases[1].err = SKY_OK;
    // 2
    cases[2].seed.p = "6162636465666768696A6B6C6D6E6F707172737475767778797A";
    cases[2].seed.n = 52;
    cases[2].path.p = "m/1'/foo";
    cases[2].path.n = 8;
    cases[2].key.p = "";
    cases[2].key.n = 0;
    cases[2].err = SKY_ErrPathNodeNotNumber;
    // 3
    cases[3].seed.p = "6162";
    cases[3].seed.n = 4;
    cases[3].path.p = "m/1";
    cases[3].path.n = 3;
    cases[3].key.p = "";
    cases[3].key.n = 0;
    cases[3].err = SKY_ErrInvalidSeedLength;

    for (size_t i = 0; i < 4; i++) {
        cases_Str tc = cases[i];
        GoUint8 bufferseed[MAXBUFFER];
        GoSlice_ seed_tmp = {bufferseed, 0, MAXBUFFER};
        GoUint32 err = SKY_base58_String2Hex(tc.seed, &seed_tmp);
        ck_assert(err == SKY_OK);

        PrivateKey__Handle k = 0;
        GoSlice seed;
        copyGoSlice_toGoSlice(&seed, &seed_tmp, seed_tmp.len);
        err = SKY_bip32_NewPrivateKeyFromPath(seed, tc.path, &k);
        ck_assert(err == tc.err);
        if (err == SKY_OK) {
            GoUint8 bufferk_string[MAXBUFFER];
            GoString_ k_string = {bufferk_string, 0};
            err = SKY_bip32_PrivateKey_String(k, &k_string);
            ck_assert(err == SKY_OK);
            ck_assert(isGoString_toGoStringEq(k_string, tc.key));
        }
    }
}
END_TEST
Suite* cipher_bip32(void)
{
    Suite* s = suite_create("Load cipher.bip32");
    TCase* tc;

    tc = tcase_create("cipher.bip32");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestMaxChildDepthError);
    tcase_add_test(tc, TestParentPublicChildDerivation);
    // tcase_add_test(tc, TestBip32TestVectors);
    tcase_add_test(tc, TestDeserializePrivateInvalidStrings);
    tcase_add_test(tc, TestDeserializePublicInvalidStrings);
    tcase_add_test(tc, TestCantCreateHardenedPublicChild);
    tcase_add_test(tc, TestNewPrivateKeyFromPath);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}