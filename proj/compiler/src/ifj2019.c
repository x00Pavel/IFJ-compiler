#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"
#include "./stack/c202.h"
#include "./hash_table/c016.h"

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
    "TOKEN_DIV_INT"
};

char *kw[] = {
    "_DEF_",
    "_ELSE_",
    "_IF_",
    "_NONE_",
    "_PASS_",
    "_RETURN_",
    "_WHILE_"
};


int
main(int arc, char **argv)
{

    (void)arc;
    /* Input file */
    FILE *file;
    file = fopen(argv[1], "r");
    
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }

    struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));
    
    // Initialization stack for INDEND/DEDEND
    tStack *stack = (tStack*) malloc(sizeof(tStack));
    if(!stack){
        return ERR_INTERNAL;
    }
    stackInit(stack);
    stackPush(stack, 0);
    
    // Initialization of hash table for global frame
    tHTable *hash_table =  (tHTable *) malloc(sizeof(tHTable));
    if(!hash_table){
        return ERR_INTERNAL;
    }
    htInit(hash_table);
    int ret_code = 0;

    ret_code = get_token(file, token, stack);
    htInsert(hash_table, types[token->type], *token);


    while (ret_code != -1){
        ret_code = get_token(file, token, stack);
        
        if (ret_code != OK){
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING || (token->type ==  TOKEN_FNC)){
                free(token->attribute.string);
            }
            return ret_code;
        }

        if(token->type == TOKEN_EOF){
#ifdef DEBUG
            printf("%s\n", types[token->type]);
#endif
            break;
        }

#ifdef DEBUG
        if((token->type ==  TOKEN_KEY_WORD) || (token->type ==  TOKEN_FNC)){
            printf("%s -- %s\n", types[token->type], (token->type == TOKEN_FNC) ? token->attribute.string : kw[token->attribute.key_word]);
            if (token->type == TOKEN_FNC && token->attribute.string){
                free(token->attribute.string);
            }
        }
        else{
            printf("%s\n", types[token->type]);
        }

        
        if(token->type == TOKEN_ID || token->type == TOKEN_STRING){
            printf("--------- attribute: %s\n", token->attribute.string);
            free(token->attribute.string);
        }
#else
        if ((token->type == TOKEN_FNC) || (token->type == TOKEN_STRING) || (token->type == TOKEN_ID) 
            && (token->attribute.string != NULL)){
            free(token->attribute.string);
        }
#endif
        
    }
    free(hash_table);
    free(stack);
    free(token);
    fclose(file);

    return 0;
}

