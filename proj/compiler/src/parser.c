/**
 * \file  ./parser.c
 * \brief Implimetation of syntax and semantics analyzes
 * 
 * \author Korniienko Oleksii (xkorni02@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"
#include "codegenerator.h"
#include "stack.h"
#include "dynamic_string.h"

int flag_while = 0;
int count_of_if = 0;

int func_mb_ret(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params){
    tHTItem *item;

    switch (token->type){
    case TOKEN_NONE:
        return 1; // we R ok
        break;
    case TOKEN_FNC:
        item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID){
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else if(item->type == TOKEN_FNC){
                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        if(item->param_count != *count_of_params){
                            return -1; // ERROR, no same count of params
                        }
                    }
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID){
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                        }else if(item->type == TOKEN_FNC){
                            func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                            if(item->param_count != *count_of_params){
                                return -1; // no same counf of params
                            }
                        }
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        item->param_count = *count_of_params;
                    }
                } 
        *count_of_params = 0; // free string inside function
        break;
    case TOKEN_ID:
        // must be free string mb inside precedencni analyzy
    case TOKEN_INT:
    case TOKEN_STRING:
    case TOKEN_FLOAT:
        // PRECEDENCNI ANALYZA
        break;

    default:
        return -1; // something else
        break;
    }
return 1;
}

int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets, table_s *hash_table, int * count_of_params){
    get_token(file, token, stack);
    if(token->type == TOKEN_L_BRACKET){
        count_of_brackets++;
        func_cond_mb(file, token, stack, count_of_brackets, hash_table, count_of_params);
        }
    if(token->type == TOKEN_FNC){
            tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID){
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else if(item->type == TOKEN_FNC){
                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        if(item->param_count != *count_of_params){
                            return -1; // ERROR, no same count of params
                        }
                    }
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID){
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                        }else if(item->type == TOKEN_FNC){
                            func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                            if(item->param_count != *count_of_params){
                                return -1; // no same counf of params
                            }
                        }
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        item->param_count = *count_of_params;
                    }
                }
            *count_of_params = 0;
        }else{
            // PRECEDENCNI ANALYZA
        }
        if(count_of_brackets != 0){
            get_token(file, token, stack);
            if(token->type == TOKEN_R_BRACKET){
                count_of_brackets--;
                return 1; 
            }else{
                return -1; // MUST BE THE SAME NUMBER OF BRACKETS
            }
        }
    return 1; // WE R OK
}

int check_next_token(FILE *file, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def){
    get_token(file, token, stack);
    if(token->type == TOKEN_COMA){
        get_token(file, token, stack);
        func_for_atributes(file, token, stack, count_of_params, hash_table, flag_def);
    }else if(token->type == TOKEN_R_BRACKET){
        return 1; // WE R OK
    }
return -1; // ERROR, dostali jsme neco jineho nez "," nebo ")"
}

int func_for_atributes(FILE *file, struct token_s *token, tStack *stack, int *count_of_params, table_s *hash_table, bool flag_def){
    (*count_of_params)++;
    switch (token->type){
    case TOKEN_ID:
        // CHECK HASH
        // IF DEF = DEF ID, IF CALL = USE ID
        if(flag_def == true){ // if DEF FUNC, DEF ID
            tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){ // naslo
                    return -1; // atributes have the same names
                }else{ // nenaslo
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_FNC){
                            return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                        }   
                    }
                    htInsert(hash_table, token->attribute.string, token->type);
                    item = htSearch(hash_table, token->attribute.string);
                    item->id_declared = true;
                }
        }else{ // IF CALL FUNC, USE ID
            tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(!item){ // nenaslo
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(!item){
                        return -1; // id was not defined
                    }else{
                        if(item->type == TOKEN_FNC){
                            return -1; // finded FNC, not ID
                        }else if(item->type == TOKEN_ID){
                            htInsert(hash_table, token->attribute.string, token->type);
                            item = htSearch(hash_table, token->attribute.string);
                            item->id_declared = false;
                        }
                    }
                }else{
                    if(item->type == TOKEN_FNC){
                        return -1; // finded FNC, not ID
                    }
                }
        }
        if(flag_def){
            def_function_call(token, count_of_params, "LF");
        }else{
            if(hash_table->prev_hash_table){
                function_call(token, count_of_params, "TF");
            }
        }
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def); 
        break;
    case TOKEN_INT:
        if(flag_def){
            return -1; // ERROR
        }else{
            if(hash_table->prev_hash_table){
                function_call(token, count_of_params, "LF");
            }else{
                function_call(token, count_of_params, "GF");
            }
        }
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
    case TOKEN_FLOAT:
        if(flag_def){
            return -1; // ERROR
        }else{
            if(hash_table->prev_hash_table){
                function_call(token, count_of_params, "LF");
            }else{
                function_call(token, count_of_params, "GF");
            }
        }
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
    case TOKEN_STRING:
        if(flag_def){
            return -1; // ERROR
        }else{
            if(hash_table->prev_hash_table){
                function_call(token, count_of_params, "LF");
            }else{
                function_call(token, count_of_params, "GF");
            }
        }
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
    default:
        return -1; // neco jineho nez int/string/float/id
        break;
    }
return 1; // WE R OK
}

int func_for_FNC(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, bool flag_def, int *count_of_params){
    
    *count_of_params = 0;
    
    struct token_s token_for_time; // token_for_time
    
    token_for_time.type=token->type;
    token_for_time.attribute=token->attribute;
    if(token->type == TOKEN_FNC){
        token_for_time.attribute.string = (char *) malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        strcpy(token_for_time.attribute.string, token->attribute.string);
        free(token->attribute.string);
    }    

    get_token(file, token, stack);

    if(token->type == TOKEN_L_BRACKET){
        get_token(file, token, stack);
        if(token->type == TOKEN_R_BRACKET){
            if(token_for_time.type == TOKEN_FNC){
                if(!flag_def)
                    call_function(&token_for_time);
                free(token_for_time.attribute.string);
                return 1; // nastala ")"
            }else if(token_for_time.type == TOKEN_INPUT_I || token_for_time.type == TOKEN_INPUT_S || token_for_time.type == TOKEN_INPUT_F){
                return 1;
            }else if(token_for_time.type == TOKEN_PRINT){
                return -1; // print nesmi byt bez parametru
            }
        }else{
            func_for_atributes(file, token, stack, count_of_params, hash_table, flag_def);
            if(token_for_time.type == TOKEN_FNC){
                if(!flag_def)
                    call_function(&token_for_time);
                free(token_for_time.attribute.string);
            }
            if(token_for_time.type == TOKEN_PRINT){
                // GENERACE CILOVEHO KODU
                
            }
            if(token_for_time.type == TOKEN_INPUT_I || token_for_time.type == TOKEN_INPUT_S || token_for_time.type == TOKEN_INPUT_F){
                return -1; // INPUT NESMI MIT PARAMETRY
            }
        }
    }else{
        return -1; // ERROR
    }
return 1; // WE R OK
}

int func_for_id(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, int *count_of_params){
    //printf("SRABOTAL func_for_id \n"); 
    tHTItem *item;
    int tmp_int = 0;

    struct token_s token_for_time; // token_for_time
    
    token_for_time.type=token->type;
    token_for_time.attribute=token->attribute;
    if(token->type == TOKEN_ID){
        token_for_time.attribute.string = (char *) malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        strcpy(token_for_time.attribute.string, token->attribute.string);
    }

    //printf("T_type: %d\n", token->type);
    //printf("must be a: %s\n", token_for_time.attribute.string);

    free(token->attribute.string);
    //printf("must be a: %s\n", token_for_time.attribute.string);
    get_token(file, token, stack);
    if(token->type == TOKEN_ASSIGN){
        // printf("SRABOTAL = \n"); 
        get_token(file, token, stack);
        //printf("T_tupe:%d\n", token->type);
        switch (token->type){
        case TOKEN_INT:
            // PRECEDENCNI ANALYZA
            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            break;
        case TOKEN_STRING:
            // PRECEDENCNI ANALYZA
            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            free(token->attribute.string); // INSIDE PREC ANALY
            break;
        case TOKEN_FLOAT:
            // PRECEDENCNI ANALYZA
            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            break;
        case TOKEN_NONE: // ----------------------------------------- ASK RAUL about ID = NONE
            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            break;
        case TOKEN_FNC:
            token_function_begin_with_y();
            item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID){
                        free(token_for_time.attribute.string);
                        free(token->attribute.string);
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else if(item->type == TOKEN_FNC){
                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        if(item->param_count != *count_of_params){
                            free(token_for_time.attribute.string);
                            return -1; // ERROR, no same count of params
                        }
                    }
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID){
                            free(token_for_time.attribute.string);
                            free(token->attribute.string);
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                        }else if(item->type == TOKEN_FNC){
                            func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                            if(item->param_count != *count_of_params){
                                free(token_for_time.attribute.string);
                                return -1; // no same counf of params
                            }
                        }
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        func_for_FNC(file, token, stack, hash_table, false, count_of_params);
                        item->param_count = *count_of_params;
                    }
                }

            // asigment_of_function_with_y(&token_for_time); // IDK 
            *count_of_params = 0;

            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            break;

        case TOKEN_ID:
            // printf("naslo ID\n");
            item = htSearch(hash_table, token->attribute.string);
                if(!item){ // nenaslo
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(!item){
                        // printf("ID WAS NOT DEFINED\n");
                        free(token->attribute.string);
                        free(token_for_time.attribute.string);
                        return -1; // id was not defined
                    }else{
                        if(item->type == TOKEN_FNC){
                            free(token->attribute.string);
                            free(token_for_time.attribute.string);
                            return -1; // finded FNC, not ID
                        }else if(item->type == TOKEN_ID){
                            htInsert(hash_table, token->attribute.string, token->type);
                            item = htSearch(hash_table, token->attribute.string);
                            item->id_declared = false;
                        }
                    }
                }else{
                    if(item->type == TOKEN_FNC){
                        free(token->attribute.string);
                        free(token_for_time.attribute.string);
                        return -1; // finded FNC, not ID
                    }
                }
            // PRECEDENCNI ANALYZA
            // printf("JA TUT\n");

            if(hash_table->prev_hash_table){
                retval_assign_function(&token_for_time, "LF");
            }else{
                retval_assign_function(&token_for_time, "GF");
            }
            free(token_for_time.attribute.string);
            free(token->attribute.string); // INSIDE PA
            break;

        case TOKEN_LEN: // ADD SOME CODEGENERATOR FUNCTIONS FOR END ----------------------------------------
                // GENERACE CILOVEHO KODU
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE L BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE STRING
                }
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("len");
                free(token->attribute.string);
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(token_for_time.attribute.string);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                free(token_for_time.attribute.string);
                break;

            case TOKEN_SUBSTR: // CILOVY KOD BUDE KONTROLOVAT VSECHNO, JA JEN MAM PREDAT TAM VSECHNY PARAMETRY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE L BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE STRING
                }
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                free(token->attribute.string);
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE INDEX - ZACATEK RETEZCE (INT)
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF");
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE RANGE OF NEW STRING
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF");
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE R BRACKET
                }
                call_inserted_functions("substr");
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(token_for_time.attribute.string);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                free(token_for_time.attribute.string);
                break;

            case TOKEN_ORD: // RDY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE L BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE STRING
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF");
                free(token->attribute.string);
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE string , int
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE RANGE OF NEW STRING
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("ord");
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(token_for_time.attribute.string);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                free(token_for_time.attribute.string);
                //GENERACE CILOVEHO KODU
                break;

            case TOKEN_CHR: // RDY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1; // MUST BE L BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(token_for_time.attribute.string);
                    return -1;
                }
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("chr");
                get_token(file, token, stack);
                if(token->type != TOKEN_R_BRACKET){
                    free(token_for_time.attribute.string);
                    return -1;
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(token_for_time.attribute.string);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                free(token_for_time.attribute.string);
                break;
        default:
            free(token_for_time.attribute.string);
            return -1;
            break;
        }
    }else{
        free(token_for_time.attribute.string);
        return -1; // ERROR must be =
    }
return 1; // WE R OK
}

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table, struct dynamic_string *str_1){

    int count_of_brackets = 0;
    int count_of_params = 0;
    int token_checked = 0;
    int actual_if = 0;

    tHTItem *item;
    table_s *local_hash_table_if;
    table_s *local_hash_table_while;
    table_s *local_hash_table_else;
    table_s *local_hash_table_def;

    struct dynamic_string *str;

    bool flag_def = false;

    int tmp_int = 0;

    (void)str_1;

    while (ret_code != -1){

            if(!token_checked){
            ret_code = get_token(file, token, stack);
            }
            token_checked = 0;
            state = token->type;      

            if (ret_code != OK){
                if (token->type == TOKEN_ID || token->type == TOKEN_STRING || (token->type ==  TOKEN_FNC)){
                    free(token->attribute.string);
                }
                break;
            }
        
        //printf("T_type:%d\n", token->type);
        //printf("T_att:%d\n",token->attribute);

        switch (state){

            case TOKEN_EOF:
                // if (token->attribute.string != NULL){
                //     free(token->attribute.string);
                // } // MB NEED 
                return 1;
                break;
            
            case TOKEN_DEDEND:
                return 1;
                break;

            case TOKEN_EOL:
                break;

            case TOKEN_ID: // DEF ID // RDY
                // check HASH TABLE
                
                item = htSearch(hash_table, token->attribute.string);
                if(item){ // naslo
                    if(item->type == TOKEN_FNC){
                        free(token->attribute.string);
                        return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                    }
                    if(item->id_declared == false ){
                        free(token->attribute.string);
                        return -1; // ERROR, DECLARED AFTER USED
                    }
                }else{ // nenaslo
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_FNC){
                            free(token->attribute.string);
                            return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                        }   
                    }
                    htInsert(hash_table, token->attribute.string, token->type);
                    item = htSearch(hash_table, token->attribute.string);
                    item->id_declared = true;

                    if(hash_table->prev_hash_table){
                        define_variable_GF(token, "LF");
                    }else{
                        define_variable_GF(token, "GF");
                    }
                }

                func_for_id(file, token, stack, hash_table, &count_of_params);
                count_of_params = 0;
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;
            
            case TOKEN_FNC: // call FNC // RDY
                // check HASH TABLE
                token_function_begin_with_y();
                flag_def = false;
                item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID){
                        free(token->attribute.string);
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else if(item->type == TOKEN_FNC){
                        func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
                        if(item->param_count != count_of_params){
                            return -1; // ERROR, no same count of params
                        }
                    }
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID){
                            free(token->attribute.string);
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                        }else if(item->type == TOKEN_FNC){
                            func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
                            if(item->param_count != count_of_params){
                                return -1; // ERROR, no same count of params
                            }
                        }
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;

                        func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
                        item->param_count = count_of_params;
                    }
                }

                count_of_params = 0;
                
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;
            
            case TOKEN_PRINT:
            case TOKEN_INPUT_I:
            case TOKEN_INPUT_S:
            case TOKEN_INPUT_F:
                flag_def = false;
                func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
                count_of_params = 0;

                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;
            
            case TOKEN_LEN: // RDY
                // GENERACE CILOVEHO KODU
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    return -1; // MUST BE STRING
                }
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("len");
                free(token->attribute.string);
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;

            case TOKEN_SUBSTR: // CILOVY KOD BUDE KONTROLOVAT VSECHNO, JA JEN MAM PREDAT TAM VSECHNY PARAMETRY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    return -1; // MUST BE STRING
                }
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                free(token->attribute.string);
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    return -1; // MUST BE INDEX - ZACATEK RETEZCE (INT)
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF");
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    return -1; // MUST BE RANGE OF NEW STRING
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF");
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    return -1; // MUST BE R BRACKET
                }
                call_inserted_functions("substr");
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                break;

            case TOKEN_ORD: // RDY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    return -1; // MUST BE STRING
                }
                tmp_int = 2;
                function_call(token, &tmp_int, "TF");
                free(token->attribute.string);
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    return -1; // MUST BE string , int
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    return -1; // MUST BE RANGE OF NEW STRING
                }
                tmp_int = 1;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("ord");
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                //GENERACE CILOVEHO KODU
                break;

            case TOKEN_CHR: // RDY
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_INT)
                    return -1;
                tmp_int = 0;
                function_call(token, &tmp_int, "TF");
                call_inserted_functions("chr");
                get_token(file, token, stack);
                if(token->type != TOKEN_R_BRACKET)
                    return -1;
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                break;

            case TOKEN_KEY_WORD:
                switch (token->attribute.key_word){
                case _IF_: // RDY w/o condition
                    local_hash_table_if = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table_if)
                        return ERR_INTERNAL;
                    htInit(local_hash_table_if);

                    local_hash_table_if->prev_hash_table = hash_table;
                    
                    count_of_if++; // if1, if2, if3 for other ifs
                    actual_if = count_of_if; // aktualni if/else, abychom mohli poznat ktery if/else to je
                    generate_if_head();
                    create_returnvalue("LF");
                    (void)actual_if;
                    count_of_brackets = 0;
                    func_cond_mb(file, token, stack, count_of_brackets, local_hash_table_if, &count_of_params);
                    // GENERATION OF CONDITION
                    count_of_params = 0;
                    if_body(&actual_if);// GENERACE JMPIFNEQ
                    //get_token(file, token, stack);
                    // if(token->type != TOKEN_DDOT){
                    //     return -1; // must be :
                    // }
                    //printf("im here\n");
                    get_token(file, token, stack);
                    //printf("%d\n", token->type);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, local_hash_table_if, str); // inside if, generace body
                    //printf("ja tutu\n");
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT

                    htClearAll(local_hash_table_if);
                    free(local_hash_table_if);

                    ret_code = get_token(file, token, stack);
                    if(ret_code != -1){
                        token_checked = 1;
                        if(token->type == TOKEN_KEY_WORD){
                            if(token->attribute.key_word == _ELSE_){
                                token_checked = 0;
                                local_hash_table_else = (table_s *) malloc(sizeof(table_s));
                                if(!local_hash_table_else)
                                    return ERR_INTERNAL;
                                htInit(local_hash_table_else);

                                local_hash_table_else->prev_hash_table = hash_table;

                                get_token(file, token, stack);
                                if(token->type != TOKEN_DDOT)
                                    return -1; // must be :
                                get_token(file, token, stack);
                                if(token->type != TOKEN_EOL)
                                    return -1; // must be end of line
                                get_token(file, token, stack);
                                if(token->type != TOKEN_INDEND)
                                    return -1; // must be INDENT
                                found_else(&actual_if);
                                func_prog(file, token, stack, state, ret_code, local_hash_table_else, str); // inside if
                                if(token->type != TOKEN_DEDEND)
                                    return -1; // must be DEDENT
                                end_of_else(&actual_if);
                                // if_end(); // NO NEED I THINK
                                htClearAll(local_hash_table_else);
                                free(local_hash_table_else);
                            }else{
                                end_of_if(&actual_if);
                            }
                        }else{
                            end_of_if(&actual_if);
                        }
                    }else{
                        return -1;
                    }
                    break;
                
                case _WHILE_:
                    
                    str_init(&str); // pomocny dynamicky radek pro spravny vypis

                    generate_while_head_1();
                    local_hash_table_while = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table_while)
                        return ERR_INTERNAL;
                    htInit(local_hash_table_while);

                    local_hash_table_while->prev_hash_table = hash_table;
                    
                    count_of_brackets = 0;
                    func_cond_mb(file, token, stack, count_of_brackets, local_hash_table_while, &count_of_params);
                    count_of_params = 0;
                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    
                    flag_while++;
                    func_prog(file, token, stack, state, ret_code, local_hash_table_while, str); // inside while
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    flag_while--;
                    generate_while_end(&count_of_if);

                    str_clean(str);
                    htClearAll(local_hash_table_while);
                    free(local_hash_table_while);
                    break;

                // case _ELSE_:
                //     // token_checked = 1;
                //     local_hash_table_else = (table_s *) malloc(sizeof(table_s));
                //     if(!local_hash_table_else)
                //         return ERR_INTERNAL;
                //     htInit(local_hash_table_else);

                //     local_hash_table_else->prev_hash_table = hash_table;

                //     get_token(file, token, stack);
                //     if(token->type != TOKEN_DDOT)
                //         return -1; // must be :
                //     get_token(file, token, stack);
                //     if(token->type != TOKEN_EOL)
                //         return -1; // must be end of line
                //     get_token(file, token, stack);
                //     if(token->type != TOKEN_INDEND)
                //         return -1; // must be INDENT
                //     found_else(&actual_if);
                //     func_prog(file, token, stack, state, ret_code, local_hash_table_else, str); // inside if
                //     if(token->type != TOKEN_DEDEND)
                //         return -1; // must be DEDENT
                //     htClearAll(local_hash_table_else);
                //     free(local_hash_table_else);
                //     break;

                case _NONE_:
                        // NO NEED HERE ___ THINK
                    break;

                case _PASS_:
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // ERROR MUST BE EOL
                    break;

                case _RETURN_:
                    get_token(file, token, stack);
                    if(token->type == TOKEN_EOL){
                        return 1; // WE R OK
                    }else{
                        func_mb_ret(file, token, stack, hash_table, &count_of_params);
                        count_of_params = 0;
                        get_token(file, token, stack);
                        if(token->type != TOKEN_EOL)
                            return -1; // must be EOL
                    }
                    break;

                case _DEF_: // RDY
                    flag_def = true;
                    get_token(file, token, stack);
                    if(token->type != TOKEN_FNC){
                        free(token->attribute.string);
                        return -1; // must be name of FUNC
                    }
                    //CHECK HASH TABLE
                    if(hash_table->prev_hash_table){
                        free(token->attribute.string);
                        return -1; // DEF CAN BE ONLY IN GLOBAL FRAME
                    }
                    local_hash_table_def = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table_def){
                        free(token->attribute.string);
                        return ERR_INTERNAL;
                    }
                    htInit(local_hash_table_def);

                    local_hash_table_def->prev_hash_table = hash_table;

                    define_function_begin(token);
                    retval_function();
                    
                    item = htSearch(hash_table, token->attribute.string);
                    if(item){
                        if(item->id_declared == false){
                            item->id_declared = true;
                            func_for_FNC(file, token, stack, local_hash_table_def, flag_def, &count_of_params);
                            if(item->param_count != count_of_params){
                                return -1; // ERROR, no same count of params
                            }
                        }else{
                            free(token->attribute.string);
                            return -1; // try to daclare fnc with the same name
                        }
                    }else{
                        htInsert(hash_table, token->attribute.string, token->type);
                        item = htSearch(hash_table, token->attribute.string);
                        item->id_declared = true;
                        func_for_FNC(file, token, stack, local_hash_table_def, flag_def, &count_of_params);
                        item->param_count = count_of_params;
                    }

                    count_of_params = 0;
                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, local_hash_table_def, str); // inside func
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    def_function_end();
                    htClearAll(local_hash_table_def);
                    free(local_hash_table_def);
                    break;
                
                default:
                    return -1; // THISH KW DOES NOT EXIST
                    break;
                }
                break;

            default:
                return -1; // THIS OPERATION DOES NOT EXIST
                break;
            }
    }
    return 1;
}