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

void define_variable(struct token_s *token)//typ id // attriubute a// int 1
{
    //printf("SRABOTAL DEFVAR %s \n", token->attribute.string);
    fprintf(stdout, "DEFVAR GF@%s\n", token->attribute.string);
}


void id_is_equal_to(struct token_s *token_old ,struct token_s *token)//a 10
{
    //printf("SRABOTAL EQUAL \n");
    switch (token->type)
    {
        
        case TOKEN_INT:
            //printf("SRABOTAL INT \n"); // type: int , attribute.int_val: 10
            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s int@%d\n",token_old->attribute.string,token_old->attribute.string, token->attribute.int_val);
            break;

        case TOKEN_FLOAT:
        
            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s float@%f\n",token_old->attribute.string,token_old->attribute.string, token->attribute.float_val);
            break;

        case TOKEN_STRING:

            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s string@%s\n",token_old->attribute.string,token_old->attribute.string, token->attribute.string);
            break;
        case TOKEN_NONE:
            
            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s nil@nil\n", token_old->attribute.string,token_old->attribute.string);

        default:

            break;
    }
}            


void token_return (struct token_s *token)
{
    switch (token->type)
    {
        case TOKEN_NONE :
            fprintf(stdout, "RETURN\n");
            break;
        case TOKEN_INT:
            fprintf(stdout, "RETURN GF@%d\n", token->attribute.int_val);
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "RETURN GF@%f\n", token->attribute.float_val);
            break;
        case TOKEN_STRING:
            fprintf(stdout, "RETURN GF@%s\n", token->attribute.string);
            break;
        
        default:
            break;
    }
}

void token_function_begin_with_y(struct token_s *token){

    fprintf(stdout, "LABEL $$main\n");
    fprintf(stdout, "CREATEFRAME\nPUSHFRAME\n");
    fprintf(stdout, "DEFVAR LF@%s\n CREATEFRAME\n",token->attribute.string);     
}
void token_function_begin(struct token_s *token){

    fprintf(stdout, "LABEL $$main\n PUSHFRAME\n");
    fprintf(stdout, "CREATEFRAME\nPUSHFRAME\n");
    //fprintf(stdout, "DEFVAR LF@%s\n CREATEFRAME\n",token->attribute.string);     
}
void token_functin_body(struct token_s *token, int *counter)
{
    switch (token->type)
    {
        case TOKEN_INT:
                fprintf(stdout, "DEFVAR TF@%d\n", *counter);
                fprintf(stdout, "MOVE TF@%%d int@%d\n",*counter, token->attribute.int_val); 
            break;
        case TOKEN_FLOAT:
                fprintf(stdout, "DEFVAR TF@%d\n", *counter);
                fprintf(stdout, "MOVE TF@%%d float@%f\n",*counter, token->attribute.float_val); 
            break;
        case TOKEN_STRING:
                fprintf(stdout, "DEFVAR TF@%d\n", *counter);
                fprintf(stdout, "MOVE TF@%%d string@%d\n",*counter, token->attribute.string);
        case TOKEN_ID:
                fprintf(stdout, "DEFVAR TF@%d\n", *counter);
                fprintf(stdout, "MOVE TF@%%d string@%d\n",*counter, token->attribute.string);
            break;
        default:
            break;
    }
}
void token_function_end(struct token_s *token)
{
    fprintf(stdout, "CALL $%s\n",token->attribute.string);
}
void asigment_of_function_with_y(struct token_s *token)
{
    fprintf(stdout, "MOVE LF@%s TF@%retval",token->attribute.string);
    fprintf(stdout, "WRITE LF@%s\n",token->attribute.string);
}

