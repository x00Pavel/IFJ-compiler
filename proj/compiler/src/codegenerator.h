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
 * This function creates the end of the main function, pops frame and clears the stack
 * \return
*/
void end_main();
/**
 * \brief
 * This function creates a code for the begging of the defenitions of the functions
 * \param[in] token Input token
 * \param[in] str String for code
 * \return
*/
void define_function_begin(struct token_s *token, struct dynamic_string *str);
/**
 * \brief
 * This function craetes a local frame return value
 * \param[in] str String for code
 * \return
*/
void retval_function(struct dynamic_string *str);
/**
 * \brief
 * This function creates parameters for function definition
 * \param[in] token Input token
 * \param[in] counter Int for arguments count 
 * \param[in] s char for frame choosing
 * \param[in] str String for code
 * \return
*/
void def_function_call(struct token_s *token, int *counter, char *s,struct dynamic_string *str);
/**
 * \brief
 * This function creates ending for function definition
 * \param[in] token Input token
 * \param[in] str String for code
 * \return
*/
void def_function_end(struct token_s *token,struct dynamic_string *str);
/**
 * \brief
 * This function creates the variables defenitions in all frames
 * \param[in] token Input token
 * \param[in] s char for frame choosing
 * \param[in] str String for code
 * \return
*/
void define_variable_GF(struct token_s *token, char *s, struct dynamic_string *str);
/**
 * \brief
 * This function assignes variables to identificators in all frames
 * \param[in] token Input token
 * \param[in] token_a Input token
 * \param[in] s char for frame choosing
 * \param[in] str String for code
 * \return
*/
void assign_to_variable(struct token_s *token,struct token_s *token_a, char *s, struct dynamic_string *str);
/**
 * \brief
 * This function creates the frame for function call
 * \param[in] str String for code
 * \return
*/
void token_function_begin_with_y(struct dynamic_string *str);
/**
 * \brief
 * This function passes arguemnts and values of the arguments to a function (when the functions is called)
 * \param[in] token Input token
 * \param[in] counter Int for arguments count 
 * \param[in] s char for frame choosing
 * \param[in] str String for code
 * \return
*/
void function_call(struct token_s *token,int *counter, char *s,struct dynamic_string *str);
/**
 * \brief
 * This function generates function call
 * \param[in] token Input token
 * \param[in] str String for code
 * \return
*/
void call_function(struct token_s *token,struct dynamic_string *str);
/**
 * \brief
 * This function generates global frame return value assignment to an identificator
 * \param[in] token Input token
 * \param[in] s char for frame choosing
 * \param[in] str String for code
 * \return
*/
void retval_assign_function(struct token_s *token, char *s,struct dynamic_string *str);
/**
 * \brief
 * This function prints float value
 * \param[in] token_write Input token
 * \param[in] str String for code
 * \return
*/
void print_float(struct token_s *token_write,struct dynamic_string *str);
/**
 * \brief
 * This function prints int value
 * \param[in] token_write Input token
 * \param[in] str String for code
 * \return
*/
void print_int(struct token_s *token_write,struct dynamic_string *str);
/**
 * \brief
 * This function prints string
 * \param[in] token_write Input token
 * \param[in] str String for code
 * \return
*/
void print_string(struct token_s *token_write,struct dynamic_string *str);
/**
 * \brief
 * This function prints "None"
 * \param[in] token_write Input token
 * \param[in] str String for code
 * \return
*/
void print_none(struct dynamic_string *str);
/**
 * \brief
 * This function prints identificator
 * \param[in] token_write Input token
 * \param[in] str String for code
 * \return
*/
void print_id(struct token_s *token_write,char *s, struct dynamic_string *str);
/**
 * \brief
 * This function prints space
 * \param[in] str String for code
 * \return
*/
void print_space(struct dynamic_string *str);
/**
 * \brief
 * This function prints new line
 * \param[in] str String for code
 * \return
*/
void print_end(struct dynamic_string *str);
/**
 * \brief
 * This function prints if condition's beggining
 * \param[in] str String for code
 * \return
*/
void generate_if_head(struct dynamic_string *str);
/**
 * \brief
 * This function generates if conditon's body
 * \param[in] str String for code
 * \return
*/
void if_body(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates else conditon's body in case if it is found
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions 
 * \param[in] str String for code
 * \return
*/
void found_else(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates end of if's condition
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void end_of_if(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates end of else's condition
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void end_of_else(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates the beggining of while cycle
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void generate_while_head_1(int *t, struct dynamic_string *str);
/**
 * \brief
 * This function generates the body of while cycle
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void while_body(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates the end of while cycle
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void generate_while_end(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates the beggining of the while cycle for the case of constant arguments of while(unchanged)
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void while_for_true(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function generates the end of while cycle for constant arguments
 * \param[in] t Int for couting the amout of while's and if's condition in while's and if's coindions
 * \param[in] str String for code
 * \return
*/
void generate_while_for_true_end(int *t,struct dynamic_string *str);
/**
 * \brief
 * This function works with 2 upper elements in stack
 * Perfomrs operatons such as SUM, MULTIPLY, MINUS, DIVISION, IDIV,EQUAL,NOT_EQUAL GREATER, LESS, LESS_EQ, TOKEN_GREATER_EQ
 * \param[in] token_type Input token
 * \param[in] str String for code
 * \return
*/
void prec_an_operator(token_t type, struct dynamic_string *str);
/**
 * \brief
 * This function generates PUSH in the stack
 * \param[in] token_type Input token
 * \param[in] str String for code
 * \return
*/
void prec_an_operand(char *s, struct token_s *token, struct dynamic_string *str);
/**
 * \brief
 * This function generates helping variables for operations with stacks
 * \param[in] token_type Input token
 * \param[in] str String for code
 * \return
*/
void prec_an_def_var();
/**
 * \brief
 * This function generates helping variables for operations with stacks
 * \param[in] str String for code
 * \return
*/
void pop_retval(struct dynamic_string *str);
/**
 * \brief
 * This function generates the call of inputs function
 * \param[in] str String for code
 * \return
*/
void inputs_call(struct dynamic_string *str);
/**
 * \brief
 * This function generates the call of inputi function
 * \param[in] str String for code
 * \return
*/
void inputi_call(struct dynamic_string *str);
/**
 * \brief
 * This function generates the call of inputf function
 * \param[in] str String for code
 * \return
*/
void inputf_call(struct dynamic_string *str);
/**
 * \brief
 * This function generates the call of all inserted function except inputi(f,s) 
 * \param[in] str String for code
 * \return
*/
void call_inserted_functions(char *d,struct dynamic_string *str);
#endif 
