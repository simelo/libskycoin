typedef struct {
    GoUint64_ Time;
    GoUint64_ BkSeq;
} coin__UxHead;

typedef struct {
    void* data; ///< Pointer to buffer containing slice data.
    GoInt_ len; ///< Number of items stored in slice buffer
    GoInt_ cap; ///< Maximum number of items that fits in this slice
                ///< considering allocated memory and item type's
                ///< size.
} coin__UxArray;

typedef struct {
    cipher__SHA256 SrcTransaction;
    cipher__Address Address;
    GoUint64_ Coins;
    GoUint64_ Hours;
} coin__UxBody;

typedef struct {
    coin__UxHead Head;
    coin__UxBody Body;
} coin__UxOut;
