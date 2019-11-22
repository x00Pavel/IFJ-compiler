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
int func_for_atributes(FILE *file, struct token_s *token, tStack *stack);

/**
 * \brief
 * 
 * \param[in] file  Source file
 * \param[in] token Input token
 * \param[in] stack Stack with count of whitespcase
 * 
 * \return
*/
int check_next_token(FILE *file, struct token_s *token, tStack *stack);

#endif 