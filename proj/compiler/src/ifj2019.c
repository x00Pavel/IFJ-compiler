#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "stack.h"
#include "symtable.h"
#include "preced_analyze.h"
#ifndef _SCANNER_H
    #include "scanner.h"
#endif

char *types[] = {

    "TOKEN_INT",    // integer int
    "TOKEN_FLOAT ", // float
    "TOKEN_STRING", // string

    // Operators
    "TOKEN_SUM ",     // +
    "TOKEN_MINUS",    // -
    "TOKEN_ASSIGN",   // =
    "TOKEN_MULTIPLY", // *
    "TOKEN_DIVISION", // /

    // Relation operators
    "TOKEN_EQUAL",      // ==
    "TOKEN_NOT_EQUAL",  // !=
    "TOKEN_GREATER",    // >
    "TOKEN_LESS",       // <
    "TOKEN_GREATER_EQ", // >=
    "TOKEN_LESS_EQ",    // <=

    // Special tokens
    "TOKEN_EOL",      // end of line \n
    "TOKEN_EOF",      // end of file
    "TOKEN_KEY_WORD", // key_word_t
    "TOKEN_EMPTY",    // "white" symbols

    // Punctuations
    "TOKEN_L_BRACKET", // (
    "TOKEN_R_BRACKET", // )
    "TOKEN_DOT",       // .
    "TOKEN_COMA",      // ,
    "TOKEN_SEMICOLON", // ;
    "TOKEN_DDOT",      // :
    "TOKEN_ID",
    "TOKEN_HEX",
    "TOKEN_INDEND", // indend
    "TOKEN_DEDEND", // dedend
    "TOKEN_FNC",
    "TOKEN_NONE",
    "TOKEN_DIV_INT",
    "TOKEN_PRINT",
    "TOKEN_INPUT_S",
    "TOKEN_INPUT_I",
    "TOKEN_INPUT_F",
    "TOKEN_ORD",
    "TOKEN_SUBSTR",
    "TOKEN_LEN",
    "TOKEN_CHR"
    };

char *kw[] = {
    "_DEF_",
    "_ELSE_",
    "_IF_",
    "_NONE_",
    "_PASS_",
    "_RETURN_",
    "_WHILE_"};

int
main(int arc, char **argv)
{

    (void)arc;
    (void)argv;
    /* Input file */
    // FILE *file;
    // file = fopen(argv[1], "r");
    
    // if (!file){
    //     fprintf(stderr, "Error in opening file %s\n", argv[0]);
    //     return ERR_OTHER;
    // }

    struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));
    
    // Initialization stack for INDEND/DEDEND
    tStack *stack = (tStack*) malloc(sizeof(tStack));
    if(!stack){
        return ERR_INTERNAL;
    }
    stackInit(stack);
    stackPush(stack, 0);
    
    // Initialization of hash table for global frame
    table_s *ht = (table_s *)malloc(sizeof(table_s));
    if(!ht){
        return ERR_INTERNAL;
    }
    htInit(ht);
    int cnt = 0;
    int ret_code = get_token(token, stack);
    htInsert(ht, "a", TOKEN_ID);
    (void)ret_code;
    preced_analyze(token, ht, cnt, NULL);

    /*int ret_code = 0;
    while (ret_code != -1){
        ret_code = get_token(token, stack);
        
        if(token->type == TOKEN_FNC || token->type == TOKEN_ID){
            htInsert(ht, token->attribute.string, token->type);
        }

        if (ret_code != OK){
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING || (token->type ==  TOKEN_FNC)){
                free(token->attribute.string);
            }
            break;
            // return ret_code;
        }
        if(token->type == TOKEN_EOF){
            printf("%s\n", types[token->type]);
            break;
        }

        switch (token->type)
        {
        case TOKEN_ID:
        case TOKEN_STRING:
            printf("--------- attribute: %s\n", token->attribute.string);
            free(token->attribute.string);
            break;
        case TOKEN_FNC:
            printf("%s -- %s\n", types[token->type], token->attribute.string);
            free(token->attribute.string);
            break;
        case TOKEN_KEY_WORD:
            printf("%s -- %s\n", types[token->type],kw[token->attribute.key_word]);
            break;
        default:
            printf("%s\n", types[token->type]);
            break;
        }
        
    }
    htPrintTable(ht);*/
    htClearAll(ht);
    free(ht);
    free(stack);
    free(token);
    
    return 0;
}

