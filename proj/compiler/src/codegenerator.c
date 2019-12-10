/**
 * \file  ./codegenerator.c
 * \brief Implimentation of target code generator \file ./codegenerator.c
 * 
 * \author  Aghayev Raul (xaghay00@stud.fit.vutbr.cz)
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
fprintf(stdout,".IFJcode19\n");
fprintf(stdout,"JUMP $$main\n\n");
fprintf(stdout,"#FUNCLEN\n");
fprintf(stdout,"LABEL $len\n");
fprintf(stdout,"PUSHFRAME\n");
// fprintf(stdout,"DEFVAR LF@%%retval\n");
fprintf(stdout,"STRLEN GF@retval LF@%%1\n");
// printf("MOVE GF@retval LF@%%retval\n");
fprintf(stdout,"POPFRAME\n");
fprintf(stdout,"RETURN\n");

fprintf(stdout, "#INPUTS\n");
fprintf(stdout, "LABEL $inputs\n");
fprintf(stdout, "PUSHFRAME\n");
fprintf(stdout, "READ GF@prec_var_temp_1 string\n");//var has yalda\n
fprintf(stdout, "TYPE GF@type_var_1 GF@prec_var_temp_1\n");
fprintf(stdout, "JUMPIFNEQ $exitforinputs GF@type_var_1 string@string\n");//18
fprintf(stdout, "MOVE GF@retval GF@prec_var_temp_1\n");
fprintf(stdout, "JUMP $EXIT_inputs\n");
fprintf(stdout, "LABEL $exitforinputs\n");
fprintf(stdout, "EXIT int@4\n");
fprintf(stdout, "LABEL $EXIT_inputs\n");
fprintf(stdout, "POPFRAME\n");
fprintf(stdout, "RETURN\n");

fprintf(stdout, "#INPUTI\n");
fprintf(stdout, "LABEL $inputi\n");
fprintf(stdout, "PUSHFRAME\n");
fprintf(stdout, "READ GF@prec_var_temp_1 int\n");//var has int value now//67
fprintf(stdout, "TYPE GF@prec_var_temp_2 GF@prec_var_temp_1\n");//shouldbeint now shouldbeint
fprintf(stdout, "MOVE GF@type_var_1 string@int\n");//int string now has int
fprintf(stdout, "JUMPIFNEQ $exitforinputi GF@prec_var_temp_2 GF@type_var_1\n");
fprintf(stdout, "MOVE GF@retval GF@prec_var_temp_1\n");
fprintf(stdout, "JUMP $EXIT_inputi\n");
fprintf(stdout, "LABEL $exitforinputi\n");
fprintf(stdout, "EXIT int@4\n");
fprintf(stdout, "LABEL $EXIT_inputi\n");
fprintf(stdout, "POPFRAME\n");
fprintf(stdout, "RETURN\n");



fprintf(stdout, "#INPUTF\n");
fprintf(stdout, "LABEL $inputf\n");
fprintf(stdout, "PUSHFRAME\n");
fprintf(stdout, "READ GF@prec_var_temp_1 float\n");//var has int value now
fprintf(stdout, "TYPE GF@prec_var_temp_2 GF@prec_var_temp_1\n");//shouldbeint now shouldbeint
fprintf(stdout, "MOVE GF@type_var_1 string@float\n");//int string now has int
fprintf(stdout, "JUMPIFNEQ $exitforinputf GF@prec_var_temp_2 GF@type_var_1\n");
fprintf(stdout, "MOVE GF@retval GF@prec_var_temp_1\n");
fprintf(stdout, "JUMP $EXIT_inputf\n");
fprintf(stdout, "LABEL $exitforinputf\n");
fprintf(stdout, "EXIT int@4\n");
fprintf(stdout, "LABEL $EXIT_inputf\n");
fprintf(stdout, "POPFRAME\n");
fprintf(stdout, "RETURN\n");





//substs is fixed now
fprintf(stdout,"#SUBSTRFUNCTION\n");
fprintf(stdout,"LABEL $substr\n");
fprintf(stdout,"PUSHFRAME\n");
fprintf(stdout,"DEFVAR LF@%%retval\n");
fprintf(stdout,"MOVE LF@%%retval string@\n");
fprintf(stdout,"DEFVAR LF@length_str\n");
fprintf(stdout,"CREATEFRAME\n");
fprintf(stdout,"DEFVAR TF@%%1\n");
fprintf(stdout,"MOVE TF@%%1 LF@%%1\n");
fprintf(stdout,"CALL $len\n");
fprintf(stdout,"MOVE LF@length_str GF@retval\n");
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
fprintf(stdout,"MOVE LF@%%3 LF@max_n\n") ;
fprintf(stdout,"LABEL $substr$process\n");
fprintf(stdout,"DEFVAR LF@index\n");
fprintf(stdout,"MOVE LF@index LF@%%2\n");
fprintf(stdout,"SUB LF@index LF@index int@1\n");
fprintf(stdout,"DEFVAR LF@char\n");
fprintf(stdout,"DEFVAR LF@process_loop_cond\n");
fprintf(stdout,"LABEL $substr$process_loop\n");
fprintf(stdout,"GETCHAR LF@char LF@%%1 LF@index\n"); // what is it ? —-----------------------------------------------—
fprintf(stdout,"CONCAT LF@%%retval LF@%%retval LF@char\n");
printf("MOVE GF@retval LF@%%retval\n");
fprintf(stdout,"ADD LF@index LF@index int@1\n");
fprintf(stdout,"SUB LF@%%3 LF@%%3 int@1\n");
fprintf(stdout,"GT LF@process_loop_cond LF@%%3 int@0\n");
fprintf(stdout,"JUMPIFEQ $substr$process_loop LF@process_loop_cond bool@true\n");
fprintf(stdout,"LABEL $substr$return\n");
fprintf(stdout,"POPFRAME\n");
fprintf(stdout,"RETURN\n");


//fixed
fprintf(stdout,"#ORDFUNCTION\n");
fprintf(stdout,"LABEL $ord\n");
fprintf(stdout,"PUSHFRAME\n");
fprintf(stdout,"DEFVAR LF@%%retval\n");
fprintf(stdout,"MOVE LF@%%retval int@0\n");
fprintf(stdout,"DEFVAR LF@cond_length\n");
fprintf(stdout,"LT LF@cond_length LF@%%2 int@1\n"); // —----------------------— WHY LF%%2 ? not LF@%%0 or 1?
fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
fprintf(stdout,"DEFVAR LF@length_str\n");
fprintf(stdout,"CREATEFRAME\n");
fprintf(stdout,"DEFVAR TF@%%1\n");
fprintf(stdout,"MOVE TF@%%1 LF@%%1\n");
fprintf(stdout,"CALL $len\n");
fprintf(stdout,"MOVE LF@length_str GF@retval\n");
fprintf(stdout,"GT LF@cond_length LF@%%2 LF@length_str\n");
fprintf(stdout,"JUMPIFEQ $asc$return LF@cond_length bool@true\n");
fprintf(stdout,"SUB LF@%%2 LF@%%2 int@1\n");
fprintf(stdout,"STRI2INT LF@%%retval LF@%%1 LF@%%2\n");
printf("MOVE GF@retval LF@%%retval\n");
fprintf(stdout,"LABEL $asc$return\n");
fprintf(stdout,"POPFRAME\n");
fprintf(stdout,"RETURN\n");



//fixed
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
printf("MOVE GF@retval LF@%%retval\n");
fprintf(stdout,"LABEL $chr$return\n");
fprintf(stdout,"POPFRAME\n");
fprintf(stdout,"RETURN\n");


fprintf(stdout, "LABEL $$main\n");
fprintf(stdout,"DEFVAR GF@res\n");
fprintf(stdout,"DEFVAR GF@TYPEOFVAR\n");
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
    //done
    void define_function_begin(struct token_s *token, struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout,"#Function start\n");
            fprintf(stdout,"JUMP $exit_%s\n", token->attribute.string);
            fprintf(stdout,"LABEL $%s\n", token->attribute.string);
            fprintf(stdout,"PUSHFRAME\n");
        }
        else
        {
            for(unsigned int i = 0; i < strlen("#Function start\nJUMP $exit_"); i++)
            {
                add_char_to_str(str, "#Function start\nJUMP $exit_"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
            {
                add_char_to_str(str, token->attribute.string[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("LABEL $"); i++)
            {
                add_char_to_str(str, "LABEL $"[i]);
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
    //done
    void retval_function(struct dynamic_string *str){
        if(flag_while == 0){
            fprintf(stdout, "DEFVAR LF@retval\n");
           
        }
        else{   
            for(unsigned int i = 0; i < strlen("DEFVAR LF@retval\n"); i++){
                add_char_to_str(str, "DEFVAR LF@retval\n"[i]);
            }
        }
    }
    //done
    void def_function_call(struct token_s *token, int *counter, char *s,struct dynamic_string *str){
        if(flag_while == 0){
            fprintf(stdout, "DEFVAR %s@%s\n",s,token->attribute.string);
            fprintf(stdout, "MOVE %s@%s %s@%%%d\n",s,token->attribute.string, s ,*counter);
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
            add_char_to_str(str,32);
            ////////////////////////////////////////////////
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
            add_char_to_str(str, 32);
            for(unsigned int i = 0; i < strlen(s); i++)
            {
                add_char_to_str(str,s[i]);
            }
            for(unsigned int i = 0; i < strlen("@%%"); i++)
            {
                add_char_to_str(str,"@%%"[i]);
            }   
            char temp28[100];
            sprintf(temp28, "%d",*counter);
            for(unsigned int i = 0; i < strlen(temp28); i++){
                add_char_to_str(str, temp28[i]);
            }
            add_char_to_str(str, 10);
        }
    
    }
    //done
    void def_function_end(struct token_s *token, struct dynamic_string *str){
        if(flag_while == 0)
        {
            fprintf(stdout, "POPFRAME\n");
            fprintf(stdout, "RETURN\n");
            fprintf(stdout, "LABEL $exit_%s\n",token->attribute.string);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPFRAME\nRETURN\nLABEL $exit_"); i++)
            {
                add_char_to_str(str, "POPFRAME\nRETURN\nLABEL $exit_"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
            {
                add_char_to_str(str, token->attribute.string[i]);
            }
            add_char_to_str(str, 10);
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
    // if(flag_while == 0)
    // {
        (void)str;
        fprintf(stdout, "DEFVAR %s@%s\n",s,token->attribute.string); 
    // }
    // else
    // {
    //     for(unsigned int i = 0; i < strlen("DEFVAR "); i++)
    //     {
    //         add_char_to_str(str, "DEFVAR "[i]);
    //     }
    //     for(unsigned int i = 0; i < strlen(s); i++)
    //     {
    //         add_char_to_str(str, s[i]);
    //     }
    //     for(unsigned int i = 0; i < strlen("@"); i++)
    //     {
    //         add_char_to_str(str, "@"[i]);
    //     }
    //     for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
    //     {
    //         add_char_to_str(str, token->attribute.string[i]);
    //     }
    //     add_char_to_str(str, 10);
    // }
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
            for(unsigned int i = 0; i < strlen("@%%"); i++){
                add_char_to_str(str, "@%%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                add_char_to_str(str, token->attribute.string[i]);
            }
            for(unsigned int i = 0; i < strlen(" int@retval"); i++){
                add_char_to_str(str, " int@retval"[i]);
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
            for(unsigned int i = 0; i < strlen("@%%"); i++)
            {
                add_char_to_str(str, "@%%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
            {
                add_char_to_str(str, token->attribute.string[i]);
            }
            for(unsigned int i = 0; i < strlen(" float@retval"); i++)
            {
                add_char_to_str(str, " float@retval"[i]);
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
            for(unsigned int i = 0; i < strlen("@%%"); i++)
            {
                add_char_to_str(str, "@%%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++)
            {
                add_char_to_str(str, token->attribute.string[i]);
            }
            for(unsigned int i = 0; i < strlen(" string@retval"); i++)
            {
                add_char_to_str(str, " string@retval"[i]);
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
            for(unsigned int i = 0; i < strlen("@%%"); i++)
            {
                add_char_to_str(str, "@%%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str, token->attribute.string [i]);
            }
            add_char_to_str(str, 32);
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
            for(unsigned int i = 0; i < strlen("@%%"); i++)
            {
                add_char_to_str(str, "@%%"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string ); i++)
            {
                add_char_to_str(str,token->attribute.string [i]);
            }
            for(unsigned int i = 0; i < strlen(" nil@nil"); i++)
            {
                add_char_to_str(str, " nil@nil"[i]);
            }
            add_char_to_str(str, 10);
            break;          
        }
        default:
            break;  
    }  
}
/*
 *   CALL FUNCTION
 */
    //Эта функия создают фрейм чтоб работать с переменными a,b  foo(a,b)
    void token_function_begin_with_y(struct dynamic_string *str){//function_call_prev
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
    //fixed
    void function_call(struct token_s *token,int *counter, char *s,struct dynamic_string *str){ 
        switch (token->type)
        {   
            case TOKEN_INT:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR TF@%%%d\n",*counter);
                    fprintf(stdout, "MOVE TF@%%%d int@%d\n",*counter, token->attribute.int_val); 
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR TF@%%"); i++){
                        add_char_to_str(str, "DEFVAR TF@%%"[i]);
                    }
                    char temp226[100];
                    sprintf(temp226, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp226); i++){
                        add_char_to_str(str, temp226[i]);
                    }
                    add_char_to_str(str, 10);
                    //////////////////////////////////////////////////////////
                    for(unsigned int i = 0; i < strlen("MOVE TF@%%"); i++){
                        add_char_to_str(str, "MOVE TF@%%"[i]);
                    }
                    char temp27[100];
                    sprintf(temp27, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp27); i++){
                        add_char_to_str(str, temp27[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen(" int@"); i++){
                        add_char_to_str(str, " int@"[i]);
                    }
                    char temp26[100];
                    sprintf(temp26, "%d",token->attribute.int_val);
                    for(unsigned int i = 0; i < strlen(temp26); i++){
                        add_char_to_str(str, temp26[i]);
                    }
                    add_char_to_str(str, 10);
                    break;
                }
                

            case TOKEN_FLOAT:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR TF@%%%d\n", *counter);
                    fprintf(stdout, "MOVE TF@%%%d float@%a\n", *counter, token->attribute.float_val); 
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR TF@%%"); i++){
                        add_char_to_str(str, "DEFVAR TF@%%"[i]);
                    }
                    char tempa226[100];
                    sprintf(tempa226, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(tempa226); i++){
                        add_char_to_str(str, tempa226[i]);
                    }
                    add_char_to_str(str, 10);
                    //////////////////////////////////////////////////////////
                    for(unsigned int i = 0; i < strlen("MOVE TF@%%"); i++){
                        add_char_to_str(str, "MOVE TF@%%"[i]);
                    }
                    char tempa27[100];
                    sprintf(tempa27, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(tempa27); i++){
                        add_char_to_str(str, tempa27[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen(" float@"); i++){
                        add_char_to_str(str, " float@"[i]);
                    }
                    char tempa26[100];
                    sprintf(tempa26, "%a",token->attribute.float_val);
                    for(unsigned int i = 0; i < strlen(tempa26); i++){
                        add_char_to_str(str, tempa26[i]);
                    }
                    add_char_to_str(str, 10);
                    break;
                }

            case TOKEN_STRING:
                if(flag_while == 0)
                {
                    fprintf(stdout, "DEFVAR TF@%%%d\n",*counter);
                    fprintf(stdout, "MOVE TF@%%%d string@%s\n",*counter,token->attribute.string);
                    break;
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR TF@%%"); i++){
                        add_char_to_str(str, "DEFVAR TF@%%"[i]);
                    }
                    char temp22[100];
                    sprintf(temp22, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp22); i++){
                        add_char_to_str(str, temp22[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE TF@%%"); i++){
                        add_char_to_str(str, "MOVE TF@%%"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    for(unsigned int i = 0; i < strlen(" string@"); i++){
                        add_char_to_str(str, " string@"[i]);
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
                    fprintf(stdout, "DEFVAR TF@%%%d\n",*counter);
                    fprintf(stdout, "MOVE TF@%%%d %s@%s\n",*counter,s,token->attribute.string);
                    break ;
                    
                }
                else
                {
                    for(unsigned int i = 0; i < strlen("DEFVAR TF@%%"); i++){
                        add_char_to_str(str, "DEFVAR TF@%%"[i]);
                    }
                    char temp[100];
                    sprintf(temp, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp); i++){
                        add_char_to_str(str, temp[i]);
                    }
                    add_char_to_str(str, 10);
                    for(unsigned int i = 0; i < strlen("MOVE TF@%%"); i++){
                        add_char_to_str(str, "MOVE TF@%%"[i]);
                    }
                    char temp21[100];
                    sprintf(temp21, "%d",*counter);
                    for(unsigned int i = 0; i < strlen(temp21); i++){
                        add_char_to_str(str, temp21[i]);
                    }
                    add_char_to_str(str, 32);
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
    // //вызов выставене функции
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
            fprintf(stdout, "MOVE %s@%s GF@retval\n",s,token->attribute.string);
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
        for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
            add_char_to_str(str, token->attribute.string[i]);
        }
        for(unsigned int i = 0; i < strlen(" GF@retval"); i++){
            add_char_to_str(str, " GF@retval"[i]);
        }
        add_char_to_str(str, 10);
        }
    }
/*
 *  END FUNCTION
 */
//принт флоута
void print_float(struct token_s *token_write,struct dynamic_string *str){
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
        fprintf(stdout,"WRITE int@%d\n",token_write->attribute.int_val);
    }else{
        for(unsigned int i = 0; i < strlen("WRITE int@"); i++){
            add_char_to_str(str, "WRITE int@"[i]);
        }
        char temp[100];
        sprintf(temp, "%d",token_write->attribute.int_val);
        for(unsigned int i = 0; i < strlen(temp); i++){
            add_char_to_str(str, temp[i]);
        }
        add_char_to_str(str, 10);
    }
}
//принт стринга
void print_string(struct token_s *token_write,struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"WRITE string@%s\n",token_write->attribute.string);
    }else{
        for(unsigned int i = 0; i < strlen("WRITE string@"); i++){
            add_char_to_str(str, "WRITE string@"[i]);
        }
        for(unsigned int i = 0; i < strlen(token_write->attribute.string); i++){
            add_char_to_str(str, token_write->attribute.string[i]);
        }
    }
    add_char_to_str(str,10);
}
//принт ничега
void print_none(struct dynamic_string *str){
    if(flag_while == 0){
            fprintf(stdout,"WRITE None\n");
    }else{
        for(unsigned int i = 0; i < strlen("WRITE None\n"); i++){
            add_char_to_str(str, "WRITE None\n"[i]);
        }
    }
}
//Функия для принта переменной с ее значением 
void print_id(struct token_s *token_write,char *s, struct dynamic_string *str){
    if(flag_while == 0)
    { 
        fprintf(stdout,"WRITE %s@%s\n",s,token_write->attribute.string); 
    }else{
        for(unsigned int i = 0; i < strlen("WRITE "); i++){
            add_char_to_str(str, "WRITE "[i]);
        }
        for(unsigned int i = 0; i < strlen(s); i++){
            add_char_to_str(str, s[i]);
        }
        for(unsigned int i = 0; i < strlen("@"); i++){
            add_char_to_str(str, "@"[i]);
        }
        for(unsigned int i = 0; i < strlen(token_write->attribute.string); i++){
            add_char_to_str(str, token_write->attribute.string[i]);
        }
        add_char_to_str(str, 10);
    }        
}
//принт пробела
void print_space(struct dynamic_string *str){
    if(flag_while == 0){
        fprintf(stdout,"WRITE string@\\032\n"); 
    }else{
        for(unsigned int i = 0; i < strlen("WRITE string@\\032\n"); i++){
            add_char_to_str(str, "WRITE string@\\032\n"[i]);
        }
    }
}
//принт \n
void print_end(struct dynamic_string *str){
    if(flag_while == 0){
             fprintf(stdout,"WRITE string@\\010\n");
        }else{
            for(unsigned int i = 0; i < strlen("WRITE string@\\010\n"); i++){
                add_char_to_str(str, "WRITE string@\\010\n"[i]);
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



    //функция выбора операторов(Привет Паша)
    /*void select_operator(struct token_s *token,struct dynamic_string *str){
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
    }*/


    //эта и предыдушая фунуция выпишуь знак а потом выпишут куда нужно прыгать в случае успеха
    //при сравнении значий retval и valueforounting1 
    void if_body(int *t,struct dynamic_string *str){
      if(flag_while == 0)
      {
            //fprintf(stdout,"GF@res LF@retval%d LF@retval1%d\n",*t,*t);
            printf("POPS GF@res\n");
            printf("TYPE GF@TYPEOFVAR GF@res\n");
            
            printf("JUMPIFEQ $skip_for_bool_%d GF@TYPEOFVAR string@bool\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_for_NONE_%d GF@TYPEOFVAR nil@nil\n", skip_counter);
            printf("MOVE GF@res bool@false\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            printf("LABEL $skip_for_NONE_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_for_int_%d GF@TYPEOFVAR string@int\n", skip_counter);
            printf("JUMPIFEQ $end_int_%d GF@res int@0\n", skip_counter);
            printf("MOVE GF@res bool@true\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            printf("LABEL $skip_for_int_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_for_float_%d GF@TYPEOFVAR string@float\n", skip_counter);
            printf("JUMPIFEQ $end_float_%d GF@res float@0x0p+0\n", skip_counter);
            printf("MOVE GF@res bool@true\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            printf("LABEL $skip_for_float_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_for_string_%d GF@TYPEOFVAR string@string\n", skip_counter);
            printf("JUMPIFEQ $end_string_%d GF@res string@''\n", skip_counter);
            printf("MOVE GF@res bool@true\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            printf("LABEL $skip_for_string_%d\n", skip_counter);

            printf("EXIT int@4\n");

            printf("LABEL $end_string_%d\n", skip_counter);
            printf("MOVE GF@res bool@false\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            
            printf("LABEL end_float_%d\n", skip_counter);
            printf("MOVE GF@res bool@false\n");
            printf("JUMP $skip_for_bool_%d\n", skip_counter);
            
            printf("LABEL $end_int_%d\n", skip_counter);
            printf("MOVE GF@res bool@false\n");     

            printf("LABEL $skip_for_bool_%d\n", skip_counter);
            fprintf(stdout,"JUMPIFNEQ $BODY_EL%d GF@res bool@true\n", *t);
            skip_counter++;
      }
      else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@res\nTYPE GF@TYPEOFVAR GF@res\nJUMPIFEQ $skip_for_bool_"); i++){
                add_char_to_str(str, "POPS GF@res\nTYPE GF@TYPEOFVAR GF@res\nJUMPIFEQ $skip_for_bool_"[i]);
            }
            char temp16[100];
            sprintf(temp16, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp16 ); i++){
                add_char_to_str(str, temp16 [i]);
            }


            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@bool\nJUMPIFNEQ $skip_for_NONE_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@bool\nJUMPIFNEQ $skip_for_NONE_"[i]);
            }
            char temp17[100];
            sprintf(temp17, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp17); i++){
                add_char_to_str(str, temp17[i]);
            }
           for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR nil@nil\nMOVE GF@res bool@false\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR nil@nil\nMOVE GF@res bool@false\nJUMP $skip_for_bool_"[i]);
            }
            char temp100[100];
            sprintf(temp100, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp100); i++){
                add_char_to_str(str, temp100[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_NONE_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_NONE_"[i]);
            }
            char temp101[100];
            sprintf(temp101, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp101); i++){
                add_char_to_str(str, temp101[i]);
            }
            add_char_to_str(str, 10);


            //Int
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_for_int_"); i++){
                add_char_to_str(str, "\nJUMPIFNEQ $skip_for_int_"[i]);
            }
            char temp102[100];
            sprintf(temp102, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp102); i++){
                add_char_to_str(str, temp102[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@int\nJUMPIFEQ $end_int_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@int\nJUMPIFEQ $end_int_"[i]);
            }
            char temp103[100];
            sprintf(temp103, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp103); i++){
                add_char_to_str(str, temp103[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res int@0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res int@0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp104[100];
            sprintf(temp104, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp104); i++){
                add_char_to_str(str, temp104[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_int_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_int_"[i]);
            }
            char temp105[100];
            sprintf(temp105, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp105); i++){
                add_char_to_str(str, temp105[i]);
            }
            add_char_to_str(str, 10);


            //Float
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $skip_for_float_"); i++){
                add_char_to_str(str, "JUMPIFNEQ $skip_for_float_"[i]);
            }
            char temp106[100];
            sprintf(temp106, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp106); i++){
                add_char_to_str(str, temp106[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@float\nJUMPIFEQ $end_float_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@float\nJUMPIFEQ $end_float_"[i]);
            }
            char temp107[100];
            sprintf(temp107, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp107); i++){
                add_char_to_str(str, temp107[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res float@0x0p+0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res float@0x0p+0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp108[100];
            sprintf(temp108, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp108); i++){
                add_char_to_str(str, temp108[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_float_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_float_"[i]);
            }
            char temp109[100];
            sprintf(temp109, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp109); i++){
                add_char_to_str(str, temp109[i]);
            }
            add_char_to_str(str, 10);



            //String
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_for_string_"); i++){
                add_char_to_str(str, "\nJUMPIFNEQ $skip_for_string_"[i]);
            }
            char temp110[100];
            sprintf(temp110, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp110); i++){
                add_char_to_str(str, temp110[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@string\nJUMPIFEQ $end_string_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@string\nJUMPIFEQ $end_string_"[i]);
            }
            char temp111[100];
            sprintf(temp111, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp111); i++){
                add_char_to_str(str, temp111[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res string@''\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res string@''\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp112[100];
            sprintf(temp112, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp112); i++){
                add_char_to_str(str, temp112[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_string_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_string_"[i]);
            }
            char temp113[100];
            sprintf(temp113, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp113); i++){
                add_char_to_str(str, temp113[i]);
            }



            for(unsigned int i = 0; i < strlen("\nEXIT int@4\n"); i++){
                add_char_to_str(str, "\nEXIT int@4\n"[i]);
            }



            for(unsigned int i = 0; i < strlen("LABEL end_string_"); i++){
                add_char_to_str(str, "LABEL end_string_"[i]);
            }
            char temp114[100];
            sprintf(temp114, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp114); i++){
                add_char_to_str(str, temp114[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("JUMP $skip_for_bool_"); i++){
                add_char_to_str(str, "JUMP $skip_for_bool_"[i]);
            }
            char temp115[100];
            sprintf(temp115, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp115); i++){
                add_char_to_str(str, temp115[i]);
            }
            add_char_to_str(str, 10);




            for(unsigned int i = 0; i < strlen("LABEL end_float_"); i++){
                add_char_to_str(str, "LABEL end_float_"[i]);
            }
            char temp1116[100];
            sprintf(temp1116, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp1116); i++){
                add_char_to_str(str, temp1116[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("JUMP $skip_for_bool_"); i++){
                add_char_to_str(str, "JUMP $skip_for_bool_"[i]);
            }
            char temp1117[100];
            sprintf(temp1117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp1117); i++){
                add_char_to_str(str, temp1117[i]);
            }
            add_char_to_str(str, 10);



            for(unsigned int i = 0; i < strlen("LABEL end_int_"); i++){
                add_char_to_str(str, "LABEL end_int_"[i]);
            }
            char temp116[100];
            sprintf(temp116, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp116); i++){
                add_char_to_str(str, temp116[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("LABEL $skip_for_bool_"); i++){
                add_char_to_str(str, "LABEL $skip_for_bool_"[i]);
            }
            char temp117[100];
            sprintf(temp117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp117); i++){
                add_char_to_str(str, temp117[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $BODY_EL"); i++){
                add_char_to_str(str, "JUMPIFNEQ $BODY_EL"[i]);
            }
            char temp118[100];
            sprintf(temp118, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp118); i++){
                add_char_to_str(str, temp118[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res bool@true\n"); i++){
                add_char_to_str(str, " GF@res bool@true\n"[i]);
            }
            skip_counter++;
        }
    }


    //Леха это уже все написано у тебя, названия функций не менял
    // будет выписываться в случае того что сканер нашел else
    void found_else(int *t,struct dynamic_string *str){    
        if(flag_while == 0)
        {
            fprintf(stdout, "JUMP $EXIT%d\n", *t);
            fprintf(stdout, "LABEL $BODY_EL%d\n", *t);
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
            for(unsigned int i = 0; i < strlen("LABEL $BODY_EL"); i++){
                add_char_to_str(str, "LABEL $BODY_EL"[i]);
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
            fprintf(stdout,"LABEL $BODY_EL%d\n", *t);
        }
        else
        {
            for(unsigned int i = 0; i < strlen("LABEL $BODY_EL"); i++){
                add_char_to_str(str, "LABEL $BODY_EL"[i]);
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
    /*void stack_operations(int *t,struct dynamic_string *str){
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
    //}}
    */
/*
 *   end of if function
 *
 */

//Создает голову циклы while
void generate_while_head_1(int *t, struct dynamic_string *str){   
    if(flag_while == 0)
    {
        fprintf(stdout,"#WHILE CYCLE\n");
        fprintf(stdout,"LABEL $while%d\n", *t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("#WHILE CYCLE\n"); i++){
            add_char_to_str(str, "#WHILE CYCLE\n"[i]);
        }
        for(unsigned int i = 0; i < strlen("LABEL $while"); i++){
            add_char_to_str(str, "LABEL $while"[i]);
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
//controlled
void while_body(int *t,struct dynamic_string *str){ 
    if(flag_while == 0){
        printf("#START_WHILE_BODY\n");
        printf("POPS GF@res\n");
        printf("TYPE GF@TYPEOFVAR GF@res\n");
            
        printf("JUMPIFEQ $skip_for_bool_%d GF@TYPEOFVAR string@bool\n", skip_counter);
            
        printf("JUMPIFNEQ $skip_for_NONE_%d GF@TYPEOFVAR nil@nil\n", skip_counter);
        printf("MOVE GF@res bool@false\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
        printf("LABEL $skip_for_NONE_%d\n", skip_counter);

        printf("JUMPIFNEQ $skip_for_int_%d GF@TYPEOFVAR string@int\n", skip_counter);
        printf("JUMPIFEQ $end_int_%d GF@res int@0\n", skip_counter);
        printf("MOVE GF@res bool@true\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
        printf("LABEL $skip_for_int_%d\n", skip_counter);

        printf("JUMPIFNEQ $skip_for_float_%d GF@TYPEOFVAR string@float\n", skip_counter);
        printf("JUMPIFEQ $end_float_%d GF@res float@0x0p+0\n", skip_counter);
        printf("MOVE GF@res bool@true\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
        printf("LABEL $skip_for_float_%d\n", skip_counter);

        printf("JUMPIFNEQ $skip_for_string_%d GF@TYPEOFVAR string@string\n", skip_counter);
        printf("JUMPIFEQ $end_string_%d GF@res string@''\n", skip_counter);
        printf("MOVE GF@res bool@true\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
        printf("LABEL $skip_for_string_%d\n", skip_counter);

        printf("EXIT int@4\n");

        printf("LABEL $end_string_%d\n", skip_counter);
        printf("MOVE GF@res bool@false\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
            
        printf("LABEL end_float_%d\n", skip_counter);
        printf("MOVE GF@res bool@false\n");
        printf("JUMP $skip_for_bool_%d\n", skip_counter);
            
        printf("LABEL $end_int_%d\n", skip_counter);
        printf("MOVE GF@res bool@false\n");     

        printf("LABEL $skip_for_bool_%d\n", skip_counter);
        printf("JUMPIFNEQ $EXIT%d GF@res bool@true\n", *t);
        skip_counter++;
        }else{
        for(unsigned int i = 0; i < strlen("#START_WHILE_BODY\nPOPS GF@res\nTYPE GF@TYPEOFVAR GF@res\nJUMPIFEQ $skip_for_bool_"); i++){
                add_char_to_str(str, "#START_WHILE_BODY\nPOPS GF@res\nTYPE GF@TYPEOFVAR GF@res\nJUMPIFEQ $skip_for_bool_"[i]);
            }
            char temp16[100];
            sprintf(temp16, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp16 ); i++){
                add_char_to_str(str, temp16 [i]);
            }


            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@bool\nJUMPIFNEQ $skip_for_NONE_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@bool\nJUMPIFNEQ $skip_for_NONE_"[i]);
            }
            char temp17[100];
            sprintf(temp17, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp17); i++){
                add_char_to_str(str, temp17[i]);
            }
           for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR nil@nil\nMOVE GF@res bool@false\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR nil@nil\nMOVE GF@res bool@false\nJUMP $skip_for_bool_"[i]);
            }
            char temp100[100];
            sprintf(temp100, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp100); i++){
                add_char_to_str(str, temp100[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_NONE_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_NONE_"[i]);
            }
            char temp101[100];
            sprintf(temp101, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp101); i++){
                add_char_to_str(str, temp101[i]);
            }
            add_char_to_str(str, 10);


            //Int
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_for_int_"); i++){
                add_char_to_str(str, "\nJUMPIFNEQ $skip_for_int_"[i]);
            }
            char temp102[100];
            sprintf(temp102, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp102); i++){
                add_char_to_str(str, temp102[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@int\nJUMPIFEQ $end_int_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@int\nJUMPIFEQ $end_int_"[i]);
            }
            char temp103[100];
            sprintf(temp103, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp103); i++){
                add_char_to_str(str, temp103[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res int@0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res int@0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp104[100];
            sprintf(temp104, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp104); i++){
                add_char_to_str(str, temp104[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_int_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_int_"[i]);
            }
            char temp105[100];
            sprintf(temp105, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp105); i++){
                add_char_to_str(str, temp105[i]);
            }
            add_char_to_str(str, 10);


            //Float
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $skip_for_float_"); i++){
                add_char_to_str(str, "JUMPIFNEQ $skip_for_float_"[i]);
            }
            char temp106[100];
            sprintf(temp106, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp106); i++){
                add_char_to_str(str, temp106[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@float\nJUMPIFEQ $end_float_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@float\nJUMPIFEQ $end_float_"[i]);
            }
            char temp107[100];
            sprintf(temp107, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp107); i++){
                add_char_to_str(str, temp107[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res float@0x0p+0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res float@0x0p+0\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp108[100];
            sprintf(temp108, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp108); i++){
                add_char_to_str(str, temp108[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_float_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_float_"[i]);
            }
            char temp109[100];
            sprintf(temp109, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp109); i++){
                add_char_to_str(str, temp109[i]);
            }
            add_char_to_str(str, 10);



            //String
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_for_string_"); i++){
                add_char_to_str(str, "\nJUMPIFNEQ $skip_for_string_"[i]);
            }
            char temp110[100];
            sprintf(temp110, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp110); i++){
                add_char_to_str(str, temp110[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@TYPEOFVAR string@string\nJUMPIFEQ $end_string_"); i++){
                add_char_to_str(str, " GF@TYPEOFVAR string@string\nJUMPIFEQ $end_string_"[i]);
            }
            char temp111[100];
            sprintf(temp111, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp111); i++){
                add_char_to_str(str, temp111[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res string@''\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"); i++){
                add_char_to_str(str, " GF@res string@''\nMOVE GF@res bool@true\nJUMP $skip_for_bool_"[i]);
            }
            char temp112[100];
            sprintf(temp112, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp112); i++){
                add_char_to_str(str, temp112[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_for_string_"); i++){
                add_char_to_str(str, "\nLABEL $skip_for_string_"[i]);
            }
            char temp113[100];
            sprintf(temp113, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp113); i++){
                add_char_to_str(str, temp113[i]);
            }



            for(unsigned int i = 0; i < strlen("\nEXIT int@4\n"); i++){
                add_char_to_str(str, "\nEXIT int@4\n"[i]);
            }



            for(unsigned int i = 0; i < strlen("LABEL end_string_"); i++){
                add_char_to_str(str, "LABEL end_string_"[i]);
            }
            char temp114[100];
            sprintf(temp114, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp114); i++){
                add_char_to_str(str, temp114[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("JUMP $skip_for_bool_"); i++){
                add_char_to_str(str, "JUMP $skip_for_bool_"[i]);
            }
            char temp115[100];
            sprintf(temp115, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp115); i++){
                add_char_to_str(str, temp115[i]);
            }
            add_char_to_str(str, 10);




            for(unsigned int i = 0; i < strlen("LABEL end_float_"); i++){
                add_char_to_str(str, "LABEL end_float_"[i]);
            }
            char temp1116[100];
            sprintf(temp1116, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp1116); i++){
                add_char_to_str(str, temp1116[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }
            for(unsigned int i = 0; i < strlen("JUMP $skip_for_bool_"); i++){
                add_char_to_str(str, "JUMP $skip_for_bool_"[i]);
            }
            char temp1117[100];
            sprintf(temp1117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp1117); i++){
                add_char_to_str(str, temp1117[i]);
            }
            add_char_to_str(str, 10);



            for(unsigned int i = 0; i < strlen("LABEL end_int_"); i++){
                add_char_to_str(str, "LABEL end_int_"[i]);
            }
            char temp116[100];
            sprintf(temp116, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp116); i++){
                add_char_to_str(str, temp116[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMOVE GF@res bool@false\n"); i++){
                add_char_to_str(str, "\nMOVE GF@res bool@false\n"[i]);
            }


            for(unsigned int i = 0; i < strlen("LABEL $skip_for_bool_"); i++){
                add_char_to_str(str, "LABEL $skip_for_bool_"[i]);
            }
            char temp117[100];
            sprintf(temp117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(temp117); i++){
                add_char_to_str(str, temp117[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $EXIT"); i++){
                add_char_to_str(str, "JUMPIFNEQ $EXIT"[i]);
            }
            char temp118[100];
            sprintf(temp118, "%d", *t);
            for(unsigned int i = 0; i < strlen(temp118); i++){
                add_char_to_str(str, temp118[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@res bool@true\n"); i++){
                add_char_to_str(str, " GF@res bool@true\n"[i]);
            }
            skip_counter++;

    }
}
//Создает конец цикла while
void generate_while_end(int *t,struct dynamic_string *str){    
    if(flag_while == 0)
    {
        fprintf(stdout,"JUMP $while%d\n", *t);
        fprintf(stdout,"LABEL $EXIT%d\n", *t);
    }
    else
    {
        for(unsigned int i = 0; i < strlen("JUMP $while"); i++){
            add_char_to_str(str, "JUMP $while"[i]);
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
/*void coomment(){
    //Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(sum)
    // void func_sum(struct token_s *token_one, char *s,struct dynamic_string *str){
    //     if(token_one->type == TOKEN_FLOAT)
    //     {   
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "ADD GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("ADD GF@retval GF@retval float@"); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval float@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%a",  token_one->attribute.float_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
    //     }
    //     if(token_one->type == TOKEN_INT)
    //     {  
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
    //             fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
    //             fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
    //             fprintf(stdout, "ADD GF@retval GF@retval TF@%%TMPF2INT\n");
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
    //                 add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%d",  token_one->attribute.int_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //             for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nADD GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
    //                 add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nADD GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
    //             } 
    //         }
            
    //     }
    //     if(token_one->type == TOKEN_ID)
    //     {
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "ADD GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
    //         }else
    //         {
    //             for(unsigned int i = 0; i < strlen("ADD GF@retval GF@retval"); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(s); i++){
    //                 add_char_to_str(str, s[i]);
    //             }
    //             for(unsigned int i = 0; i < strlen("@"); i++){
    //                 add_char_to_str(str, "@"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);  
    //         }
            
            
    //     }
    //     if(token_one->type == TOKEN_STRING)
    //     {
    //         if(flag_while == 0)
    //         {
    //              fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
           
    //     }    
    // }
    //Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(mul)
    // void func_mul(struct token_s *token_one, char *s, struct dynamic_string *str){
    //     if(token_one->type == TOKEN_FLOAT)
    //     {   
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "MUL GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("MUL GF@retval GF@retval float@"); i++){
    //                 add_char_to_str(str, "MUL GF@retval GF@retval float@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%a",  token_one->attribute.float_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
    //     }
    //     if(token_one->type == TOKEN_INT)
    //     {  
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
    //             fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
    //             fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
    //             fprintf(stdout, "MUL GF@retval GF@retval TF@%%TMPF2INT\n");
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
    //                 add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%d",  token_one->attribute.int_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //             for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nMUL GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
    //                 add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nMUL GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
    //             } 
    //         }
            
    //     }
    //     if(token_one->type == TOKEN_ID)
    //     {
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "MUL GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
    //         }else
    //         {
    //             for(unsigned int i = 0; i < strlen("MUL GF@retval GF@retval"); i++){
    //                 add_char_to_str(str, "MUL GF@retval GF@retval"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(s); i++){
    //                 add_char_to_str(str, s[i]);
    //             }
    //             for(unsigned int i = 0; i < strlen("@"); i++){
    //                 add_char_to_str(str, "@"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);  
    //         }
            
            
    //     }
    //     //Умножение двух стрингов
    //     //if(token_one->type == TOKEN_STRING){
    //         if(flag_while == 0)
    //         {
    //              fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
           
    //     //}        
    // }
    //Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(sub)
    // void func_sub(struct token_s *token_one, char *s,struct dynamic_string *str){
    //     if(token_one->type == TOKEN_FLOAT)
    //     {   
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "SUB GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("SUB GF@retval GF@retval float@"); i++){
    //                 add_char_to_str(str, "SUB GF@retval GF@retval float@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%a",  token_one->attribute.float_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
    //     }
    //     if(token_one->type == TOKEN_INT)
    //     {  
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
    //             fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
    //             fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
    //             fprintf(stdout, "SUB GF@retval GF@retval TF@%%TMPF2INT\n");
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
    //                 add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%d",  token_one->attribute.int_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //             for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nSUB GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
    //                 add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nSUB GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
    //             } 
    //         }
            
    //     }
    //     if(token_one->type == TOKEN_ID)
    //     {
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "SUB GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
    //         }else
    //         {
    //             for(unsigned int i = 0; i < strlen("SUB GF@retval GF@retval"); i++){
    //                 add_char_to_str(str, "SUB GF@retval GF@retval"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(s); i++){
    //                 add_char_to_str(str, s[i]);
    //             }
    //             for(unsigned int i = 0; i < strlen("@"); i++){
    //                 add_char_to_str(str, "@"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);  
    //         }
            
            
    //     }
    //     //There is no string sub
    //     //if(token_one->type == TOKEN_STRING){
    //         if(flag_while == 0)
    //         {
    //              fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
           
    //     //}       
    // }
    //Функия посчитает и запишет в помоцную переменную valueforcouing все что вы туда пошлете(div)
    // void func_div(struct token_s *token_one, char *s,struct dynamic_string *str){
    //     if(token_one->type == TOKEN_FLOAT)
    //     {   
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DIV GF@retval GF@retval float@%a\n", token_one->attribute.float_val);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval float@"); i++){
    //                 add_char_to_str(str, "DIV GF@retval GF@retval float@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%a",  token_one->attribute.float_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
    //     }
    //     if(token_one->type == TOKEN_INT)
    //     {  
    //         if(flag_while == 0)
    //         { 
    //             fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
    //             fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
    //             fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
    //             fprintf(stdout, "DIV GF@retval GF@retval TF@%%TMPF2INT\n");
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
    //                 add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%d",  token_one->attribute.int_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //             for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
    //                 add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
    //             } 
    //         }
            
    //     }
    //     if(token_one->type == TOKEN_ID)
    //     {
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DIV GF@retval GF@retval %s@%s\n", s,token_one->attribute.string);
    //         }else
    //         {
    //             for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval"); i++){
    //                 add_char_to_str(str, "DIV GF@retval GF@retval"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(s); i++){
    //                 add_char_to_str(str, s[i]);
    //             }
    //             for(unsigned int i = 0; i < strlen("@"); i++){
    //                 add_char_to_str(str, "@"[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);  
    //         }
            
            
    //     }
    //     //There is no string sub
    //     //if(token_one->type == TOKEN_STRING){
    //         if(flag_while == 0)
    //         {
    //              fprintf(stdout, "CONCAT GF@retval GF@retval@ %s\n",token_one->attribute.string);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("CONCAT GF@retval GF@retval "); i++){
    //                 add_char_to_str(str, "ADD GF@retval GF@retval "[i]);
    //             } 
    //             for(unsigned int i = 0; i < strlen(token_one->attribute.string); i++){
    //                 add_char_to_str(str, token_one->attribute.string[i]);
    //             }
    //             add_char_to_str(str, 10);   
    //         }   
           
    //     //}  
    // }
    // void func_int_div(struct token_s *token_one,struct dynamic_string *str){
    //     if(flag_while == 0)
    //     {
    //         fprintf(stdout, "INT2FLOAT GF@retval GF@retval\n");
    //     }
    //     else
    //     {
    //         for(unsigned int i = 0; i < strlen("INT2FLOAT GF@retval GF@retval\n"); i++){
    //             add_char_to_str(str, "INT2FLOAT GF@retval GF@retval\n"[i]);
    //         } 
    //     }
        
       
    //     if(token_one->type == TOKEN_INT)
    //     {
    //         if(flag_while == 0)
    //         {        
    //             fprintf(stdout, "DEFVAR LF@TMPF2INT\n");
    //             fprintf(stdout, "MOVE LF@TMPF2INT int@%d\n", token_one->attribute.int_val);
    //             fprintf(stdout, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\n");
    //             fprintf(stdout, "DIV GF@retval GF@retval TF@%%TMPF2INT\n");
    //         }
    //         else
    //         {
    //         for(unsigned int i = 0; i < strlen("DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"); i++){
    //             add_char_to_str(str, "DEFVAR LF@TMPF2INT\nMOVE LF@TMPF2INT int@"[i]);
    //         } 
    //         char temp[100];
    //         sprintf(temp, "%d", token_one->attribute.int_val);
    //         for(unsigned int i = 0; i < strlen(temp); i++){
    //             add_char_to_str(str, temp[i]);
    //         }
    //         add_char_to_str(str, 10);
    //         }
    //        for(unsigned int i = 0; i < strlen("INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"); i++){
    //             add_char_to_str(str, "INT2FLOAT TF@%%TMPF2INT TF@%%TMPF2INT\nDIV GF@retval GF@retval TF@%%TMPF2INT\n"[i]);
    //         } 
    //     }
    //     if(token_one->type == TOKEN_FLOAT)
    //     {
    //         if(flag_while == 0)
    //         {
    //             fprintf(stdout, "DIV GF@retval GF@retval float@%a\n",token_one->attribute.float_val);
    //         }
    //         else
    //         {
    //             for(unsigned int i = 0; i < strlen("DIV GF@retval GF@retval float"); i++){
    //                 add_char_to_str(str, "DIV GF@retval GF@retval float"[i]);
    //             } 
    //             char temp[100];
    //             sprintf(temp, "%a", token_one->attribute.float_val);
    //             for(unsigned int i = 0; i < strlen(temp); i++){
    //                 add_char_to_str(str, temp[i]);
    //             }
    //             add_char_to_str(str, 10);
    //         }
            
            
    //     }
    //     if(flag_while == 0)
    //     {
    //         fprintf(stdout, "FLOAT2INTS GF@retval GF@retval\n");
    //     }
    //     else
    //     {
    //         for(unsigned int i = 0; i < strlen("FLOAT2INTS GF@retval GF@retval\n"); i++){
    //             add_char_to_str(str, "FLOAT2INTS GF@retval GF@retval\n"[i]);
    //         } 
    //     }
    // }
}*/
// PASHA`S FUNCTIONS //
void prec_an_def_var(){
        printf("DEFVAR GF@type_var_1\n");
        printf("DEFVAR GF@type_var_2\n");
        printf("DEFVAR GF@prec_var_eq\n");
        printf("DEFVAR GF@prec_var_temp_1\n");
        printf("DEFVAR GF@prec_var_temp_2\n");
        fprintf(stdout, "DEFVAR GF@retval\n");
        fprintf(stdout, "DEFVAR GF@retval1\n"); 
        fprintf(stdout, "DEFVAR GF@retval2\n"); 
}
void prec_an_operand(char *s, struct token_s *token, struct dynamic_string *str){
    
    switch (token->type){
    case TOKEN_ID:
        if( flag_while == 0)
        {
            printf("PUSHS %s@%s\n", s, token->attribute.string);
            free(token->attribute.string);
            break;
        }
        
        else
        {
            for(unsigned int i = 0; i < strlen("PUSHS "); i++){
                add_char_to_str(str, "PUSHS "[i]);
            } 
            for(unsigned int i = 0; i < strlen(s); i++){
                add_char_to_str(str, s[i]);
            } 
            for(unsigned int i = 0; i < strlen("@"); i++){
                add_char_to_str(str, "@"[i]);
            }
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                add_char_to_str(str, token->attribute.string[i]);
            }
            free(token->attribute.string);
            add_char_to_str(str, 10);
            break;
        }
    case TOKEN_INT:
        if( flag_while == 0)
        {
            printf("PUSHS int@%d\n", token->attribute.int_val);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("PUSHS int@"); i++){
                add_char_to_str(str, "PUSHS int@"[i]);
            } 
            char i1[100];
            sprintf(i1, "%d",token->attribute.int_val);
            for(unsigned int i = 0; i < strlen(i1); i++){
                add_char_to_str(str, i1[i]);
            } 
            add_char_to_str(str, 10);
            break;
        }
    case TOKEN_FLOAT:
        if( flag_while == 0)
        {
            printf("PUSHS float@%a\n", token->attribute.float_val);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("PUSHS float@"); i++){
                add_char_to_str(str, "PUSHS float@"[i]);
        } 
            char f1[100];
            sprintf(f1, "%a",token->attribute.float_val);
            for(unsigned int i = 0; i < strlen(f1); i++){
                add_char_to_str(str, f1[i]);
            } 
            add_char_to_str(str, 10);
            break;
        }
    case TOKEN_STRING:
        if( flag_while == 0)
        {
            printf("PUSHS string@%s\n", token->attribute.string);
            free(token->attribute.string);
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("PUSHS string@"); i++){
                add_char_to_str(str, "PUSHS string@"[i]);
            } 
            for(unsigned int i = 0; i < strlen(token->attribute.string); i++){
                add_char_to_str(str, token->attribute.string[i]);
            }
            free(token->attribute.string);
            add_char_to_str(str, 10);
            break;
        }
    case TOKEN_NONE:
        if(flag_while == 0){
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");

            printf("JUMPIFNEQ $SKIP_INT_NONE_%d GF@type_var_1 string@int\n", skip_counter);
            printf("MOVE GF@prec_var_temp_2 int@0\n");
            printf("JUMP $END_OF_NONE_%d\n", skip_counter); 
            printf("LABEL $SKIP_INT_NONE_%d\n", skip_counter);

            printf("JUMPIFNEQ $SKIP_FLOAT_NONE_%d GF@type_var_1 string@float\n", skip_counter);
            printf("MOVE GF@prec_var_temp_2 float@0x0p+0\n");
            printf("JUMP $END_OF_NONE_%d\n", skip_counter);
            printf("LABEL $SKIP_FLOAT_NONE_%d\n", skip_counter);

            printf("JUMPIFNEQ $SKIP_STRING_NONE_%d GF@type_var_1 string@string\n", skip_counter);
            printf("MOVE GF@prec_var_temp_2 string@''\n");
            printf("JUMP $END_OF_NONE_%d\n", skip_counter);
            printf("LABEL $SKIP_STRING_NONE_%d\n", skip_counter); 

            printf("EXIT int@4\n");

            printf("LABEL $END_OF_NONE_%d\n", skip_counter);
            printf("PUSHS GF@prec_var_temp_1\n");
            printf("PUSHS GF@prec_var_temp_2\n");
            skip_counter++;
        }else{
            for(unsigned int i = 0; i < strlen("PUSHS nil@nil\n"); i++){
                add_char_to_str(str, "PUSHS nil@nil\n"[i]);
            }
        }
            break;
    default:
        break;
    }
}
void prec_an_operator(token_t type, struct dynamic_string *str){
    (void)str;
    switch(type){

    case TOKEN_SUM:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");
            printf("JUMPIFEQ $SUM_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_%d\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_2_%d\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $SUM_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");
            
            printf("LABEL $SUM_SKIP_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_end_%d GF@type_var_1 string@string\n", skip_counter);
            printf("CONCAT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");
            printf("JUMP $END_SUM_%d\n", skip_counter);
            printf("LABEL $skip_end_%d\n", skip_counter);
            printf("ADD GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("LABEL $END_SUM_%d\n", skip_counter);
            printf("PUSHS GF@prec_var_temp_1\n");

            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nPOPS GF@prec_var_temp_2\nJUMPIFEQ $SUM_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nPOPS GF@prec_var_temp_2\nJUMPIFEQ $SUM_SKIP_"[i]);
            }    
            char tmp14[100];
            sprintf(tmp14, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp14); i++){
                add_char_to_str(str, tmp14[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_string_"); i++){
                add_char_to_str(str,  "GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_string_"[i]);
            } 
            char tmp15[100];
            sprintf(tmp15, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp15); i++){
                add_char_to_str(str, tmp15[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"[i]);
            } 
            char tmp16[100];
            sprintf(tmp16, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp16); i++){
                add_char_to_str(str, tmp16[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_string_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_string_2_"[i]);
            } 
            char tmp17[100];
            sprintf(tmp17, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp17); i++){
                add_char_to_str(str, tmp17[i]);
            } 
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"[i]);
            } 
            char tmp18[100];
            sprintf(tmp18, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp18); i++){
                add_char_to_str(str, tmp18[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_int_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_int_"[i]);
            } 
            char tmp19[100];
            sprintf(tmp19, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp19); i++){
                add_char_to_str(str, tmp19[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $SUM_SKIP_"); i++){
                add_char_to_str(str,    "GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $SUM_SKIP_"[i]);
            }
            char tmp20[100];
            sprintf(tmp20, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp20); i++){
                add_char_to_str(str, tmp20[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_int_"); i++){
                add_char_to_str(str,    "\nLABEL $skip_int_"[i]);
            }
            char tmp21[100];
            sprintf(tmp21, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp21); i++){
                add_char_to_str(str, tmp21[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temo_2\nLABEL $SUM_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temo_2\nLABEL $SUM_SKIP_"[i]);
            }
            char tmp22[100];
            sprintf(tmp22, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp22); i++){
                add_char_to_str(str, tmp22[i]);
            } 
            add_char_to_str(str, 10);//  printf("JUMPIFNEQ $skip_end_%d GF@type_var_1 string@string\n", skip_counter);
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ  $skip_end_"); i++){
                add_char_to_str(str,   "JUMPIFNEQ  $skip_end_"[i]);
            }
            char tmp23[100];
            sprintf(tmp23, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp23); i++){
                add_char_to_str(str, tmp23[i]);
            } 
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\n"); i++){
                add_char_to_str(str,   " @type_var_1 string@string\n"[i]);// printf("CONCAT GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            }
            for(unsigned int i = 0; i < strlen("CONCAT GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $END_SUM_"); i++){
                add_char_to_str(str,   "CONCAT GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $END_SUM_"[i]);
            }
            char tmp24[100];
            sprintf(tmp24, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp24); i++){
                add_char_to_str(str, tmp24[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_end_"); i++){
                add_char_to_str(str,   "\nLABEL $skip_end_"[i]);
            } 
            char tmp25[100];
            sprintf(tmp25, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp25); i++){
                add_char_to_str(str, tmp25[i]);
            }
            for(unsigned int i = 0; i < strlen("\nADD GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\nLABEL $END_SUM_"); i++){
                add_char_to_str(str,   "\nADD GF@prec_var_temp_1 GF@prec_var_temp_1 GF@prec_var_temp_1\nLABEL $END_SUM_"[i]);
            } 
            char tmp26[100];
            sprintf(tmp26, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp26); i++){
                add_char_to_str(str, tmp26[i]);
            }
            for(unsigned int i = 0; i < strlen("\nPUSHS GF@prec_var_temp_1"); i++){
                add_char_to_str(str,  "\nPUSHS GF@prec_var_temp_1"[i]);
            }
            skip_counter++; 
            break;
            
        }


    
    case TOKEN_DIVISION:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_%d\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
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

            printf("JUMPIFNEQ $SKIP_EXIT_0_%d GF@prec_var_temp_1 float@0x0p+0\n", skip_counter);
            printf("EXIT 9\n");
            printf("LABEL $SKIP_EXIT_0_%d\n", skip_counter);
            printf("DIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");
            
            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"[i]);
            }    
            char tmp1[100];
            sprintf(tmp1, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp1); i++){
                add_char_to_str(str, tmp1[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"); i++){
                add_char_to_str(str,  " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"[i]);
            } 
            char tmp2[100];
            sprintf(tmp2, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp2); i++){
                add_char_to_str(str, tmp2[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_string_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_string_2_"[i]);
            } 
            char tmp3[100];
            sprintf(tmp3, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp3); i++){
                add_char_to_str(str, tmp3[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"[i]);
            } 
            char tmp4[100];
            sprintf(tmp4, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp4); i++){
                add_char_to_str(str, tmp4[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_int_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_int_"[i]);
            } 
            char tmp5[100];
            sprintf(tmp5, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp5); i++){
                add_char_to_str(str, tmp5[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nLABEL $skip_int_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nLABEL $skip_int_"[i]);
            } 
            char tmp6[100];
            sprintf(tmp6, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp6); i++){
                add_char_to_str(str, tmp6[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_int_2_"); i++){
                add_char_to_str(str,    "\nJUMPIFNEQ $skip_int_2_"[i]);
            }
            char tmp7[100];
            sprintf(tmp7, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp7); i++){
                add_char_to_str(str, tmp7[i]);
            } 
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@int\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $skip_int_2_"); i++){
                add_char_to_str(str,    " GF@type_var_2 string@int\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $skip_int_2_"[i]);
            }  
            char tmp8[100];
            sprintf(tmp8, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp8); i++){
                add_char_to_str(str, tmp8[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $SKIP_EXIT_0_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $SKIP_EXIT_0_"[i]);
            }
            char tmp9[100];
            sprintf(tmp9, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp9); i++){
                add_char_to_str(str, tmp9[i]);
            } 
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("GF@prec_var_temp_1 float0x0\nEXIT 9\nLABEL $SKIP_EXIT_0_"); i++){
                add_char_to_str(str,   "GF@prec_var_temp_1 float0x0\nEXIT 9\nLABEL $SKIP_EXIT_0_"[i]);
            }
            char tmp10[100];
            sprintf(tmp10, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp10); i++){
                add_char_to_str(str, tmp10[i]);
            } 
            for(unsigned int i = 0; i < strlen("DIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,   "DIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            }
            skip_counter++;
            break;
        }
    


    case TOKEN_MINUS:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_%d\n", skip_counter);
            
            printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_2_%d\n", skip_counter);
            
            printf("JUMPIFEQ $MINUS_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $MINUS_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $MINUS_SKIP_%d\n", skip_counter);

            // printf("JUMPIFNEQ $SKIP_EXIT_0_%d GF@prec_var_temp_1 float@0x0\n", skip_counter);
            // printf("EXIT 9\n");
            // printf("LABEL $SKIP_EXIT_0_%d\n", skip_counter);
            printf("SUB GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");
            
            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"[i]);
            }    
            char tmp27[100];
            sprintf(tmp27, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp27); i++){
                add_char_to_str(str, tmp27[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"); i++){
                add_char_to_str(str,  " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"[i]);
            } 
            char tmp28[100];
            sprintf(tmp28, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp28); i++){
                add_char_to_str(str, tmp28[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_string_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_string_2_"[i]);
            } 
            char tmp29[100];
            sprintf(tmp29, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp29); i++){
                add_char_to_str(str, tmp29[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"[i]);
            } 
            char tmp30[100];
            sprintf(tmp30, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp30); i++){
                add_char_to_str(str, tmp30[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFEQ $MINUS_SKIP_"); i++){
                add_char_to_str(str,   "\nJUMPIFEQ $MINUS_SKIP_"[i]);
            } 
            char tmp31[100];
            sprintf(tmp31, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp31); i++){
                add_char_to_str(str, tmp31[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\n"); i++){
                add_char_to_str(str,   " GF@type_var_1 GF@type_var_2\n"[i]);
            } 
            // char tmp32[100];
            // sprintf(tmp32, "%d", skip_counter);
            // for(unsigned int i = 0; i < strlen(tmp32); i++){
            //     add_char_to_str(str, tmp32[i]);
            // }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_int_"); i++){
                add_char_to_str(str,    "\nJUMPIFNEQ $skip_int_"[i]);
            }
            char tmp33[100];
            sprintf(tmp33, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp33); i++){
                add_char_to_str(str, tmp33[i]);
            } 
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $MINUS_SKIP_"); i++){
                add_char_to_str(str,    " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $MINUS_SKIP_"[i]);
            }  
            char tmp34[100];
            sprintf(tmp34, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp34); i++){
                add_char_to_str(str, tmp34[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_int_"); i++){
                add_char_to_str(str,   "\nLABEL $skip_int_"[i]);
            }
            char tmp35[100];
            sprintf(tmp35, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp35); i++){
                add_char_to_str(str, tmp35[i]);
            } 
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $MINUS_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $MINUS_SKIP_"[i]);
            }
            char tmp36[100];
            sprintf(tmp36, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp36); i++){
                add_char_to_str(str, tmp36[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nSUB GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,   "\nSUB GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            }
            skip_counter++;
            break;
        }



    case TOKEN_DIV_INT:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_float_%d GF@type_var_1 string@float\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_float_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_float_2_%d GF@type_var_2 string@float\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_float_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $SKIP_EXIT_0_%d GF@prec_var_temp_1 int@0\n", skip_counter);
            printf("EXIT 9\n");
            printf("LABEL $SKIP_EXIT_0_%d\n", skip_counter);
            printf("IDIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");

            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"[i]);
            }    
            char tmp37[100];
            sprintf(tmp37, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp37); i++){
                add_char_to_str(str, tmp37[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"); i++){
                add_char_to_str(str,  " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"[i]);
            } 
            char tmp38[100];
            sprintf(tmp38, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp38); i++){
                add_char_to_str(str, tmp38[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_string_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_string_2_"[i]);
            } 
            char tmp39[100];
            sprintf(tmp39, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp39); i++){
                add_char_to_str(str, tmp39[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"[i]);
            } 
            char tmp40[100];
            sprintf(tmp40, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp40); i++){
                add_char_to_str(str, tmp40[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_float"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $skip_float"[i]);
            } 
            char tmp41[100];
            sprintf(tmp41, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp41); i++){
                add_char_to_str(str, tmp41[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@float\nEXIT int@4\nLABEL $skip_float_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@float\nEXIT int@4\nLABEL $skip_float_"[i]);
            } 
            char tmp42[100];
            sprintf(tmp42, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp42); i++){
                add_char_to_str(str, tmp42[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_float_2"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_float_2"[i]);
            } 
            char tmp43[100];
            sprintf(tmp43, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp43); i++){
                add_char_to_str(str, tmp43[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@float\nEXIT int@4\nLABEL $skip_float_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@float\nEXIT int@4\nLABEL $skip_float_2_"[i]);
            } 
            char tmp44[100];
            sprintf(tmp44, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp44); i++){
                add_char_to_str(str, tmp44[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $MINUS_EXIT_0_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $MINUS_SKIP_"[i]);
            } 
            char tmp45[100];
            sprintf(tmp45, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp45); i++){
                add_char_to_str(str, tmp45[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@prec_var_temp_1 int@0\nEXIT 9\nLABEL $SKIP_EXIT_0_"); i++){
                add_char_to_str(str,   "GF@type_var_1 GF@type_var_2\n"[i]);
            } 
            char tmp46[100];
            sprintf(tmp46, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp46); i++){
                add_char_to_str(str, tmp46[i]);
            }
            for(unsigned int i = 0; i < strlen("IDIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,   "IDIV GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            } 
       
            skip_counter++;
            break;
        }

    

    case TOKEN_MULTIPLY:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFNEQ $skip_string_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_string_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_string_2_%d\n", skip_counter);

            printf("JUMPIFEQ $MUL_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_float_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $MUL_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_float_%d\n", skip_counter);

            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $MUL_SKIP_%d\n", skip_counter);

            printf("MUL GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");

            skip_counter++;

            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFNEQ $skip_string_"[i]);
            }    
            char tmp50[100];
            sprintf(tmp50, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp50); i++){
                add_char_to_str(str, tmp50[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"); i++){
                add_char_to_str(str,  " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_string_"[i]);
            } 
            char tmp51[100];
            sprintf(tmp51, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp51); i++){
                add_char_to_str(str, tmp51[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_string_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_string_2_"[i]);
            } 
            char tmp52[100];
            sprintf(tmp52, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp52); i++){
                add_char_to_str(str, tmp52[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_string_2_"[i]);
            } 
            char tmp53[100];
            sprintf(tmp53, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp53); i++){
                add_char_to_str(str, tmp53[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFEQ $MUL_SKIP_"); i++){
                add_char_to_str(str,  "\nJUMPIFEQ $MUL_SKIP_"[i]);
            } 
            char tmp54[100];
            sprintf(tmp54, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp54); i++){
                add_char_to_str(str, tmp54[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\n"); i++){
                add_char_to_str(str,   " GF@type_var_1 GF@type_var_2\n"[i]);
            } 
            // char tmp55[100];
            // sprintf(tmp55, "%d", skip_counter);
            // for(unsigned int i = 0; i < strlen(tmp55); i++){
            //     add_char_to_str(str, tmp55[i]);
            // } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_float_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_float_"[i]);
            } 
            char tmp56[100];
            sprintf(tmp56, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp56); i++){
                add_char_to_str(str, tmp56[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP MUL_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP MUL_SKIP_"[i]);
            } 
            char tmp57[100];
            sprintf(tmp57, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp57); i++){
                add_char_to_str(str, tmp57[i]);
            } 

            for(unsigned int i = 0; i < strlen("\nLABEL $skip_float_"); i++){
                add_char_to_str(str,   "\nLABEL $skip_float_"[i]);
            } 
            char tmp58[100];
            sprintf(tmp58, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp58); i++){
                add_char_to_str(str, tmp58[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $MUL_SKIP_"); i++){
                add_char_to_str(str,  "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $MUL_SKIP_"[i]);
            } 
            char tmp59[100];
            sprintf(tmp59, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp59); i++){
                add_char_to_str(str, tmp59[i]);
            }
            for(unsigned int i = 0; i < strlen("\nMUL GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str, "\nMUL GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            } 
            skip_counter++;
            break;
        }
        

    //done
    case TOKEN_EQUAL:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $EQ_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_eq_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_eq_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_eq_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_eq_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_eq_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $EQ_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_eq_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $EQ_SKIP_%d\n", skip_counter);

            printf("EQ GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");
            skip_counter++;
            break;
        }
        else
        {
          for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $EQ_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $EQ_SKIP_"[i]);
            }    
            char tmp59[100];
            sprintf(tmp59, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp59); i++){
                add_char_to_str(str, tmp59[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\n"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\n"[i]);
            } 
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $skip_eq_"); i++){
                add_char_to_str(str,   "JUMPIFNEQ $skip_eq_"[i]);
            } 
            char tmp61[100];
            sprintf(tmp61, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp61); i++){
                add_char_to_str(str, tmp61[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_eq_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_eq_"[i]);
            } 
            char tmp62[100];
            sprintf(tmp62, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp62); i++){
                add_char_to_str(str, tmp62[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_eq_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_eq_2_"[i]);
            } 
            char tmp63[100];
            sprintf(tmp63, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp63); i++){
                add_char_to_str(str, tmp63[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_eq_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_eq_2_"[i]);
            } 
            char tmp64[100];
            sprintf(tmp64, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp64); i++){
                add_char_to_str(str, tmp64[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_eq_int_"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $skip_eq_int_"[i]);
            } 
            char tmp65[100];
            sprintf(tmp65, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp65); i++){
                add_char_to_str(str, tmp65[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $EQ_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $EQ_SKIP_"[i]);
            } 
            char tmp66[100];
            sprintf(tmp66, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp66); i++){
                add_char_to_str(str, tmp66[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_eq_int_"); i++){
                add_char_to_str(str,   "\nLABEL $skip_eq_int_"[i]);
            } 
            char tmp67[100];
            sprintf(tmp67, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp67); i++){
                add_char_to_str(str, tmp67[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2"[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $EQ_SKIP_"); i++){
                add_char_to_str(str,   "\nLABEL $EQ_SKIP_"[i]);
            } 
            char tmp69[100];
            sprintf(tmp69, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp69); i++){
                add_char_to_str(str, tmp69[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("EQ GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1"); i++){
                add_char_to_str(str,  "EQ GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1"[i]);
            }             
            skip_counter++;
            break;
        }

    
    //fixed
    case TOKEN_NOT_EQUAL:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $NE_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_ne_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ne_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_ne_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ne_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_neq_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $NE_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_neq_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $NE_SKIP_%d\n", skip_counter);

            printf("JUMPIFNEQ $NOT_EQUAL_%d GF@prec_var_temp_2 GF@prec_var_temp_1\n", skip_counter);
            printf("PUSHS bool@false\n");
            printf("JUMP $END_AFTER_NE_%d\n", skip_counter);
            printf("LABEL $NOT_EQUAL_%d\n", skip_counter);
            printf("PUSHS bool@true\n");

            printf("LABEL $END_AFTER_NE_%d\n", skip_counter);

            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $NE_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $NE_SKIP_"[i]);
            }
            char tmp70[100];
            sprintf(tmp70, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp70); i++){
                add_char_to_str(str, tmp70[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_ne_"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_ne_"[i]);
            } 
            char tmp71[100];
            sprintf(tmp71, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp71); i++){
                add_char_to_str(str, tmp71[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ne_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ne_"[i]);
            } 
            char tmp72[100];
            sprintf(tmp72, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp72); i++){
                add_char_to_str(str, tmp72[i]);
            } 
            add_char_to_str(str,10);
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $skip_ne_2_"); i++){
                add_char_to_str(str,  "JUMPIFNEQ $skip_ne_2_"[i]);
            } 
            char tmp78[100];
            sprintf(tmp78, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp78); i++){
                add_char_to_str(str, tmp78[i]);
            } 
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ne_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ne_2_"[i]);
            } 
            char tmp73[100];
            sprintf(tmp73, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp73); i++){
                add_char_to_str(str, tmp73[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_neq_int_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_neq_int_"[i]);
            } 
            char tmp79[100];
            sprintf(tmp79, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp79); i++){
                add_char_to_str(str, tmp79[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $NE_SKIP_"); i++){
                add_char_to_str(str,  " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $NE_SKIP_"[i]);
            } 
            char tmp74[100];
            sprintf(tmp74, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp74); i++){
                add_char_to_str(str, tmp74[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_neq_int_"); i++){
                add_char_to_str(str,  "\nLABEL $skip_neq_int_"[i]);
            } 
            char tmp75[100];
            sprintf(tmp75, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp75); i++){
                add_char_to_str(str, tmp75[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $NE_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $NE_SKIP_"[i]);
            } 
            char tmp77[100];
            sprintf(tmp77, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp77); i++){
                add_char_to_str(str, tmp77[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $NOT_EQUAL_"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $NOT_EQUAL_"[i]);
            } 
            char tmp80[100];
            sprintf(tmp80, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp80); i++){
                add_char_to_str(str, tmp80[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS bool@false\nJUMP $END_AFTER_NE_"); i++){
                add_char_to_str(str,   " GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS bool@false\nJUMP $END_AFTER_NE_"[i]);
            } 
            char tmp81[100];
            sprintf(tmp81, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp81); i++){
                add_char_to_str(str, tmp81[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $NOT_EQUAL_"); i++){
                add_char_to_str(str,   "\nLABEL $NOT_EQUAL_"[i]);
            } 
            char tmp83[100];
            sprintf(tmp83, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp83); i++){
                add_char_to_str(str, tmp83[i]);
            } 

            for(unsigned int i = 0; i < strlen("\nPUSHS bool@true\nLABEL $END_AFTER_NE_"); i++){
                add_char_to_str(str,   "\nPUSHS bool@true\nLABEL $END_AFTER_NE_"[i]);
            } 
            char tmp84[100];
            sprintf(tmp84, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp84); i++){
                add_char_to_str(str, tmp84[i]);
            }
            add_char_to_str(str, 10);
            skip_counter++;
            break;
        }

   
    //fixed
    case TOKEN_LESS:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $LS_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_ls_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ls_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_ls_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ls_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $LS_SKIP_%d\n", skip_counter);
            printf("LABEL $skip_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $LS_SKIP_%d\n", skip_counter);

            printf("LT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");
            skip_counter++;
            break;
        }
        else
        {
          for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $LS_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $LS_SKIP_"[i]);
            }    
            char tmp85[100];
            sprintf(tmp85, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp85); i++){
                add_char_to_str(str, tmp85[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\n"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\n"[i]);
            } 
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("JUMPIFNEQ $skip_ls_"); i++){
                add_char_to_str(str,   "JUMPIFNEQ $skip_ls_"[i]);
            } 
            char tmp87[100];
            sprintf(tmp87, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp87); i++){
                add_char_to_str(str, tmp87[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ls_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ls_"[i]);
            } 
            char tmp88[100];
            sprintf(tmp88, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp88); i++){
                add_char_to_str(str, tmp88[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_ls_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_ls_2_"[i]);
            } 
            char tmp89[100];
            sprintf(tmp89, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp89); i++){
                add_char_to_str(str, tmp89[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ls_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ls_2_"[i]);
            } 
            char tmp90[100];
            sprintf(tmp90, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp90); i++){
                add_char_to_str(str, tmp90[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_int_"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $skip_int_"[i]);
            } 
            char tmp91[100];
            sprintf(tmp91, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp91); i++){
                add_char_to_str(str, tmp91[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $LS_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $LS_SKIP_"[i]);
            } 
            char tmp92[100];
            sprintf(tmp92, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp92); i++){
                add_char_to_str(str, tmp92[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_int_"); i++){
                add_char_to_str(str,  "\nLABEL $skip_int_"[i]);
            } 
            char tmp93[100];
            sprintf(tmp93, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp93); i++){
                add_char_to_str(str, tmp93[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $LS_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $LS_SKIP_"[i]);
            } 
            char tmp95[100];
            sprintf(tmp95, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp95); i++){
                add_char_to_str(str, tmp95[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,  "\nLT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            }             
            skip_counter++;
            break;
        }

    
    //fixed
    case TOKEN_GREATER: 
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $GT_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_gt_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_gt_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_gt_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_gt_2_%d\n", skip_counter);

            printf("JUMPIFEQ $skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n"); 
            printf("JUMP $GT_SKIP_%d\n", skip_counter); 
            printf("LABEL $skip_int_%d\n", skip_counter); 
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n"); 

            printf("LABEL $GT_SKIP_%d\n", skip_counter);

            printf("GT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");

            printf("PUSHS GF@prec_var_temp_1\n");
            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $GT_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $GT_SKIP_"[i]);
            }    
            char tmp96[100];
            sprintf(tmp96, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp96); i++){
                add_char_to_str(str, tmp96[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_gt_"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_gt_"[i]);
            } 
            char tmp98[100];
            sprintf(tmp98, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp98); i++){
                add_char_to_str(str, tmp98[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_gt_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_gt_"[i]);
            } 
            char tmp99[100];
            sprintf(tmp99, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp99); i++){
                add_char_to_str(str, tmp99[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_gt_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_gt_2_"[i]);
            } 
            char tmp100[100];
            sprintf(tmp100, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp100); i++){
                add_char_to_str(str, tmp100[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_gt_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_gt_2_"[i]);
            } 
            char tmp101[100];
            sprintf(tmp101, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp101); i++){
                add_char_to_str(str, tmp101[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFEQ $skip_int_"); i++){
                add_char_to_str(str,  "\nJUMPIFEQ $skip_int_"[i]);
            } 
            char tmp102[100];
            sprintf(tmp102, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp102); i++){
                add_char_to_str(str, tmp102[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $GT_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $GT_SKIP_"[i]);
            } 
            char tmp103[100];
            sprintf(tmp103, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp103); i++){
                add_char_to_str(str, tmp103[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $skip_int_"); i++){
                add_char_to_str(str,   "\nLABEL $skip_int_"[i]);
            } 
            char tmp104[100];
            sprintf(tmp104, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp104); i++){
                add_char_to_str(str, tmp104[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2"[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $GT_SKIP_"); i++){
                add_char_to_str(str,   "\nLABEL $GT_SKIP_"[i]);
            } 
            char tmp106[100];
            sprintf(tmp106, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp106); i++){
                add_char_to_str(str, tmp106[i]);
            }
            for(unsigned int i = 0; i < strlen("\nGT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,  "\nGT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nPUSHS GF@prec_var_temp_1\n"[i]);
            }             
            skip_counter++;
            break;
        }
    

    //fixed
    case TOKEN_LESS_EQ:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $LS_EQ_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_ls_eq_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ls_eq_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_ls_eq_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_ls_eq_2_%d\n", skip_counter);

            printf("JUMPIFNEQ $ls_eq_skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $LS_EQ_SKIP_%d\n", skip_counter);
            printf("LABEL $ls_eq_skip_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $LS_EQ_SKIP_%d\n", skip_counter);

            printf("JUMPIFNEQ $SKIP_IN_LSEQ%d GF@prec_var_temp_1 GF@prec_var_temp_2\n", skip_counter);
            printf("MOVE GF@prec_var_temp_1 bool@true\n");
            printf("JUMP $END_LSEQ%d\n", skip_counter);

            printf("LABEL $SKIP_IN_LSEQ%d\n", skip_counter);
            printf("LT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");
            
            printf("LABEL $END_LSEQ%d\n", skip_counter);
            printf("PUSHS GF@prec_var_temp_1\n");
            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $LS_EQ_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $LS_EQ_SKIP_"[i]);
            }    
            char tmp107[100];
            sprintf(tmp107, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp107); i++){
                add_char_to_str(str, tmp107[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_ls_eq_"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_ls_eq_"[i]);
            } 
            char tmp109[100];
            sprintf(tmp109, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp109); i++){
                add_char_to_str(str, tmp109[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ls_eq_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_ls_eq_"[i]);
            } 
            char tnp110[100];
            sprintf(tnp110, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tnp110); i++){
                add_char_to_str(str, tnp110[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_ls_eq_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_ls_eq_2_"[i]);
            } 
            char tmp111[100];
            sprintf(tmp111, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp111); i++){
                add_char_to_str(str, tmp111[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ls_eq_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_ls_eq_2_"[i]);
            } 
            char tmp112[100];
            sprintf(tmp112, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp112); i++){
                add_char_to_str(str, tmp112[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $ls_eq_skip_int_"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $ls_eq_skip_int_"[i]);
            } 
            char tmp113[100];
            sprintf(tmp113, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp113); i++){
                add_char_to_str(str, tmp113[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $LS_EQ_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $LS_EQ_SKIP_"[i]);
            } 
            char tmp114[100];
            sprintf(tmp114, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp114); i++){
                add_char_to_str(str, tmp114[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $ls_eq_skip_int_"); i++){
                add_char_to_str(str,   "\nLABEL $ls_eq_skip_int_"[i]);
            } 
            char tmp115[100];
            sprintf(tmp115, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp115); i++){
                add_char_to_str(str, tmp115[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $LS_EQ_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $LS_EQ_SKIP_"[i]);
            } 
            char tmp117[100];
            sprintf(tmp117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp117); i++){
                add_char_to_str(str, tmp117[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $SKIP_IN_LSEQ"); i++){
                add_char_to_str(str,  "\nJUMPIFNEQ $SKIP_IN_LSEQ"[i]);
            } 
            char tmp1118[100];
            sprintf(tmp1118, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp1118); i++){
                add_char_to_str(str, tmp1118[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_temp_1 GF@type_var_temp_2\nMOVE GF@prec_var_temp_1 bool@true\nJUMP $END_LSEQ"); i++){
                add_char_to_str(str,  " GF@type_var_temp_1 GF@type_var_temp_2\nMOVE GF@prec_var_temp_1 bool@true\nJUMP $END_LSEQ"[i]);
            }   
            char tmpa118[100];
            sprintf(tmpa118, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmpa118); i++){
                add_char_to_str(str, tmpa118[i]);
            }    
            for(unsigned int i = 0; i < strlen("\nLABEL $SKIP_IN_LSEQ"); i++){
                add_char_to_str(str,  "\nLABEL $SKIP_IN_LSEQ"[i]);
            }        
            char tmp11119a[100];
            sprintf(tmp11119a, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp11119a); i++){
                add_char_to_str(str, tmp11119a[i]);
            }
            for(unsigned int i = 0; i < strlen("\nLT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nLABEL $END_LSEQ"); i++){
                add_char_to_str(str,  "\nLT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nLABEL $END_LSEQ"[i]);
            } 
            char tmp11119[100];
            sprintf(tmp11119, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp11119); i++){
                add_char_to_str(str, tmp11119[i]);
            }
            add_char_to_str(str, 10);
            for(unsigned int i = 0; i < strlen("PUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,  "PUSHS GF@prec_var_temp_1\n"[i]);
            }  
            skip_counter++;
            break;
        }

    
    //fixed
    case TOKEN_GREATER_EQ:
        if(flag_while == 0)
        {
            printf("POPS GF@prec_var_temp_1\n");
            printf("TYPE GF@type_var_1 GF@prec_var_temp_1\n");
            printf("POPS GF@prec_var_temp_2\n");
            printf("TYPE GF@type_var_2 GF@prec_var_temp_2\n");

            printf("JUMPIFEQ $GT_EQ_SKIP_%d GF@type_var_1 GF@type_var_2\n", skip_counter);

            printf("JUMPIFNEQ $skip_gt_eq_%d GF@type_var_1 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_gt_eq_%d\n", skip_counter);

            printf("JUMPIFNEQ $skip_gt_eq_2_%d GF@type_var_2 string@string\n", skip_counter);
            printf("EXIT int@4\n");
            printf("LABEL $skip_gt_eq_2_%d\n", skip_counter);

            printf("JUMPIFEQ $gt_eq_skip_int_%d GF@type_var_1 string@int\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\n");
            printf("JUMP $GT_EQ_SKIP_%d\n", skip_counter);
            printf("LABEL $gt_eq_skip_int_%d\n", skip_counter);
            printf("INT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\n");

            printf("LABEL $GT_EQ_SKIP_%d\n", skip_counter);

            printf("JUMPIFNEQ $SKIP_IN_GTEQ%d GF@prec_var_temp_1 GF@prec_var_temp_2\n", skip_counter);
            printf("MOVE GF@prec_var_temp_1 bool@true\n");
            printf("JUMP $END_GTEQ%d\n", skip_counter);

            printf("LABEL $SKIP_IN_GTEQ%d\n", skip_counter);
            printf("GT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\n");
            
            printf("LABEL $END_GTEQ%d\n", skip_counter);
            printf("PUSHS GF@prec_var_temp_1\n");
            skip_counter++;
            break;
        }
        else
        {
            for(unsigned int i = 0; i < strlen("POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $GT_EQ_SKIP_"); i++){
                add_char_to_str(str, "POPS GF@prec_var_temp_1\nTYPE GF@type_var_1 GF@prec_var_temp_1\nPOPS GF@prec_var_temp_2\nTYPE GF@type_var_2 GF@prec_var_temp_2\nJUMPIFEQ $GT_EQ_SKIP_"[i]);
            }    
            char tmp107[100];
            sprintf(tmp107, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp107); i++){
                add_char_to_str(str, tmp107[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_gt_eq_"); i++){
                add_char_to_str(str,  " GF@type_var_1 GF@type_var_2\nJUMPIFNEQ $skip_gt_eq_"[i]);
            } 
           char tmp109[100];
            sprintf(tmp109, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp109); i++){
                add_char_to_str(str, tmp109[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_gt_eq_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@string\nEXIT int@4\nLABEL $skip_gt_eq_"[i]);
            } 
            char tnp110[100];
            sprintf(tnp110, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tnp110); i++){
                add_char_to_str(str, tnp110[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $skip_gt_eq_2_"); i++){
                add_char_to_str(str,   "\nJUMPIFNEQ $skip_gt_eq_2_"[i]);
            } 
            char tmp111[100];
            sprintf(tmp111, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp111); i++){
                add_char_to_str(str, tmp111[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_gt_eq_2_"); i++){
                add_char_to_str(str,   " GF@type_var_2 string@string\nEXIT int@4\nLABEL $skip_gt_eq_2_"[i]);
            } 
            char tmp112[100];
            sprintf(tmp112, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp112); i++){
                add_char_to_str(str, tmp112[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nJUMPIFEQ $gt_eq_skip_int_"); i++){
                add_char_to_str(str,  "\nJUMPIFEQ $gt_eq_skip_int_"[i]);
            } 
            char tmp113[100];
            sprintf(tmp113, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp113); i++){
                add_char_to_str(str, tmp113[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $GT_EQ_SKIP_"); i++){
                add_char_to_str(str,   " GF@type_var_1 string@int\nINT2FLOAT GF@prec_var_temp_1 GF@prec_var_temp_1\nJUMP $GT_EQ_SKIP_"[i]);
            } 
            char tmp114[100];
            sprintf(tmp114, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp114); i++){
                add_char_to_str(str, tmp114[i]);
            } 
            for(unsigned int i = 0; i < strlen("\nLABEL $gt_eq_skip_int_"); i++){
                add_char_to_str(str,   "\nLABEL $gt_eq_skip_int_"[i]);
            } 
            char tmp115[100];
            sprintf(tmp115, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp115); i++){
                add_char_to_str(str, tmp115[i]);
            }
            for(unsigned int i = 0; i < strlen("\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $GT_EQ_SKIP_"); i++){
                add_char_to_str(str,   "\nINT2FLOAT GF@prec_var_temp_2 GF@prec_var_temp_2\nLABEL $GT_EQ_SKIP_"[i]);
            } 
            char tmp117[100];
            sprintf(tmp117, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp117); i++){
                add_char_to_str(str, tmp117[i]);
            }
            for(unsigned int i = 0; i < strlen("\nJUMPIFNEQ $SKIP_IN_GTEQ"); i++){
                add_char_to_str(str, "\nJUMPIFNEQ $SKIP_IN_GTEQ"[i]);
            } 
            char tmp118[100];
            sprintf(tmp118, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp118); i++){
                add_char_to_str(str, tmp118[i]);
            }
            for(unsigned int i = 0; i < strlen(" GF@prec_var_temp_1 GF@prec_var_temp_2\nMOVE GF@prec_var_temp_1 bool@true\nJUMP $END_GTEQ"); i++){
                add_char_to_str(str,  " GF@prec_var_temp_1 GF@prec_var_temp_2\nMOVE GF@prec_var_temp_1 bool@true\nJUMP $END_GTEQ"[i]);
            }             
            char tmp119a[100];
            sprintf(tmp119a, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp119a); i++){
                add_char_to_str(str, tmp119a[i]);
            }
            add_char_to_str(str,10);
            for(unsigned int i = 0; i < strlen("LABEL $SKIP_IN_GTEQ"); i++){
                add_char_to_str(str,  "LABEL $SKIP_IN_GTEQ"[i]);
            }             
            char tmp119b[100];
            sprintf(tmp119b, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp119b); i++){
                add_char_to_str(str, tmp119b[i]);
            }
            add_char_to_str(str,10);
            for(unsigned int i = 0; i < strlen("GT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nLABEL $END_GTEQ"); i++){
                add_char_to_str(str,  "GT GF@prec_var_temp_1 GF@prec_var_temp_2 GF@prec_var_temp_1\nLABEL $END_GTEQ"[i]);
            } 
            char tmp119c[100];
            sprintf(tmp119c, "%d", skip_counter);
            for(unsigned int i = 0; i < strlen(tmp119c); i++){
                add_char_to_str(str, tmp119c[i]);
            }
            for(unsigned int i = 0; i < strlen("\nPUSHS GF@prec_var_temp_1\n"); i++){
                add_char_to_str(str,  "\nPUSHS GF@prec_var_temp_1\n"[i]);
            }   
            skip_counter++;
            break;
        }

    default:
        break;
    }
}
//fixed
void pop_retval(struct dynamic_string *str){  
    if(flag_while == 0)
    {
        fprintf(stdout, "POPS GF@retval\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("POPS GF@retval\n"); i++){
            add_char_to_str(str,  "POPS GF@retval\n"[i]);
        } 
    }
}
//fixed
void inputf_call(struct dynamic_string *str){
   if(flag_while == 0)
    {
        printf("CALL $inputf\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("CALL $inputf\n"); i++){
            add_char_to_str(str,  "CALL $inputf\n"[i]);
        } 
    }
   
}
//fixed
void inputi_call(struct dynamic_string *str){
   if(flag_while == 0){
        // fprintf(stdout, "CREATEFRAME\n");
        printf("CALL $inputi\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("CALL $inputi\n"); i++){
            add_char_to_str(str,  "CALL $inputi\n"[i]);
        } 
    }
  
}
//fixed
void inputs_call(struct dynamic_string *str){   
    if(flag_while == 0)
    {
        printf("CALL $inputs\n");
    }
    else
    {
        for(unsigned int i = 0; i < strlen("CALL $inputs\n"); i++){
            add_char_to_str(str,  "CALL $inputs\n"[i]);
        } 
    }

}