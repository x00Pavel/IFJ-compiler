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


#define FUNCTION_LENGTH														\
	"\n LABEL $length\n"													\
	"PUSHFRAME\n"															\
	"DEFVAR LF@%%retval\n"													\
	"STRLEN LF@%%retval LF@%%0\n"											\
	"POPFRAME\n"															\
	"RETURN\n"


#define FUNCTION_SUBSTR														\
	"LABEL $substr\n"														\
	"PUSHFRAME\n"															\
	"DEFVAR LF@%%retval\n"													\
	"MOVE LF@%%retval string@\n"											\
	"DEFVAR LF@length_str\n"												\
	"CREATEFRAME\n"													     	\
	"DEFVAR TF@%%0\n"														\
	"MOVE TF@%%0 LF@%%0\n"													\
	"CALL $length\n"														\
	"MOVE LF@length_str TF@%%retval\n"										\
	"DEFVAR LF@ret_cond\n"													\
	"LT LF@ret_cond LF@length_str int@0\n"									\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"EQ LF@ret_cond LF@length_str int@0\n"									\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"LT LF@ret_cond LF@%%1 int@0\n"											\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"EQ LF@ret_cond LF@%%1 int@0\n"											\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"GT LF@ret_cond LF@%%1 LF@length_str\n"									\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"EQ LF@ret_cond LF@%%2 int@0\n"											\
	"JUMPIFEQ $substr$return LF@ret_cond bool@true\n"						\
	"DEFVAR LF@max_n\n"													\
	"MOVE LF@max_n LF@length_str\n"										\
	"SUB LF@max_n LF@max_n LF@%%1\n"										\
	"ADD LF@max_n LF@max_n int@1\n"										\
	"DEFVAR LF@edit_n_cond\n"												\
	"LT LF@edit_n_cond LF@%%2 int@0\n"										\
	"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n"					\
	"GT LF@edit_n_cond LF@%%2 LF@max_n\n"									\
	"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n"					\
	"JUMP $substr$process\n"												\
	"LABEL $substr$edit_n\n"												\
	"MOVE LF@%%2 LF@max_n\n"												\
	"LABEL $substr$process\n"												\
	"DEFVAR LF@index\n"													\
	"MOVE LF@index LF@%%1\n"												\
	"SUB LF@index LF@index int@1\n"										\
	"DEFVAR LF@char\n"														\
	"DEFVAR LF@process_loop_cond\n"										\
	"LABEL $substr$process_loop\n"											\
	"GETCHAR LF@char LF@%0 LF@index\n"										\
	"CONCAT LF@%%retval LF@%%retval LF@char\n"								\
	"ADD LF@index LF@index int@1\n"										\
	"SUB LF@%%2 LF@%%2 int@1\n"												\
	"GT LF@process_loop_cond LF@%%2 int@0\n"								\
	"JUMPIFEQ $substr$process_loop LF@process_loop_cond bool@true\n"		\
	"LABEL $substr$return\n"												\
	"POPFRAME\n"															\
	"RETURN\n"


#define FUNCTION_ASC														\
	"LABEL $asc\n"															\
	"PUSHFRAME\n"															\
	"DEFVAR LF@%%retval\n"													\
	"MOVE LF@%%retval int@0\n"												\
	"DEFVAR LF@cond_length\n"												\
	"LT LF@cond_length LF@%%1 int@1\n"										\
	"JUMPIFEQ $asc$return LF@cond_length bool@true\n"						\
	"DEFVAR LF@length_str\n"												\
	"CREATEFRAME\n"														    \
	"DEFVAR TF@%%0\n"														\
	"MOVE TF@%0 LF@%%0\n"													\
	"CALL $length\n"														\
	"MOVE LF@length_str TF@%%retval\n"										\
	"GT LF@cond_length LF@%%1 LF@length_str\n"								\
	"JUMPIFEQ $asc$return LF@cond_length bool@true\n"						\
	"SUB LF@%%1 LF@%%1 int@1\n"												\
	"STRI2INT LF@%%retval LF@%0 LF@%%1\n"									\
	"LABEL $asc$return\n"													\
	"POPFRAME\n"															\
	"RETURN\n"


