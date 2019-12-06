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

// #include "dynamic_string.h"
#include "parser.h"
// #include "codegenerator.h"
// #include "stack.h"
// #include "ifj2019_old.h"

static int skip_counter = 0;

void create_functions(){
    fprintf(stdout,"FUNCLEN\n");
	fprintf(stdout,"PUSHFRAME\n");
	fprintf(stdout,"LABEL $len\n");
	fprintf(stdout,"DEFVAR LF@%%retval\n");
	fprintf(stdout,"STRLEN LF@%%retval LF@%%1\n");
	fprintf(stdout,"POPFRAME\n");
	fprintf(stdout,"RETURN\n\n");

    fprintf(stdout, "#INPUTS\n");
	fprintf(stdout, "PUSHFRAME\n");
	fprintf(stdout, "LABEL inputs\n");
    fprintf(stdout, "DEFVAR LF@%%HELPER\n");
	fprintf(stdout, "DEFVAR LF@%%retval\n"); 
	fprintf(stdout, "DEFVAR LF@%%var\n");
	fprintf(stdout, "READ LF@%%var LF@%%1\n");
	fprintf(stdout, "DEFVAR LF@%%symb1\n");
	fprintf(stdout, "STRLEN LF@%%symb1 LF@%%1\n");
	fprintf(stdout, "DEFVAR LF@%%symb2\n");
	fprintf(stdout, "MOVE LF@%%symb2 string@''\n");
	fprintf(stdout, "SETCHAR LF@%%HELPER LF@%%symb1 LF@%%symb2\n");
	fprintf(stdout, "MOVE LF@%%retval LF@%%HELPER\n");


    fprintf(stdout, "#INPUTI\n");
    fprintf(stdout, "PUSHFRAME\n");
    fprintf(stdout, "LABEL inputi\n");
    fprintf(stdout, "DEFVAR LF@$$var\n");
    fprintf(stdout, "DEFVAR LF@%%retval\n");
    fprintf(stdout, "MOVE LF@$$var LF@%%1\n");
    fprintf(stdout, "FLOAT2INT LF@$$retval LF@$$var\n");


    
    fprintf(stdout, "#INPUTF\n");
    fprintf(stdout, "PUSHFRAME\n");
    fprintf(stdout, "LABEL inputf\n");
    fprintf(stdout, "DEFVAR LF@$$var\n");
    fprintf(stdout, "DEFVAR LF@%%retval\n");
    fprintf(stdout, "MOVE LF@$$var LF@%%1\n");
    fprintf(stdout, "INT2FLOAT LF@$$retval LF@$$var\n");

    
    fprintf(stdout,"#SUBSTRFUNCTION\n");
	fprintf(stdout,"LABEL $substr\n");
	fprintf(stdout,"PUSHFRAME\n");
	fprintf(stdout,"DEFVAR LF@%%retval\n");
	fprintf(stdout,"MOVE LF@%%retval string@\n");
	fprintf(stdout,"DEFVAR LF@length_str\n");
	fprintf(stdout,"CREATEFRAME\n");
	fprintf(stdout,"DEFVAR TF@%%1\n");
	fprintf(stdout,"MOVE TF@%%1 LF@%%1\n");
	fprintf(stdout,"CALL $length\n");
	fprintf(stdout,"MOVE LF@length_str TF@%%retval\n");
	fprintf(stdout,"DEFVAR LF@ret_cond\n");
	fprintf(stdout,"LT LF@ret_cond LF@length_str int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@length_str int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"LT LF@ret_cond LF@%%2 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@%%2 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"GT LF@ret_cond LF@%%2 LF@length_str\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"EQ LF@ret_cond LF@%%3 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$return LF@ret_cond bool@true\n");
	fprintf(stdout,"DEFVAR LF@max_n\n");
	fprintf(stdout,"MOVE LF@max_n LF@length_str\n");
	fprintf(stdout,"SUB LF@max_n LF@max_n LF@%%2\n");
	fprintf(stdout,"ADD LF@max_n LF@max_n int@1\n");
	fprintf(stdout,"DEFVAR LF@edit_n_cond\n");
	fprintf(stdout,"LT LF@edit_n_cond LF@%%3 int@0\n");
	fprintf(stdout,"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n");
	fprintf(stdout,"GT LF@edit_n_cond LF@%%3 LF@max_n\n");
	fprintf(stdout,"JUMPIFEQ $substr$edit_n LF@edit_n_cond bool@true\n");
	fprintf(stdout,"JUMP $substr$process\n");
	fprintf(stdout,"LABEL $substr$edit_n\n");
	fprintf(stdout,"MOVE LF@%%3 LF@max_n\n")                                                                                                                                                                                                                                                    ;
	fprintf(stdout,"LABEL $substr$process\n");
	fprintf(stdout,"DEFVAR LF@index\n");
	fprintf(stdout,"MOVE LF@index LF@%%2\n");
	fprintf(stdout,"SUB LF@index LF@index int@1\n");
	fprintf(stdout,"DEFVAR LF@char\n");
	fprintf(stdout,"DEFVAR LF@process_loop_cond\n");
	fprintf(stdout,"LABEL $substr$process_loop\n");
	fprintf(stdout,"GETCHAR LF@char LF@%%1 LF@index\n");									
	fprintf(stdout,"CONCAT LF@%%retval LF@%%retval LF@char\n");							
	fprintf(stdout,"ADD LF@index LF@index int@1\n");										
	fprintf(stdout,"SUB LF@%%3 LF@%%2 int@1\n");											
	fprintf(stdout,"GT LF@process_loop_cond LF@%%3 int@0\n");							
	fprintf(stdout,"JUMPIFEQ $substr$process_loop LF@process_loop_cond bool@true\n");	
	fprintf(stdout,"LABEL $substr$return\n");										
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n");

	fprintf(stdout,"#ASCFUNCTION\n");													
	fprintf(stdout,"LABEL $ord\n");															
	fprintf(stdout,"PUSHFRAME\n");															
	fprintf(stdout,"DEFVAR LF@%%retval\n");													
	fprintf(stdout,"MOVE LF@%%retval int@0\n");												
	fprintf(stdout,"DEFVAR LF@cond_length\n");									
	fprintf(stdout,"LT LF@cond_length LF@%%2 int@1\n");						
	fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
	fprintf(stdout,"DEFVAR LF@length_str\n");												
	fprintf(stdout,"CREATEFRAME\n");														    
	fprintf(stdout,"DEFVAR TF@%%1\n");														
	fprintf(stdout,"MOVE TF@%%1 LF@%%1\n");													
	fprintf(stdout,"CALL $len\n");														
	fprintf(stdout,"MOVE LF@length_str TF@%%retval\n");										
	fprintf(stdout,"GT LF@cond_length LF@%%2 LF@length_str\n");						
	fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
	fprintf(stdout,"SUB LF@%%2 LF@%%2 int@1\n");									
	fprintf(stdout,"STRI2INT LF@%%retval LF@%%1 LF@%%2\n");
	fprintf(stdout,"LABEL $asc$return\n");
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n");

	fprintf(stdout,"#CHRFUNCTION\n");														
	fprintf(stdout,"LABEL $chr\n");															
	fprintf(stdout,"PUSHFRAME\n");															
	fprintf(stdout,"DEFVAR LF@%%retval\n");													
	fprintf(stdout,"MOVE LF@%%retval string@\n");											
	fprintf(stdout,"DEFVAR LF@cond_range\n");									
	fprintf(stdout,"LT LF@cond_range LF@%%1 int@0\n");					
	fprintf(stdout,"JUMPIFEQ $chr$return LF@cond_range bool@true\n");
	fprintf(stdout,"GT LF@cond_range LF@%%1 int@255\n");						
	fprintf(stdout,"JUMPIFEQ $chr$return LF@cond_range bool@true\n");
	fprintf(stdout,"INT2CHAR LF@%%retval LF@%%1\n");											
	fprintf(stdout,"LABEL $chr$return\n");													
	fprintf(stdout,"POPFRAME\n");														
	fprintf(stdout,"RETURN\n\n");

    // printf("#ERRORS\n");
    // printf("LABEL $INCOMPATIBLE\n");
    // printf("EXIT 4\n");

    // printf("#CHECK_TYPE_AND_SUM\n");
    // printf("LABEL $CHECK_TYPE_AND_SUM\n");
    // printf("");
    // printf("JUMPIFEQ $CONCATE GF@type_var_1 string@string\n");
    // printf("JUMP $ADD");


    // printf("#FUNC_FOR_CONCATE\n");
}



void jump_to_main(){
    fprintf(stdout,".IFJcode19\n");
    fprintf(stdout,"JUMP $$main\n");
}
void label_main(){
    fprintf(stdout, "LABEL $%%main\n");
}
void end_main(){
    fprintf(stdout,"# End of main scope\n");
	fprintf(stdout,"POPFRAME\n");
	fprintf(stdout,"CLEARS\n");
}






/*
*
* START CODE DEFINE FUNCTION
*
*/
    void define_function_begin(struct token_s *token, struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout,"# Start of function\n");
            fprintf(stdout,"LABEL $%s\n", token->attribute.string);
            fprintf(stdout,"PUSHFRAME\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("# Start of function\nLABEL $"); i++)
            {
                add_char_to_str(str, "# Start of function\nLABEL $"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
            {
                add_char_to_str(str, token->attribute.string[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("PUSHFRAME\n"); i++)
            {
                add_char_to_str(str, "PUSHFRAME\n"[i]);
            }
            
        }
            
    }
    void retval_function(struct dynamic_string *str){
        if(flag_while == 0){
            fprintf(stdout, "DEFVAR LF@retval\n");
            fprintf(stdout, "MOVE LF@%%retval nil@nil\n");
        }
        else{   
            for(unsigned int i = 0; i < strlen("DEFVAR LF@retval\n"); i++){
                add_char_to_str(str, "DEFVAR LF@retval\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("MOVE LF@%%retval nil@nil\n"); i++){
                add_char_to_str(str, "MOVE LF@%%retval nil@nil\n"[i]);
            }
        }
    }
    void def_function_call(struct token_s *token, int *counter, char *s,struct dynamic_string *str){
        if(flag_while == 0){
            fprintf(stdout, "DEFVAR %s@%s%d\n",s,token->attribute.string, *counter);
            fprintf(stdout, "MOVE %s@%s%d %s@%%%d\n",s,token->attribute.string, *counter ,s ,*counter);
        }
        else{
            for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                add_char_to_str(str, "DEFVAR "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str,s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str,"@"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                add_char_to_str(str,token->attribute.string[i]);
            }
            char temp30[100];
            sprintf(temp30, "%d",*counter);
            for(unsigned int i = 0; i < strlen(temp30); i++){
                add_char_to_str(str, temp30[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("MOVE "); i++){
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str,s[i]);
            }       
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str,"@"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                add_char_to_str(str,token->attribute.string[i]);
            }
            char temp29[100];
            sprintf(temp29, "%d",*counter);
            for(unsigned int i = 0; i < strlen(temp29); i++){
                add_char_to_str(str, temp29[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str,s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++)
            {
                add_char_to_str(str,"@%"[i]);
            }   
            char temp28[100];
            sprintf(temp28, "%d",*counter);
            for(unsigned int i = 0; i < strlen(temp28); i++){
                add_char_to_str(str, temp28[i]);
            }
            add_char_to_str(str, 10);
        }
    
    }
    void def_function_end(struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "POPFRAME\n");
            fprintf(stdout, "RETURN\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPFRAME\nRETURN\n"); i++)
            {
                add_char_to_str(str, "POPFRAME\nRETURN\n"[i]);
            }
        }
           
        
    }
/*
 *
 * END CODE DEFINE FUNCTION
 * 
*/

/*
* Define variables in all scopes
*/
  void define_variable_GF(struct token_s *token, char *s, struct dynamic_string *str){
    if(flag_while == 0)
    {
        fprintf(stdout, "DEFVAR %s@%s\n",s,token->attribute.string); 
    }
    else
    {
        for(unsigned int i = 0; i < strlen("DEFVAR "); i++)
        {
            add_char_to_str(str, "DEFVAR "[i]);
        }
        for(unsigned int i = 0; i < strlen(s); i++)
        {
            add_char_to_str(str, s[i]);
        }
        for(unsigned int i = 0; i < strlen("@"); i++)
        {
            add_char_to_str(str, "@"[i]);
        }
        for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
        {
            add_char_to_str(str, token->attribute.string[i]);
        }
        add_char_to_str(str, 10);
    }
    
        
}
/*
*End define variables in all scopes
*/

//y = a + b + c эта функиция приржадит все что спарава к у
void assign_to_variable(struct token_s *token,struct token_s *token_a, char *s, struct dynamic_string *str){
      switch (token->type)
    {  
        case TOKEN_INT:
        if(flag_while == 0){
            fprintf(stdout, "MOVE %s@%%%s int@retval\n",s,token->attribute.string ); 
            break;
        } else {
            for(unsigned int i = 0; i < strlen("MOVE "); i++){
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++){
                add_char_to_str(str, "@%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++){
                add_char_to_str(str, token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen("int@retval"); i++){
                add_char_to_str(str, "int@retval"[i]);
            }
            add_char_to_str(str, 10);
            break;
            
        }
        case TOKEN_FLOAT:
        if(flag_while == 0)
        {
            fprintf(stdout, "MOVE %s@%%%s float@retval\n",s,token->attribute.string); 
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MOVE "); i++)
            {
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++)
            {
                add_char_to_str(str, "@%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str, token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen("float@retval"); i++)
            {
                add_char_to_str(str, "float@retval"[i]);
            }
            add_char_to_str(str, 10);
            break; 
        }
        case TOKEN_STRING:
        if(flag_while == 0)
        {
            fprintf(stdout, "MOVE %s@%%%s string@retval\n",s,token->attribute.string);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MOVE "); i++)
            {
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++)
            {
                add_char_to_str(str, "@%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str, token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen("string@retval"); i++)
            {
                add_char_to_str(str, "string@retval"[i]);
            }
            add_char_to_str(str, 10);
            break; 
        }
        case TOKEN_ID:
        if(flag_while == 0)
        {
            fprintf(stdout, "MOVE %s@%%%s %s@retval\n",s,token->attribute.string, token_a->attribute.string);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MOVE "); i++)
            {
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++)
            {
                add_char_to_str(str, "@%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str, token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen(token_a->attribute.string); i++)
            {
                add_char_to_str(str, token_a->attribute.string[i]);
            }
            for(unsigned int i = 0; i < strlen("@retval"); i++)
            {
                add_char_to_str(str, "@retval"[i]);
            }
            add_char_to_str(str, 10);
            break;    
        }
        case TOKEN_NONE:
        if(flag_while == 0)
        {
            fprintf(stdout, "MOVE %s@%%%s nil@nil\n",s,token->attribute.string);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MOVE "); i++)
            {
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%"); i++)
            {
                add_char_to_str(str, "@%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str,token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen("nil@nil"); i++)
            {
                add_char_to_str(str, "nil@nil"[i]);
            }
            add_char_to_str(str, 10);
            break;          
        }
        default:
            break;  
    }  
}


//Это функия y=foo(a,b) приржадит то что вышло в fоо к у
void assign_to_y(struct token_s *token, char *s,struct dynamic_string *str){
    if(flag_while == 0)
    {
        fprintf(stdout, " MOVE %s@%s %s@retval\n",s, token->attribute.string,s); 
    }
    else
    {
        for(unsigned int i = 0; i < strlen("MOVE "); i++){
            add_char_to_str(str, "MOVE "[i]);
        }
        for(unsigned int i = 0; i < strlen(s); i++){
            add_char_to_str(str,s[i]);
        }
        for(unsigned int i = 0; i < strlen("@"); i++){
            add_char_to_str(str,"@"[i]);
        }
        for(unsigned int i = 0; i < strlen(s); i++){
            add_char_to_str(str,s[i]);
        }
        for(unsigned int i = 0; i < strlen("@"); i++){
            add_char_to_str(str,"@"[i]);
        }
        for(unsigned int i = 0; i < strlen("retval"); i++){
            add_char_to_str(str,"retval"[i]);
        }
        add_char_to_str(str, 10);
    }
    
   
}









/*
*   CALL FUNCTION
*/
    //Эта функия создают фрейм чтоб работать с переменными a,b  foo(a,b)
    void token_function_begin_with_y(struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "CREATEFRAME\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CREATEFRAME\n"); i++){
                add_char_to_str(str, "CREATEFRAME\n"[i]);
            }
        }
        
    
    }

    //Эта функция дефинирует значение и прираживает им ходноту foo(a,b) мы дефинируем параметры
    //1 и 2  а потом посылаем туда значения a и b
    void function_call(struct token_s *token,int *counter, char *s,struct dynamic_string *str){
        switch (token->type)
        {   
            case TOKEN_INT:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR %s@%d\n",s, *counter);
                    fprintf(stdout, "MOVE %s@%d int@%d\n",s, *counter, token->attribute.int_val); 
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                        add_char_to_str(str, "DEFVAR "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp27[100];
                    sprintf(temp27, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp27); i++){
                        add_char_to_str(str, temp27[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE "); i++){
                        add_char_to_str(str, "MOVE "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp26[100];
                    sprintf(temp26, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp26); i++){
                        add_char_to_str(str, temp26[i]);
                    }
                    for(unsigned int i = 0; i < strlen("int@"); i++){
                        add_char_to_str(str, "int@"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%d", token->attribute.int_val);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    add_char_to_str(str, 10);
                    break;
                }
                

            case TOKEN_FLOAT:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR %s@%d\n",s, *counter);
                    fprintf(stdout, "MOVE %s@%d float@%f\n",s, *counter, token->attribute.float_val); 
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                        add_char_to_str(str, "DEFVAR "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp24[100];
                    sprintf(temp24, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp24); i++){
                        add_char_to_str(str, temp24[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE "); i++){
                        add_char_to_str(str, "MOVE "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp23[100];
                    sprintf(temp23, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp23); i++){
                        add_char_to_str(str, temp23[i]);
                    }
                    for(unsigned int i = 0; i < strlen("float@"); i++){
                        add_char_to_str(str, "float@"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%f", token->attribute.float_val);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    add_char_to_str(str, 10);
                    break;
                }

            case TOKEN_STRING:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR %s@%d\n",s,*counter);
                    fprintf(stdout, "MOVE %s@%d string@%s\n",s,*counter,token->attribute.string);
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                        add_char_to_str(str, "DEFVAR "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp22[100];
                    sprintf(temp22, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp22); i++){
                        add_char_to_str(str, temp22[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE "); i++){
                        add_char_to_str(str, "MOVE "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    for(unsigned int i = 0; i < strlen("string@"); i++){
                        add_char_to_str(str, "string@"[i]);
                    }
                    for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                        add_char_to_str(str,token->attribute.string[i]);
                    }
                    add_char_to_str(str, 10); 
                    break;                  
                }

                break;
            case TOKEN_ID:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR %s@%d\n",s,*counter);
                    fprintf(stdout, "MOVE %s@%d %s@%s\n",s,*counter,s,token->attribute.string);
                    break ;
                    
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                        add_char_to_str(str, "DEFVAR "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE "); i++){
                        add_char_to_str(str, "MOVE "[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str,s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    char temp21[100];
                    sprintf(temp21, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp21); i++){
                        add_char_to_str(str, temp21[i]);
                    }
                    for(unsigned int i = 0; i < strlen(s); i++){
                        add_char_to_str(str, s[i]);
                    }
                    for(unsigned int i = 0; i < strlen("@"); i++){
                        add_char_to_str(str,"@"[i]);
                    }
                    for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                        add_char_to_str(str,token->attribute.string[i]);
                    }
                    add_char_to_str(str, 10); 
                    break;                    
                }
            default:
                break;  
        } 
    }



    //вызов функции
    void call_function(struct token_s *token,struct dynamic_string *str){   
        if(flag_while == 0)
        {
            fprintf(stdout,"CALL $%s\n", token->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CALL $"); i++){
                add_char_to_str(str, "CALL $"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                 add_char_to_str(str, token->attribute.string[i]);
            }
            add_char_to_str(str, 10);            
        }                              
    }
    //вызов выставене функции
    void call_inserted_functions(char *d,struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "CALL $%s\n", d);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CALL $"); i++){
                add_char_to_str(str, "CALL $"[i]);
            }
            for(unsigned int i = 0; i < strlen(d); i++){
                 add_char_to_str(str, d[i]);
            }
            add_char_to_str(str, 10);            
        }
    }
    //функия чтоб вернуть прирадить ретвал какому-нибудь значению
    void retval_assign_function(struct token_s *token, char *s,struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "MOVE %s@%s TF@%%retval\n",s, token->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MOVE "); i++){
                add_char_to_str(str, "MOVE "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++){
                 add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++){
                add_char_to_str(str, token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen("TF@%%retval"); i++){
                add_char_to_str(str, "TF@%%retval"[i]);
            }
            add_char_to_str(str, 10);            
        }
    }
/*
 *  END FUNCTION
 */











//принт флоута
void print_float(struct token_s *token_write    ,struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"WRITE float@%a",token_write->attribute.float_val);
    }else{
        for(unsigned int i = 0; i < strlen("WRITE float@"); i++){
            add_char_to_str(str, "WRITE float@"[i]);
        }
        char temp[100];
        sprintf(temp, "%a", token_write->attribute.float_val);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
    }
}

//принт инта   
void print_int(struct token_s *token_write,struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"WRITE int@%d",token_write->attribute.int_val);
    }else{
        for(unsigned int i = 0; i < strlen("WRITE int@"); i++){
            add_char_to_str(str, "WRITE int@"[i]);
        }
        char temp[100];
        sprintf(temp, "%d",token_write->attribute.int_val);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
    }
    
}

//принт стринга
void print_string(struct token_s *token_write,struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"WRITE string@%s",token_write->attribute.string);
    }else{
        for(unsigned int i = 0; i < strlen("WRITE string@"); i++){
            add_char_to_str(str, "WRITE string@"[i]);
        }
        for(unsigned int i = 0; i < strlen(token_write->attribute.string); i++){
            add_char_to_str(str, token_write->attribute.string[i]);
        }
    }
    
}

//принт ничега
void print_none(struct dynamic_string *str){
    if(flag_while == 0){
            fprintf(stdout,"WRITE None");
    }else{
        for(unsigned int i = 0; i < strlen("WRITE None"); i++){
            add_char_to_str(str, "WRITE None"[i]);
        }
    }
    
}


//Функия для принта переменной с ее значением 
void print_id(struct token_s *token_write,char *s, struct dynamic_string *str){
    //if(item->ret_val == TOKEN_INT)
    //{
        if(flag_while == 0)
        { 
           fprintf(stdout,"WRITE %s@%%%s\n",s,token_write->attribute.string); 
        }else{
            for(unsigned int i = 0; i < strlen("WRITE int@"); i++){
                add_char_to_str(str, "WRITE int@"[i]);
            }
            char temp[100];
            sprintf(temp, "%d",token_write->attribute.int_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
        }        
        
    /*}
    if(item->ret_val == TOKEN_FLOAT)
    {
       
        if(flag_while == 0){
           fprintf(stdout,"WRITE float@%a",token_write->attribute.float_val);
        }else{
            for(unsigned int i = 0; i < strlen("WRITE float@"); i++){
                add_char_to_str(str, "WRITE float@"[i]);
            }
            char temp[100];
            sprintf(temp, "%a",token_write->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
        }  
    }
    if(item->ret_val == TOKEN_STRING)
    {
        if(flag_while == 0){
            fprintf(stdout,"WRITE string@%s",token_write->attribute.string); 
        }else{
            for(unsigned int i = 0; i < strlen("WRITE string@"); i++){
                add_char_to_str(str, "WRITE string@"[i]);
            }
            for(unsigned int i = 0; i < strlen(token_write->attribute.string); i++){
                add_char_to_str(str, token_write->attribute.string[i]);
            }
        }   
    }*/

}
//принт пробела
void print_space(struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout," "); 
    }else{
        for(unsigned int i = 0; i < strlen(" "); i++){
            add_char_to_str(str, " "[i]);
        }
    }
}
//принт \n
void print_end(struct dynamic_string *str){
    if(flag_while == 0){
             fprintf(stdout,"\n");
        }else{
            for(unsigned int i = 0; i < strlen("\n"); i++){
                add_char_to_str(str, "\n"[i]);
            }
        }
}





/*
*   if function
*
*/
    //выписывает хлавичку if start
    void generate_if_head(struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout,"#IF_START\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("#IF START\n"); i++){
                add_char_to_str(str, "#IF START\n"[i]);
            }
        }
    }

    //здесь будет тру или фалсе в зависимоти он выследка сравнение
    //и если булет фалсе то деламе скок 
    void create_returnvalue(struct dynamic_string *str,char *s, int *t){
        if(flag_while == 0)
        {
            fprintf(stdout,"DEFVAR %s@res%d\n",s, *t);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR "); i++){
                add_char_to_str(str, "DEFVAR "[i]);
            }
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str,  s[i]);
            }
            for(unsigned int i = 0; i < strlen("@res"); i++){
                add_char_to_str(str, "@res"[i]);
            }
            char temp[100];
            sprintf(temp, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
        }  
        
    }

    //функция выбора операторов(Привет Паша)
    void select_operator(struct token_s *token,struct dynamic_string *str){
        switch (token->type)
        {
            case TOKEN_EQUAL:
                if(flag_while == 0)
                {
                    fprintf(stdout,"EQ ");
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("EQ "); i++){
                        add_char_to_str(str, "EQ"[i]);
                    }   
                    break;
                }
            

            case TOKEN_NOT_EQUAL:
                if(flag_while == 0)
                {
                    fprintf(stdout,"NOT EQ ");
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("NOT EQ "); i++){
                        add_char_to_str(str, "NOT EQ "[i]);
                    }
                    break;  
                }

            case TOKEN_GREATER:
                if(flag_while == 0)
                {
                    fprintf(stdout,"GT ");
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("GT "); i++){
                        add_char_to_str(str, "GT "[i]);
                    }  
                    break;
                }
                
            case TOKEN_GREATER_EQ:
                if(flag_while == 0)
                {
                fprintf(stdout,"EQ AND GT ");
                break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("EQ AND GT "); i++){
                        add_char_to_str(str, "EQ AND GT"[i]);
                    }
                    break;
                }
 
            case TOKEN_LESS:
                if(flag_while == 0)
                {
                    fprintf(stdout,"LT" );
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("LT "); i++){
                        add_char_to_str(str, "LT "[i]);
                    }
                    break;
                }

            case TOKEN_LESS_EQ:
                if(flag_while == 0)
                {
                    fprintf(stdout,"LT AND EQ ");
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("LT AND EQ "); i++){
                        add_char_to_str(str, "LT AND EQ"[i]);
                    }
                    break;
                }

            default:
                break;
        }
    }


    //эта и предыдушая фунуция выпишуь знак а потом выпишут куда нужно прыгать в случае успеха
    //при сравнении значий retval и valueforounting1 
    void if_body(int *t,struct dynamic_string *str){
      if(flag_while == 0)
      {
        fprintf(stdout,"LF@res LF@retval%d LF@retval1%d\n",*t,*t);
        fprintf(stdout,"JUMPIFNEQ $B0DY-EL%d LF@res bool@true\n", *t);
      }
      else
      {
        for(unsigned int i = 0; i < strlen("LF@res LF@retval"); i++){
            add_char_to_str(str, "LF@res LF@retval"[i]);
        }
        char temp16[100];
        sprintf(temp16, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp16 ); i++){
            add_char_to_str(str, temp16 [i]);
        }
        for(unsigned int i = 0; i < strlen("\nLF@res LF@retval1"); i++){
            add_char_to_str(str, "\nLF@res LF@retval1"[i]);
        }
        char temp17[100];
        sprintf(temp17, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp17); i++){
            add_char_to_str(str, temp17[i]);
        }
        add_char_to_str(str, 10);
        for(unsigned int i = 0; i < strlen("JUMPIFNEQ $B0DY-EL"); i++){
            add_char_to_str(str, "JUMPIFNEQ $B0DY-EL"[i]);
        }
        char temp18[100];
        sprintf(temp18, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp18); i++){
            add_char_to_str(str, temp18[i]);
        }
        for(unsigned int i = 0; i < strlen(" LF@res bool@true\n"); i++){
            add_char_to_str(str, " LF@res bool@true\n"[i]);
        }
      }

      

    }

    //Леха это уже все написано у тебя, названия функций не менял
    // будет выписываться в случае того что сканер нашел else
    void found_else(int *t,struct dynamic_string *str){    
        if(flag_while == 0)
        {
            fprintf(stdout, "JUMP $EXIT%d\n", *t);
            fprintf(stdout, "LABEL B0DY-EL%d\n", *t);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("JUMP $EXIT"); i++){
                add_char_to_str(str, "JUMP $EXIT"[i]);
            } 
            char temp16[100];
            sprintf(temp16, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp16); i++){
                add_char_to_str(str, temp16[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("LABEL B0DY-EL"); i++){
                add_char_to_str(str, "LABEL B0DY-EL"[i]);
            } 
            char temp15[100];
            sprintf(temp15, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp15); i++){
                add_char_to_str(str, temp15[i]);
            }
            add_char_to_str(str, 10);
        }
        

    }

    //Конец if
    void end_of_if(int *t,struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout,"BODY_EL%d\n", *t);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("BODY_EL"); i++){
                add_char_to_str(str, "BODY_EL"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }        
            add_char_to_str(str, 10); 
        }
        
      
    }   

    //Конец подминки else 
    void end_of_else(int *t,struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout,"LABEL $EXIT%d\n", *t);   
        }
        else
        {
            for(unsigned int i = 0; i < strlen("LABEL $EXIT"); i++){
                add_char_to_str(str, "LABEL $EXIT"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }        
            add_char_to_str(str, 10); 
        }
        
 

    }


    //Эта функция создает дополнительные переменные в которые будем записывать
    //то что слева от знака и справа от знака %d для того если у нас if в if
    void stack_operations(int *t,struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "DEFVAR GT@retval1\n");
            fprintf(stdout, "DEFVAR GT@retval2\n");
        
            
            fprintf(stdout, "MOVE GT@retval1 int@0\n");
            fprintf(stdout, "MOVE GT@retval2 int@0\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR GT@retval"); i++){
                add_char_to_str(str, "DEFVAR GT@retval"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            } 
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("DEFVAR GT@retval1"); i++){
                add_char_to_str(str, "DEFVAR GT@retval1"[i]);
            } 
            char temp1[100];
            sprintf(temp1, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp1); i++){
                add_char_to_str(str, temp1[i]);
            }        
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("MOVE GT@retval"); i++){
                add_char_to_str(str, "MOVE GT@retval"[i]);
            } 
            char temp2[100];
            sprintf(temp2, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp2); i++){
                add_char_to_str(str, temp2[i]);
            }  
            for(unsigned int i = 0; i < strlen(" int@\n"); i++){
                add_char_to_str(str, " int@0\n"[i]);
            } 
            for(unsigned int i = 0; i < strlen("MOVE GT@retval1"); i++){
                add_char_to_str(str, "MOVE GT@retval1"[i]);
            } 
            char temp3[100];
            sprintf(temp3, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp3); i++){
                add_char_to_str(str, temp3[i]);
            }  
            for(unsigned int i = 0; i < strlen(" int@0\n"); i++){
                add_char_to_str(str, " int@0\n"[i]);
            } 
    }
}


