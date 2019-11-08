#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"
#include "./stack/c202.h"

#ifdef DEBUG
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
    // "TOKEN_COMENT"
    "TOKEN_FNC"
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

#endif

int
main(int arc, char **argv)
{

    (void)arc;
    /* Input file */
    FILE *file;
    file = fopen("test.txt", "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }

    struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));

    tStack *stack = (tStack*) malloc(sizeof(tStack));

    stackInit(stack);
    stackPush(stack, 0);
    
    int ret_code = 0;
    while (ret_code != -1){
        ret_code = get_token(file, &token, stack);

        if (ret_code != OK){
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING){
                free(token->attribute.string);
            }
            break;
        }
#ifdef DEBUG
        if((token->type ==  TOKEN_KEY_WORD) || (token->type ==  TOKEN_FNC)){
            printf("%s -- %s\n", types[token->type], (token->type == TOKEN_FNC) ? token->attribute.string : kw[token->attribute.key_word]);
            if (token->type == TOKEN_FNC){
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
        if ((token->type == TOKEN_FNC) || (token->type == TOKEN_STRING) || (token->type == TOKEN_ID)){
            free(token->attribute.string);
        }
#endif
        
    }


    free(stack);
    free(token);
    fclose(file);

    return 0;
}

