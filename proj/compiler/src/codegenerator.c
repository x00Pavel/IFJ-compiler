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

void define_variable(struct token_s *token)//typ id // attriubute a// int 10
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
            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s int@%d\n",token->attribute.string,token_old->attribute.string, token->attribute.int_val);
            break;

        case TOKEN_FLOAT:
        
            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s float@%f\n",token->attribute.string,token_old->attribute.string, token->attribute.float_val);
            break;

        case TOKEN_STRING:

            fprintf(stdout, "DEFVAR GF @%s\nMOVE GF@%s string@%s\n",token->attribute.string,token_old->attribute.string, token->attribute.string);
            break;

        default:

            break;
    }
}            


bool token_return (struct token_s *token)
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

bool token_function(struct token_s *token, int counter)//TOKEN_FUNC
{

    fprintf(stdout, "LABEL $%s\n PUSHFRAME", token->attribute.string);
    sprintf(stdout, "CREATEFRAME\nPUSHFRAME\n");
    sprintf(stdout,)
    for(int i = 0; i < counter;i++)
    {   
        

    }
     
}
    /*LABEL $$main # main body
    CREATEFRAME  # no main-body vars
    PUSHFRAME
    DEFVAR LF@y
    CREATEFRAME
    DEFVAR TF@%1
    MOVE TF@%1 int@10
    DEFVAR TF@%2
    MOVE TF@%2 string@Hi\032X!
    CALL $foo
    MOVE LF@y TF@%retval
    WRITE LF@y
    # end of main body*/