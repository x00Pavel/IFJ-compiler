/**
 * \file  ./parser.h
 * \brief Implimetation of syntax and semantics analyzes
 * 
 * \author Korniienko Oleksii (xkorni02@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/
#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include "scaner.h"
#include "symtable.h"
#include "dynamic_string.h"
#include "errors.h"
#include "codegenerator.h"
#include "stack.h"
#include "preced_analyze.h"
// #include "ifj2019_old.h"

int flag_while;
// static void my_func(){
//     (void)flag_while;
//     // if(flag_while){
//     //     my_func();
//     // }

// }
/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] count_of_params Number of paramaters in function
 * 
 * \return
*/
int func_for_id(struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] flag_def Flag for def/use of function
 * \param[in] count_of_params Number of paramaters in function
 * 
 * \return
*/
int func_for_FNC(struct token_s *token, tStack *stack, table_s *hash_table, bool flag_def, int *count_of_params, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] flag_def Flag for def/use of function
 * \param[in] count_of_params Number of paramaters in function
 * 
 * \return
*/
int func_for_atributes(struct token_s *token_for_time, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] flag_def Flag for def/use of function
 * \param[in] count_of_params Number of paramaters in function
 * 
 * \return
*/
int check_next_token(struct token_s *token_for_time, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] state Token
 * \param[in] ret_code Returned code
 * \param[in] str String for code
 * 
 * \return
*/
int func_prog(struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] count_of_params Number of paramaters in function
 * \param[in] count_of_brackets Number of brackets; "(" must be the same as ")"
 * 
 * \return
*/
int func_cond_mb(struct token_s *token, tStack *stack, int count_of_brackets, table_s *hash_table, int *count_of_params, struct dynamic_string *str_1);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * \param[in] hash_table Table of symbols
 * \param[in] count_of_params Number of paramaters in function
 * 
 * \return
*/
int func_mb_ret(struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params, struct dynamic_string *str_1);


#endif 