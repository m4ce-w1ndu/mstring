#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Maximum value of 16 bit size types
#define SIZE_MAX_16 0xFFFF
/// @brief Maximum value of 32 bit size types
#define SIZE_MAX_32 0xFFFFFFFF
/// @brief Maximum value of 64 bit size types
#define SIZE_MAX_64 0xFFFFFFFFFFFFFFFF

// Checks the size of the size_t type and sets
// the ARCH_BITS macro accordinlgy
#if (SIZE_MAX == SIZE_MAX_16)
    #define ARCH_BITS_16
#elif (SIZE_MAX == SIZE_MAX_32)
    #define ARCH_BITS_32
#elif (SIZE_MAX == SIZE_MAX_64)
    #define ARCH_BITS_64
#else
    #error Unsupported architecture
#endif

/// @brief Initial buffer capacity
#define INITIAL_CAPACITY 1

/// @brief Invalid string size constant
#define MSTRING_NPOS SIZE_MAX

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

/**
 * @brief Ordinally compares two mstring objects.
 * 
 * @param lhs left side.
 * @param rhs right side.
 * @return int that follows the same rules as strcmp().
 */
int mstr_compare(mstring lhs, mstring rhs);

/**
 * @brief Get the size (length) of the string.
 * 
 * @param str mstring object pointer.
 * @return size_t length of string.
 */
size_t mstr_get_size(mstring str);

/**
 * @brief Get the size (length) of the string.
 *
 * @param str mstring object pointer.
 * @return size_t length of string.
 */
size_t mstr_get_length(mstring str);

/**
 * @brief Get the capacity (memory size) of the string.
 * 
 * @param str mstring object pointer.
 * @return size_t capacity (in elements) of string.
 */
size_t mstr_get_capacity(mstring str);

/**
 * @brief Checks if the string object is empty.
 * 
 * @param str mstring object pointer.
 * @return int 0: non-empty, 1: empty.
 */
int mstr_is_empty(mstring str);

/**
 * @brief Reserves memory for the string, setting its
 * capacity to the given value.
 * 
 * @param str mstring object pointer.
 * @param sz new capacity to assign.
 */
void mstr_reserve(mstring str, size_t sz);

/**
 * @brief Resizes the string to the new given size.
 * If the value is smaller than the current string
 * length, memory is freed and characters out of
 * bounds are dropped. If the value is larger than
 * the current string length, the capacity is
 * increased accordingly and excess characters are
 * zero-initialized.
 * 
 * @param str mstring object pointer.
 * @param new_sz new size.
 */
void mstr_resize(mstring str, size_t new_sz);

/**
 * @brief Assigns a new value to the string object.
 * 
 * @param str mstring object pointer.
 * @param value value to assign.
 */
void mstr_assign(mstring str, const char value[]);

/**
 * @brief Returns an immutable pointer to the buffer.
 * 
 * @param str mstring object pointer.
 * @return const char* immutable pointer to internal 
 * buffer.
 */
const char *mstr_get(mstring str);

/**
 * @brief Removes the last character from string.
 * 
 * @param str mstring object pointer.
 */
void mstr_remove_last(mstring str);

/**
 * @brief Appends a character to an existing string.
 * 
 * @param str mstring object pointer.
 * @param ch character to append.
 */
void mstr_append_char(mstring str, char ch);

/**
 * @brief Appends a string to the current object.
 * 
 * @param str mstring object pointer.
 * @param c_str string value to append.
 */
void mstr_append_string(mstring str, const char c_str[]);

/**
 * @brief Finds a character in string.
 * 
 * @param str mstring object pointer.
 * @param ch character to find.
 * @return size_t index of character if found, 
 * max value of size_t if not found.
 */
size_t mstr_find_char(mstring str, char ch);

/**
 * @brief Finds a string in the current object.
 * 
 * @param str mstring object pointer of haystack.
 * @param to_find mstring object pointer of needle.
 * @return size_t start offset of needle, max value
 * of size_t if not found.
 */
size_t mstr_find_mstr(mstring str, mstring to_find);

/**
 * @brief Finds a string in the current object.
 * 
 * @param str mstring object pointer of haystack.
 * @param c_str cstring value or pointer of needle.
 * @return size_t start offset of needle, max value
 * of size_t if not found.
 */
size_t mstr_find_cstr(mstring str, const char c_str[]);

/**
 * @brief Returns the character at the specified index.
 * 
 * @param str mstring object pointer.
 * @param idx character index.
 * @return char character at specified index.
 */
char mstr_at(mstring str, size_t idx);

/**
 * @brief Returns an immutable pointer to the start 
 * of the string.
 * 
 * @param str mstring object pointer.
 * @return const char* start of the string.
 */
const char *mstr_at_cbegin(mstring str);

/**
 * @brief Returns an immutable pointer to the end
 * of the string.
 * 
 * @param str mstring object pointer.
 * @return const char* end of the string.
 */
const char *mstr_at_cend(mstring str);

/**
 * @brief Returns an immutable pointer to the
 * end of the string (reverse iterator).
 * 
 * @param str mstring object pointer.
 * @return const char* end of the string.
 */
const char *mstr_at_crbegin(mstring str);

/**
 * @brief Returns an immutable pointer to the
 * start of the string (reverse iterator).
 *
 * @param str mstring object pointer.
 * @return const char* start of the string.
 */
const char *mstr_at_crend(mstring str);

/**
 * @brief Returns a mutable pointer to the start 
 * of the string.
 * 
 * @param str mstring object pointer.
 * @return const char* start of the string.
 */
char *mstr_at_begin(mstring str);

/**
 * @brief Returns a mutable pointer to the end
 * of the string.
 * 
 * @param str mstring object pointer.
 * @return const char* end of the string.
 */
char *mstr_at_end(mstring str);

/**
 * @brief Returns an immutable pointer to the
 * end of the string (reverse iterator).
 *
 * @param str mstring object pointer.
 * @return const char* end of the string.
 */
char *mstr_at_rbegin(mstring str);

/**
 * @brief Returns an immutable pointer to the
 * start of the string (reverse iterator).
 *
 * @param str mstring object pointer.
 * @return const char* start of the string.
 */
char *mstr_at_rend(mstring str);

/**
 * @brief Returns the last character.
 * 
 * @param str mstring object pointer.
 * @return last character or -1 if string is empty
 */
char mstr_at_back(mstring str);

/**
 * @brief Returns the first character.
 *
 * @param str mstring object pointer.
 * @return first character or -1 if string is empty
 */
char mstr_at_front(mstring str);

/**
 * @brief Clears the value of the string buffer.
 * 
 * @param str mstring object pointer.
 */
void mstr_clear(mstring str);

/**
 * @brief Swaps the content of two strings.
 * 
 * @param lhs left side object pointer.
 * @param rhs right side object pointer.
 */
void mstr_swap(mstring lhs, mstring rhs);

#ifdef __cplusplus
}
#endif