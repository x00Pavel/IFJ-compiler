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
#include "./stack.h"


void create_functions(){
    fprintf(stdout,"FUNCLEN\n");
	fprintf(stdout,"PUSHFRAME\n");
	fprintf(stdout,"\n LABEL $length\n");
	fprintf(stdout,"DEFVAR LF@%%retval\n");
	fprintf(stdout,"STRLEN LF@%%retval LF@%%0\n");
	fprintf(stdout,"POPFRAME\n");
	fprintf(stdout,"RETURN\n\n\n");
	fprintf(stdout,"#SUBSTRFUNCTION\n");
	fprintf(stdout,"LABEL $substr\n");
	fprintf(stdout,"PUSHFRAME\n");
	fprintf(stdout,"DEFVAR LF@%%retval\n");
	fprintf(stdout,"MOVE LF@%%retval string@\n");
	fprintf(stdout,"DEFVAR LF@length_str\n");
	fprintf(stdout,"CREATEFRAME\n");
	fprintf(stdout,"DEFVAR TF@%%0\n");
	fprintf(stdout,"MOVE TF@%%0 LF@%%0\n");
	fprintf(stdout,"CALL $length\n");
	fprintf(stdout,"MOVE LF@length_str TF@%%retval\n");
	fprintf(stdout,"DEFVAR LF@ret_cond\n");
	fprintf(stdout,"LT LF@ret_cond LF@length_str int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@length_str int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"LT LF@ret_cond LF@%%1 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@%%1 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"GT LF@ret_cond LF@%%1 LF@length_str\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@%%2 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"DEFVAR LF@max_n\n");
	fprintf(stdout,"MOVE LF@max_n LF@length_str\n");
	fprintf(stdout,"SUB LF@max_n LF@max_n LF@%%1\n");
	fprintf(stdout,"ADD LF@max_n LF@max_n int@1\n");
	fprintf(stdout,"DEFVAR LF@edit_n_cond\n");
	fprintf(stdout,"LT LF@edit_n_cond LF@%%2 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n");
	fprintf(stdout,"GT LF@edit_n_cond LF@%%2 LF@max_n\n");
	fprintf(stdout,"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n");
	fprintf(stdout,"JUMP $substr$process\n");
	fprintf(stdout,"LABEL $substr$edit_n\n");
	fprintf(stdout,"MOVE LF@%%2 LF@max_n\n");
	fprintf(stdout,"LABEL $substr$process\n");
	fprintf(stdout,"DEFVAR LF@index\n");
	fprintf(stdout,"MOVE LF@index LF@%%1\n");
	fprintf(stdout,"SUB LF@index LF@index int@1\n");
	fprintf(stdout,"DEFVAR LF@char\n");
	fprintf(stdout,"DEFVAR LF@process_loop_cond\n");
	fprintf(stdout,"LABEL $substr$process_loop\n");
	fprintf(stdout,"GETCHAR LF@char LF@%%0 LF@index\n");									
	fprintf(stdout,"CONCAT LF@%%retval LF@%%retval LF@char\n");							
	fprintf(stdout,"ADD LF@index LF@index int@1\n");										
	fprintf(stdout,"SUB LF@%%2 LF@%%2 int@1\n");											
	fprintf(stdout,"GT LF@process_loop_cond LF@%%2 int@0\n");							
	fprintf(stdout,"JUMPIFEQ $substr$process_loop LF@process_loop_cond bool@true\n");	
	fprintf(stdout,"LABEL $substr$return\n");										
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n\n");
	fprintf(stdout,"#ASCFUNCTION\n");													
	fprintf(stdout,"LABEL $asc\n");															
	fprintf(stdout,"PUSHFRAME\n");															
	fprintf(stdout,"DEFVAR LF@%%retval\n");													
	fprintf(stdout,"MOVE LF@%%retval int@0\n");												
	fprintf(stdout,"DEFVAR LF@cond_length\n");									
	fprintf(stdout,"LT LF@cond_length LF@%%1 int@1\n");						
	fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
	fprintf(stdout,"DEFVAR LF@length_str\n");												
	fprintf(stdout,"CREATEFRAME\n");														    
	fprintf(stdout,"DEFVAR TF@%%0\n");														
	fprintf(stdout,"MOVE TF@%%0 LF@%%0\n");													
	fprintf(stdout,"CALL $length\n");														
	fprintf(stdout,"MOVE LF@length_str TF@%%retval\n");										
	fprintf(stdout,"GT LF@cond_length LF@%%1 LF@length_str\n");						
	fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
	fprintf(stdout,"SUB LF@%%1 LF@%%1 int@1\n");									
	fprintf(stdout,"STRI2INT LF@%%retval LF@%%0 LF@%%1\n");
	fprintf(stdout,"LABEL $asc$return\n");
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n\n");
	fprintf(stdout,"#CHRFUNCTION\n");														
	fprintf(stdout,"LABEL $chr\n");															
	fprintf(stdout,"PUSHFRAME\n");															
	fprintf(stdout,"DEFVAR LF@%%retval\n");													
	fprintf(stdout,"MOVE LF@%%retval string@\n");											
	fprintf(stdout,"DEFVAR LF@cond_range\n");									
	fprintf(stdout,"LT LF@cond_range LF@%%0 int@0\n");					
	fprintf(stdout,"JUMPIFEQ $chr$return LF@cond_range bool@true\n");
	fprintf(stdout,"GT LF@cond_range LF@%%0 int@255\n");						
	fprintf(stdout,"JUMPIFEQ $chr$return LF@cond_range bool@true\n");
	fprintf(stdout,"INT2CHAR LF@%%retval LF@%%0\n");											
	fprintf(stdout,"LABEL $chr$return\n");													
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n");
}

//generate main function
void generate_main()
{
    fprintf(stdout, "LABEL $%%main\n"); 
    fprintf(stdout,".IFJcode19\n    ");
    fprintf(stdout,"JUMP $$main\n");
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
            fprintf(stdout, "MOVE %s@%%%s int@%d\n",s,token->attribute.string, token_a->attribute.int_val); 
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "MOVE %s@%%%s float@%f\n",s,token->attribute.string, token_a->attribute.float_val); 
            break;
        case TOKEN_STRING:
        case TOKEN_ID:
            fprintf(stdout, "MOVE %s@%%%s string@%s\n",s,token->attribute.string, token_a->attribute.string);
            break;
        default:
            break;  
    }  
}

