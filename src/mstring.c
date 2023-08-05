#include "include/mstring.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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

/**
 * @brief Handles errors of different kinds.
 * 
 */
static void error_handler();

/**
 * @brief Reallocates the string buffer.
 * 
 * @param str string object
 * @param new_sz new size (capacity)
 */
void reallocate(mstring str, size_t new_sz)
{
    new_sz = new_size(new_sz);
    char *tmp = realloc(str->buffer, sizeof(char) * new_sz);
    if (NULL != tmp) str->buffer = tmp;
    error_handler();
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

int mstr_compare(mstring lhs, mstring rhs)
{
    if (NULL == lhs || NULL == rhs) return 0;
    return strcmp(lhs->buffer, rhs->buffer);
}

static void error_handler()
{

}
