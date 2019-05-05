
#ifndef CIPHER_TESTSUITE_TESTSUITE
#define CIPHER_TESTSUITE_TESTSUITE


#include "base64.h"
#include "json.h"
#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"

#define BUFFER_SIZE         1024
#define STRING_SIZE         128
#define JSON_FILE_SIZE      4096
#define JSON_BIG_FILE_SIZE  32768

#define FILEPATH_SEPARATOR      "/"
#define TEST_DATA_DIR           "vendor/github.com/skycoin/skycoin/src/cipher/testsuite/testdata/"
#define MANY_ADDRESSES_FILENAME "many-addresses.golden"
#define  INPUT_HASHES_FILENAME   "input-hashes.golden"
#define SEED_FILE_REGEX         "seed-\d+.golden"

//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

// InputTestData contains hashes to be signed
typedef struct {
  // Slice data is an array of cipher.SHA256's
  GoSlice Hashes;
} InputTestData; 

// InputTestDataJSON contains hashes to be signed
typedef struct {
  // Slice data is an array of GoString's
  GoSlice Hashes;
} InputTestDataJSON;

// KeysTestData contains address, public key,  secret key and list of signatures
typedef struct {
  cipher__Address Address;
  cipher__SecKey Secret;
  cipher__PubKey Public;
  // Slice data is an array of cipher.Sig's
  GoSlice Signatures;
} KeysTestData;

// KeysTestDataJSON contains address, public key,  secret key and list of signatures
typedef struct {
  GoString  Address;
  GoString  Secret;
  GoString  Public;
  // Slice data is an array of GoString's
  GoSlice   Signatures;
} KeysTestDataJSON;

// SeedTestDataJSON contains data generated by Seed
typedef struct {
  GoString  Seed;
  // Slice data is an array of KeysTestDataJSON's
  GoSlice   Keys;
} SeedTestDataJSON;

// SeedTestData contains data generated by Seed
typedef struct {
  // Slice data is a bytes array buffer
  GoSlice Seed;
  // Slice data is an array of KeysTestData
  GoSlice Keys;
} SeedTestData;

struct cr_mem
{
  const void *data;
  size_t size;

#ifdef __cplusplus
  template <typename T, size_t N>
  constexpr cr_mem(const T (&arr)[N])
      : data(static_cast<const void *>(&arr)), size(N)
  {
  }

  template <typename T>
  constexpr cr_mem(const T *arr, size_t n)
      : data(static_cast<const void *>(arr)), size(n)
  {
  }
#endif /* !__cplusplus */
};
//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

json_value* loadGoldenFile(const char* file);
InputTestDataJSON* jsonToInputTestData(json_value* json, InputTestDataJSON* input_data);
InputTestData* registerInputTestDataCleanup(InputTestData* input_data);
InputTestDataJSON* registerInputTestDataJSONCleanup(InputTestDataJSON* input_data);
void InputTestDataToJSON(InputTestData* input_data, InputTestDataJSON* json_data);
GoUint32 InputTestDataFromJSON(InputTestDataJSON* json_data, InputTestData* input_data);
KeysTestDataJSON* jsonToKeysTestData(json_value* json, KeysTestDataJSON* input_data);
KeysTestData* registerKeysTestDataCleanup(KeysTestData* input_data);
KeysTestDataJSON* registerKeysTestDataJSONCleanup(KeysTestDataJSON* input_data);
void KeysTestDataToJson(KeysTestData* input_data, KeysTestDataJSON* json_data);
GoUint32 KeysTestDataFromJSON(KeysTestDataJSON* json_data, KeysTestData* input_data);
SeedTestDataJSON* jsonToSeedTestData(json_value* json, SeedTestDataJSON* input_data);
SeedTestData* registerSeedTestDataCleanup(SeedTestData* input_data);
SeedTestDataJSON* registerSeedTestDataJSONCleanup(SeedTestDataJSON* input_data);
void SeedTestDataToJson(SeedTestData* input_data, SeedTestDataJSON* json_data);
GoUint32 SeedTestDataFromJSON(SeedTestDataJSON* json_data, SeedTestData* input_data);
void ValidateSeedData(SeedTestData* seedData, InputTestData* inputData);
int isGoldenFile(const char *filename);

#endif

