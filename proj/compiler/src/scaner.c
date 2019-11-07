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
#define SCANNER_LESS_GREATER 25
#define SCANNER_ASSIGN 26
#define SCANNER_NOT 27
#define SCANNER_BRACKET 28
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
    _log(stdout, __FILE__, __LINE__, msg, ret_code);\

inline int _log(FILE *fd, char *file, int line, char *msg, int ret_code){
    fprintf(fd, "%s:%d %s\n", file, line, msg);
    return ret_code;
}

typedef struct stack tStack;

int get_token(FILE *file, struct token_s **token, tStack *stack)
{

    if (!file){
        SLOG("There is no input file.Rerun with file", ERR_INTERNAL);
    }

    // string to writing down attribute
    struct dynamic_string *str;
    str_init(&str);
       
    int state = SCANNER_START;
    static bool first_token = true;
    static int double_quot = 0;
    static int count_of_quot = 0;
    int c; // for symbol
    int space_cnt = 0;
     
    while (state != SCANNER_EOF)
    {
        c = getc(file);

        if (feof(file)){
                (*token)->type = TOKEN_EOF;
                state = SCANNER_EOF;
            
        }

        switch (state){
        case SCANNER_START:
            if(c == ' '){
                if(first_token){
                    state = SCANNER_WHITE_SPACE;
                    space_cnt++;
                }
                else{
                    state = SCANNER_START;
                }
                break;
            }
            else if (first_token){
                /* If it is a new line and previous was INDEND*/
                if((stackTop(stack) != 0) && (c != '\n' && c != '\r')){
                    ungetc(c, file);
                    stackPop(stack);
                    (*token)->type = TOKEN_DEDEND;
                    str_clean(str);
                    return OK;
                }
            }

            if (c == '#'){
                state = SCANNER_COMMENT;
            }
            else if (isalpha(c)){
                add_char_to_str(str, c);
                state = SCANNER_ID;
                first_token = false;
                break;
            }
            else if (isdigit(c)){
                state = SCANNER_INT_OR_FLOAT;
                ungetc(c, file);
                first_token = false;
                break;
            }
            else if((c == '\n') || (c == '\r') ){
                if(!first_token){
                    (*token)->type = TOKEN_EOL;
                    state = SCANNER_START;
                    first_token = true;
                    str_clean(str);
                    return OK;
                }
                else{
                    state = SCANNER_START;
                }
                break;
            }
            else if (c == '\''){
                state = SCANNER_STRING;
                break;
            }
            else if (c == '"'){
                state = SCANNER_BLOCK_STRING_BEGIN;
                ungetc(c, file);
                break;
            }
            else if (c == '<' || c == '>'){
                state = SCANNER_LESS_GREATER;
                ungetc(c, file);
                break;
            }
            else if (c == '='){
                state = SCANNER_ASSIGN;
                break;
            }
            else if (c == '+'){
                (*token)->type = TOKEN_SUM;
                str_clean(str);
                return OK;
            }
            else if (c == '-'){
                (*token)->type = TOKEN_MINUS;
                str_clean(str);
                return OK;
            }
            else if (c == '*') {
                (*token)->type = TOKEN_MULTIPLY;
                str_clean(str);
                return OK;
            }
            else if (c == '/'){
                (*token)->type = TOKEN_DIVISION;
                str_clean(str);
                return OK;
            }
            else if (c == ':'){
                (*token)->type = TOKEN_DDOT;
                str_clean(str);
                return OK;
            }
            else if (c == '!'){
                state = SCANNER_NOT;
                break;
            }
            else if (c == '(' || c == ')'){
                state = SCANNER_BRACKET;
                ungetc(c, file);
                break;
            }
            

            break;
        case SCANNER_ID:
            if(isalpha(c) || (c == '_') || (isdigit(c))){
                if(!add_char_to_str(str, c)){
                    return ERR_INTERNAL;
                }
            }
            else{
                ungetc(c, file);
                if (strcmp(str->str, "while") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _WHILE_;
                }
                else if (strcmp(str->str, "define") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _DEF_;
                }
                else if (strcmp(str->str, "else") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _ELSE_;
                }
                else if(strcmp(str->str, "none") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _NONE_;
                }
                else if(strcmp(str->str, "pass") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _PASS_;
                }
                else if(strcmp(str->str, "return") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _RETURN_;
                }
                else if(strcmp(str->str, "if") == 0){
                    (*token)->type = TOKEN_KEY_WORD;
                    (*token)->attribute.key_word = _IF_;
                }
                else{
                    (*token)->type = TOKEN_ID;
                    (*token)->attribute.string = (char *)malloc(str->size);
                    strncpy((*token)->attribute.string, str->str, str->size);
                }
                
                str_clean(str);
                state = SCANNER_START;
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
                else if (isdigit(c)){
                    FREE_ALL(str->str, str);
                    SLOG("ERROR. In the begining of number cant be more then one", ERR_LEXER);
                }
                else{
                    ungetc(c,file);
                    add_char_to_str(str, '0');
                    state = SCANNER_INT;
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
                (*token)->attribute.int_val = num;
                (*token)->type = TOKEN_INT;
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
                (*token)->attribute.float_val = strtof(str->str, NULL);
                (*token)->type = TOKEN_FLOAT;
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
                (*token)->attribute.float_val = strtof(str->str, NULL);
                (*token)->type = TOKEN_FLOAT;
                FREE_ALL(str->str, str);
                return OK;
            }
            break;
       
        case SCANNER_WHITE_SPACE:
            if(c == '\n' || c == '\r'){
                space_cnt = 0;
                state = SCANNER_START;
            }
            else if(c == ' '){
                space_cnt++;
                state = SCANNER_WHITE_SPACE;
                break;
            }
            else{
                ungetc(c,file);
                // INDENT OR DEDEND
                first_token = false;
                if(space_cnt > stackTop(stack)){
                    // INDEND
                    // printf("TOKEN INDEND\n");
                    stackPush(stack, space_cnt);
                    (*token)->type = TOKEN_INDEND;
                    state = SCANNER_START;
                    str_clean(str);
                    return OK;
                }
                else if (space_cnt < stackTop(stack)){
                    // DEDEND
                    bool found =  false;
                    while (stackTop(stack) != 0){
                        stackPop(stack); 
                        if(stackTop(stack) == space_cnt){
                            printf("TOKEN DEDEND\n");
                            // we found same level 
                            (*token)->type = TOKEN_DEDEND;
                            state = SCANNER_START;
                            found = true;
                            break;
                        }
                    }
                    if (!found){
                        // in case if there is no same offset
                        str_clean(str);
                        state = SCANNER_START;
                        printf("Wrong offset\n");
                        return ERR_LEXER;
                    }
                    else{
                        state = SCANNER_START;
                        str_clean(str);
                        return OK;
                    }
                }                
            }
            state = SCANNER_START;
            break;   
        case SCANNER_STRING:
            if (c == '\''){
                (*token)->type = TOKEN_STRING;
                (*token)->attribute.string = (char *)malloc(str->size);
                strncpy((*token)->attribute.string, str->str, str->size);
                str_clean(str);
                state = SCANNER_START;
                return OK;
            }
            else if (c == '\n'){
                str_clean(str);
                str_clean(str);
                SLOG("ERROR. String must be in one line!", ERR_LEXER);
            }
            else{
                add_char_to_str(str, c);
            }
            break;
        case SCANNER_BLOCK_STRING_BEGIN:
            if (c == '"' && double_quot < 3 && count_of_quot < 2 ){
                double_quot++;
                if(double_quot == 3){
                    count_of_quot++;
                }
            }
            else if(c != '"' && (double_quot == 3 || double_quot == 0)){  
                double_quot = 0;
                if(count_of_quot < 2){
                    if(c != '\n' && c != '\r')
                        add_char_to_str(str, c);
                }
                else{
                    count_of_quot = 0;
                    ungetc(c,file);
                    (*token)->type = TOKEN_STRING;
                    // printf("%s\n", str->str);
                    (*token)->attribute.string = (char *)malloc(str->size);
                    // printf("%s\n", (*token)->attribute.string);
                    strncpy((*token)->attribute.string, str->str, str->size);
                    str_clean(str);
                    state = SCANNER_START;
                    return OK;
                }
            }
            else{
                FREE_ALL(str->str, str);
                SLOG("ERROR. Block string must start from '\"\"\"' !", ERR_LEXER);
            }
            break;
        case SCANNER_COMMENT:
            if (c == '\n'){
                first_token = true;
                state = SCANNER_START;
            }
            break;
        case SCANNER_LESS_GREATER:
            if (c == '>'){
                (*token)->type = TOKEN_GREATER;
            }
            else{
                (*token)->type = TOKEN_LESS;
            }
            c = getc(file);
            if (c == '='){
                (*token)->type += 2; // look to scaner.h
            }
            else{
                ungetc(c, file);
            }
            
            str_clean(str);
            state = SCANNER_START;
            return OK;
            break;
        case SCANNER_ASSIGN:
            if(c == '='){
                (*token)->type = TOKEN_EQUAL;
            }
            else{
                ungetc(c,file);
                (*token)->type = TOKEN_ASSIGN;
            }
            FREE_ALL(str->str, str);
            state = SCANNER_START;
            return OK; 
            break;
        case SCANNER_NOT:
            if(c == '='){
                (*token)->type = TOKEN_NOT_EQUAL;
                if(str->str != NULL){
                    FREE_ALL(str->str, str);
                } 
                else{
                    FREE_ALL(str);
                }
                state = SCANNER_START;
                return OK; 
            }
            else{
                FREE_ALL(str->str, str);
                SLOG("ERROR. After '!' can be only '=' !", ERR_LEXER);
            }
            break;
        case SCANNER_BRACKET:
            if(c == '('){
                (*token)->type = TOKEN_L_BRACKET;
            }
            else if (c == ')'){
                (*token)->type = TOKEN_R_BRACKET;
            }
            
            if(str->str != NULL){
                FREE_ALL(str->str, str);
            } 
            else{
                FREE_ALL(str);
            }
            state = SCANNER_START;
            return OK; 
            break;
        case SCANNER_EOF:
            break;
        default:
            state = SCANNER_START;
            break;
        }
    }

    FREE_ALL(str->str, str);
    return -1;
}
