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

char *key_word_arr[] = {"def", "else", "if", "none", "pass", "return", "while"};

typedef enum {
    // Numbers
    TOKEN_INT,       // integer int
    TOKEN_FLOAT,     // float 
    TOKEN_STRING,    // string 

    // Operators
    TOKEN_SUM,       // +
    TOKEN_ASSIGN,    // =
    TOKEN_MULTIPLY,  // *
    TOKEN_DIVISION,  // /

    // Relation operators
    TOKEN_EQUAL,     // ==
    TOKEN_NOT_EQUAL, // !=
    TOKEN_GREATER,   // >
    TOKEN_LESS,      // <
    TOKEN_GREATER_EQ,// >= 
    TOKEN_LESS_EQ,   // <=

    // Special tokens
    TOKEN_EOL,      // end of line \n
    TOKEN_EOF,      // end of file 
    TOKEN_KEY_WORD, // key_word_t
    TOKEN_EMPTY,     // "white" symbols

    // Punctuations
    TOKEN_L_BRACKET, // (
    TOKEN_R_BRACKET, // )
    TOKEN_DOT,       // .
    TOKEN_COMA,      // ,
    TOKEN_SEMICOLON, // ;  
} token_t;

typedef union {
    int int_val;
    float float_val;
    char  *string;
    key_word_t key_word;
} attribute_t;

struct token{
    token_t type;
    attribute_t attribute; 
};

typedef struct token* token_ptr;

void scanner (FILE *file ,token_ptr token);

#endif //_SCANNER_H