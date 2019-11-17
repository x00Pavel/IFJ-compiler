#include <stdbool.h>

#ifndef _DYNAMIC_STRING_H
    #define _DYNAMIC_STRING_H

#define DEF_STR_SIZE 8

/**
 * Structure representing dynamic string 
*/
typedef struct{
    char *str;   /*< String                  */
    size_t len;  /*< Length of string        */
    size_t size; /*< Size of string in bytes */
} *dynamic_string_ptr;

typedef char *string;

/**
 * \brief Function for reallocating string 
 * 
 * \param[in] str Pointer to structure of dynamic string
 * 
 * \return 0 on success
 * \return #ERR_INTERNAL in case of memory allocation error  
*/
int realloc_string(dynamic_string_ptr str);

/**
 * \brief Function for adding one character to string 
 * 
 * \param[in] dst Destination string
 * \param[in] src Source string
 * 
 * \return true if everthings is OK, else false
*/
bool add_char_to_str(dynamic_string_ptr dst, char *src);

/**
 * \brief Function for deleting string
 * 
 * \param str String to be cleaned 
*/
void str_clean(dynamic_string_ptr str);

/**
 * \brief Function for initialization of dynamic string
 * 
 * \param[in] str Structure of dynamic string
*/
void string_init(dynamic_string_ptr str);

/**
 * \brief Inline function for compating string DST with SRC
 * 
 * \param[in] dst 
 * \param[in] src
 *  
 * \return True if strings are the same, else false
*/
inline str_cp(string dst, string src);

#endif // _DYNAMIC_STRING_H