#include "./dynamic_string/dynamic_string.h"
#include "errors.h"
#include "scaner.h"


bool define_variable(struct token_s *token)//typ id // attriubute a// int 10
{
    fprintf(stdout, "DEFVAR GF@%s", token->attribute.string);
}


bool id_is_equal_to(struct token_s *token)//a 10
{
    fprintf(stdout, "MOVE GF@%s %s@%s",)
}