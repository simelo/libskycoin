typedef struct {
    GoString_ DataDir;
    GoString_ Coin;
    GoString_ RPCAddress;
    GoString_ RPCUsername;
    GoString_ RPCPassword;
} cli__Config;
typedef struct {
    GoInt32_ _unnamed;
} cli__WalletLoadError;
typedef struct {
    GoInt32_ _unnamed;
} cli__WalletSaveError;
typedef GoInterface_ cli__PasswordReader;
typedef GoSlice_ cli__PasswordFromBytes;
typedef struct {
} cli__PasswordFromTerm;
