typedef struct {
    GoUint64_ Time;
    GoUint64_ BkSeq;
} coin__UxHead;
typedef struct {
    cipher__SHA256 SrcTransaction;
    cipher__Address Address;
    GoUint64_ Coins;
    GoUint64_ Hours;
} coin__UxBody;
typedef GoMap_ coin__UxHashSet;
typedef GoMap_ coin__AddressUxOuts;
typedef struct {
    coin__UxHead Head;
    coin__UxBody Body;
} coin__UxOut;

typedef struct {
    void* data;
    GoInt_ len;
    GoInt_ cap;
    GoInt_ a;
} coin__UxArray;