/*
*   end of if function
*
*/



//Создает голову циклы while
void generate_while_head_1(int *t, struct dynamic_string *str)
{   
    if(flag_while == 0)
    {
        fprintf(stdout,"#WHILE CYCLE\n");
        fprintf(stdout,"LABEL while%d\n", *t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("#WHILE CYCLE\n"); i++){
            add_char_to_str(str, "#WHILE CYCLE\n"[i]);
        }
        for(unsigned int i = 0; i < strlen("LABEL while"); i++){
            add_char_to_str(str, "LABEL while"[i]);
        }
        char temp[100];
        sprintf(temp, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
        add_char_to_str(str, 10);
    }
    

}

//Создает тело функции 
void while_body(int *t,struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"LF@res LF@retval1 LF@retval2\n");
        fprintf(stdout,"JUMPIFNEQ $EXIT%d LF@res bool@true\n", *t);  
    }else
    {
        for(unsigned int i = 0; i < strlen("LF@res LF@retval1"); i++){
            add_char_to_str(str, "LF@res LF@retval1"[i]);
        }
       // char temp11[100];
       //sprintf(temp11, "%d", *t);
       //  for(unsigned int i = 0; i < strlen(temp11); i++){
       //    add_char_to_str(str, temp11[i]);
       // }
        for(unsigned int i = 0; i < strlen(" LF@retval"); i++){
            add_char_to_str(str, " LF@retval2"[i]);
        }
        //char temp12[100];
        //sprintf(temp12, "%d", *t);
        //for(unsigned int i = 0; i < strlen(temp12); i++){
         //   add_char_to_str(str, temp12[i]);
        //}
        add_char_to_str(str, 10);
        for(unsigned int i = 0; i < strlen("JUMPIFNEQ $EXIT"); i++){
            add_char_to_str(str, "JUMPIFNEQ $EXIT"[i]);
        }
        char temp13[100];
        sprintf(temp13, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp13); i++){
            add_char_to_str(str, temp13[i]);
        }
        for(unsigned int i = 0; i < strlen(" LF@res bool@true\n"); i++){
            add_char_to_str(str, " LF@res bool@true\n"[i]);
        }

    }
    

}


