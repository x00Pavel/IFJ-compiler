#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"
#include "parser.h"
#include "stack.h"
#include "symtable.h"
#include "codegenerator.h"
#include "dynamic_string.h"

// #ifdef DEBUG
// char *types[] = {

//     "TOKEN_INT",    // integer int
//     "TOKEN_FLOAT ", // float
//     "TOKEN_STRING", // string

//     // Operators
//     "TOKEN_SUM ",     // +
//     "TOKEN_MINUS",    // -
//     "TOKEN_ASSIGN",   // =
//     "TOKEN_MULTIPLY", // *
//     "TOKEN_DIVISION", // /

//     // Relation operators
//     "TOKEN_EQUAL",      // ==
//     "TOKEN_NOT_EQUAL",  // !=
//     "TOKEN_GREATER",    // >
//     "TOKEN_LESS",       // <
//     "TOKEN_GREATER_EQ", // >=
//     "TOKEN_LESS_EQ",    // <=

//     // Special tokens
//     "TOKEN_EOL",      // end of line \n
//     "TOKEN_EOF",      // end of file
//     "TOKEN_KEY_WORD", // key_word_t
//     "TOKEN_EMPTY",    // "white" symbols

//     // Punctuations
//     "TOKEN_L_BRACKET", // (
//     "TOKEN_R_BRACKET", // )
//     "TOKEN_DOT",       // .
//     "TOKEN_COMA",      // ,
//     "TOKEN_SEMICOLON", // ;
//     "TOKEN_DDOT",      // :
//     "TOKEN_ID",
//     "TOKEN_HEX",
//     "TOKEN_INDEND", // indend
//     "TOKEN_DEDEND", // dedend
//     // "TOKEN_COMENT"
//     "TOKEN_FNC",
//     "TOKEN_NONE",
//     "TOKEN_DIV_INT"
// };

// char *kw[] = {
//     "_DEF_",
//     "_ELSE_",
//     "_IF_",
//     "_NONE_",
//     "_PASS_",
//     "_RETURN_",
//     "_WHILE_"
// };

// #endif

int main(int arc, char **argv){

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

    tStack *stack = (tStack*) malloc(sizeof(tStack));
    if(!stack)
        return ERR_INTERNAL;

    stackInit(stack);
    stackPush(stack, 0);
    
    table_s *hash_table = (table_s *) malloc(sizeof(table_s));
    if(!hash_table)
        return ERR_INTERNAL;
    htInit(hash_table);

    int state = 999;
    int ret_code = 0;

    struct dynamic_string *str;
    str_init(&str);
    // generate_main();
    // generate_inserted_functions();
    create_functions(); // generate all inside functions

    // printf("IM HERE\n");
    ret_code = func_prog(token, stack, state, ret_code, hash_table, str);
    
    str_clean(str);
    htClearAll(hash_table, true);
    free(hash_table);
    free(stack);
    if(token->type == TOKEN_STRING || token->type == TOKEN_ID || token->type == TOKEN_FNC){
        free(token->attribute.string);
    }
    free(token);
    // fclose(file);

return ret_code;
}