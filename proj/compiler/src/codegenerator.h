#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include <stdio.h>
#include "parser.h"

void define_variable(struct token_s *token);
void id_is_equal_to(struct token_s *token_old, struct token_s *token);

#endif 