#define FUNCTION_CHR														\
	"LABEL $chr\n"															\
	"PUSHFRAME\n"															\
	"DEFVAR LF@%%retval\n"													\
	"MOVE LF@%%retval string@\n"											\
	"DEFVAR LF@cond_range\n"												\
	"LT LF@cond_range LF@%0 int@0\n"										\
	"JUMPIFEQ $chr$return LF@cond_range bool@true\n"						\
	"GT LF@cond_range LF@%0 int@255\n"										\
	"JUMPIFEQ $chr$return LF@cond_range bool@true\n"						\
	"INT2CHAR LF@%%retval LF@%%0\n"											\
	"LABEL $chr$return\n"													\
	"POPFRAME\n"															\
	"RETURN\n"

//generate main function
void generate_main()
{
    fprintf(stdout, "LABEL $%main\n"); 
}

//Define variables in all scopes
void define_variable_GF(struct token_s *token, char *s){
    fprintf(stdout, "DEFVAR %s@%s\n",s,token->attribute.string);   
}
//Assign value to variablei in all scopes
void assign_to_variable(struct token_s *token,struct token_s *token_a, char *s)
{//MOVE TF@%1 int@10
      switch (token->type)
    {  
        case TOKEN_INT:
            fprintf(stdout, "MOVE %s@%%s int@%d\n",s,token->attrubite.string, token_a->attribute.int_val); 
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "MOVE %s@%%s float@%f\n",s,token->attrubite.string, token_a->attribute.float_val); 
            break;
        case TOKEN_STRING:
        case TOKEN_ID:
            fprintf(stdout, "MOVE %s@%%s string@%s\n",s,token->attrubite.string, token_a->attribute.string);
            break;
        default:
            break;  
    }  
}

void token_return(struct token_s *token, char *s)
{
    //MOVE LF@%retval float@0x0p+0
    fprintf("MOVE LF@%%retval ");
    //fprintf("%s", returnvalue);
    switch (token->type)
    {
        case TOKEN_INT:
            fprintf(stdout, "int@%d\n",s, token->attribute.int_val);
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "float@%f\n",s, token->attribute.float_val);
            break;
        case TOKEN_STRING:
            fprintf(stdout, "string@%s\n",s, token->attribute.string);
            break;
        case TOKEN_ID:

        default:
            break;
    }
}
//foo , y





/*
*   CALL FUNCTION
*/

void token_function_begin_with_y(){

   
    fprintf(stdout, "CREATEFRAME\n");
    //fprintf(stdout, "DEFVAR LF@%s\n CREATEFRAME\n",token->attribute.string);     
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
        case TOKEN_ID:
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

void def_function_call(struct token_s *token, int *counter, char *s)//def char *s = TF
{   //DEFVAR LF@param1
    //MOVE LF@param1  LF@%1     
    
    fprintf(stdout, "DEFVAR %s@%s%d\n",s,token->attribute.string, *counter);
    fprintf(stdout, "MOVE %s@%s%d %s@%%d\n",s,token->attribute.string , *counter); 
}

void def_function_end()
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




void generate_while_head()
{
    fprintf(stdout, "#WHILE CYCLE\n");
    fprintf("LABEL while\n");
}

void generate_while_head(struct token_s *token, char *s){
    //while true
    //while ( a == b)
    //while ( a != b)   
    //while (i <= 100)
    switch (token->type)
    {
        case TOKEN_GREATER_EQ:

            break;
        case TOKEN_GREATER:

            break;
        case//TOKEN true ci false
            TOKEN_INT:
            TOKEN_FLOAT:
            fprintf("")
            break;
        case TOKEN_EQUAL:
            fprintf("JUMPIFEQ %s\n", token->attribute.string);
            fprintf("LABEL to")//a == b
        case TOKEN_NOT_EQUAL:
            fprintf("JUMPIFNEQ %s\n", token->attribute.string);

    
    default:
        break;
    }

}

void generate_while_end(struct token_s *token){

    fprintf("JUMP WHILE\n");
    fprintf("LABEL %s\n", token->attribute.string);
}




void generate_if_head()
{
    fprintf("#Endif\n");
}

void generate_if_start(){

}