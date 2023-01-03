#include <stdint.h>
#include <stddef.h>

/// @brief Maximum value of 16 bit size types
#define SIZE_MAX_16 0xFFFF
/// @brief Maximum value of 32 bit size types
#define SIZE_MAX_32 0xFFFFFFFF
/// @brief Maximum value of 64 bit size types
#define SIZE_MAX_64 0xFFFFFFFFFFFFFFFF

// Checks the size of the size_t type and sets
// the ARCH_BITS macro accordinlgy
#if (SIZE_MAX == SIZE_MAX_16)
    #define ARCH_BITS 16
#elif (SIZE_MAX == SIZE_MAX_32)
    #define ARCH_BITS 32
#elif (SIZE_MAX == SIZE_MAX_64)
    #define ARCH_BITS 64
#else
    #error Unsupported architecture
#endif

/**
 * @brief mstring object structure.
 * 
 * The implementation is header-private, as it must not be visible
 * to the user
 */
typedef struct mstring_t* mstring;

/**
 * @brief Constructs a new mstring object.
 * 
 * @return mstring value or NULL pointer on failure.
 */
mstring mstr_construct();

/**
 * @brief Constructs a new mstring object initializing
 * its internal value.
 * 
 * @param init initialization value.
 * @return mstring value or NULL pointer on failure.
 */
mstring mstr_construct_init(const char init[]);

/**
 * @brief Deletes an mstring object from memory.
 * 
 * @param str string to delete.
 */
void mstr_delete(mstring str);
