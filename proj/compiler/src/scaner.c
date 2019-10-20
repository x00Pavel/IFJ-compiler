#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "errors.h"
#include "scaner.h"

#define DEF_STR_SIZE 8

#define SCANNER_OK    0  // Read sucsessful 
#define SCANNER_START 10 // Scaner begin to work 
#define SCANER_STOP   11 // Scaner read one token 
#define SCANNER_STRING 12 // Begining of string
#define SCANNER_EOL   13 // Reade end of line
#define SCANNER_ID    14 // It is a identifire or keyword
#define SCANNER_INT_OR_FLOAT 15
#define SCANNER_BLOCK_STRING_BEGIN 16
#define SCANNER_BLOCK_STRING_START 17
#define SCANNER_OUT_BLOCK_1 18
#define SCANNER_OUT_BLOCK_2 19
#define SCANNER_HEX_OR_FLOAT 20
#define SCANER_FINISH 100 // Scaner readed last token 

void make_token(char *str, token_ptr ptr);

char *key_word_arr[] = {"def", "else", "if", "none", "pass", "return", "while"};

void realloc_string(char *str){
    size_t prev_size = strlen(str) * sizeof(char) ;

    char *string = (char *) realloc( str, prev_size + DEF_STR_SIZE);    
    (void) (string);
}

int scanner(FILE *file,token_ptr token){
    
    if (!file){
        fprintf(stdout, "---------------------------------------\n\\
                         There is no input file. Rerun with file\n\\
                         ---------------------------------------\n");
        return ERR_INTERNAL;
    }

    int state = SCANNER_START;    

    // string to wretting down attribute
    char *str = (char *)malloc(DEF_STR_SIZE);
    if (!str){
        fprintf(stdout, "---------------------------\n\\
                         Error in allocating memory!\n\\
                         ---------------------------\n");
        return ERR_INTERNAL;
    }

    char c;

    for(;;){
        c = (char) getc(file);

        switch (state)
        {
        case SCANNER_START:
            if((isalpha(c)) || (c == '_')){
                /* countinue to read to any white space charectare
                   then copy string to token atrribute
                */
               add_char_to_str(); // TODO
               state = SCANNER_ID;
               break;
            }
            else if (c == "\n"){
                /* new line*/
                state = SCANNER_EOL;
            }
            else if(c == "\'"){
                state = SCANNER_STRING;
            }       
            else if (c == "\""){
                state = SCANNER_BLOCK_STRING_BEGIN;
            }     
            else if (isdigit(c)){
                if (c == "0"){
                    state = SCANNER_HEX_OR_FLOAT;
                }
                else
                {
                    add_char_to_str(str, c);
                    state = SCANNER_INT_OR_FLOAT;
                }
            }
            else if(c == "{"){

            }

            break;
        case SCANNER_BLOCK_STRING_BEGIN:
            if (c == "\""){
                state = SCANNER_BLOCK_STRING_START;
            }
            break;
        case SCANNER_BLOCK_STRING_START:
            if (c == "\""){
                // process the string
                while ((c = (char)getc(file)) !="\""){
                    // add escape atd
                    if (c != '#'){
                        add_char_to_string(str, c);
                    }
                }
                state = SCANNER_OUT_BLOCK_1;
            }
            else{
                free(str);
                return ERR_SYNTAX;
            }
            break;            
        case SCANNER_OUT_BLOCK_1:
            if (c == "\""){
                state = SCANNER_OUT_BLOCK_2;
            }
            else{
                free(str);
                return ERR_SYNTAX;
            }
            break;
        case SCANNER_OUT_BLOCK_2:
            if(c == "\"")
            {
                strcpy(token->attribute.string, str);
                free(str);
                token->type = TOKEN_STRING;
                return SCANNER_OK;
            }
            else
            {   
                free(str);
                return ERR_SYNTAX;
            }

            
        case SCANNER_STRING:
            while ((c = (char) getc(file)) != '\''){
                // add escape atd
                if (c != '#'){
                    add_char_to_string(str, c);
                }
            }
            strcpy(token->attribute.string, str); 
            token->type = TOKEN_STRING;
            free(str);
            return SCANNER_OK;
        case SCANNER_ID:
            /* choose if it identifire or keyword */        
                /* countinue to read to any white space charectare
                   then copy string to token atrribute
                */
            if((isalpha(c)) || (c == "_") || (isdigit(c))){
                add_char_to_string(str, c);
            }
            else{
                ungetc(c, file);
                check_kw_or_id(str, token);     
                return SCANNER_OK;           
            }
        case SCANNER_HEX_OR_FLOAT:
            if ((c == "x") || (c == "X")){
                while ((c = (char) getc(file)) != ' '){
                    if ((c > 47 && c < 58) || (c > 64 && c < 71) || (c > 96 && c < 103)){
                        add_char_to_str(str, c);
                    }
                    else{
                        free(str);
                        return ERR_SYNTAX;
                    }
                }
                strcpy(token->attribute.string, str);
                token->type = TOKEN_HEX;
                free(str);
                return SCANNER_OK;
            }
            else if (c == "."){
                add_char_to_str(str, "0.");
                while ((c = (char)getc(file)) != ' ')
                {
                    if ((c > 47) && (c < 58)){
                        add_char_to_str(str, c);
                    }
                    else
                    {
                        free(str);
                        return ERR_SYNTAX;
                    }
                }
                token->attribute.float_val = atof(str);
                token->type = TOKEN_FLOAT;
                free(str);
                return SCANNER_OK;
            }
            else
            {
                free(str);
                return ERR_SYNTAX;
            }
            break;
        case SCANNER_INT_OR_FLOAT:
            bool flt = false;
            if(c == ' '){
                strcpy(token->attribute.string, str);
                free(str);
                token->type = TOKEN_INT;
                return SCANNER_OK;
            }
            do{
                if ((c == '.') && (flt == false)){
                    flt = true;
                }
                else if (!(c > 47 && c < 58)){
                    free(str);
                    return ERR_SYNTAX;
                } 
                add_char_to_str(str, c);
            } while ((c = (char)getc(file)) != ' ');
            if(flt == false){
                token->type = TOKEN_INT;
            }
            else{
                token->type = TOKEN_FLOAT;
            }
            strcpy(token->attribute.string, str);
            free(str);
            return SCANNER_OK;
            break;
        
        default:
            break;
        }
    }

    printf("TOKEN: %s\n", str);
    free(str);
    return SCANNER_OK;
}

void check_kw_or_id(char *str, token_ptr token){
    if (strcmp(str, "define"))
    {
        token->attribute.key_word = _DEF_;
        token->type = TOKEN_KEY_WORD;
    }
    if (strcmp(str, "else"))
    {
        token->attribute.key_word = _ELSE_;
        token->type = TOKEN_KEY_WORD;
    }
    if (strcmp(str, "if"))
    {
        token->attribute.key_word = _IF_;
        token->type = TOKEN_KEY_WORD;
    }
    if (strcmp(str, "none"))
    {
        token->attribute.key_word = _NONE_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "pass"))
    {
        token->attribute.key_word = _PASS_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "return"))
    {
        token->attribute.key_word = _RETURN_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "while"))
    {
        token->attribute.key_word = _WHILE_;
        token->type = TOKEN_KEY_WORD;
    }
    else {
        token->type = TOKEN_ID;
        token->attribute.string = str;
    }
}

