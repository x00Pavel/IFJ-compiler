/**
 * \file src/scanner/scanner.h
 * \author Pavel Yadlouski (xyadlo00@stud.fit.vutbr.cz)
 * \brief Implementation of scanner
 * \date 2019
*/
#ifndef _SCANNER_H
#define _SCANNER_H

#include "./stack/c202.h"

/**
 * \brief Enumeration of avaliable key words
*/
typedef enum {
    _DEF_ = 0, 
    _ELSE_, 
    _IF_,  
    _NONE_, 
    _PASS_,
    _RETURN_,
    _WHILE_
} key_word_t;

/**
 * \brief Enumeration with types of tokens
*/
typedef enum{
    // Numbers
    TOKEN_INT = 0,    // integer int
    TOKEN_FLOAT = 1,  // float
    TOKEN_STRING = 2, // string

    // Operators
    TOKEN_SUM = 3,      // +
    TOKEN_MINUS = 4,    // -
    TOKEN_ASSIGN = 5,   // =
    TOKEN_MULTIPLY = 6, // *
    TOKEN_DIVISION = 7, // /

    // Relation operators
    TOKEN_EQUAL = 8,       // ==
    TOKEN_NOT_EQUAL = 9,   // !=
    TOKEN_GREATER = 10,    // >
    TOKEN_LESS = 11,       // <
    TOKEN_GREATER_EQ = 12, // >=
    TOKEN_LESS_EQ = 13,    // <=

    // Special tokens
    TOKEN_EOL = 14,      // end of line \n
    TOKEN_EOF = 15,      // end of file
    TOKEN_KEY_WORD = 16, // key_word_t
    TOKEN_EMPTY = 17,    // "white" symbols

    // Punctuations
    TOKEN_L_BRACKET = 18, // (
    TOKEN_R_BRACKET = 19, // )
    TOKEN_DOT = 20,       // .
    TOKEN_COMA = 21,      // ,
    TOKEN_SEMICOLON = 22, // ;
    TOKEN_DDOT = 23,      // :
    TOKEN_ID = 24,
    TOKEN_HEX = 25,
    TOKEN_INDEND = 26, // indend
    TOKEN_DEDEND = 27, // dedend
    // TOKEN_COMENT
    TOKEN_FNC = 28
} token_t;
/**
 * \brief Union with atrributes
*/
typedef union {
    int int_val;        /*< For integer value*/
    double float_val;   /*< For */
    char  *string;
    key_word_t key_word;
} attribute_t;

struct token_s{
    token_t type;
    attribute_t attribute; 
};

typedef struct token* token_ptr;

int get_token(FILE *file, struct token_s **token, tStack *stack);

#endif //_SCANNER_H