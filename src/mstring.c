#include "include/mstring.h"

#include <string.h>
#include <stdlib.h>

/// @brief Contains the actual mstring private
/// implementation.
struct mstring_t {

};

mstring mstr_construct()
{

}

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
