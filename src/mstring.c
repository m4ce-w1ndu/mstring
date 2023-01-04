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
    if (NULL != tmp) { 
        str->buffer = tmp;
        str->capacity = new_sz;
        return;
    }
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

size_t mstr_get_size(mstring str)
{
    if (NULL == str || NULL == str->buffer) return 0;
    return str->size;
}

size_t mstr_get_capacity(mstring str)
{
    if (NULL == str || NULL == str->buffer) return 0;
    return str->capacity;
}

int mstr_is_empty(mstring str)
{
    return (mstr_get_size(str) == 0);
}

void mstr_reserve(mstring str, size_t sz)
{
    if (NULL == str || NULL == str->buffer) return;
    char *buf = realloc(str->buffer, sizeof(char) * new_size(sz));
    if (NULL == buf) return;

    str->buffer = buf;
    str->capacity = new_size(sz);
}

void mstr_resize(mstring str, size_t new_sz)
{
    if (NULL == str || NULL == str->buffer) return;
    char *buf = (char *) realloc(str->buffer, sizeof(char) * new_sz + 1);
    if (NULL == buf) return;

    str->buffer = buf;
    str->size = new_sz;
    str->capacity = new_sz + 1;
}

void mstr_assign(mstring str, const char c_str[])
{
    if (NULL == str) return;
    if (NULL == c_str || strlen(c_str) == 0) {
        free(str->buffer);
        str->capacity = 0;
        str->size = 0;
        return;
    }

    if (NULL != str->buffer) free(str->buffer);
    str->size = strlen(c_str);
    str->capacity = strlen(c_str) + 1;
    str->buffer = (char *) malloc(sizeof(char) * str->capacity);

    if (NULL == str->buffer) {
        str->capacity = 0;
        str->size = 0;
        return;
    }

    memcpy(str->buffer, c_str, str->capacity * sizeof(char));
}

const char* mstr_get(mstring str)
{
    if (NULL == str || NULL == str->buffer) return NULL;
    return ((const char *)str->buffer);
}

void mstr_remove_last(mstring str)
{
    if (NULL == str || NULL == str->buffer) return;
    str->buffer[str->size - 1] = '\0';
    str->size--;
}

void mstr_append_char(mstring str, char ch)
{
    if (NULL == str) return;
    if (str->size + 2 >= str->capacity)
        reallocate(str, str->size + 2);
    
    if (NULL == str->buffer) return;
    str->buffer[str->size] = ch;
    str->buffer[str->size + 1] = '\0';
}

void mstr_append_string(mstring str, const char c_str[])
{
    if (NULL == str) return;

    // Get the length of the string to append
    size_t len_app = strlen(c_str);
    if (str->size + len_app + 1 >= str->capacity)
        reallocate(str, str->size + len_app + 1);

    if (NULL == str->buffer) return;

    // Update all sizes
    str->size += len_app;

    // Concatenate strings
    strcat(str->buffer, c_str);
    str->buffer[str->size + 1] = '\0';
}

size_t mstr_find_char(mstring str, char ch)
{
    if (NULL == str || NULL == str->buffer) return MSTRING_NPOS;
    char *found = strchr(str->buffer, ch);
    return (NULL == found ? MSTRING_NPOS : (found - str->buffer));
}

size_t mstr_find_mstr(mstring str, mstring to_find)
{
    if (NULL == str || NULL == str->buffer) return MSTRING_NPOS;
    return mstr_find_cstr(str, to_find->buffer);
}

size_t mstr_find_cstr(mstring str, const char c_str[])
{
    if (NULL == str || NULL == str->buffer) return MSTRING_NPOS;
    char *found = strstr(str->buffer, c_str);
    return (NULL == found ? MSTRING_NPOS : (found - str->buffer));
}

char mstr_at(mstring str, size_t idx)
{
    if (NULL == str || NULL == str->buffer || idx >= str->size)
        return '\0';
    return str->buffer[idx];
}

const char *mstr_at_cfront(mstring str)
{
    return (NULL == str || NULL == str->buffer ? 
            NULL : (const char *) str->buffer);
}

const char *mstr_at_clast(mstring str)
{
    return (NULL == str || NULL == str->buffer ?
            NULL : (const char *) &str->buffer[str->size - 1]);
}

char *mstr_at_front(mstring str)
{
    return (NULL == str || NULL == str->buffer ? 
            NULL : str->buffer);
}

char *mstr_at_last(mstring str)
{
    return (NULL == str || NULL == str->buffer ? 
            NULL : &str->buffer[str->size - 1]);
}

void mstr_clear(mstring str)
{
    if (NULL == str || NULL == str->buffer) return;
    memset(str->buffer, '\0', sizeof(char) * str->capacity);
}

static void error_handler()
{
    char *error = strerror(errno);
    fprintf(stderr, "error: %s\n", error);
}
