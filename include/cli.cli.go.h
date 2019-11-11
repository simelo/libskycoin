typedef struct {
    void* data; ///< Pointer to buffer containing slice data.
    GoInt_ len; ///< Number of items stored in slice buffer
    GoInt_ cap; ///< Maximum number of items that fits in this slice
                ///< considering allocated memory and item type's
                ///< size.
} cli__PasswordFromBytes;
