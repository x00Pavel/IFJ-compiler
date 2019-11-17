#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include <stdio.h>
#include "parser.h"

void define_variable(struct token_s *token);
void id_is_equal_to(struct token_s *token_old, struct token_s *token);
void token_return (struct token_s *token);
void token_function_begin_with_y(struct token_s *token_new ,struct token_s *token);
void token_function_begin();
void token_function_body(struct token_s *token, int *counter);
void token_function_end(struct token_s *token);
void asigment_of_function_with_y(struct token_s *token);


#endif 