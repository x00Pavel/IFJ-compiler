/**
 * \file  ./parser.c
 * \brief Implimetation of syntax and semantics analyzes
 *
 * \author Korniienko Oleksii (xkorni02@stud.fit.vutbr.cz)
 *
 * \date 2019
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int count_of_if = 0;
int flag_while = 0;
int flag_if = 0;
int flag_else = 0;

int func_mb_ret(struct token_s *token, tStack *stack, table_s *hash_table,
                int *count_of_params, struct dynamic_string *str_1) {
    int ret_code = 0;

    switch (token->type) {
        case TOKEN_NONE:
            return OK;
            break;
        case TOKEN_FNC:
        case TOKEN_ID:
        case TOKEN_INT:
        case TOKEN_STRING:
        case TOKEN_FLOAT:
            ret_code = preced_analyze(token, hash_table, count_of_params, str_1,
                                      stack);
            if (ret_code != OK) {
                return ret_code;
            }
            pop_retval(str_1);

            break;

        default:
            return ERR_SYNTAX;
            break;
    }
    return OK;
}

int func_cond_mb(struct token_s *token, tStack *stack, int count_of_brackets,
                 table_s *hash_table, int *count_of_params,
                 struct dynamic_string *str_1) {
    int ret_code = 0;
    (void)count_of_brackets;
    ret_code = get_token(token, stack);

    if (ret_code != OK) return ret_code;

    ret_code = preced_analyze(token, hash_table, count_of_params, str_1, stack);

    if (ret_code != OK) {
        return ret_code;
    }

    return OK;
}

int check_next_token(struct token_s *token_for_time, struct token_s *token,
                     tStack *stack, int *count_of_params, table_s *hash_table,
                     bool flag_def, struct dynamic_string *str_1) {
    int ret_code = 0;
    ret_code = get_token(token, stack);

    if (ret_code != OK) return ret_code;
    if (token->type == TOKEN_COMA) {
        print_space(str_1);
        ret_code = get_token(token, stack);
        if (ret_code != OK) return ret_code;
        ret_code =
            func_for_atributes(token_for_time, token, stack, count_of_params,
                               hash_table, flag_def, str_1);
        if (ret_code != OK) return ret_code;
    } else if (token->type == TOKEN_R_BRACKET) {
        return OK;
    } else {
        return ERR_SYNTAX;
    }
    return OK;
}

int func_for_atributes(struct token_s *token_for_time, struct token_s *token,
                       tStack *stack, int *count_of_params, table_s *hash_table,
                       bool flag_def, struct dynamic_string *str_1) {
    (*count_of_params)++;
    int ret_code = 0;
    tHTItem *item;
    switch (token->type) {
        case TOKEN_ID:

            if (flag_def == true) {
                item = htSearch(hash_table, token->attribute.string);
                if (item) {
                    return ERR_UNDEF;
                } else {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (item) {
                        if (item->type == TOKEN_FNC) {
                            return ERR_UNDEF;
                        }
                    }
                    htInsert(hash_table, token->attribute.string, token->type);
                    item = htSearch(hash_table, token->attribute.string);
                    item->id_declared = true;
                }
            } else {
                item = htSearch(hash_table, token->attribute.string);
                if (!item) {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (!item) {
                        return ERR_UNDEF;
                    } else {
                        if (item->type == TOKEN_FNC) {
                            return ERR_UNDEF;
                        } else if (item->type == TOKEN_ID) {
                            htInsert(hash_table, token->attribute.string,
                                     token->type);
                            item =
                                htSearch(hash_table, token->attribute.string);
                            item->id_declared = false;
                        }
                    }
                } else {
                    if (item->type == TOKEN_FNC) {
                        return ERR_UNDEF;
                    }
                }
            }
            if (flag_def) {
                def_function_call(token, count_of_params, "LF", str_1);
            } else {
                if (token_for_time->type == TOKEN_PRINT) {
                    if (hash_table->prev_hash_table) {
                        item = htSearch(hash_table, token->attribute.string);
                        if (item) {
                            print_id(token, "LF", str_1);
                        } else {
                            print_id(token, "GF", str_1);
                        }
                    } else {
                        print_id(token, "GF", str_1);
                    }
                } else {
                    if (hash_table->prev_hash_table) {
                        function_call(token, count_of_params, "LF", str_1);
                    } else {
                        function_call(token, count_of_params, "GF", str_1);
                    }
                }
            }
            free(token->attribute.string);
            ret_code =
                check_next_token(token_for_time, token, stack, count_of_params,
                                 hash_table, flag_def, str_1);
            if (ret_code != OK) return ret_code;
            break;
        case TOKEN_INT:
            if (flag_def) {
                return ERR_PARAM;
            } else {
                if (token_for_time->type == TOKEN_PRINT) {
                    print_int(token, str_1);
                } else {
                    function_call(token, count_of_params, "TF", str_1);
                }
            }
            ret_code =
                check_next_token(token_for_time, token, stack, count_of_params,
                                 hash_table, flag_def, str_1);
            if (ret_code != OK) return ret_code;
            break;
        case TOKEN_FLOAT:
            if (flag_def) {
                return ERR_PARAM;
            } else {
                if (token_for_time->type == TOKEN_PRINT) {
                    print_float(token, str_1);
                } else {
                    function_call(token, count_of_params, "TF", str_1);
                }
            }
            ret_code =
                check_next_token(token_for_time, token, stack, count_of_params,
                                 hash_table, flag_def, str_1);
            if (ret_code != OK) return ret_code;
            break;
        case TOKEN_STRING:
            if (flag_def) {
                free(token->attribute.string);
                return ERR_PARAM;
            } else {
                if (token_for_time->type == TOKEN_PRINT) {
                    print_string(token, str_1);
                } else {
                    function_call(token, count_of_params, "TF", str_1);
                }
            }
            free(token->attribute.string);
            ret_code =
                check_next_token(token_for_time, token, stack, count_of_params,
                                 hash_table, flag_def, str_1);
            if (ret_code != OK) return ret_code;
            break;
        default:
            return ERR_SYNTAX;
            break;
    }
    return OK;
}

int func_for_FNC(struct token_s *token, tStack *stack, table_s *hash_table,
                 bool flag_def, int *count_of_params,
                 struct dynamic_string *str_1) {
    int ret_code = 0;
    *count_of_params = 0;

    struct token_s token_for_time;

    token_for_time.type = token->type;
    token_for_time.attribute = token->attribute;
    if (token->type == TOKEN_FNC) {
        token_for_time.attribute.string =
            (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        strcpy(token_for_time.attribute.string, token->attribute.string);
        free(token->attribute.string);
    }

    ret_code = get_token(token, stack);
    if (ret_code != OK) {
        free(token_for_time.attribute.string);
        return ret_code;
    }

    if (token->type == TOKEN_L_BRACKET) {
        ret_code = get_token(token, stack);
        if (ret_code != OK) {
            free(token_for_time.attribute.string);
            return ret_code;
        }
        if (token->type == TOKEN_R_BRACKET) {
            if (token_for_time.type == TOKEN_FNC) {
                if (!flag_def) call_function(&token_for_time, str_1);
                free(token_for_time.attribute.string);
                return OK;
            } else if (token_for_time.type == TOKEN_INPUT_I ||
                       token_for_time.type == TOKEN_INPUT_S ||
                       token_for_time.type == TOKEN_INPUT_F) {
                if (token_for_time.type == TOKEN_INPUT_I) {
                    token_function_begin_with_y(str_1);
                    inputi_call(str_1);
                } else if (token_for_time.type == TOKEN_INPUT_F) {
                    token_function_begin_with_y(str_1);
                    inputf_call(str_1);
                } else if (token_for_time.type == TOKEN_INPUT_S) {
                    token_function_begin_with_y(str_1);
                    inputs_call(str_1);
                }
                return OK;
            } else if (token_for_time.type == TOKEN_PRINT) {
                return ERR_SYNTAX;
            }
        } else {
            ret_code = func_for_atributes(&token_for_time, token, stack,
                                          count_of_params, hash_table, flag_def,
                                          str_1);

            if (ret_code != OK) {
                if (token_for_time.type == TOKEN_FNC)
                    free(token_for_time.attribute.string);
                return ret_code;
            }
            if (token_for_time.type == TOKEN_FNC) {
                if (!flag_def) call_function(&token_for_time, str_1);
                free(token_for_time.attribute.string);
            } else if (token_for_time.type == TOKEN_PRINT) {
                print_end(str_1);
            } else if (token_for_time.type == TOKEN_INPUT_I ||
                       token_for_time.type == TOKEN_INPUT_S ||
                       token_for_time.type == TOKEN_INPUT_F) {
                return ERR_SYNTAX;
            } else {
                return ERR_SYNTAX;
            }
        }
    } else {
        return ERR_SYNTAX;
    }
    return OK;
}

int func_for_id(struct token_s *token, tStack *stack, table_s *hash_table,
                int *count_of_params, struct dynamic_string *str_1) {
    tHTItem *item;
    int tmp_int = 1;
    int ret_code = 0;

    struct token_s token_for_time;

    token_for_time.type = token->type;

    if (token->type == TOKEN_ID) {
        token_for_time.attribute.string =
            (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        strcpy(token_for_time.attribute.string, token->attribute.string);
    }

    free(token->attribute.string);

    ret_code = get_token(token, stack);
    if (ret_code != OK) {
        free(token_for_time.attribute.string);
        return ret_code;
    }
    if (token->type == TOKEN_ASSIGN) {
        ret_code = get_token(token, stack);
        if (ret_code != OK) {
            free(token_for_time.attribute.string);
            return ret_code;
        }

        switch (token->type) {
            case TOKEN_INT:
                ret_code = preced_analyze(token, hash_table, 0, str_1, stack);

                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                pop_retval(str_1);

                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            case TOKEN_STRING:
                ret_code = preced_analyze(token, hash_table, 0, str_1, stack);
                if (ret_code != OK) {
                    return ret_code;
                }
                pop_retval(str_1);
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            case TOKEN_FLOAT:

                ret_code = preced_analyze(token, hash_table, 0, str_1, stack);
                if (ret_code != OK) {
                    return ret_code;
                }
                pop_retval(str_1);
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            case TOKEN_NONE:

                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            case TOKEN_FNC:
                token_function_begin_with_y(str_1);
                item = htSearch(hash_table, token->attribute.string);
                if (item) {
                    if (item->type == TOKEN_ID) {
                        free(token_for_time.attribute.string);
                        free(token->attribute.string);
                        return ERR_UNDEF;

                    } else if (item->type == TOKEN_FNC) {
                        ret_code = func_for_FNC(token, stack, hash_table, false,
                                                count_of_params, str_1);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            return ret_code;
                        }
                        if (item->param_count != *count_of_params) {
                            free(token_for_time.attribute.string);
                            return ERR_INCOMPATIBLE;
                        }
                    }
                } else {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (item) {
                        if (item->type == TOKEN_ID) {
                            free(token_for_time.attribute.string);
                            free(token->attribute.string);
                            return ERR_UNDEF;

                        } else if (item->type == TOKEN_FNC) {
                            ret_code =
                                func_for_FNC(token, stack, hash_table, false,
                                             count_of_params, str_1);
                            if (ret_code != OK) {
                                free(token_for_time.attribute.string);
                                return ret_code;
                            }
                            if (item->param_count != *count_of_params) {
                                free(token_for_time.attribute.string);
                                return ERR_INCOMPATIBLE;
                            }
                        }
                    } else {
                        table_s *glob_hash_table = hash_table;

                        while (glob_hash_table->prev_hash_table != NULL) {
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string,
                                 token->type);
                        item =
                            htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        ret_code = func_for_FNC(token, stack, hash_table, false,
                                                count_of_params, str_1);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            return ret_code;
                        }
                        item->param_count = *count_of_params;
                    }
                }

                *count_of_params = 0;

                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL) {
                    return ERR_SYNTAX;
                }
                break;

            case TOKEN_ID:

                item = htSearch(hash_table, token->attribute.string);
                if (!item) {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (!item) {
                        free(token->attribute.string);
                        free(token_for_time.attribute.string);
                        return ERR_UNDEF;
                    } else {
                        if (item->type == TOKEN_FNC) {
                            free(token->attribute.string);
                            free(token_for_time.attribute.string);
                            return ERR_UNDEF;
                        } else if (item->type == TOKEN_ID) {
                            htInsert(hash_table, token->attribute.string,
                                     token->type);
                            item =
                                htSearch(hash_table, token->attribute.string);
                            item->id_declared = false;
                        }
                    }
                } else {
                    if (item->type == TOKEN_FNC) {
                        free(token->attribute.string);
                        free(token_for_time.attribute.string);
                        return ERR_UNDEF;
                    }
                }

                ret_code = preced_analyze(token, hash_table, 0, str_1, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);

                    return ret_code;
                }
                pop_retval(str_1);

                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);

                break;

            case TOKEN_LEN:

                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_L_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }

                if (token->type != TOKEN_STRING && token->type != TOKEN_ID) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }

                tmp_int = 1;
                token_function_begin_with_y(str_1);
                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                call_inserted_functions("len", str_1);
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_R_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;

            case TOKEN_SUBSTR:

                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_L_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_STRING && token->type != TOKEN_ID) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                token_function_begin_with_y(str_1);
                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_COMA) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);

                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_INT && token->type != TOKEN_ID) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 2;

                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_COMA) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_INT && token->type != TOKEN_ID) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 3;

                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_R_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                call_inserted_functions("substr", str_1);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;

            case TOKEN_ORD:
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_L_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_STRING) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                token_function_begin_with_y(str_1);
                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_COMA) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_INT) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 2;

                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                call_inserted_functions("ord", str_1);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_R_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);

                break;

            case TOKEN_CHR:
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_L_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_INT) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                token_function_begin_with_y(str_1);
                if (hash_table->prev_hash_table) {
                    function_call(token, &tmp_int, "LF", str_1);
                } else {
                    function_call(token, &tmp_int, "GF", str_1);
                }
                call_inserted_functions("chr", str_1);
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_R_BRACKET) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) {
                    free(token_for_time.attribute.string);
                    return ret_code;
                }
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    free(token_for_time.attribute.string);
                    return ERR_SYNTAX;
                }
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            case TOKEN_INPUT_I:
            case TOKEN_INPUT_S:
            case TOKEN_INPUT_F:
                ret_code = func_for_FNC(token, stack, hash_table, false,
                                        count_of_params, str_1);
                if (ret_code != OK) return ret_code;
                count_of_params = 0;

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND)
                    return ERR_SYNTAX;
                if (hash_table->prev_hash_table) {
                    retval_assign_function(&token_for_time, "LF", str_1);
                } else {
                    retval_assign_function(&token_for_time, "GF", str_1);
                }
                free(token_for_time.attribute.string);
                break;
            default:
                free(token_for_time.attribute.string);
                return ERR_SYNTAX;
                break;
        }
    } else {
        free(token_for_time.attribute.string);
        return ERR_SYNTAX;
    }
    return OK;
}

int func_prog(struct token_s *token, tStack *stack, int state, int ret_code,
              table_s *hash_table, struct dynamic_string *str_1) {
    int count_of_brackets = 0;
    int count_of_params = 0;
    int token_checked = 0;
    int actual_if = 0;
    int actual_while = 0;

    tHTItem *item;

    table_s *local_hash_table_def;

    struct dynamic_string *str;

    bool flag_def = false;

    int tmp_int = 1;

    (void)str_1;

    while (ret_code == OK) {
        if (!token_checked) {
            ret_code = get_token(token, stack);
        }
        token_checked = 0;
        state = token->type;

        if (ret_code != OK) {
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING ||
                (token->type == TOKEN_FNC)) {
                free(token->attribute.string);
            }
            break;
        }

        switch (state) {
            case TOKEN_EOF:

                return OK;
                break;

            case TOKEN_DEDEND:
                return OK;
                break;

            case TOKEN_EOL:
                break;

            case TOKEN_ID:

                item = htSearch(hash_table, token->attribute.string);
                if (item) {
                    if (item->type == TOKEN_FNC) {
                        free(token->attribute.string);
                        return ERR_SYNTAX;
                    }
                    if (item->id_declared == false) {
                        free(token->attribute.string);
                        return ERR_SYNTAX;
                    }
                    if (item->type == TOKEN_ID) {
                        if (flag_else) {
                            if (!(item->in_else)) {
                                if (hash_table->prev_hash_table) {
                                    define_variable_GF(token, "LF", str_1);
                                } else {
                                    define_variable_GF(token, "GF", str_1);
                                }
                            }
                        }
                    }
                } else {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (item) {
                        if (item->type == TOKEN_FNC) {
                            free(token->attribute.string);
                            return ERR_UNDEF;
                        }
                    }
                    htInsert(hash_table, token->attribute.string, token->type);
                    item = htSearch(hash_table, token->attribute.string);
                    item->id_declared = true;
                    item->in_if = 0;
                    item->in_else = 0;
                    if (hash_table->prev_hash_table) {
                        if (flag_if) {
                            item->in_if = flag_if;
                        }
                        if (flag_else) {
                            item->in_else = flag_else;
                        }
                    } else {
                        item->in_if = 1;
                        item->in_else = 1;
                    }
                    if (hash_table->prev_hash_table) {
                        define_variable_GF(token, "LF", str_1);
                    } else {
                        define_variable_GF(token, "GF", str_1);
                    }
                }

                ret_code = func_for_id(token, stack, hash_table,
                                       &count_of_params, str_1);
                if (ret_code != OK) return ret_code;

                count_of_params = 0;

                break;

            case TOKEN_FNC:

                token_function_begin_with_y(str_1);
                flag_def = false;
                item = htSearch(hash_table, token->attribute.string);
                if (item) {
                    if (item->type == TOKEN_ID) {
                        free(token->attribute.string);
                        return ERR_UNDEF;

                    } else if (item->type == TOKEN_FNC) {
                        ret_code =
                            func_for_FNC(token, stack, hash_table, flag_def,
                                         &count_of_params, str_1);
                        if (ret_code != OK) return ret_code;
                        if (item->param_count != count_of_params) {
                            return ERR_INCOMPATIBLE;
                        }
                    }
                } else {
                    item =
                        search_everywhere(hash_table, token->attribute.string);
                    if (item) {
                        if (item->type == TOKEN_ID) {
                            free(token->attribute.string);
                            return ERR_UNDEF;

                        } else if (item->type == TOKEN_FNC) {
                            ret_code =
                                func_for_FNC(token, stack, hash_table, flag_def,
                                             &count_of_params, str_1);
                            if (ret_code != OK) return ret_code;
                            if (item->param_count != count_of_params) {
                                return ERR_INCOMPATIBLE;
                            }
                        }
                    } else {
                        table_s *glob_hash_table = hash_table;

                        while (glob_hash_table->prev_hash_table != NULL) {
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string,
                                 token->type);
                        item =
                            htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        ret_code =
                            func_for_FNC(token, stack, hash_table, flag_def,
                                         &count_of_params, str_1);
                        if (ret_code != OK) return ret_code;
                        item->param_count = count_of_params;
                    }
                }

                count_of_params = 0;

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND)
                    return ERR_SYNTAX;
                break;

            case TOKEN_PRINT:
                flag_def = false;
                ret_code = func_for_FNC(token, stack, hash_table, flag_def,
                                        &count_of_params, str_1);
                if (ret_code != OK) return ret_code;
                count_of_params = 0;

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND)
                    return ERR_SYNTAX;
                break;
            case TOKEN_INPUT_I:
            case TOKEN_INPUT_S:
            case TOKEN_INPUT_F:

                flag_def = false;
                ret_code = func_for_FNC(token, stack, hash_table, flag_def,
                                        &count_of_params, str_1);
                if (ret_code != OK) return ret_code;
                count_of_params = 0;

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND)
                    return ERR_SYNTAX;
                break;
            case TOKEN_LEN:

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_L_BRACKET)
                    return ERR_SYNTAX;
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_STRING && token->type != TOKEN_ID) {
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF", str_1);
                call_inserted_functions("len", str_1);
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_R_BRACKET) {
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND)
                    return ERR_SYNTAX;
                break;

            case TOKEN_SUBSTR:

                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_L_BRACKET)
                    return ERR_SYNTAX;
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_STRING && token->type != TOKEN_ID) {
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF", str_1);
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_COMA) {
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_INT && token->type != TOKEN_ID) {
                    return ERR_SYNTAX;
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF", str_1);
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_COMA) {
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_INT && token->type != TOKEN_ID) {
                    return ERR_SYNTAX;
                }
                tmp_int = 3;
                function_call(token, &tmp_int, "TF", str_1);
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_R_BRACKET) {
                    return ERR_SYNTAX;
                }
                call_inserted_functions("substr", str_1);
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    return ERR_SYNTAX;
                }
                break;

            case TOKEN_ORD:
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_L_BRACKET)
                    return ERR_SYNTAX;
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_STRING &&
                    token->type != TOKEN_STRING) {
                    return ERR_SYNTAX;
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF", str_1);
                free(token->attribute.string);
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_COMA) {
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_INT && token->type != TOKEN_ID) {
                    return ERR_SYNTAX;
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF", str_1);
                call_inserted_functions("ord", str_1);
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_R_BRACKET) {
                    return ERR_SYNTAX;
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    return ERR_SYNTAX;
                }

                break;

            case TOKEN_CHR:
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_L_BRACKET)
                    return ERR_SYNTAX;
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_INT && token->type != TOKEN_ID)
                    return ERR_SYNTAX;
                tmp_int = 1;
                function_call(token, &tmp_int, "TF", str_1);
                call_inserted_functions("chr", str_1);
                if (token->type == TOKEN_ID) {
                    free(token->attribute.string);
                }
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_R_BRACKET) return ERR_SYNTAX;
                ret_code = get_token(token, stack);
                if (ret_code != OK) return ret_code;
                if (token->type != TOKEN_EOL && token->type != TOKEN_EOF &&
                    token->type != TOKEN_DEDEND) {
                    return ERR_SYNTAX;
                }
                break;

            case TOKEN_KEY_WORD:
                switch (token->attribute.key_word) {
                    case _IF_:
                        flag_if++;
                        count_of_if++;
                        actual_if =
                            count_of_if;

                        generate_if_head(str_1);
                        count_of_brackets = 0;
                        ret_code =
                            func_cond_mb(token, stack, count_of_brackets,
                                         hash_table, &count_of_params, str_1);
                        if (ret_code != OK) return ret_code;

                        count_of_params = 0;
                        if_body(&actual_if, str_1);
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) return ret_code;
                        if (token->type != TOKEN_INDEND)
                            return ERR_SYNTAX;
                        ret_code =
                            func_prog(token, stack, state, ret_code, hash_table,
                                      str_1);
                        if (ret_code != OK) return ret_code;

                        if (token->type != TOKEN_DEDEND)
                            return ERR_SYNTAX;

                        flag_if--;
                        ret_code = get_token(token, stack);
                        if (ret_code == OK) {
                            token_checked = 1;
                            if (token->type == TOKEN_KEY_WORD) {
                                if (token->attribute.key_word == _ELSE_) {
                                    token_checked = 0;
                                    flag_else++;

                                    ret_code = get_token(token, stack);
                                    if (ret_code != OK) {
                                        return ret_code;
                                    }
                                    if (token->type != TOKEN_DDOT) {
                                        return ERR_SYNTAX;
                                    }

                                    ret_code = get_token(token, stack);
                                    if (ret_code != OK) {
                                        return ret_code;
                                    }
                                    if (token->type != TOKEN_EOL) {
                                        return ERR_SYNTAX;
                                    }

                                    ret_code = get_token(token, stack);
                                    if (ret_code != OK) {
                                        return ret_code;
                                    }
                                    if (token->type != TOKEN_INDEND) {
                                        return ERR_SYNTAX;
                                    }

                                    found_else(&actual_if, str_1);
                                    ret_code = func_prog(token, stack, state,
                                                         ret_code, hash_table,
                                                         str_1);
                                    if (ret_code != OK) {
                                        return ret_code;
                                    }
                                    if (token->type != TOKEN_DEDEND) {
                                        return ERR_SYNTAX;
                                    }
                                    end_of_else(&actual_if, str_1);
                                    flag_else--;

                                } else {
                                    end_of_if(&actual_if, str_1);
                                }
                            } else {
                                end_of_if(&actual_if, str_1);
                            }
                        } else {
                            return ret_code;
                        }
                        break;

                    case _WHILE_:

                        str_init(
                            &str);
                        count_of_if++;
                        actual_while = count_of_if;
                        flag_while++;
                        generate_while_head_1(&actual_while, str_1);

                        count_of_brackets = 0;
                        ret_code =
                            func_cond_mb(token, stack, count_of_brackets,
                                         hash_table, &count_of_params, str_1);

                        if (ret_code != OK) {
                            str_clean(str);

                            return ret_code;
                        }

                        count_of_params = 0;
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) {
                            str_clean(str);

                            return ret_code;
                        }
                        if (token->type != TOKEN_INDEND) {
                            str_clean(str);

                            return ERR_SYNTAX;
                        }
                        while_body(&actual_while, str_1);

                        ret_code = func_prog(token, stack, state, ret_code,
                                             hash_table, str);

                        if (str->len) {
                            for (unsigned int i = 0; i < strlen(str->str);
                                 i++) {
                                add_char_to_str(str_1, (str->str)[i]);
                            }
                        }

                        flag_while--;

                        if (ret_code != OK) {
                            str_clean(str);

                            return ret_code;
                        }

                        if (token->type != TOKEN_DEDEND) {
                            str_clean(str);

                            return ERR_SYNTAX;
                        }

                        if (!flag_while && str_1->len) {
                            printf("%s", str_1->str);

                            free(str_1->str);
                            str_1->str = (string)malloc(DEF_STR_SIZE);
                            if (!str_1->str) {
                                str_clean(str);

                                return ERR_INTERNAL;
                            }
                            str_1->size = DEF_STR_SIZE;
                            str_1->len = 0;
                        }

                        generate_while_end(&actual_while, str_1);

                        str_clean(str);

                        break;

                    case _PASS_:
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) return ret_code;
                        if (token->type != TOKEN_EOL)
                            return ERR_SYNTAX;
                        break;

                    case _RETURN_:
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) return ret_code;
                        if (token->type == TOKEN_EOL) {
                            return OK;
                        } else {
                            ret_code = func_mb_ret(token, stack, hash_table,
                                                   &count_of_params, str_1);
                            if (ret_code != OK) return ret_code;
                            count_of_params = 0;
                        }
                        break;

                    case _DEF_:

                        flag_def = true;
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) {
                            free(token->attribute.string);
                            return ret_code;
                        }

                        if (token->type != TOKEN_FNC) {
                            free(token->attribute.string);
                            return ERR_SYNTAX;
                        }

                        if (hash_table->prev_hash_table) {
                            free(token->attribute.string);

                            return ERR_OTHER;
                        }
                        local_hash_table_def =
                            (table_s *)malloc(sizeof(table_s));
                        if (!local_hash_table_def) {
                            free(token->attribute.string);
                            return ERR_INTERNAL;
                        }
                        htInit(local_hash_table_def);

                        local_hash_table_def->prev_hash_table = hash_table;

                        define_function_begin(token, str_1);
                        retval_function(str_1);

                        struct token_s token_for_time;

                        token_for_time.type = token->type;
                        token_for_time.attribute = token->attribute;

                        token_for_time.attribute.string = (char *)malloc(
                            sizeof(char) * strlen(token->attribute.string) + 1);
                        strcpy(token_for_time.attribute.string,
                               token->attribute.string);

                        item = htSearch(hash_table, token->attribute.string);
                        if (item) {
                            if (item->type == TOKEN_ID) {
                                free(token->attribute.string);
                                free(token_for_time.attribute.string);
                                htClearAll(local_hash_table_def, false);
                                free(local_hash_table_def);
                                return ERR_UNDEF;
                            } else {
                                if (item->id_declared == false) {
                                    item->id_declared = true;
                                    ret_code = func_for_FNC(
                                        token, stack, local_hash_table_def,
                                        flag_def, &count_of_params, str_1);
                                    if (ret_code != OK) {
                                        free(token->attribute.string);
                                        free(token_for_time.attribute.string);
                                        htClearAll(local_hash_table_def, false);
                                        free(local_hash_table_def);
                                        return ret_code;
                                    }
                                    if (item->param_count != count_of_params) {
                                        free(token->attribute.string);
                                        free(token_for_time.attribute.string);
                                        htClearAll(local_hash_table_def, false);
                                        free(local_hash_table_def);
                                        return ERR_INCOMPATIBLE;
                                    }
                                } else {
                                    free(token->attribute.string);
                                    free(token_for_time.attribute.string);
                                    htClearAll(local_hash_table_def, false);
                                    free(local_hash_table_def);
                                    return ERR_UNDEF;
                                }
                            }
                        } else {
                            htInsert(hash_table, token->attribute.string,
                                     token->type);
                            item =
                                htSearch(hash_table, token->attribute.string);
                            item->id_declared = true;
                            ret_code =
                                func_for_FNC(token, stack, local_hash_table_def,
                                             flag_def, &count_of_params, str_1);
                            if (ret_code != OK) {
                                free(token->attribute.string);
                                free(token_for_time.attribute.string);
                                htClearAll(local_hash_table_def, false);
                                free(local_hash_table_def);
                                return ret_code;
                            }
                            item->param_count = count_of_params;
                        }

                        count_of_params = 0;
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ret_code;
                        }
                        if (token->type != TOKEN_DDOT) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ERR_SYNTAX;
                        }
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ret_code;
                        }
                        if (token->type != TOKEN_EOL) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ERR_SYNTAX;
                        }
                        ret_code = get_token(token, stack);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ret_code;
                        }
                        if (token->type != TOKEN_INDEND) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ERR_SYNTAX;
                        }
                        ret_code = func_prog(token, stack, state, ret_code,
                                             local_hash_table_def,
                                             str);
                        if (ret_code != OK) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ret_code;
                        }
                        if (token->type != TOKEN_DEDEND) {
                            free(token_for_time.attribute.string);
                            htClearAll(local_hash_table_def, false);
                            free(local_hash_table_def);
                            return ERR_SYNTAX;
                        }

                        def_function_end(&token_for_time, str_1);

                        free(token_for_time.attribute.string);
                        htClearAll(local_hash_table_def, false);
                        free(local_hash_table_def);
                        break;

                    default:
                        return ERR_SYNTAX;
                        break;
                }
                break;

            default:
                return ERR_SYNTAX;
                break;
        }
    }
    return ret_code;
}