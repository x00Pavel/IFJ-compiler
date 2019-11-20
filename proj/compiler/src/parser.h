#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include "scaner.h"

/**
 * \brief
 * 
 * \param[in] file
 * \param[in] token
 * \param[in] stack
 * 
 * \return
*/
int func_for_id(FILE *file, struct token_s *token, tStack *stack);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
int func_for_FNC(FILE *file, struct token_s *token, tStack *stack);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
int func_for_atributes(FILE *file, struct token_s *token, tStack *stack, int *count_of_params);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
int check_next_token(FILE *file, struct token_s *token, tStack *stack, int *count_of_params);

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code);
int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets);
int func_mb_ret(FILE *file, struct token_s *token, tStack *stack);


#endif 