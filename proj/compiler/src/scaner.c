#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "errors.h"
#include "dynamic_string.h"
#include "scaner.h"


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
/*#define FREE_ALL(...)                                      \
    do                                                     \
    {                                                      \
        unsigned int i = 0;                                \
        void *pta[] = {__VA_ARGS__};                       \
        for (i = 0; i < sizeof(pta) / sizeof(void *); i++) \
        {                                                  \
            free(pta[i]);                                  \
        }                                                  \
    } while (0)*/


/* Macros for log*/
#define SLOG(msg) \
    _log(stdout, __FILE__, __LINE__, msg);\

inline void _log(FILE *fd, char *file, int line, char *msg){
    fprintf(fd, "%s:%d %s\n", file, line, msg);
}

typedef struct stack tStack;

int get_token(FILE *file, struct token_s *token, tStack *stack)
{

    if (!file){
        SLOG("There is no input file.Rerun with file");
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
        // printf("%c\n", c);

        switch (state){
        case SCANNER_START:
            if (feof(file))
            {
                token->type = TOKEN_EOF;
                if (stackTop(stack))
                {
                    token->type = TOKEN_DEDEND;
                    stackPop(stack);
                    str_clean(str);
                    return OK;
                }
                str_clean(str);
                state = SCANNER_EOF;
                return OK;
            }
            else if(c == ' '){
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
                if(c == '#'){
                    state = SCANNER_COMMENT;
                    break;    
                }
                if((stackTop(stack) != 0) && (c != '\n' && c != '\r')){
                    ungetc(c, file);
                    stackPop(stack);
                    token->type = TOKEN_DEDEND;
                    str_clean(str);
                    return OK;
                }
            }

            if (c == '#'){
                state = SCANNER_COMMENT;
                break;
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
            else if(c == ','){
                token->type = TOKEN_COMA;
                str_clean(str);
                return OK;
            }
            else if((c == '\n') || (c == '\r') ){
                if(!first_token){
                    token->type = TOKEN_EOL;
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
                token->type = TOKEN_SUM;
                str_clean(str);
                return OK;
            }
            else if (c == '-'){
                token->type = TOKEN_MINUS;
                str_clean(str);
                return OK;
            }
            else if (c == '*') {
                token->type = TOKEN_MULTIPLY;
                str_clean(str);
                return OK;
            }
            else if (c == '/'){
                c = getc(file);
                if(c == '/'){
                    token->type = TOKEN_DIV_INT;
                }
                else{
                    ungetc(c, file);
                    token->type = TOKEN_DIVISION;
                }
                str_clean(str);
                return OK;
            }
            else if (c == ':'){
                token->type = TOKEN_DDOT;
                // first_token = true;
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
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _WHILE_;
                }
                else if (strcmp(str->str, "def") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _DEF_;
                }
                else if (strcmp(str->str, "else") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _ELSE_;
                }
                else if(strcmp(str->str, "none") == 0){
                    token->type = TOKEN_NONE;
                    // token->attribute.key_word = _NONE_;
                }
                else if(strcmp(str->str, "pass") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _PASS_;
                }
                else if(strcmp(str->str, "return") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _RETURN_;
                }
                else if(strcmp(str->str, "if") == 0){
                    token->type = TOKEN_KEY_WORD;
                    token->attribute.key_word = _IF_;
                }
                else if(strcmp(str->str, "print") == 0){
                    token->type = TOKEN_PRINT;
                }
                else if(strcmp(str->str, "inputs") == 0){
                    token->type = TOKEN_INPUT_S;
                }
                else if(strcmp(str->str, "inputi") == 0){
                    token->type = TOKEN_INPUT_I;
                }
                else if(strcmp(str->str, "inputf") == 0){
                    token->type = TOKEN_INPUT_F;
                }
                else if(strcmp(str->str, "ord") == 0){
                    token->type = TOKEN_ORD;
                }
                else if(strcmp(str->str, "len") == 0){
                    token->type = TOKEN_LEN;
                }
                else if(strcmp(str->str, "substr") == 0){
                    token->type = TOKEN_SUBSTR;
                }
                else if(strcmp(str->str, "chr") == 0){
                    token->type = TOKEN_CHR;
                }
                else{
                    for(;;c = getc(file)){ 
                        if(c == ' '){
                            continue;
                        }
                        else if(c == '('){
                            token->type = TOKEN_FNC;
                            break;
                        }
                        else{
                            /* I dont know why, but if without this IF it 
                            doesn't generate TOKEN_ASSIGN type*/ 
                            if(c == '='){
                                ungetc(c, file);
                            }
                            token->type = TOKEN_ID;
                            break;
                        }
                    }
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
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
                    str_clean(str);
                    SLOG("ERROR. In the begining of number cant be more then one");
                }
                else{
                    if(isalpha(c)){
                        SLOG("Wrong indetificator");
                        // return 
                    }
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
                if(isalpha(c)){
                    SLOG("Wrong indetificator");
                    return ERR_LEXER; 
                }
                ungetc(c,file);
                int num = atoi(str->str);
                token->attribute.int_val = num;
                token->type = TOKEN_INT;
                str_clean(str);
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
                if(isalpha(c)){
                    SLOG("Wrong indetificator");
                    return ERR_LEXER; 
                }

                ungetc(c, file);
                token->attribute.float_val = strtof(str->str, NULL);
                token->type = TOKEN_FLOAT;
                str_clean(str);
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
                if(isalpha(c)){
                    SLOG("Wrong indetificator");
                    return ERR_LEXER; 
                }

                ungetc(c, file);
                token->attribute.float_val = strtof(str->str, NULL);
                token->type = TOKEN_FLOAT;
                str_clean(str);
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
            else if(c == '#'){
                state = SCANNER_COMMENT;
                break;
            }
            else{
                ungetc(c,file);
                // INDENT OR DEDEND
                first_token = false;
                if(space_cnt > stackTop(stack)){
                    // INDEND
                    stackPush(stack, space_cnt);
                    token->type = TOKEN_INDEND;
                    state = SCANNER_START;
                    str_clean(str);
                    return OK;
                }
                else if (space_cnt < stackTop(stack)){
                    // DEDEND
                    c = getc(file);
                    //  If it is a commnet line, so just skip it without DEDEND
                    if(c == '#'){
                        state = SCANNER_COMMENT;                                    
                        break;
                    }
                    else{
                        ungetc(c, file);
                    }
                    bool found =  false;
                    while (stackTop(stack) != 0){
                        stackPop(stack); 
                        if(stackTop(stack) == space_cnt){
                            // we found same level 
                            token->type = TOKEN_DEDEND;
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
                token->type = TOKEN_STRING;
                token->attribute.string = (char *)malloc(str->size);
                strncpy(token->attribute.string, str->str, str->size);
                str_clean(str);
                state = SCANNER_START;
                return OK;
            }
            else if (c == '\\'){
                c = getc(file);
                // Hexadecimal value
                if((c == 'x') || (c == 'X')){
                    char tmp[4];
                    tmp[0] = '0';
                    tmp[1] = (char)c;
                    for(int i = 2; i < 4; i++){
                        c = getc(file);
                        if (isdigit(c) ||
                            (c == 'A') ||
                            (c == 'a') ||
                            (c == 'B') ||
                            (c == 'b') ||
                            (c == 'C') ||
                            (c == 'c') ||
                            (c == 'D') ||
                            (c == 'd') ||
                            (c == 'E') ||
                            (c == 'e') ||
                            (c == 'F') ||
                            (c == 'f'))
                        {
                            tmp[i] = (char)c;
                        }
                        else{
                            SLOG("Hexadecimal value in string must be in format '\\xAB, where A and B are integer numbers");
                            return ERR_LEXER;
                        }
                    }

                    char hex;
                    // Convert to hex value
                    sscanf(tmp, "%hhx", &hex);
                    add_char_to_str(str, hex);
                }
                else if (c == 'n' ){
                    add_char_to_str(str, '\n');
                }
                else if (c == 't'){
                    add_char_to_str(str, '\t');
                }
                else if (c == '\\'){
                    add_char_to_str(str, '\\');
                }
                else if (c == '\''){
                    add_char_to_str(str, '\\');
                }
                else if (c == '\"'){
                    add_char_to_str(str, '\"');
                }
                else{
                    add_char_to_str(str,'\\');
                    add_char_to_str(str, c);
                }
            }
            else if (c == '\n'){
                str_clean(str);
                str_clean(str);
                SLOG("ERROR. String must be in one line!");
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
                    if (c == '\\'){
                        c = getc(file);
                        // Hexadecimal value
                        if((c == 'x') || (c == 'X')){
                            char tmp[4];
                            tmp[0] = '0';
                            tmp[1] = (char)c;
                            for(int i = 2; i < 4; i++){
                                c = getc(file);
                                if (isdigit(c) ||
                                (c == 'A') ||
                                (c == 'a') ||
                                (c == 'B') ||
                                (c == 'b') ||
                                (c == 'C') ||
                                (c == 'c') ||
                                (c == 'D') ||
                                (c == 'd') ||
                                (c == 'E') ||
                                (c == 'e') ||
                                (c == 'F') ||
                                (c == 'f'))
                                {
                                    tmp[i] = (char)c;
                                }
                                else{
                                    SLOG("Hexadecimal value in string must be in format '\\xAB, where A and B are integer numbers");
                                }
                            }
                            char hex;
                            // Convert to hex value
                            sscanf(tmp, "%hhx", &hex);
                            add_char_to_str(str, hex);
                        }
                        else if (c == 'n' ){
                            add_char_to_str(str, '\n');
                        }
                        else if (c == 't'){
                            add_char_to_str(str, '\t');
                        }
                        else if (c == '\\'){
                            add_char_to_str(str, '\\');
                        }
                        else if (c == '\''){
                            add_char_to_str(str, '\\');
                        }
                        else if (c == '\"'){
                            add_char_to_str(str, '\"');
                        }
                        else{
                            add_char_to_str(str,'\\');
                            add_char_to_str(str, c);
                        }
                    }
                    else if (c == '\n' || c == '\r'){
                        add_char_to_str(str, ' ');
                    }
                    else{
                        add_char_to_str(str, c);
                    }
                }
                else{
                    count_of_quot = 0;
                    ungetc(c,file);
                    token->type = TOKEN_STRING;
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
                    str_clean(str);
                    state = SCANNER_START;
                    return OK;
                }
            }
            else{
                str_clean(str);
                SLOG("ERROR. Block string must start from '\"\"\"' !");
            }
            break;
        case SCANNER_COMMENT:
            if (c == '\n'){
                first_token = true;
                state = SCANNER_START;
                break;
            }
            break;
        case SCANNER_LESS_GREATER:
            if (c == '>'){
                token->type = TOKEN_GREATER;
            }
            else{
                token->type = TOKEN_LESS;
            }
            c = getc(file);
            if (c == '='){
                token->type += 2; // look to scaner.h
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
                token->type = TOKEN_EQUAL;
            }
            else{
                ungetc(c,file);
                token->type = TOKEN_ASSIGN;
            }
            str_clean(str);
            state = SCANNER_START;
            return OK; 
            break;
        case SCANNER_NOT:
            if(c == '='){
                token->type = TOKEN_NOT_EQUAL;
                if(str->str != NULL){
                    str_clean(str);
                } 
                else{
                    str_clean(str);
                }
                state = SCANNER_START;
                return OK; 
            }
            else{
                str_clean(str);
                SLOG("ERROR. After '!' can be only '=' !");
            }
            break;
        case SCANNER_BRACKET:
            if(c == '('){
                token->type = TOKEN_L_BRACKET;
            }
            else if (c == ')'){
                token->type = TOKEN_R_BRACKET;
            }
            
            str_clean(str);

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

    str_clean(str);
    return -1;
}
