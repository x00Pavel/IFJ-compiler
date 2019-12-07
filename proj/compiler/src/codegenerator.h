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
#include "dynamic_string.h"

// int flag_while = 0;

// #ifndef _PARSER_H

/**
 * \brief
 * This funtions generates code of inserted functions 
 * \return
*/
void create_functions();

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
void label_main();
void end_main();
void define_function_begin(struct token_s *token, struct dynamic_string *str);
void retval_function(struct dynamic_string *str);
void def_function_call(struct token_s *token, int *counter, char *s,struct dynamic_string *str);
void def_function_end(struct dynamic_string *str);
void define_variable_GF(struct token_s *token, char *s, struct dynamic_string *str);
void assign_to_variable(struct token_s *token,struct token_s *token_a, char *s, struct dynamic_string *str);
void assign_to_y(struct token_s *token, char *s,struct dynamic_string *str);
void token_function_begin_with_y(struct dynamic_string *str);
void function_call(struct token_s *token,int *counter, char *s,struct dynamic_string *str);
void call_function(struct token_s *token,struct dynamic_string *str);
void call_inserted_functions(char *d,struct dynamic_string *str);
void retval_assign_function(struct token_s *token, char *s,struct dynamic_string *str);
void print_float(struct token_s *token_write,struct dynamic_string *str);
void print_int(struct token_s *token_write,struct dynamic_string *str);
void print_string(struct token_s *token_write,struct dynamic_string *str);
void print_none(struct dynamic_string *str);
void print_id(struct token_s *token_write,char *s, struct dynamic_string *str);
void print_space(struct dynamic_string *str);
void print_end(struct dynamic_string *str);
void generate_if_head(struct dynamic_string *str);
//void create_returnvalue(struct dynamic_string *str);
void select_operator(struct token_s *token,struct dynamic_string *str);
void if_body(int *t,struct dynamic_string *str);
void found_else(int *t,struct dynamic_string *str);
void end_of_if(int *t,struct dynamic_string *str);
void end_of_else(int *t,struct dynamic_string *str);
void stack_operations(int *t,struct dynamic_string *str);
void generate_while_head_1(int *t, struct dynamic_string *str);
void while_body(int *t,struct dynamic_string *str);
void generate_while_end(int *t,struct dynamic_string *str);
void while_for_true(int *t,struct dynamic_string *str);
void generate_while_for_true_end(int *t,struct dynamic_string *str);
void func_sum(struct token_s *token_one, char *s,struct dynamic_string *str);
void func_mul(struct token_s *token_one, char *s, struct dynamic_string *str);
void func_sub(struct token_s *token_one, char *s,struct dynamic_string *str);
void func_div(struct token_s *token_one, char *s,struct dynamic_string *str);
void func_int_div(struct token_s *token_one,struct dynamic_string *str);
void prec_an_operator(token_t type, struct dynamic_string *str);
void prec_an_operand(char *s, struct token_s *token, struct dynamic_string *str);
void prec_an_def_var();
void pop_retval();
#endif 
