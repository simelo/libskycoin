
typedef struct {
    const char* p; ///< Pointer to string characters buffer.
    GoInt_ n;      ///< String size not counting trailing `\0` char
                   ///< if at all included.
} wallet__CryptoType;