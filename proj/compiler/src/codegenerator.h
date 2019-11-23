/**
 * \file  ./codegenerator.h
 * \brief Header file for target code generator \file ./codegenerator.c
 * 
 * \author 	Aghayev Raul (xaghay00@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/

#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include <stdio.h>
#include "parser.h"

void define_variable(struct token_s *token);
void id_is_equal_to(struct token_s *token_old, struct token_s *token);
void print_function(struct token_s *token_write, char *s);
void def_function_end();
void def_function_call(struct token_s *token, int *counter, char *s);
void define_function_begin(struct token_s *token);
void retval_assign_function(struct token_s *token);
void retval_function();
void call_function(struct token_s *token);
void function_call(struct token_s *token,int *counter, char *s);
void token_function_begin_without_y(struct token_s *token_new);
void token_function_begin_with_y();
void assign_to_variable(struct token_s *token,struct token_s *token_a, char *s);
void token_return (struct token_s *token, char *s);
void define_variable_GF(struct token_s *token, char *s);
void generate_if_start();
void generate_if_head();
void generate_while_head(struct token_s *token, char *s);
void generate_while_head_1();
void generate_main();
void if_end();
void if_else_body(struct token_s *token, char *s);
void if_body(struct token_s *token, char *s);   
void returnvalue1 (struct token_s *token, char *s);
void select_operator(struct token_s *token);
void generate_if_start(struct token_s *token, char *s);
void change_int_and_float(struct token_s *token, struct token_s *token_a);
void stack_operation(struct token_s *token);
void dedend_of_if(int *is_else);
void found_else();
void returnvalue1(struct token_s *token_right_side, char *s);
void returnvalue(struct token_s *token_left_side, char *s);
void generate_while_end(struct token_s *token);
#endif 
