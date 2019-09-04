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
    GoSlice seed = {bufferseed, 0, MAXBUFFER};
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
    GoString stringPrivKey = {bufferstringPrivKey, 0};
    GoString stringPubKey = {bufferstringPubKey, 0};
    err = SKY_bip32_PrivateKey_String(privkey, &stringPrivKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoStringEq(stringPrivKey, vector.privkey));
    err = SKY_bip32_PublicKey_String(pubkey, &stringPubKey);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(isGoStringEq(stringPubKey, vector.pubKey));

    GoUint8 bufferhexPubKey[1024];
    GoString hexPubKey = {bufferhexPubKey, 0};
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
    GoUint8 bufferwif[1024];
    GoString wif = {bufferwif, 0};
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
    GoUint8 bufferpriv_Fringerprint[MAXBUFFER];
    GoString priv_Fringerprint = {bufferpriv_Fringerprint, 0};
    GoUint8 bufferpub_Fringerprint[MAXBUFFER];
    GoString pub_Fringerprint = {bufferpub_Fringerprint, 0};
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
        printf("Iter %d\n", i);
        testChildKey tck = vector.children[i];
        privkey = 0;
        err = SKY_bip32_NewPrivateKeyFromPath(seed, tck.path, &privkey);
        ck_assert_int_eq(SKY_OK, err);

        // Get this private key's public key
        pubkey = 0;
        err = SKY_bip32_PrivateKey_Publickey(privkey, &pubkey);
        ck_assert_int_eq(SKY_OK, err);

        // Test DeserializePrivateKey
        GoUint8 bufferppk[MAXBUFFER];
        GoSlice ppk = {bufferppk, 0, MAXBUFFER};
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
    GoSlice extendedMasterPublicBytes;
    GoString tmp_str = {"xpub6DxSCdWu6jKqr4isjo7bsPeDD6s3J4YVQV1JSHZg12Eagdqnf7XX4fxqyW2sLhUoFWutL7tAELU2LiGZrEXtjVbvYptvTX5Eoa4Mamdjm9u", 111};
    GoUint32 err = SKY_base58_Decode(tmp_str, &extendedMasterPublicBytes);
    ck_assert_int_eq(err, SKY_OK);

    PublicKey__Handle extendedMasterPublic = 0;
    err = SKY_bip32_DeserializePublicKey(extendedMasterPublicBytes, &extendedMasterPublic);
    ck_assert_int_eq(err, SKY_OK);

    GoSlice extendedMasterPrivateBytes;
    tmp_str.p = "xprv9zy5o7z1GMmYdaeQdmabWFhUf52Ytbpe3G5hduA4SghboqWe7aDGWseN8BJy1GU72wPjkCbBE1hvbXYqpCecAYdaivxjNnBoSNxwYD4wHpW";
    tmp_str.n = 111;
    err = SKY_base58_Decode(tmp_str, &extendedMasterPrivateBytes);
    ck_assert_int_eq(err, SKY_OK);

    PrivateKey__Handle extendedMasterPrivate = 0;
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

    for (size_t i = 0; i < 1; i++) {
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
        GoSlice pubkey_key;
        err = SKY_bip32_PublicKey_GetKey(pubKey, &pubkey_key);
        ck_assert_int_eq(err, SKY_OK);

        GoString pubkey_hexpubkey;
        err = SKY_base58_Hex2String(pubkey_key, &pubkey_hexpubkey);
        ck_assert(isGoStringEq(child.hexPubKey, pubkey_hexpubkey));

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

Suite* cipher_bip32(void)
{
    Suite* s = suite_create("Load cipher.bip32");
    TCase* tc;

    tc = tcase_create("cipher.bip32");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestMaxChildDepthError);
    tcase_add_test(tc, TestParentPublicChildDerivation);
    tcase_add_test(tc, TestBip32TestVectors);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}