//Создает конец цикла while
void generate_while_end(int *t,struct dynamic_string *str){    
    if(flag_while == 0)
    {
        fprintf(stdout,"JUMP while%d\n", *t);
        fprintf(stdout,"LABEL $EXIT%d\n", *t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("JUMP while"); i++){
            add_char_to_str(str, "JUMP while"[i]);
        } 
        char temp8[100];
        sprintf(temp8, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp8); i++){
            add_char_to_str(str, temp8[i]);
        }
        add_char_to_str(str, 10);
        for(unsigned int i = 0; i < strlen("LABEL $EXIT"); i++){
            add_char_to_str(str, "LABEL $EXIT"[i]);
        } 
        char temp9[100];
        sprintf(temp9, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp9); i++){
            add_char_to_str(str, temp9[i]);
        }
        add_char_to_str(str, 10);
    }

}


//Создает цикл while для while(true)  или while(1)
void while_for_true(int *t,struct dynamic_string *str){
    if(flag_while == 0)
    {
        fprintf(stdout,"#WHILE CYCLE\n");
        fprintf(stdout,"LABEL while%d\n",*t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("#WHILE CYCLE\n"); i++){
            add_char_to_str(str, "#WHILE CYCLE\n"[i]);
        }
        for(unsigned int i = 0; i < strlen("LABEL while"); i++){
            add_char_to_str(str, "LABEL while"[i]);
        }
        char temp[100];
        sprintf(temp, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
        add_char_to_str(str, 10);
    }
}


//Создает конец для функции описанной выше
void generate_while_for_true_end(int *t,struct dynamic_string *str){    
    if(flag_while == 0)
    {
        fprintf(stdout,"JUMP while%d\n", *t);
        fprintf(stdout,"LABEL $EXIT%d\n", *t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("JUMP while"); i++){
            add_char_to_str(str, "JUMP while"[i]);
        } 
        char temp5[100];
        sprintf(temp5, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp5); i++){
            add_char_to_str(str, temp5[i]);
        }
        add_char_to_str(str, 10);
        for(unsigned int i = 0; i < strlen("LABEL $EXIT"); i++){
            add_char_to_str(str, "LABEL $EXIT"[i]);
        } 
        char temp6[100];
        sprintf(temp6, "%d", *t);
        for(unsigned int i = 0; i < strlen(temp6); i++){
            add_char_to_str(str, temp6[i]);
        }
        add_char_to_str(str, 10);
    }
}


//Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(sum)
void func_sum(struct token_s *token_one, char *s,struct dynamic_string *str){
    if(token_one->type == TOKEN_FLOAT)
    {   
        if(flag_while == 0)
        {
            fprintf(stdout, "ADD GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("ADD GF@retval GF@retval float@"); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval float@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%f",  token_one->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
        }   
    }
    if(token_one->type == TOKEN_INT)
    {  

        if(flag_while == 0)
        {
            fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
            fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
            fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
            fprintf(stdout, "ADD GF@retval GF@retval TF@%%TMPF2INT\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
                add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d",  token_one->attribute.int_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
            for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nADD GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
                add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nADD GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
            } 
        }
        
    }
    if(token_one->type == TOKEN_ID)
    {
        if(flag_while == 0)
        {
            fprintf(stdout, "ADD GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
        }else
        {
            for(unsigned int i = 0; i < strlen("ADD GF@retval GF@retval"); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval"[i]);
            } 
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);  
        }
        

        
    }
    if(token_one->type == TOKEN_STRING)
    {
        if(flag_while == 0)
        {
             fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);   
        }   
       
    }    
}

//Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(mul)
void func_mul(struct token_s *token_one, char *s, struct dynamic_string *str){

    if(token_one->type == TOKEN_FLOAT)
    {   
        if(flag_while == 0)
        {
            fprintf(stdout, "MUL GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("MUL GF@retval GF@retval float@"); i++){
                add_char_to_str(str, "MUL GF@retval GF@retval float@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%f",  token_one->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
        }   
    }
    if(token_one->type == TOKEN_INT)
    {  

        if(flag_while == 0)
        {
            fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
            fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
            fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
            fprintf(stdout, "MUL GF@retval GF@retval TF@%%TMPF2INT\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
                add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d",  token_one->attribute.int_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
            for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nMUL GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
                add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nMUL GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
            } 
        }
        
    }
    if(token_one->type == TOKEN_ID)
    {
        if(flag_while == 0)
        {
            fprintf(stdout, "MUL GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
        }else
        {
            for(unsigned int i = 0; i < strlen("MUL GF@retval GF@retval"); i++){
                add_char_to_str(str, "MUL GF@retval GF@retval"[i]);
            } 
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);  
        }
        

        
    }
    //Умножение двух стрингов
    //if(token_one->type == TOKEN_STRING){
        if(flag_while == 0)
        {
             fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);   
        }   
       
    //}        
}

//Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(sub)
void func_sub(struct token_s *token_one, char *s,struct dynamic_string *str){

    if(token_one->type == TOKEN_FLOAT)
    {   
        if(flag_while == 0)
        {
            fprintf(stdout, "SUB GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("SUB GF@retval GF@retval float@"); i++){
                add_char_to_str(str, "SUB GF@retval GF@retval float@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%f",  token_one->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
        }   
    }
    if(token_one->type == TOKEN_INT)
    {  

        if(flag_while == 0)
        {
            fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
            fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
            fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
            fprintf(stdout, "SUB GF@retval GF@retval TF@%%TMPF2INT\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
                add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d",  token_one->attribute.int_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
            for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nSUB GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
                add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nSUB GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
            } 
        }
        
    }
    if(token_one->type == TOKEN_ID)
    {
        if(flag_while == 0)
        {
            fprintf(stdout, "SUB GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
        }else
        {
            for(unsigned int i = 0; i < strlen("SUB GF@retval GF@retval"); i++){
                add_char_to_str(str, "SUB GF@retval GF@retval"[i]);
            } 
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);  
        }
        

        
    }
    //There is no string sub
    //if(token_one->type == TOKEN_STRING){
        if(flag_while == 0)
        {
             fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);   
        }   
       
    //}       
}


//Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(div)
void func_div(struct token_s *token_one, char *s,struct dynamic_string *str){
    if(token_one->type == TOKEN_FLOAT)
    {   
        if(flag_while == 0)
        {
            fprintf(stdout, "DIV GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval float@"); i++){
                add_char_to_str(str, "DIV GF@retval GF@retval float@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%f",  token_one->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
        }   
    }
    if(token_one->type == TOKEN_INT)
    {  

        if(flag_while == 0)
        { 
            fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
            fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
            fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
            fprintf(stdout, "DIV GF@retval GF@retval TF@%%TMPF2INT\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
                add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
            } 
            char temp[100];
            sprintf(temp, "%d",  token_one->attribute.int_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);   
            for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
                add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
            } 
        }
        
    }
    if(token_one->type == TOKEN_ID)
    {
        if(flag_while == 0)
        {
            fprintf(stdout, "DIV GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
        }else
        {
            for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval"); i++){
                add_char_to_str(str, "DIV GF@retval GF@retval"[i]);
            } 
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            }
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);  
        }
        

        
    }
    //There is no string sub
    //if(token_one->type == TOKEN_STRING){
        if(flag_while == 0)
        {
             fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
                add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
            } 
            for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
                add_char_to_str(str, token_one->attribute.string[i]);
            }
            add_char_to_str(str, 10);   
        }   
       
    //}  
}
void func_int_div(struct token_s *token_one,struct dynamic_string *str){

    if(flag_while == 0)
    {
        fprintf(stdout, "INT2FLOAT GF@retval GF@retval\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("INT2FLOAT GF@retval GF@retval\n"); i++){
            add_char_to_str(str, "INT2FLOAT GF@retval GF@retval\n"[i]);
        } 
    }
    

   
    if(token_one->type == TOKEN_INT)
    {
        if(flag_while == 0)
        {        
            fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
            fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
            fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
            fprintf(stdout, "DIV GF@retval GF@retval TF@%%TMPF2INT\n");
        }
        else
        {
        for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
            add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
        } 
        char temp[100];
        sprintf(temp, "%d", token_one->attribute.int_val);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
        add_char_to_str(str, 10);
        }
       for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
            add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
        } 
        


    }
    if(token_one->type == TOKEN_FLOAT)
    {
        if(flag_while == 0)
        {
            fprintf(stdout, "DIV GF@retval GF@retval float@%a\n",token_one->attribute.float_val);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval float"); i++){
                add_char_to_str(str, "DIV GF@retval GF@retval float"[i]);
            } 
            char temp[100];
            sprintf(temp, "%f", token_one->attribute.float_val);
            for(unsigned int i = 0; i < strlen(temp); i++){
                add_char_to_str(str, temp[i]);
            }
            add_char_to_str(str, 10);
        }
        
        
    }
    if(flag_while == 0)
    {
        fprintf(stdout, "FLOAT2INTS GF@retval GF@retval\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("FLOAT2INTS GF@retval GF@retval\n"); i++){
            add_char_to_str(str, "FLOAT2INTS GF@retval GF@retval\n"[i]);
        } 
    }
    

      
}