void make_token(char *str, token_ptr ptr) {
    //types of token
    for (int i = 0; i < 22; i++)
    {
        if (strcmp(str, "+"))
        {
            ptr->type = TOKEN_SUM;
        }
        if (strcmp(str, "*"))
        {
            ptr->type = TOKEN_MULTIPLY;
        }
        if (strcmp(str, "/"))
        {
            ptr->type = TOKEN_DIVISION;
        }
        if (strcmp(str, "="))
        {
            ptr->type = TOKEN_ASSIGN;
        }
        if (strcmp(str, "=="))
        {
            ptr->type = TOKEN_EQUAL;
        }
        if (strcmp(str, "!="))
        {
            ptr->type = TOKEN_NOT_EQUAL;
        }
        if (strcmp(str, ">")){
            ptr->type = TOKEN_GREATER;
        }
        if (strcmp(str, "<"))
        {
            ptr->type = TOKEN_LESS;
        }
        if (strcmp(str, ">="))
        {
            ptr->type = TOKEN_GREATER_EQ;
        }
        if (strcmp(str, "<="))
        {
            ptr->type = TOKEN_LESS_EQ;
        }
        if (strcmp(str, "\n"))
        {
            ptr->type = TOKEN_EOL;
        }
        if (strcmp(str, " "))
        {
            ptr->type = TOKEN_EMPTY;
        }
        if (strcmp(str, "("))
        {
            ptr->type = TOKEN_L_BRACKET;
        }
        if (strcmp(str, ")"))
        {
            ptr->type = TOKEN_R_BRACKET;
        }
        if (strcmp(str, "."))
        {
            ptr->type = TOKEN_DOT;
        }
        if (strcmp(str, ","))
        {
            ptr->type = TOKEN_COMA;
        }
        if (strcmp(str, ";"))
        {
            ptr->type = TOKEN_SEMICOLON;
        }
        // check if it is STRING
        if ((str[0] == 0x24) ||
            ((str[0] == 0x22) &&
             (str[1] == 0x22) &&
             (str[2] == 0x22))){
                ptr->type = TOKEN_STRING;
                // if string must end with \0 or \n or someting else?
                ptr->attribute.string = str;
        }
        // check if it is INT or FLOAT
        // if (&str){

        // }
        if (*str == EOF)
        {
            ptr->type = TOKEN_EOF;
        }
        //at , asi podarzi se nam tento kus kodu zoptimizovat
    }
}
