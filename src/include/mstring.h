
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
