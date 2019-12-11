/**
 * \file ./scaner.c
 * \brief Implementation lexical analyzes
 *
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 *
 * \date 2019
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_string.h"
#include "errors.h"
#include "scaner.h"

#define SCANNER_START 10   // Scanner begin to work
#define SCANNER_STOP 11    // Scanner read one token
#define SCANNER_STRING 12  // Begining of string
#define SCANNER_EOL 13     // Reade end of line
#define SCANNER_ID 14      // It is a identifier or keyword
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
#define SCANNER_EOF 100  /// Scanner read last token

typedef struct stack tStack;

int convert_num_to_str(struct dynamic_string *str) {
    int c = getchar();
    // Hexadecimal value
    if ((c == 'x') || (c == 'X')) {
        char tmp[4];
        tmp[0] = '0';
        tmp[1] = (char)c;
        for (int i = 2; i < 4; i++) {
            c = getchar();
            if (isdigit(c) || (c == 'A') || (c == 'a') || (c == 'B') ||
                (c == 'b') || (c == 'C') || (c == 'c') || (c == 'D') ||
                (c == 'd') || (c == 'E') || (c == 'e') || (c == 'F') ||
                (c == 'f')) {
                tmp[i] = (char)c;
            } else {
                return ERR_LEXER;
            }
        }
        c = getchar();
        if (isalpha(c) || isdigit(c)) {
            // error in hex value
            return ERR_LEXER;
        }
        ungetc(c, stdin);

        long hex = strtol(tmp, NULL, 16);
        char tmp_1[3];
        sprintf(tmp_1, "%ld", hex);
        if (hex < 100) {
            add_char_to_str(str, '0');
            add_char_to_str(str, tmp_1[0]);
            add_char_to_str(str, tmp_1[1]);
        } else if (hex > 255) {
            return ERR_LEXER;
        } else {
            for (int b = 0; b < 3; b++) {
                add_char_to_str(str, tmp_1[b]);
            }
        }
    } else if (c == 'n') {
        add_char_to_str(str, '0');
        add_char_to_str(str, '1');
        add_char_to_str(str, '0');
    } else if (c == 't') {
        add_char_to_str(str, '0');
        add_char_to_str(str, '0');
        add_char_to_str(str, '9');
    } else if (c == '\\') {
        add_char_to_str(str, '0');
        add_char_to_str(str, '9');
        add_char_to_str(str, '2');
    } else if (c == '\'') {
        add_char_to_str(str, '0');
        add_char_to_str(str, '3');
        add_char_to_str(str, '9');
    } else if (c == '\"') {
        add_char_to_str(str, '0');
        add_char_to_str(str, '3');
        add_char_to_str(str, '4');
    } else {
        add_char_to_str(str, c);
    }
    return OK;
}

int get_token(struct token_s *token, tStack *stack) {
    // string to writing down attribute
    struct dynamic_string *str;
    str_init(&str);

    int state = SCANNER_START;
    static bool first_token = true;
    static int double_quot = 0;
    static int count_of_quot = 0;
    int c;
    static int prev_sym;
    int space_cnt = 0;
    int ret_code;

    while (state != SCANNER_EOF) {
        c = getchar();
        if (c == -1 && prev_sym != '\n' && state == SCANNER_START) {
            token->type = TOKEN_EOL;
            str_clean(str);
            prev_sym = '\n';
            ungetc(c, stdin);
            return OK;
        } else {
            prev_sym = c;
        }
        switch (state) {
            case SCANNER_START:
                if (c == -1) {
                    token->type = TOKEN_EOF;
                    if (stackTop(stack)) {
                        token->type = TOKEN_DEDEND;
                        stackPop(stack);
                        str_clean(str);
                        return OK;
                    }
                    str_clean(str);
                    return OK;
                } else if (c == ' ') {
                    if (first_token) {
                        state = SCANNER_WHITE_SPACE;
                        space_cnt++;
                    } else {
                        state = SCANNER_START;
                    }
                    break;
                } else if (c == '\t') {
                    if (first_token) {
                        state = SCANNER_WHITE_SPACE;
                        space_cnt += 4;
                    } else {
                        state = SCANNER_START;
                    }
                    break;
                } else if (first_token) {
                    /* If it is a new line and previous was INDEND*/
                    if (c == '#' || c == '"') {
                        state = SCANNER_COMMENT;
                        break;
                    }
                    if ((stackTop(stack) != 0) && (c != '\n' && c != '\r')) {
                        ungetc(c, stdin);
                        stackPop(stack);
                        token->type = TOKEN_DEDEND;
                        str_clean(str);
                        return OK;
                    }
                }
                if (c == '#') {
                    state = SCANNER_COMMENT;
                    break;
                } else if (isalpha(c)) {
                    add_char_to_str(str, c);
                    state = SCANNER_ID;
                    first_token = false;
                    break;
                } else if (isdigit(c)) {
                    state = SCANNER_INT_OR_FLOAT;
                    ungetc(c, stdin);
                    first_token = false;
                    break;
                } else if (c == ',') {
                    token->type = TOKEN_COMA;
                    str_clean(str);
                    return OK;
                } else if ((c == '\n') || (c == '\r')) {
                    if (!first_token) {
                        token->type = TOKEN_EOL;
                        state = SCANNER_START;
                        first_token = true;
                        str_clean(str);
                        return OK;
                    } else {
                        state = SCANNER_START;
                    }
                    break;
                } else if (c == '\'') {
                    state = SCANNER_STRING;
                    break;
                } else if (c == '"') {
                    state = SCANNER_BLOCK_STRING_BEGIN;
                    ungetc(c, stdin);
                    break;
                } else if (c == '<' || c == '>') {
                    state = SCANNER_LESS_GREATER;
                    ungetc(c, stdin);
                    break;
                } else if (c == '=') {
                    state = SCANNER_ASSIGN;
                    break;
                } else if (c == '+') {
                    token->type = TOKEN_SUM;
                    str_clean(str);
                    return OK;
                } else if (c == '-') {
                    token->type = TOKEN_MINUS;
                    str_clean(str);
                    return OK;
                } else if (c == '*') {
                    token->type = TOKEN_MULTIPLY;
                    str_clean(str);
                    return OK;
                } else if (c == '/') {
                    c = getchar();
                    if (c == '/') {
                        token->type = TOKEN_DIV_INT;
                    } else {
                        ungetc(c, stdin);
                        token->type = TOKEN_DIVISION;
                    }
                    str_clean(str);
                    return OK;
                } else if (c == ':') {
                    token->type = TOKEN_DDOT;

                    str_clean(str);
                    return OK;
                } else if (c == '!') {
                    state = SCANNER_NOT;
                    break;
                } else if (c == '(' || c == ')') {
                    state = SCANNER_BRACKET;
                    ungetc(c, stdin);
                    break;
                }
                break;
            case SCANNER_ID:
                if (isalpha(c) || (c == '_') || (isdigit(c))) {
                    if (!add_char_to_str(str, c)) {
                        str_clean(str);
                        return ERR_INTERNAL;
                    }
                } else {
                    ungetc(c, stdin);
                    if (strcmp(str->str, "while") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _WHILE_;
                    } else if (strcmp(str->str, "def") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _DEF_;
                    } else if (strcmp(str->str, "else") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _ELSE_;
                    } else if (strcmp(str->str, "None") == 0) {
                        token->type = TOKEN_NONE;
                    } else if (strcmp(str->str, "pass") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _PASS_;
                    } else if (strcmp(str->str, "return") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _RETURN_;
                    } else if (strcmp(str->str, "if") == 0) {
                        token->type = TOKEN_KEY_WORD;
                        token->attribute.key_word = _IF_;
                    } else if (strcmp(str->str, "print") == 0) {
                        token->type = TOKEN_PRINT;
                    } else if (strcmp(str->str, "inputs") == 0) {
                        token->type = TOKEN_INPUT_S;
                    } else if (strcmp(str->str, "inputi") == 0) {
                        token->type = TOKEN_INPUT_I;
                    } else if (strcmp(str->str, "inputf") == 0) {
                        token->type = TOKEN_INPUT_F;
                    } else if (strcmp(str->str, "ord") == 0) {
                        token->type = TOKEN_ORD;
                    } else if (strcmp(str->str, "len") == 0) {
                        token->type = TOKEN_LEN;
                    } else if (strcmp(str->str, "substr") == 0) {
                        token->type = TOKEN_SUBSTR;
                    } else if (strcmp(str->str, "chr") == 0) {
                        token->type = TOKEN_CHR;
                    } else {
                        for (c = getchar();; c = getchar()) {
                            if (c == ' ') {
                                continue;
                            } else if (c == '(') {
                                token->type = TOKEN_FNC;
                                ungetc(c, stdin);
                                break;
                            } else {
                                /* I dont know why, but if without this IF it
                                doesn't generate TOKEN_ASSIGN type */
                                token->type = TOKEN_ID;
                                ungetc(c, stdin);
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
                if (c == '0') {
                    c = getchar();
                    if (c == '.') {
                        add_char_to_str(str, '0');
                        add_char_to_str(str, c);
                        state = SCANNER_FLOAT;
                    } else if ((c == 'E') || (c == 'e')) {
                        add_char_to_str(str, '0');
                        add_char_to_str(str, c);
                        state = SCANNER_EXP;
                    } else if (isdigit(c)) {
                        str_clean(str);
                        return ERR_LEXER;
                    } else {
                        if (isalpha(c)) {
                            str_clean(str);
                            return ERR_LEXER;
                        }
                        ungetc(c, stdin);
                        add_char_to_str(str, '0');
                        state = SCANNER_INT;
                    }
                } else {
                    add_char_to_str(str, c);
                    state = SCANNER_INT;
                }
                break;
            case SCANNER_INT:
                if (isdigit(c)) {
                    add_char_to_str(str, c);
                } else if (c == '.') {
                    add_char_to_str(str, c);
                    state = SCANNER_FLOAT;
                } else if ((c == 'E') || (c == 'e')) {
                    add_char_to_str(str, c);
                    state = SCANNER_EXP;
                } else {
                    if (isalpha(c)) {
                        str_clean(str);
                        return ERR_LEXER;
                    }
                    ungetc(c, stdin);
                    int num = atoi(str->str);
                    token->attribute.int_val = num;
                    token->type = TOKEN_INT;
                    str_clean(str);
                    return OK;
                }
                break;
            case SCANNER_FLOAT:
                if (isdigit(c)) {
                    add_char_to_str(str, c);
                } else if ((c == 'e') || (c == 'E')) {
                    add_char_to_str(str, c);
                    state = SCANNER_EXP;
                } else {
                    if (isalpha(c)) {
                        str_clean(str);
                        return ERR_LEXER;
                    }

                    ungetc(c, stdin);
                    token->attribute.float_val = strtof(str->str, NULL);
                    token->type = TOKEN_FLOAT;
                    str_clean(str);
                    return OK;
                }
                break;
            case SCANNER_EXP:
                if ((c == '-') || (c == '+')) {
                    add_char_to_str(str, c);
                } else if (isdigit(c)) {
                    add_char_to_str(str, c);
                } else {
                    if (isalpha(c)) {
                        str_clean(str);
                        return ERR_LEXER;
                    }

                    ungetc(c, stdin);
                    token->attribute.float_val = strtof(str->str, NULL);
                    token->type = TOKEN_FLOAT;
                    str_clean(str);
                    return OK;
                }
                break;

            case SCANNER_WHITE_SPACE:
                if (c == '\n' || c == '\r') {
                    space_cnt = 0;
                    state = SCANNER_START;
                } else if (c == '\t') {
                    space_cnt += 4;
                    state = SCANNER_WHITE_SPACE;
                    break;
                } else if (c == ' ') {
                    space_cnt++;
                    state = SCANNER_WHITE_SPACE;
                    break;
                } else if (c == '#') {
                    state = SCANNER_COMMENT;
                    break;
                } else {
                    ungetc(c, stdin);
                    // INDENT OR DEDEND
                    first_token = false;
                    if (space_cnt > stackTop(stack)) {
                        // INDEND
                        stackPush(stack, space_cnt);
                        token->type = TOKEN_INDEND;
                        state = SCANNER_START;
                        str_clean(str);
                        return OK;
                    } else if (space_cnt < stackTop(stack)) {
                        // DEDEND
                        c = getchar();
                        //  If it is a commnet line, so just skip it without
                        //  DEDEND
                        if (c == '#') {
                            state = SCANNER_COMMENT;
                            break;
                        } else {
                            ungetc(c, stdin);
                        }
                        bool found = false;
                        while (stackTop(stack) != 0) {
                            stackPop(stack);
                            if (stackTop(stack) == space_cnt) {
                                // we found same level
                                token->type = TOKEN_DEDEND;
                                state = SCANNER_START;
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            // in case if there is no same offset
                            str_clean(str);
                            state = SCANNER_START;
                            printf("Wrong offset\n");
                            return ERR_LEXER;
                        } else {
                            state = SCANNER_START;
                            str_clean(str);
                            return OK;
                        }
                    }
                }
                state = SCANNER_START;
                break;
            case SCANNER_STRING:
                if (c == '\'') {
                    token->type = TOKEN_STRING;
                    token->attribute.string = (char *)malloc(str->size);
                    strncpy(token->attribute.string, str->str, str->size);
                    str_clean(str);
                    state = SCANNER_START;
                    return OK;
                } else if (c == '\\') {
                    add_char_to_str(str, c);
                    ret_code = convert_num_to_str(str);
                    if (ret_code != OK) {
                        str_clean(str);
                        return ret_code;
                    }
                } else if (c == ' ') {
                    add_char_to_str(str, '\\');
                    add_char_to_str(str, '0');
                    add_char_to_str(str, '3');
                    add_char_to_str(str, '2');
                } else if (c == '\"') {
                    add_char_to_str(str, '\"');
                } else if (c == '\n') {
                    str_clean(str);
                    return ERR_LEXER;
                } else {
                    add_char_to_str(str, c);
                }
                break;
            case SCANNER_BLOCK_STRING_BEGIN:
                if (c == '"' && double_quot < 3 && count_of_quot < 2) {
                    double_quot++;
                    if (double_quot == 3) {
                        count_of_quot++;
                    }
                } else if (c != '"' && (double_quot == 3 || double_quot == 0)) {
                    double_quot = 0;
                    if (count_of_quot < 2) {
                        if (c == '\\') {
                            add_char_to_str(str, c);
                            ret_code = convert_num_to_str(str);
                            if (ret_code != OK) {
                                str_clean(str);
                                return ret_code;
                            }
                        } else if (c == ' ') {
                            add_char_to_str(str, '\\');
                            add_char_to_str(str, '0');
                            add_char_to_str(str, '3');
                            add_char_to_str(str, '2');
                        } else if (c == '\'') {
                            add_char_to_str(str, '\'');
                        }

                        else if (c == '\n') {
                            add_char_to_str(str, '\\');
                            add_char_to_str(str, '0');
                            add_char_to_str(str, '1');
                            add_char_to_str(str, '0');
                        } else {
                            add_char_to_str(str, c);
                        }
                    } else {
                        count_of_quot = 0;
                        ungetc(c, stdin);
                        token->type = TOKEN_STRING;
                        token->attribute.string = (char *)malloc(str->size);
                        strncpy(token->attribute.string, str->str, str->size);
                        str_clean(str);
                        state = SCANNER_START;
                        return OK;
                    }
                } else {
                    str_clean(str);
                    return ERR_OTHER;
                }
                break;
            case SCANNER_COMMENT:
                if (c == '\n') {
                    if (first_token) {
                        state = SCANNER_START;
                        break;
                    }
                    first_token = true;
                    token->type = TOKEN_EOL;
                    str_clean(str);
                    return OK;
                }
                break;
            case SCANNER_LESS_GREATER:
                if (c == '>') {
                    token->type = TOKEN_GREATER;
                } else {
                    token->type = TOKEN_LESS;
                }
                c = getchar();
                if (c == '=') {
                    token->type += 2;  // look to scaner.h
                } else {
                    ungetc(c, stdin);
                }

                str_clean(str);
                state = SCANNER_START;
                return OK;
                break;
            case SCANNER_ASSIGN:
                if (c == '=') {
                    token->type = TOKEN_EQUAL;
                } else {
                    ungetc(c, stdin);
                    token->type = TOKEN_ASSIGN;
                }
                str_clean(str);
                state = SCANNER_START;
                return OK;
                break;
            case SCANNER_NOT:
                if (c == '=') {
                    token->type = TOKEN_NOT_EQUAL;
                    str_clean(str);
                    state = SCANNER_START;
                    return OK;
                } else {
                    str_clean(str);

                    return ERR_LEXER;
                }
                break;
            case SCANNER_BRACKET:
                if (c == '(') {
                    token->type = TOKEN_L_BRACKET;
                } else if (c == ')') {
                    token->type = TOKEN_R_BRACKET;
                }

                str_clean(str);

                state = SCANNER_START;
                return OK;
                break;
            case SCANNER_EOL:
                token->type = TOKEN_EOL;
                str_clean(str);
                return OK;
            case SCANNER_EOF:
                break;
            default:
                state = SCANNER_START;
                break;
        }
    }

    str_clean(str);
    return ERR_LEXER;
}
