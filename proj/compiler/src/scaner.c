#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "errors.h"
#include "scaner.h"

#define DEF_STR_SIZE 8

void realloc_string(const char *str){
    size_t prev_size = strlen(str) * sizeof(char) ;

    char *string = (char *) realloc(str, prev_size + DEF_STR_SIZE);    
}

void create_token_kw(char *str, token_ptr ptr, int *i){
    ptr->type = TOKEN_KEY_WORD;
    ptr->attribute.key_word = i;
}

void make_token(char *str, int *c, token_ptr ptr) {

    // check if it is keyword    
    for (int i = 0; i < 7; i++){ 
        if (strcmp(*str, *key_word_arr[i])){
            create_token_kw(str, ptr, &i); 
        }
    }
    // other types of token
    for (int i = 0; i < 22; i++)
    {
        if (strcmp(*str, "+"))
        {
            ptr->type = TOKEN_SUM;
        }
        if (strcmp(*str, "*"))
        {
            ptr->type = TOKEN_MULTIPLY;
        }
        if (strcmp(*str, "/"))
        {
            ptr->type = TOKEN_DIVISION;
        }
        if (strcmp(*str, "="))
        {
            ptr->type = TOKEN_ASSIGN;
        }
        if (strcmp(*str, "=="))
        {
            ptr->type = TOKEN_EQUAL;
        }
        if (strcmp(*str, "!="))
        {
            ptr->type = TOKEN_NOT_EQUAL;
        }
        if (strcmp(*str, ">"))
        {
            ptr->type = TOKEN_GREATER;
        }
        if (strcmp(*str, "<"))
        {
            ptr->type = TOKEN_LESS;
        }
        if (strcmp(*str, ">="))
        {
            ptr->type = TOKEN_GREATER_EQ;
        }
        if (strcmp(*str, "<="))
        {
            ptr->type = TOKEN_LESS_EQ;
        }
        if (strcmp(*str, "\n"))
        {
            ptr->type = TOKEN_EOL;
        }
        if (strcmp(*str, " "))
        {
            ptr->type = TOKEN_EMPTY;
        }
        if (strcmp(*str, "("))
        {
            ptr->type = TOKEN_L_BRACKET;
        }
        if (strcmp(*str, ")"))
        {
            ptr->type = TOKEN_R_BRACKET;
        }
        if (strcmp(*str, "."))
        {
            ptr->type = TOKEN_DOT;
        }
        if (strcmp(*str, ","))
        {
            ptr->type = TOKEN_COMA;
        }
        if (strcmp(*str, ";"))
        {
            ptr->type = TOKEN_SEMICOLON;
        }
        // check if it is STRING
        if ((str[0] == "'") || 
            ((str[0] == "\"") && 
             (str[1] == "\"") && 
             (str[2] == "\""))){
                ptr->type = TOKEN_STRING;
                // if string must end with \0 or \n or someting else?
                ptr->attribute.string = str;
        }
        // check if it is INT or FLOAT
        if (strcmp(*str, "EOF"))
        {
            ptr->type = TOKEN_EOF;
        }
        //at , asi podarzi se nam tento kus kodu zoptimizovat
    }
}


void scanner(FILE *file,token_ptr ptr){
    
    // string to wretting down attribute
    char *str = (char *)malloc(DEF_STR_SIZE);
    if (!str){
        sprintf(stdout, "Error in allocating memory!\n");
        return ERR_INTERNAL;
    }

    // MAX length of allocated string 
    size_t max_len = DEF_STR_SIZE * sizeof(char);
    int c;
    for (int i = 0; (c = getchar()) != ' ' || c != '\n'; i++){
        if (i + 1 == max_len){
            realloc_string(str);
            if (!str){
                sprintf(stdout, "Error in allocating memory!\n");
                return ERR_INTERNAL;
            }
        }
        str[i] = c;
    }
    make_token(str, &c, ptr);
    //scaner(str);
}