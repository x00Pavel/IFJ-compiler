#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "errors.h"
#include "dynamic_string.h"
#include "scaner.h"
<<<<<<< Updated upstream
=======
#include "./stack/c202.h"
>>>>>>> Stashed changes

#define TOKEN_READY 0      // Read successful
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
<<<<<<< Updated upstream
#define SCANNER_EQUAL 27
#define SCANNER_SUM_MINUS_MULTIPLY_DIVISION_DDOT 28
#define SCANNER_NONE 29
#define SCANNER_BRACKET 30
=======
#define SCANNER_NOT 27
#define SCANNER_BRACKET 28
>>>>>>> Stashed changes
#define SCANNER_EOF 100 // Scanner read last token

/* Macros for freeing resources*/
#define FREE_ALL(...)                                      \
    do                                                     \
    {                                                      \
        unsigned int i = 0;                                         \
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

int get_token(FILE *file, struct token_s* token)
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
    static bool first_token = true;
    static int double_quot = 0;
    static int count_of_quot = 0;
    int c;
<<<<<<< Updated upstream
    while (state != SCANNER_EOF)
    {
        c = getc(file);
        printf("c: %c\n", c);
        //printf("c: %d\n", c);
        // printf("state: %d\n", state);
        // printf("first_token: %d\n", first_token);
=======
    int space_cnt = 0;
    while (state != SCANNER_EOF)
    {
        c = getc(file);
        //printf("c: %c\n", c);
        //printf("c: %d\n", c);
        // printf("state: %d\n", state);
        //printf("first_token: %d\n", first_token);
        //printf("space_cnt: %d\n", space_cnt);
        //printf("stackTop: %d\n", stackTop(stack));
>>>>>>> Stashed changes

        if (feof(file)){
            if(stackTop(stack)){
                state = SCANNER_WHITE_SPACE;
            }else{
                printf("EOF\n");
                token->type = TOKEN_EOF;        
                state = SCANNER_EOF;
            }
        }
        switch (state){
        case SCANNER_START: case TOKEN_READY:
<<<<<<< Updated upstream
            if (c == '#'){
=======
            if (stackTop(stack) && first_token){
                state = SCANNER_WHITE_SPACE;
            }
            else if (c == '#'){
>>>>>>> Stashed changes
                printf("comment skipped\n\n");
                //first_token = false;
                state = SCANNER_COMMENT;
            }
            else if (isalpha(c)){
                add_char_to_str(str, c);
                state = SCANNER_ID;
                first_token = false;
            }
            else if (isdigit(c)){
                // printf("is digit\n");
                state = SCANNER_INT_OR_FLOAT;
                ungetc(c, file);
                first_token = false;
            }
            else if(c == 10 || c == 13){
                if(!first_token){
                    token->type = TOKEN_EOL;
                    state = TOKEN_READY;
<<<<<<< Updated upstream
=======
                    first_token = true;
>>>>>>> Stashed changes
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
                    space_cnt++;
                }
                else{
                    state = SCANNER_START;
                }
            }
            else if(c == '\''){
                state = SCANNER_STRING;
                token->type = TOKEN_STRING;
            }
            else if(c == '<' || c == '>'){
                state = SCANNER_LESS_GREATER;
                ungetc(c, file);
            }
            else if(c == '='){
                state = SCANNER_ASSIGN;
            }
            else if(c == '+' || c == '-' || c == '*' || c == '/' || c == ':'){
<<<<<<< Updated upstream
                state = SCANNER_SUM_MINUS_MULTIPLY_DIVISION_DDOT;
                if(c == '+')
                token->type = TOKEN_SUM;
                if(c == '-')
                token->type = TOKEN_MINUS;
                if(c == '*')
                token->type = TOKEN_MULTIPLY;
                if(c == '/')
                token->type = TOKEN_DIVISION;
                if(c == ':')
                token->type = TOKEN_DDOT;
            }
            else if(c == '!'){
                state = SCANNER_NONE;
                add_char_to_str(str, c);
=======
                if(c == '+'){
                    token->type = TOKEN_SUM;
                    printf("token attribute: SUM\n");
                }
                if(c == '-'){
                    token->type = TOKEN_MINUS;
                    printf("token attribute: MINUS\n");
                }
                if(c == '*'){
                    token->type = TOKEN_MULTIPLY;
                    printf("token attribute: MULTIPLY\n");
                }  
                if(c == '/'){
                    token->type = TOKEN_DIVISION;
                    printf("token attribute: DIVISION\n");
                }
                if(c == ':'){
                    token->type = TOKEN_DDOT;
                    printf("token attribute: DDOT\n");
                }
            FREE_ALL(str->str, str);
            state = SCANNER_START;
            return TOKEN_READY;
            }
            else if(c == '!'){
                state = SCANNER_NOT;
>>>>>>> Stashed changes
            }
            else if(c == '(' || c == ')'){
                state = SCANNER_BRACKET;
                ungetc(c,file);
            }
            else if( c == '"'){
                state = SCANNER_BLOCK_STRING_BEGIN;
                ungetc(c,file);
            }
            break;
        case SCANNER_ID:
            if(isalpha(c) || (c == '_') || (isdigit(c))){
                add_char_to_str(str, c);
            }
            else{
                ungetc(c, file);
                printf("token attribute: %s\n", str->str);
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
                state = SCANNER_START;
                return TOKEN_READY;
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
                    // fprintf(stdout,"ERROR. In the begining of number cant be more then one\n");
                    FREE_ALL(str->str, str);
                    SLOG("ERROR. In the begining of number cant be more then one", ERR_LEXER);
                    // return ERR_LEXER;
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
                printf("token attribute: %d\n",num);
                // проверка на правильность выполнения перевода на инт
                // if(num ==){
                //     fprintf(stdout, "ERROR. Can not convert string to integer value\n");
                //     FREE_ALL(str->str, str);
                //     return ERR_INTERNAL;
                // }
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
                state = SCANNER_WHITE_SPACE;
            }
            else{
                ungetc(c,file);
                // INDENT OR DEDEND
                first_token = false;
<<<<<<< Updated upstream
            }
            break;
        case SCANNER_STRING:
            if (c == '\''){
                printf("token attribute: %s\n", str->str);
                token->attribute.string = (char *)malloc(str->size);
                strncpy(token->attribute.string, str->str, str->size);
                FREE_ALL(str->str, str);
                state = SCANNER_START;
                return TOKEN_READY;
            }
            else if (c == '\n'){
                FREE_ALL(str->str, str);
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
                    if(c != 13 && c != 10)
                        add_char_to_str(str, c);
                }else{
                    count_of_quot = 0;
                    ungetc(c,file);
                    token->type = TOKEN_STRING;
                    printf("token attribute: %s\n", str->str);
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
=======
                if(space_cnt > stackTop(stack)){
                    // INDEND
                    stackPush(stack, space_cnt);
                    token->type = TOKEN_INDEND;
                    printf("token attribute: INDEND\n");
                    state = SCANNER_START;
                    FREE_ALL(str->str, str);
                    return OK;

                }
                else if (space_cnt < stackTop(stack)){
                    // DEDEND
                    while (stackTop(stack) != 0){
                        printf("stackTop: %d\n", stackTop(stack));
                        stackPop(stack); // ungetc(c,file); --------------------------------
                        if(stackTop(stack) == space_cnt){
                            // we found same level 
                            token->type = TOKEN_DEDEND;
                            printf("token attribute: DEDEND\n");
                            state = SCANNER_START;
                            FREE_ALL(str->str, str);
                            return OK;
                        }
                    }
                    // in case if there is now same offset
>>>>>>> Stashed changes
                    FREE_ALL(str->str, str);
                    state = SCANNER_START;
                    return TOKEN_READY;
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
<<<<<<< Updated upstream
        case SCANNER_LESS_GREATER:
            add_char_to_str(str, c);
            if (c == '>'){
                token->type = TOKEN_GREATER;
                printf("token attribute: MORE\n");
            }else{
                token->type = TOKEN_LESS;
                printf("token attribute: LESS\n");
=======
        case SCANNER_STRING:
            if (c == '\''){
                printf("token attribute: %s\n", str->str);
                token->attribute.string = (char *)malloc(str->size);
                strncpy(token->attribute.string, str->str, str->size);
                FREE_ALL(str->str, str);
                state = SCANNER_START;
                return TOKEN_READY;
            }
            else if (c == '\n'){
                FREE_ALL(str->str, str);
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
                    if(c != 13 && c != 10)
                        add_char_to_str(str, c);
                }else{
                    count_of_quot = 0;
                    ungetc(c,file);
                    token->type = TOKEN_STRING;
                    printf("token attribute: %s\n", str->str);
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
                    FREE_ALL(str->str, str);
                    state = SCANNER_START;
                    return TOKEN_READY;
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
                token->type = TOKEN_GREATER;
                printf("token attribute: MORE");
            }else{
                token->type = TOKEN_LESS;
                printf("token attribute: LESS");
>>>>>>> Stashed changes
            }
            c = getc(file);
            if (c == '='){
                token->type += 2;
<<<<<<< Updated upstream
                printf("token attribute: MORE/LESS_OR_EQUAL\n");
            }else if (c == ' '){
                ungetc(c, file);
            }else{
                FREE_ALL(str->str, str);
                SLOG("ERROR. Can be only '<' or '<=' !", ERR_LEXER);
=======
                printf("_OR_EQUAL\n");
            }else{
                printf("\n");
                ungetc(c, file);
>>>>>>> Stashed changes
            }
            
            FREE_ALL(str->str, str);
            state = SCANNER_START;
            return TOKEN_READY;
            break;
        case SCANNER_ASSIGN:
<<<<<<< Updated upstream
            if(c == ' '){
                ungetc(c,file);
                token->type = TOKEN_ASSIGN;
                printf("token attribute: ASSIGN\n");
            }
            else if(c == '='){
                state = SCANNER_EQUAL;
                printf("token attribute: EQUAL\n");
            }
            else{
                FREE_ALL(str->str, str);
                SLOG("ERROR. After '=' can be only '=' or ' ' !", ERR_LEXER);
=======
            if(c == '='){
                token->type = TOKEN_EQUAL;
                printf("token attribute: EQUAL\n");
            }
            else{
                ungetc(c,file);
                token->type = TOKEN_ASSIGN;
                printf("token attribute: ASSIGN\n");
>>>>>>> Stashed changes
            }
            FREE_ALL(str->str, str);
            state = SCANNER_START;
            return TOKEN_READY; 
            break;
<<<<<<< Updated upstream
        case SCANNER_EQUAL:
            if(c != ' '){
                FREE_ALL(str->str, str);
                SLOG("ERROR. After '==' can be only ' ' !", ERR_LEXER);
            }
            else{
                token->type = TOKEN_EQUAL;
                printf("token attribute: %s\n", str->str);
                token->attribute.string = (char *)malloc(str->size);
                strncpy(token->attribute.string, str->str, str->size);
                FREE_ALL(str->str, str);
                state = SCANNER_START;
                return TOKEN_READY; 
            }
            break;
        case SCANNER_SUM_MINUS_MULTIPLY_DIVISION_DDOT:
            if((c == ' ') || (c == 13) || (c == 10)){
                printf("token attribute: SUM_MINUS_MULTIPLY_DIVISION_DDOT\n");
                FREE_ALL(str->str, str);
                state = SCANNER_START;
                return TOKEN_READY;
            }
            else{
                SLOG("ERROR. After '+,-,*,/,:' can be only ' ' !", ERR_LEXER);
                FREE_ALL(str->str, str);
            }
            break;
        case SCANNER_NONE:
            if(c == '='){
                add_char_to_str(str, c);
                c = getc(file);
                if(c != ' '){
                    FREE_ALL(str->str, str);
                    SLOG("ERROR. After '!=' can be only ' ' !", ERR_LEXER);
                }
                ungetc(c,file);

                printf("token attribute: %s\n", str->str);
                token->attribute.string = (char *)malloc(str->size);
                strncpy(token->attribute.string, str->str, str->size);
=======
        // case SCANNER_EQUAL: // ---leave it here for future---
        //     if(c != ' '){
        //         FREE_ALL(str->str, str);
        //         SLOG("ERROR. After '==' can be only ' ' !", ERR_LEXER);
        //     }
        //     else{
        //         token->type = TOKEN_EQUAL;
        //         printf("token attribute: %s\n", str->str);
        //         token->attribute.string = (char *)malloc(str->size);
        //         strncpy(token->attribute.string, str->str, str->size);
        //         FREE_ALL(str->str, str);
        //         state = SCANNER_START;
        //         return TOKEN_READY; 
        //     }
        //     break;
        // case SCANNER_SUM_MINUS_MULTIPLY_DIVISION_DDOT: ---leave it here for future---
        //     if((c == ' ') || (c == 13) || (c == 10)){
        //         printf("token attribute: SUM_MINUS_MULTIPLY_DIVISION_DDOT\n");
        //         FREE_ALL(str->str, str);
        //         state = SCANNER_START;
        //         return TOKEN_READY;
        //     }
        //     else{
        //         SLOG("ERROR. After '+,-,*,/,:' can be only ' ' !", ERR_LEXER);
        //         FREE_ALL(str->str, str);
        //     }
        //     break;
        case SCANNER_NOT:
            if(c == '='){
                printf("token attribute: NOT_EQUAL\n");
                token->type = TOKEN_NOT_EQUAL;
>>>>>>> Stashed changes
                FREE_ALL(str->str, str);
                state = SCANNER_START;
                return TOKEN_READY; 
            }
            else{
                FREE_ALL(str->str, str);
                SLOG("ERROR. After '!' can be only '=' !", ERR_LEXER);
            }
            break;
        case SCANNER_BRACKET:
            if(c == '('){
                token->type = TOKEN_L_BRACKET;
                printf("token attribute: L_BRACKET\n");
            }
            else{
                token->type = TOKEN_R_BRACKET;
                printf("token attribute: R_BRACKET\n");
            }
            FREE_ALL(str->str, str);
            state = SCANNER_START;
            return TOKEN_READY; 
            break;
        case SCANNER_EOF:  
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
