#include "include/mstring.h"

#include <string.h>
#include <stdlib.h>

/// @brief Contains the actual mstring private
/// implementation.
struct mstring_t {
    char *buffer;
    size_t size;
    size_t capacity;
};

/**
 * @brief Calculates the new size of the string
 * 
 * @param sz 
 * @return size_t 
 */
inline static size_t new_size(size_t sz)
{
    --sz;

    sz |= sz >> 1;
    sz |= sz >> 2;
    sz |= sz >> 4;
    sz |= sz >> 8;
#if defined(ARCH_BITS_32)
    sz |= sz >> 16;
#elif defined(ARCH_BITS_64)
    sz |= sz >> 16;
    sz |= sz >> 32;
#endif

    ++sz;
    return sz;
}

mstring mstr_construct()
{
    mstring str = (mstring) malloc(sizeof(struct mstring_t));
    if (NULL == str) return NULL;

    // Allocate internal storage
    str->buffer = (char *) malloc(sizeof(char) * INITIAL_CAPACITY);

    // Allocation error check
    if (NULL == str->buffer) {
        // Free the object
        free(str);
        return NULL;
    }

    str->buffer[0] = '\0';
    str->size = 0;
    str->capacity = INITIAL_CAPACITY;

    return str;
}

mstring mstr_construct_init(const char init[])
{
    mstring str = (mstring) malloc(sizeof(struct mstring_t));
    if (NULL == str) return NULL;

    // Get the length of the string
    size_t len = strlen(init);
    size_t cap = len + 1;

    // Allocate internal storage and copy the string
    str->buffer = (char *)malloc(sizeof(char) * cap);
    if (NULL == str->buffer) {
        free(str);
        return NULL;
    }

    memcpy(str->buffer, init, cap * sizeof(char));
    str->size = len;
    str->capacity = cap;

    return str;
}

void mstr_delete(mstring str)
{
    if (NULL == str) return;
    if (NULL != str->buffer) {
        free(str->buffer);
    }

    free(str);
}