void token_return(struct token_s *token, char *s)
{
    (void)s;
    //MOVE LF@%retval float@0x0p+0
    fprintf(stdout,"MOVE LF@%%retval\n");
    //fprintf("%s", returnvalue);
    switch (token->type)
    {
        case TOKEN_INT:
            fprintf(stdout, "int@%d\n", token->attribute.int_val);
            break;
        case TOKEN_FLOAT:
            fprintf(stdout, "float@%f\n", token->attribute.float_val);
            break;
        case TOKEN_STRING:
            fprintf(stdout, "string@%s\n", token->attribute.string);
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
    fprintf(stdout, "MOVE %s@%s1 %s@%%%d\n", s, token->attribute.string, s, *counter); 
}

void def_function_end()
{
    fprintf(stdout, "POPFRAME\n");
    fprintf(stdout, "RETURN\n");
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




void generate_while_head_1()
{
    fprintf(stdout, "#WHILE CYCLE\n");
    fprintf(stdout,"LABEL while\n");
}

void generate_while_head(struct token_s *token, char *s){
    //while 32
    //while ( a == b)
    //while ( a != b)   
    //while (i <= 100)
    //while(len("huy") < 5)
    fprintf(stdout,"DEFVAR %s@res\n",s);//res helps us to check if podminka je splnena
    fprintf(stdout,"DEFVAR %s@returnvalueforwhile\n",s);//
    switch (token->type)
    {
    case TOKEN_FLOAT :
        fprintf(stdout,"MOVE %s@returnvalue float@%f\n",s, token->attribute.float_val);
        break;
    case TOKEN_INT :
        fprintf(stdout,"MOVE %s@returnvalue int@%d\n",s, token->attribute.int_val);
        break;
    case TOKEN_STRING:
        printf("MOVE %s@returnvalue string@%s\n",s, token->attribute.string);
        break;
    case TOKEN_ID:
        printf("MOVE %s@returnvalue %s@%s\n",s, s,token->attribute.string);
        break;
    
    default:
        break;
    }

}
void generate_while_end(){
    fprintf(stdout,"JUMP WHILE\n");
}




void generate_if_head(){
    fprintf(stdout,"#Endif\n");
}
void generate_if_start(struct token_s *token, char *s){ 
    //if a == a
    //if a != b
    //if a >= b
    //if a <= b
    //if a < b
    //if a > b
    fprintf(stdout,"DEFVAR %s@res\n",s);//res helps us to check if podminka je splnena
    fprintf(stdout,"DEFVAR %s@returnvalue\n",s);
    fprintf(stdout,"DEFVAR %s@returnvalue1\n",s);
    switch (token->type)
    {
    case TOKEN_FLOAT :
        fprintf(stdout,"MOVE %s@returnvalue float@%f\n",s, token->attribute.float_val);
        break;
    case TOKEN_INT :
        fprintf(stdout,"MOVE %s@returnvalue int@%d\n",s, token->attribute.int_val);
        break;
    case TOKEN_STRING:
        printf("MOVE %s@returnvalue string@%s\n",s, token->attribute.string);
        break;
    case TOKEN_ID:
        printf("MOVE %s@returnvalue %s@%s\n",s, s,token->attribute.string);
        break;
    
    default:
        break;
    }
}
void select_operator(struct token_s *token){
    switch (token->type)
    {
    case TOKEN_EQUAL:
        fprintf(stdout,"EQ ");
        break;
     case TOKEN_NOT_EQUAL:
        fprintf(stdout,"NOT EQ ");
        break;
    case TOKEN_GREATER:
        fprintf(stdout,"GT ");
        break;
    case TOKEN_GREATER_EQ:
        fprintf(stdout,"EQ AND GT ");
        break;
    case TOKEN_LESS:
       fprintf(stdout,"LT" );
        break;
    case TOKEN_LESS_EQ:
       fprintf(stdout,"LT AND EQ ");
        break;
    
    default:
        break;
    }
    
}
void returnvalue1 (struct token_s *token, char *s){
    switch (token->type)
    {
    case TOKEN_FLOAT :
        fprintf(stdout,"MOVE %s@returnvalue1 float@%f\n",s, token->attribute.float_val);
        break;
    case TOKEN_INT :
        fprintf(stdout,"MOVE %s@returnvalue1 int@%d\n",s, token->attribute.int_val);
        break;
    case TOKEN_STRING:
        printf("MOVE %s@returnvalue1 string@%s\n",s, token->attribute.string);
        break;
    case TOKEN_ID:
        printf("MOVE %s@returnvalue1 %s@%s\n",s, s,token->attribute.string);
        break;
    
    default:
        break;
    }
}
void if_body(struct token_s *token, char *s){
    switch (token->type)
    {
    case TOKEN_FLOAT:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_INT:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_ID:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_STRING:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
    
    default:
        break;
    }
    fprintf(stdout, "JUMPIFNEQ $EXIT %s@res boot@true",s);//if(a < b)
                                                            //  print b
                                                            //else
}                                                          //  print a
void if_else_body(struct token_s *token, char *s){

    switch (token->type)
    {
    case TOKEN_FLOAT:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_INT:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_ID:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
        break;
    case TOKEN_STRING:
        fprintf(stdout,"%s@res %s@returnvalue %s@returnvalue1",s,s,s);
    
    default:
        break;
    }
    fprintf(stdout, "JUMPIFNEQ $ELSE %s@res boot@true", s );
}
void if_end(){
    fprintf(stdout,"LABEL $EXIT\n");
}