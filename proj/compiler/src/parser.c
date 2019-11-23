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

#define N 32

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
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID)
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;
                    }
                } //----------------------------------------------------------- CONT FROM HERE
        func_for_FNC(file, token, stack, hash_table, false, count_of_params); // free string inside function
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
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID)
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;
                    }
                }
            func_for_FNC(file, token, stack, hash_table, false, count_of_params);
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
    
    count_of_params = 0;
    
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
            if(token_for_time.type == TOKEN_FNC || token_for_time.type == TOKEN_INPUT_I || token_for_time.type == TOKEN_INPUT_S || token_for_time.type == TOKEN_INPUT_F){
                return 1; // nastala ")"
            }else if(token_for_time.type == TOKEN_PRINT){
                return -1; // print nesmi byt bez parametru
            }
        }else{
            func_for_atributes(file, token, stack, count_of_params, hash_table, flag_def);
            if(token_for_time.type == TOKEN_FNC){
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
    if(hash_table->prev_hash_table){
        define_variable_GF(token, "LF");
    }else{
        define_variable_GF(token, "GF");
    }

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
        printf("SRABOTAL = \n"); 
        get_token(file, token, stack);
        //printf("T_tupe:%d\n", token->type);
        switch (token->type){
        case TOKEN_INT:
            //printf("SRABOTAL int \n");
            // if(hash_table->prev_hash_table){
            //     assign_to_variable(&token_for_time, token, "LF");
            // }else{
            //     assign_to_vatiable(&token_for_time, token, "GF");
            // }
            // PRECEDENCNI ANALYZA
            free(token_for_time.attribute.string);
            break;
        case TOKEN_STRING:
            // if(hash_table->prev_hash_table){
            //     assign_to_variable(&token_for_time, token, "LF");
            // }else{
            //     assign_to_vatiable(&token_for_time, token, "GF");
            // }
            // PRECEDENCNI ANALYZA
            free(token_for_time.attribute.string);
            free(token->attribute.string); // INSIDE PREC ANALY
            break;
        case TOKEN_FLOAT:
            // move float to ID
            // precedencni analyza
            // if(hash_table->prev_hash_table){
            //     assign_to_variable(&token_for_time, token, "LF");
            // }else{
            //     assign_to_vatiable(&token_for_time, token, "GF");
            // }
            // PRECEDENCNI ANALYZA
            free(token_for_time.attribute.string);
            break;
        case TOKEN_NONE:
            //printf("SRABOTAL NONE \n");
            // move NONE to ID
            // def_and_move(&token_for_time, &(*token));
            if(hash_table->prev_hash_table){
                assign_to_variable(&token_for_time, token, "LF");
            }else{
                assign_to_variable(&token_for_time, token, "GF");
            }
            free(token_for_time.attribute.string);
            break;
        case TOKEN_FNC:
            item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID)
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else{
                        table_s *glob_hash_table = hash_table;

                        while(glob_hash_table->prev_hash_table != NULL){
                            glob_hash_table = glob_hash_table->prev_hash_table;
                        }

                        htInsert(glob_hash_table, token->attribute.string, token->type);
                        item = htSearch(glob_hash_table, token->attribute.string);
                        item->id_declared = false;
                    }
                }
            token_function_begin_with_y(); // ------------------------------- CHECK
            func_for_FNC(file, token, stack, hash_table, false, count_of_params);
            // asigment_of_function_with_y(&token_for_time); // IDK 
            free(token_for_time.attribute.string);
            break;

        case TOKEN_ID:
            printf("naslo ID\n");
            item = htSearch(hash_table, token->attribute.string);
                if(!item){ // nenaslo
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(!item){
                        printf("ID WAS NOT DEFINED\n");
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
            printf("JA TUT\n");
            free(token_for_time.attribute.string);
            free(token->attribute.string); // INSIDE PA
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
 // mb need free
return 1; // WE R OK
}

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table, struct dynamic_string *str_1){

    int count_of_brackets = 0;
    int count_of_params = 0;
    int is_else = 0;
    int actual_if = 0;

    tHTItem *item;
    table_s *local_hash_table_if;
    table_s *local_hash_table_while;
    table_s *local_hash_table_else;
    table_s *local_hash_table_def;

    struct dynamic_string *str;

    bool flag_def = false;

    int substr_i = 0;
    int substr_n = 0;
    char *substr_s;
    char *ord_s;
    int ord_i = 0;
    (void)ord_i;
    (void)substr_n;
    (void)substr_i;
    (void)str_1;

    while (ret_code != -1){

            ret_code = get_token(file, token, stack);
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

            case TOKEN_ID: // DEF ID
                // check HASH TABLE
                item = htSearch(hash_table, token->attribute.string);
                if(item){ // naslo
                    if(item->type == TOKEN_FNC){
                        return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                    }
                    if(item->id_declared == false ){
                        return -1; // ERROR, DECLARED AFTER USED
                    }
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

                func_for_id(file, token, stack, hash_table, &count_of_params);
                count_of_params = 0;
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;
            
            case TOKEN_FNC: // call FNC
                // check HASH TABLE
                flag_def = false;
                item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID){
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                    }else if(item->type == TOKEN_FNC){
                        func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
                    }
                }else{
                    item = search_everywhere(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_ID){
                            return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                        }else if(item->type == TOKEN_FNC){
                            func_for_FNC(file, token, stack, hash_table, flag_def, &count_of_params);
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
            
            case TOKEN_LEN:
                // GENERACE CILOVEHO KODU
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING)
                    return -1; // MUST BE STRING
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
                }else{
                    substr_s = (char *) malloc(sizeof(char) * strlen(token->attribute.string) + 1);
                    strcpy(substr_s, token->attribute.string);
                    free(token->attribute.string);
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(substr_s);
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(substr_s);
                    return -1; // MUST BE INDEX - ZACATEK RETEZCE (INT)
                }else{
                    substr_i = token->attribute.int_val;
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(substr_s);
                    return -1; // MUST BE something , something
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(substr_s);
                    return -1; // MUST BE RANGE OF NEW STRING
                }else{
                    substr_n = token->attribute.int_val;
                }
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    free(substr_s);
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(substr_s);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                // GENERACE CILOVEHO KODU
                free(substr_s);
                break;

            case TOKEN_ORD:
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_STRING){
                    return -1; // MUST BE STRING
                }else{
                    ord_s = (char *) malloc(sizeof(char) * strlen(token->attribute.string) + 1);
                    strcpy(ord_s, token->attribute.string);
                    free(token->attribute.string);
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA){
                    free(ord_s);
                    return -1; // MUST BE string , int
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(ord_s);
                    return -1; // MUST BE RANGE OF NEW STRING
                }else{
                    ord_i = token->attribute.int_val;
                }
                get_token(file, token, stack);
                if (token->type != TOKEN_R_BRACKET){
                    free(ord_s);
                    return -1; // MUST BE R BRACKET
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND){
                    free(ord_s);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                }
                //GENERACE CILOVEHO KODU
                free(ord_s);
                break;

            case TOKEN_CHR:
                get_token(file, token, stack);
                if(token->type != TOKEN_L_BRACKET)
                    return -1; // MUST BE L BRACKET
                get_token(file, token, stack);
                if(token->type != TOKEN_INT)
                    return -1;
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
                case _IF_:
            
                    local_hash_table_if = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table_if)
                        return ERR_INTERNAL;
                    htInit(local_hash_table_if);

                    local_hash_table_if->prev_hash_table = hash_table;
                    
                    count_of_if++; // if1, if2, if3 for other ifs
                    actual_if = count_of_if; // aktualni if/else, abychom mohli poznat ktery if/else to je
                    // generate_if_head();
                    (void)actual_if;
                    count_of_brackets = 0;
                    func_cond_mb(file, token, stack, count_of_brackets, local_hash_table_if, &count_of_params);
                    count_of_params = 0;

                    // GENERACE JMPIFNEQ

                    // get_token(file, token, stack);
                    // if(token->type != TOKEN_DDOT)
                    //     return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, local_hash_table_if, str); // inside if, generace body
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT

                    if(is_else){
                        // GENERACE endif s else
                    }else{
                        // GENERACE endif bez else
                    }

                    // if_end(); // NO NEED I THINK
                    htClearAll(local_hash_table_if);
                    free(local_hash_table_if);
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
                    generate_while_end();

                    str_clean(str);
                    htClearAll(local_hash_table_while);
                    free(local_hash_table_while);
                    break;

                case _ELSE_:

                    is_else = 1;
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
                    func_prog(file, token, stack, state, ret_code, local_hash_table_else, str); // inside if
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    htClearAll(local_hash_table_else);
                    free(local_hash_table_else);
                    break;

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
                    if(token->type != TOKEN_FNC)
                        return -1; // must be name of FUNC
                    //CHECK HASH TABLE
                    if(hash_table->prev_hash_table){
                        return -1; // DEF CAN BE ONLY IN GLOBAL FRAME
                    }
                    local_hash_table_def = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table_def)
                        return ERR_INTERNAL;
                    htInit(local_hash_table_def);

                    local_hash_table_def->prev_hash_table = hash_table;

                    define_function_begin(token);
                    retval_function();
                    
                    item = htSearch(hash_table, token->attribute.string);
                    if(item){
                        if(item->id_declared == false){
                            item->id_declared = true;
                            func_for_FNC(file, token, stack, local_hash_table_def, flag_def, &count_of_params);
                        }else{
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