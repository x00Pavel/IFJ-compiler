#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "errors.h"
#include "dynamic_string.h"
#include "scaner.h"
#include "./stack/c202.h"


#define SCANNER_START 10  // Scanner begin to work
#define SCANNER_STOP 11    // Scanner read one token
#define SCANNER_STRING 12 // Begining of string
#define SCANNER_EOL 13    // Reade end of line
#define SCANNER_ID 14     // It is a identifier or keyword
#define SCANNER_INT_OR_FLOAT 15
#define SCANNER_BLOCK_STRING_BEGIN 16
#define SCANNER_BLOCK_STRING_START 17
#define SCANNER_OUT_BLOCK_1 18
#define SCANNER_OUT_BLOCK_2 19
#define SCANNER_FLOAT 20
#define SCANNER_EXP 21
#define SCANNER_COMMENT 22
#define SCANNER_INT 23 
#define SCANNER_WHITE_SPACE 24
#define SCANNER_EOF 100 // Scanner read last token

/* Macros for freeing resources*/
#define FREE_ALL(...)                                      \
    do                                                     \
    {                                                      \
        unsigned int i = 0;                                \
        void *pta[] = {__VA_ARGS__};                       \
        for (i = 0; i < sizeof(pta) / sizeof(void *); i++) \
        {                                                  \
            free(pta[i]);                                  \
        }                                                  \
    } while (0)

char *key_word_arr[] = {"def", "else", "if", "none", "pass", "return", "while"};

/* Macros for log*/
#define SLOG(msg, ret_code) \
    _log(stdout, __FILE__, __LINE__, msg);\
    return ret_code

inline void _log(FILE *fd, char *file, int line, char *msg){
    fprintf(fd, "%s:%d %s\n", file, line, msg);
}

int get_token(FILE *file, struct token_s* token, tStack *stack)
{

    if (!file){
        SLOG("There is no input file.Rerun with file", ERR_INTERNAL);
    }

    // string to writing down attribute
    struct dynamic_string *str;
    str = (dynamic_string_ptr)malloc(sizeof(struct dynamic_string));
    if (str == NULL)
    {
        SLOG("Error in allocating memory!", ERR_INTERNAL);
    }

    str->str = (string)malloc(DEF_STR_SIZE);
    if (!str->str)
    {
        FREE_ALL(str);
        SLOG("Error in allocating memory!", ERR_INTERNAL);
    }
    str->size = DEF_STR_SIZE;
    str->len = 0;

    int state = SCANNER_START; 
    bool first_token = true;
    int c; // for symbol
    int space_cnt = 0;
     
    while (state != SCANNER_EOF)
    {
        c = getc(file);

        if (feof(file)){
            printf("EOF\n");
            token->type = TOKEN_EOF;        
            state = SCANNER_EOF;
        }
        switch (state){
        case SCANNER_START:
            if (c == '#'){
                printf("comment\n");
                first_token = false;
            }
            else if (isalpha(c)){
                add_char_to_str(str, c);
                state = SCANNER_ID;
                first_token = false;
            }
            else if (isdigit(c)){
                printf("is digit\n");
                state = SCANNER_INT_OR_FLOAT;
                ungetc(c, file);
                first_token = false;
            }
            else if(c == '\n'){
                if(!first_token){
                    token->type = TOKEN_EOL;
                    state = SCANNER_START;
                    FREE_ALL(str->str, str);
                    return OK;
                }
                else{
                    state = SCANNER_START;
                }
            }
            else if(c == ' '){
                if(first_token){
                    // наверное надо заполнить в табулку с одсазеним??
                    state = SCANNER_WHITE_SPACE;
                }
                else{
                    state = SCANNER_START;
                }
            }
            else if(c == '('){
                
            }
            break;
        case SCANNER_ID:
            if(isalpha(c) || (c == '_') || (isdigit(c))){
                add_char_to_str(str, c);
            }
            else{
                ungetc(c, file);
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
                FREE_ALL(str->str, str);
                return OK;
            }
            break;
        case SCANNER_INT_OR_FLOAT:
            // if zero, then it can be only float number, or 0 as integer
            if(c == '0'){
                c = getc(file);
                if (c == '.'){
                    add_char_to_str(str, '0');
                    add_char_to_str(str, c);
                    state = SCANNER_FLOAT;
                }
                else if ((c == 'E') || (c == 'e')){
                    add_char_to_str(str, '0');
                    add_char_to_str(str, c);
                    state = SCANNER_EXP;
                }
                else if (c == '0'){
                    FREE_ALL(str->str, str);
                    SLOG("ERROR. In the begining of number cant be more then one", ERR_LEXER);
                }
            }            
            else{
                add_char_to_str(str, c);
                state = SCANNER_INT;
            }
            break;
        case SCANNER_INT:
            if(isdigit(c)){
                add_char_to_str(str,c);
            }
            else if (c == '.'){
                add_char_to_str(str, c);
                state = SCANNER_FLOAT;
            }
            else if ((c == 'E') || (c == 'e')){
                add_char_to_str(str,c);
                state = SCANNER_EXP;
            }
            else{
                ungetc(c,file);
                int num = atoi(str->str);
                // проверка на правильность выполнения перевода на инт
                token->attribute.int_val = num;
                token->type = TOKEN_INT;
                FREE_ALL(str->str, str);
                return OK;
            }
            break;
        case SCANNER_FLOAT:
            if (isdigit(c)){
                add_char_to_str(str, c);
            }
            else if((c == 'e') || (c == 'E')){
                add_char_to_str(str, c);
                state = SCANNER_EXP;
            }
            else{
                ungetc(c, file);
                token->attribute.float_val = strtof(str->str, NULL);
                token->type = TOKEN_FLOAT;
                FREE_ALL(str->str, str);
                return OK;
            }
            break;
        case SCANNER_EXP:
            if((c == '-') || (c == '+')){
                add_char_to_str(str, c);
            }
            else if(isdigit(c)){
                add_char_to_str(str, c);
            }
            else{
                ungetc(c, file);
                token->attribute.float_val = strtof(str->str, NULL);
                token->type = TOKEN_FLOAT;
                FREE_ALL(str->str, str);
                return OK;
            }
            break;
        case SCANNER_WHITE_SPACE:
            if(c == '\n'){
                state = SCANNER_START;
            }
            else if(c == ' '){
                space_cnt++;
                state = SCANNER_WHITE_SPACE;
            }
            else{
                // INDENT OR DEDEND
                first_token = false;
                if(space_cnt > stackTop(stack)){
                    // INDEND
                    stackPush(stackPush, space_cnt);
                    // token->type = TOKEN_INDEND;

                }
                else if (space_cnt < stackTop(stack)){
                    // DEDEND
                    while (stackTop(stack) != 0){
                        stackPop(stack);
                        if(stackTop(stack) == space_cnt){
                            // we found same level 
                            token->type = TOKEN_DEDEND;
                            state = SCANNER_START;
                            break; // or return?
                        }
                    }
                    // in case if there is now same offset
                    FREE_ALL(str->str, str);
                    SLOG("Error. Wrong count of spaces!", ERR_SYNTAX);
                }
                state = SCANNER_START;
            }
            break;
        default:
            state = SCANNER_START;
            break;
        }
        
        
    }

    // printf("HERE\n");
    FREE_ALL(str->str, str);
    return -1;
}
