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
int func_for_id(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params);

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
int func_for_FNC(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, bool flag_def, int *count_of_params);

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
int func_for_atributes(FILE *file, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def);

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
int check_next_token(FILE *file, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def);

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
int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table, struct dynamic_string *str);

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
int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets, table_s *hash_table, int *count_of_params);

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
int func_mb_ret(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params);


#endif 