/**
 * \file src/scanner.h
 * \author Pavel Yadlouski (xyadlo00@stud.fit.vutbr.cz)
 * \brief Implementation of scanner
 * \date 2019
*/
#ifndef _SCANNER_H
#define _SCANNER_H


/**
 * Enumeration of avaliable key words
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



typedef enum {
    // Numbers
    TOKEN_INT = 0,       // integer int
    TOKEN_FLOAT = 1,     // float 
    TOKEN_STRING = 2,    // string 

    // Operators
    TOKEN_SUM = 3,       // +
    TOKEN_ASSIGN = 4,    // =
    TOKEN_MULTIPLY = 5,  // *
    TOKEN_DIVISION = 6,  // /

    // Relation operators
    TOKEN_EQUAL = 7,     // ==
    TOKEN_NOT_EQUAL = 8, // !=
    TOKEN_GREATER = 9,   // >
    TOKEN_LESS = 10,      // <
    TOKEN_GREATER_EQ = 11,// >= 
    TOKEN_LESS_EQ = 12,   // <=

    // Special tokens
    TOKEN_EOL = 13,      // end of line \n
    TOKEN_EOF = 14,      // end of file 
    TOKEN_KEY_WORD = 15, // key_word_t
    TOKEN_EMPTY = 16,     // "white" symbols

    // Punctuations
    TOKEN_L_BRACKET = 17, // (
    TOKEN_R_BRACKET = 18, // )
    TOKEN_DOT = 19,       // .
    TOKEN_COMA = 20,      // ,
    TOKEN_SEMICOLON = 21, // ;  
    TOKEN_ID   = 22,
    TOKEN_HEX = 23
} token_t;

typedef union {
    int int_val;
    double float_val;
    char  *string;
    key_word_t key_word;
} attribute_t;

struct token{
    token_t type;
    attribute_t attribute; 
};

typedef struct token* token_ptr;

int scanner (FILE *file ,token_ptr token);

#endif //_SCANNER_H