#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "../errors.h"
#include "../dynamic_string/dynamic_string.h"
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
        fprintf(stdout, "---------------------------------------\nThere is no input file. Rerun with file\n ---------------------------------------\n");
        return ERR_INTERNAL;
    }

    int state = SCANNER_START;    

    // string to wretting down attribute
    char *str = (char *)malloc(DEF_STR_SIZE);
    if (!str){
        fprintf(stdout, "---------------------------\nError in allocating memory!\n ---------------------------\n");
        return ERR_INTERNAL;
    }

    int c;

    while(42){
        c = (char) getc(file);
        if (feof(file)){
            token->type = TOKEN_EOF;
        }
        // switch (state)
        // {
        // case SCANNER_START:
            if((isalpha(c)) || (c == '_')){
                /* countinue to read to any white space charectare
                   then copy string to token atrribute
                */
                //add_char_to_str(); // TODO
                state = SCANNER_ID;
                printf("ALPHABET\n");
                // break;
            }
            else if (c == '\n'){
                /* new line*/
                state = SCANNER_EOL;
                printf("EOL\n");
            }
            else if(c == '\''){
                state = SCANNER_STRING;
                printf("BEGIG STRING\n");
            }       
            else if (c == '\"'){
                state = SCANNER_BLOCK_STRING_BEGIN;
            }     
            else if (isdigit(c)){
                if (c == '0'){
                    state = SCANNER_HEX_OR_FLOAT;
                    printf("ZERO\n");
                }
                else
                {
                 //   add_char_to_str(str, c);
                    state = SCANNER_INT_OR_FLOAT;
                }
            // }
        }
    }
    // printf("TOKEN: %s\n", str);
    free(str);
    return SCANNER_OK;
}
/*
void check_kw_or_id(char *str, token_ptr token){
    if (strcmp(str, "define"))
    {
        token->attribute.key_word = _DEF_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "else"))
    {
        token->attribute.key_word = _ELSE_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "if"))
    {
        token->attribute.key_word = _IF_;
        token->type = TOKEN_KEY_WORD;
    }
    else if (strcmp(str, "none"))
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
}*/