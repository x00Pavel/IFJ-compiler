/**
 * \file  ./ifj2019.c
 * \brief Main function of compiler
 * 
 * \author Korniienko Oleksii (xkorni02@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/

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

int main(int arc, char **argv)
{

    (void)arc;
    (void)argv;
    (void)flag_while;

    struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));

    tStack *stack = (tStack *)malloc(sizeof(tStack));
    if (!stack)
        return ERR_INTERNAL;

    stackInit(stack);
    stackPush(stack, 0);

    table_s *hash_table = (table_s *)malloc(sizeof(table_s));
    if (!hash_table)
        return ERR_INTERNAL;
    htInit(hash_table);

    int state = 999;
    int ret_code = 0;

    struct dynamic_string *str;
    str_init(&str);

    create_functions();
    prec_an_def_var();

    ret_code = func_prog(token, stack, state, ret_code, hash_table, str);

    str_clean(str);
    htClearAll(hash_table, true);
    free(hash_table);
    free(stack);
    if (token->type == TOKEN_STRING || token->type == TOKEN_ID || token->type == TOKEN_FNC)
    {
        free(token->attribute.string);
    }
    free(token);

    return ret_code;
}