// PASHA`S FUNCTIONS //
void prec_an_def_var(){
    printf("DEFVAR GF@type_var_1\n");
    printf("DEFVAR GF@type_var_2\n");
    printf("DEFVAR GF@prec_var_eq\n");
    printf("DEFVAR GF@prec_var_temp_1\n");
    printf("DEFVAR GF@prec_var_temp_2\n");
}

void prec_an_operand(char *s, struct token_s *token, struct dynamic_string *str){
    switch (token->type){
    case TOKEN_ID:
        printf("PUSHS %s@%s\n", s, token->attribute.string);
        break;
    case TOKEN_INT:
        printf("PUSHS int@%s\n", token->attribute.int_val);
        break;
    case TOKEN_FLOAT:
        printf("PUSHS float@%s\n", token->attribute.float_val);
        break;
    case TOKEN_STRING:
        printf("PUSHS string@%s\n", token->attribute.string);
        break;
    default:
        break;
    }
}

void prec_an_operator(struct token_s *token, struct dynamic_string *str){
    switch(token->type){
    case TOKEN_SUM:
        printf("POPS GF@prec_var_temp_1\n");
        printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
        printf("POPS GF@prec_var_temp_2\n");
        printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");
        
        printf("JUMPIFEQ $SUM_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_%d\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_2_%d\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
        printf("JUMP $SUM_SKIP_%d\n", skip_counter);
        printf("LABEL $skip_int_%d\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");
        
        printf("LABEL $SUM_SKIP_%d\n", skip_counter);

        printf("JUMPIFNEQ $skip_end_%d GF@type_var_1 string@string\n", skip_counter);
        printf("CONCAT GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\n");
        printf("JUMP $END_SUM_%d\n", skip_counter);
        printf("LABEL $skip_end_%d\n", skip_counter);
        printf("ADD GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\n");

        printf("LABEL $END_SUM_%d\n", skip_counter);
        printf("PUSHS GF@prec_var_temp_1\n");

        skip_counter++;
        break;
    case TOKEN_DIVISION:
        printf("POPS GF@prec_var_temp_1\n");
        printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
        printf("POPS GF@prec_var_temp_2\n");
        printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

        printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_%d\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_2_%d\n", skip_counter);
        
        // printf("JUMPIFEQ $DIV_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

        printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
        // printf("JUMP $DIV_SKIP_%d\n", skip_counter);
        printf("LABEL $skip_int_%d\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_int_2_%d GF@type_var_2 string@int\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");
        printf("LABEL $skip_int_2_%d\n", skip_counter);

        // printf("LABEL $DIV_SKIP_%d\n", skip_counter);

        printf("JUMPIFNEQ $SKIP_EXIT_0_%d GF@prec_var_temp_1 float@0x0\n", skip_counter);
        printf("EXIT 57\n");
        printf("LABEL $SKIP_EXIT_0_%d\n", skip_counter);
        printf("DIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

        printf("PUSHS GF@prec_var_temp_1\n");
        
        skip_counter++;
        break;
    case TOKEN_MINUS:
        printf("POPS GF@prec_var_temp_1\n");
        printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
        printf("POPS GF@prec_var_temp_2\n");
        printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

        printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_%d\n", skip_counter);
        
        printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
        printf("EXIT 4\n");
        printf("LABEL $skip_string_2_%d\n", skip_counter);
        
        printf("JUMPIFEQ $MINUS_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

        printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
        printf("JUMP $MINUS_SKIP_%d\n", skip_counter);
        printf("LABEL $skip_int_%d\n", skip_counter);
        printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

        printf("LABEL $MINUS_SKIP_%d\n", skip_counter);

        // printf("JUMPIFNEQ $SKIP_EXIT_0_%d GF@prec_var_temp_1 float@0x0\n", skip_counter);
        // printf("EXIT 57\n");
        // printf("LABEL $SKIP_EXIT_0_%d\n", skip_counter);
        printf("SUB GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

        printf("PUSHS GF@prec_var_temp_1\n");
        
        skip_counter++;
        break;
    case TOKEN_DIV_INT:
        break;
    case TOKEN_MULTIPLY:
        break;
    case TOKEN_EQUAL:
        break;
    case TOKEN_NOT_EQUAL:
        break;
    case TOKEN_LESS:
        break;
    case TOKEN_GREATER:
        break;
    case TOKEN_LESS_EQ:
        break;
    case TOKEN_GREATER_EQ:
        break;
    default:
        break;
    }
}
