/**
 * \file  ./parser.h
 * \brief Header of syntax and semantics analyzes for \file ./parser.c
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

/**
 * \brief
 * 
 * \param[in] file
 * \param[in] token
 * \param[in] stack
 * 
 * \return
*/
int func_for_id(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
int func_for_FNC(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, bool flag_def);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
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
 * 
 * \return
*/
int check_next_token(FILE *file, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def);

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table);
int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets, table_s *hash_table);
int func_mb_ret(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table);

#endif