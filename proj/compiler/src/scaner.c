#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "errors.h"
#include "dynamic_string.h"
#include "scaner.h"

#define TOKEN_READY 0      // Read sucsessful
#define SCANNER_START 10  // Scaner begin to work
#define SCANER_STOP 11    // Scaner read one token
#define SCANNER_STRING 12 // Begining of string
#define SCANNER_EOL 13    // Reade end of line
#define SCANNER_ID 14     // It is a identifire or keyword
#define SCANNER_INT_OR_FLOAT 15
#define SCANNER_BLOCK_STRING_BEGIN 16
#define SCANNER_BLOCK_STRING_START 17
#define SCANNER_OUT_BLOCK_1 18
#define SCANNER_OUT_BLOCK_2 19
#define SCANNER_HEX_OR_FLOAT 20
#define SCANNER_COMMENT 21
#define SCANNER_EOF 100 // Scaner readed last token

// void make_token(char *str, token_s *ptr);

char *key_word_arr[] = {"def", "else", "if", "none", "pass", "return", "while"};

int get_token(FILE *file, struct token_s* token)
{

    if (!file)
    {
        fprintf(stdout, "---------------------------------------\nThere is no input file. Rerun with file\n ---------------------------------------\n");
        return ERR_INTERNAL;
    }

    // string to wretting down attribute
    struct dynamic_string *str;
    str = (dynamic_string_ptr)malloc(sizeof(struct dynamic_string));
    if (str == NULL)
    {
        fprintf(stdout, "---------------------------\nError in allocating memory!\n---------------------------\n");
        return ERR_INTERNAL;
    }

    str->str = (string)malloc(DEF_STR_SIZE);
    if (!str->str)
    {
        fprintf(stdout, "---------------------------\nError in allocating memory!\n---------------------------\n");
        return ERR_INTERNAL;
    }
    str->size = DEF_STR_SIZE;
    str->len = 0;

    int state = SCANNER_START;

    int c;
    while (state != SCANNER_EOF)
    {
        c = getc(file);

        if (feof(file))
        {
            printf("EOF\n");
            // token->type = TOKEN_EOF;        
            state = SCANNER_EOF;
        }
        switch (state){
        case SCANNER_START:
            if (c == '#')
            {
                printf("comment\n");
            }
            else if (isalpha(c))
            {
                add_char_to_str(str, c);
                state = SCANNER_ID;
            }
            else if (isdigit(c))
            {
                printf("is digit\n");
                add_char_to_str(str, c);
                state = SCANNER_INT_OR_FLOAT;
                ungetc(c, file);
            }
            break;
        case SCANNER_ID:
            if(isalpha(c) || (c == '_') || (isdigit(c))){
                add_char_to_str(str, c);
            }
            else{
                printf("%s\n", str->str);
                if (strcmp(str->str, "while") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _WHILE_;
                }
                else if (strcmp(str->str, "define") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _DEF_;
                }
                else if (strcmp(str->str, "else") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _ELSE_;
                }
                else if(strcmp(str->str, "none") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _NONE_;
                }
                else if(strcmp(str->str, "pass") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _PASS_;
                }
                else if(strcmp(str->str, "return") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _RETURN_;
                }
                else{
                    token->type = TOKEN_ID;
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
                }
                free(str->str);
                free(str);
                return TOKEN_READY;
            }
            break;
        case SCANNER_INT_OR_FLOAT:
            /*
            
            ДОДЕЛАТЬ ОБРАБОТКУ ЧИСЕЛ. ОСОБЕННО ПОДУМАТЬ НАД FLOAT ЧИСЛАМИ
            
            */
            // if zero, then it can be only float number
            if(c == '0'){
                c = getc(file);
                if(c == '0'){
                    printf("ERROR. In the begining of number cant be more then one\n");
                    return ERR_LEXER;
                }
                else if ((c == '.') || (c == 'E') || (c == 'e') ){
                    add_char_to_str(str, c);
                }
            //
            else{

            }
                
            }            
            break;
        default:
            break;
        }
        
        
    }

    // printf("HERE\n");
    free(str->str);
    free(str);
    return -1;
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