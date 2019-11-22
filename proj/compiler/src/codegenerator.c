/**
 * \file  ./codegenerator.c
 * \brief Implimentation of target code generator \file ./codegenerator.c
 * 
 * \author 	Aghayev Raul (xaghay00@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/

//#include "./dynamic_string/dynamic_string.h"

#include "errors.h"
#include "scaner.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "codegenerator.h"
#include "./stack/c202.h"

void define_variable_GF(struct token_s *token, char *s)//typ id // attriubute a// int 1
{
    //printf("SRABOTAL DEFVAR %s \n", token->attribute.string);
    fprintf(stdout, "DEFVAR %s@%s\n",s,token->attribute.string);
    
}

void token_return (struct token_s *token, char *s)
{
    switch (token->type)
    {
        case TOKEN_NONE :
            fprintf(stdout, "RETURN\n");
            break;
        case TOKEN_INT:
            fprintf(stdout, "RETURN %s@%d\n",s, token->attribute.int_val);
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "RETURN %s@%f\n",s, token->attribute.float_val);
            break;
        case TOKEN_STRING:
            fprintf(stdout, "RETURN %s@%s\n",s, token->attribute.string);
            break;

        default:
            break;
    }
}
//foo , y



/*
*   CALL FUNCTION
*/

void token_function_begin_with_y(struct token_s *token_new, struct token_s *token){

    fprintf(stdout, "LABEL $%s\n",token_new->attribute.string);
    fprintf(stdout, "CREATEFRAME\nPUSHFRAME\n");
    fprintf(stdout, "DEFVAR LF@%s\n CREATEFRAME\n",token->attribute.string);     
}
void token_function_begin_without_y(struct token_s *token_new){

    fprintf(stdout, "LABEL $%s\n",token_new->attribute.string);
    fprintf(stdout, "CREATEFRAME\nPUSHFRAME\n");   
}
void function_call(struct token_s *token,int *counter, char *s)
{
     switch (token->type)
    {   //DEFVAR TF@%1
        //MOVE TF@%1 int@10
        case TOKEN_INT:
                fprintf(stdout, "DEFVAR %s@%d\n",s, *counter);
                fprintf(stdout, "MOVE %s@%d int@%d\n",s,*counter, token->attribute.int_val); 
            break;
        case TOKEN_FLOAT:
                fprintf(stdout, "DEFVAR %s@%d\n",s, *counter);
                fprintf(stdout, "MOVE %s@%d float@%f\n",s,*counter, token->attribute.float_val); 
            break;
        case TOKEN_STRING:
                fprintf(stdout, "DEFVAR %s@%d\n",s, *counter);
                fprintf(stdout, "MOVE %s@%d string@%s\n",s,*counter, token->attribute.string);
            break;
        default:
            break;  
    } 
}
void call_function(struct token_s *token)
{   
    printf("CALL $%s", token->attribute.string);
}

void retval_function()
{
    fprintf(stdout, "DEFVAR LF@retval\n");
    fprintf(stdout, "MOVE LF@%%retval nil@nil\n");
}
void retval_assign_function(struct token_s *token)
{
    fprintf(stdout, "MOVE LF@%s TF@%%retval",token->attribute.string);
}
/*
 * END FUNCTION
 */


/*
 *
 * DEFINE FUNCTION
 *
 */
void define_function_begin(struct token_s *token)//1
{
    fprintf(stdout,"# Start of function\n");
    fprintf(stdout,"LABEL $%s\n", token->attribute.string);
    fprintf(stdout,"PUSHFRAME\n");    
}

void def_function_call(struct token_s *token, int *counter, char *s)
{   //DEFVAR LF@param1
    //MOVE LF@param1  LF@%1
    fprintf(stdout, "DEFVAR %s@param%d\n",s, *counter);
    fprintf(stdout, "MOVE %s@param%d %s@%%d\n",s,*counter,s, *counter); 
}

void def_function_end(struct token_s *token)
{
    fprintf(stdout, "POPFRAME\n");
    fprontf(stdout, "RETURN\n");
}
/*
 *
 * END DEFINE 
 * 
*/

void print_function(struct token_s *token_write, char *s)
{
    fprintf(stdout,"WRITE %s@%s",s,token_write->attribute.string);
}
