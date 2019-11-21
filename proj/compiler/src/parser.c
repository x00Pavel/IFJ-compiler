#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"
#include "parser.h"
#include "codegenerator.h"
#include "./stack/c202.h"


int func_mb_ret(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table){

    switch (token->type){
    case TOKEN_NONE:
        return 1; // we R ok
        break;
    case TOKEN_FNC:
        tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = find_key(hash_table, token->attribute.string);
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
        func_for_FNC(file, token, stack, hash_table, false); // free string inside function
        break;
    case TOKEN_ID:
        // must be free string mb inside precedencni analyzy
    case TOKEN_INT:
    case TOKEN_STRING:
    case TOKEN_FLOAT:
        // PRECEDENCNI ANALYZA
        break;

    default:
        break;
    }
return 1;
}

int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets, table_s *hash_table){
    get_token(file, token, stack);
    if(token->type == TOKEN_L_BRACKET){
        count_of_brackets++;
        func_cond_mb(file, token, stack, count_of_brackets, hash_table);
        }
    if(token->type == TOKEN_FNC){
            tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = find_key(hash_table, token->attribute.string);
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
            func_for_FNC(file, token, stack, hash_table, false);
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
                    item = find_key(hash_table, token->attribute.string);
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
                    item = find_key(hash_table, token->attribute.string);
                    if(!item){
                        return -1; // id was not defined
                    }else{
                        if(item->type == TOKEN_FNC){
                            return -1; // finded FNC, not ID
                        }
                    }
                }else{
                    if(item->type == TOKEN_FNC){
                        return -1; // finded FNC, not ID
                    }
                }
        }
        token_function_body(token, count_of_params);
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def); 
        break;
    case TOKEN_INT:
        token_function_body(token, count_of_params);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
    case TOKEN_FLOAT:
        token_function_body(token, count_of_params);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
    case TOKEN_STRING:
        token_function_body(token, count_of_params);
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params, hash_table, flag_def);
        break;
        // MB NEED CASE TOKEN_FNC ----------------------------------------------------------
    default:
        return -1; // neco jineho nez int/string/float/id
        break;
    }
return 1; // WE R OK
}

int func_for_FNC(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table, bool flag_def){
    
    int count_of_params = 0;
    
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
            func_for_atributes(file, token, stack, &count_of_params, hash_table, flag_def);
            if(token_for_time.type == TOKEN_FNC){
                token_function_end(&token_for_time);
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

int func_for_id(FILE *file, struct token_s *token, tStack *stack, table_s *hash_table){
    //printf("SRABOTAL func_for_id \n");
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
        //printf("SRABOTAL = \n"); 
        get_token(file, token, stack);
        //printf("T_tupe:%d\n", token->type);
        switch (token->type){
        case TOKEN_INT: // ------------------------------------------------------- ADD ID
            //printf("SRABOTAL int \n");
            // move int to ID
            // precedencni analyza
            //define_variable(&token_for_time);
            id_is_equal_to(&token_for_time ,token);
            free(token_for_time.attribute.string); // --------------------- precedencni analyza
            break;
        case TOKEN_STRING:
            // move string to ID
            // precedencni analyza
            id_is_equal_to(&token_for_time, token);
            free(token_for_time.attribute.string); // --------------------- precedencni analyza
            break;
        case TOKEN_FLOAT:
            // move float to ID
            // precedencni analyza
            id_is_equal_to(&token_for_time, token);
            free(token_for_time.attribute.string); // --------------------- precedencni analyza
            break;
        case TOKEN_NONE:
            //printf("SRABOTAL NONE \n");
            // move NONE to ID
            // def_and_move(&token_for_time, &(*token));
            id_is_equal_to(&token_for_time, token);
            free(token_for_time.attribute.string);
            break;
        case TOKEN_FNC:
            token_function_begin_with_y(token, &token_for_time);
            tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = find_key(hash_table, token->attribute.string);
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
            func_for_FNC(file, token, stack, hash_table, false);
            asigment_of_function_with_y(&token_for_time);
            free(token_for_time.attribute.string);
            break;

        case TOKEN_ID:
            // -------------------------------------------------------------- ADD CODE
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

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code, table_s *hash_table){

    int count_of_brackets = 0;

    bool flag_def = false;

    int substr_i = 0;
    int substr_n = 0;
    char *substr_s;

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
                tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){ // naslo
                    if(item->type == TOKEN_FNC){
                        return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                    }
                    if(item->id_declared == false ){
                        return -1; // ERROR, DECLARED AFTER USED
                    }
                }else{ // nenaslo
                    item = find_key(hash_table, token->attribute.string);
                    if(item){
                        if(item->type == TOKEN_FNC){
                            return -1; // TRY TO DEFINE ID WITH THE SAME NAME AS FNC
                        }   
                    }
                    htInsert(hash_table, token->attribute.string, token->type);
                    item = htSearch(hash_table, token->attribute.string);
                    item->id_declared = true;
                }

                func_for_id(file, token, stack, hash_table);
            
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                break;
            
            case TOKEN_FNC: // call FNC
                // check HASH TABLE
                flag_def = false;
                tHTItem *item = htSearch(hash_table, token->attribute.string);
                if(item){
                    if(item->type == TOKEN_ID)
                        return -1; // ERROR, FNC WITH THE SAME NAME AS ID
                }else{
                    item = find_key(hash_table, token->attribute.string);
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

                func_for_FNC(file, token, stack, hash_table, flag_def);
                
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                    
                break;
            
            case TOKEN_PRINT:
            case TOKEN_INPUT_I:
            case TOKEN_INPUT_S:
            case TOKEN_INPUT_F:
                flag_def = false;
                func_for_FNC(file, token, stack, hash_table, flag_def);

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
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA)
                    free(substr_s);
                    return -1; // MUST BE something , something
                get_token(file, token, stack);
                if(token->type != TOKEN_INT){
                    free(substr_s);
                    return -1; // MUST BE INDEX - ZACATEK RETEZCE (INT)
                }else{
                    substr_i = token->attribute.int_val;
                }
                get_token(file, token, stack);
                if(token->type != TOKEN_COMA)
                    free(substr_s);
                    return -1; // MUST BE something , something
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
                if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                    free(substr_s);
                    return -1; // ERROR MUST BE EOL or EOF or DEDENT
                // GENERACE CILOVEHO KODU
                free(substr_s);
                break;

            case TOKEN_ORD:

                break;

            case TOKEN_CHR:

                break;

            case TOKEN_KEY_WORD:
                switch (token->attribute.key_word){
                case _IF_:
            
                    count_of_brackets = 0;
                    func_cond_mb(file, token, stack, count_of_brackets, hash_table);
                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, hash_table); // inside if
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    break;
                
                case _WHILE_:
                    
                    count_of_brackets = 0;
                    func_cond_mb(file, token, stack, count_of_brackets, hash_table);
                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, hash_table); // inside if
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    break;

                case _ELSE_:

                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, hash_table); // inside if
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
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
                        func_mb_ret(file, token, stack, hash_table);
                        get_token(file, token, stack);
                        if(token->type != TOKEN_EOL)
                            return -1; // must be EOL
                    }
                    break;

                case _DEF_:
                    flag_def = true;
                    get_token(file, token, stack);
                    if(token->type != TOKEN_FNC)
                        return -1; // must be name of FUNC
                    //CHECK HASH TABLE
                    if(hash_table->prev_hash_table){
                        return -1; // DEF CAN BE ONLY IN GLOBAL FRAME
                    }
                    tHTItem *item = htSearch(hash_table, token->attribute.string);
                    if(item){
                        if(item->id_declared == false){
                            item->id_declared = true;
                        }else{
                            return -1; // try to daclare fnc with the same name
                        }
                    }else{
                        htInsert(hash_table, token->attribute.string, token->type);
                        item = htSearch(hash_table, token->attribute.string);
                        item->id_declared = true;
                    }
                    
                    table_s *local_hash_table = (table_s *) malloc(sizeof(table_s));
                    if(!local_hash_table)
                        return ERR_INTERNAL;
                    htInit(local_hash_table);

                    local_hash_table->prev_hash_table = hash_table;

                    func_for_FNC(file, token, stack, local_hash_table, flag_def);
                    get_token(file, token, stack);
                    if(token->type != TOKEN_DDOT)
                        return -1; // must be :
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be end of line
                    get_token(file, token, stack);
                    if(token->type != TOKEN_INDEND)
                        return -1; // must be INDENT
                    func_prog(file, token, stack, state, ret_code, local_hash_table); // inside func
                    if(token->type != TOKEN_DEDEND)
                        return -1; // must be DEDENT
                    htClearAll(local_hash_table);
                    free(local_hash_table);
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

       // if(token->type == TOKEN_EOF){
// #ifdef DEBUG
//             printf("%s\n", types[token->type]);
// #endif
       //      break;
       //  }

// #ifdef DEBUG
//         if((token->type ==  TOKEN_KEY_WORD) || (token->type ==  TOKEN_FNC)){
//             printf("%s -- %s\n", types[token->type], (token->type == TOKEN_FNC) ? token->attribute.string : kw[token->attribute.key_word]);
//             if (token->type == TOKEN_FNC && token->attribute.string){
//                 free(token->attribute.string);
//             }
//         }
//         else{
//             printf("%s\n", types[token->type]);
//         }

        
//         if(token->type == TOKEN_ID || token->type == TOKEN_STRING){
//             printf("--------- attribute: %s\n", token->attribute.string);
//             free(token->attribute.string);
//         }
// #else
        // if (((token->type == TOKEN_FNC) || (token->type == TOKEN_STRING) || (token->type == TOKEN_ID)) && (token->attribute.string != NULL)){
        //     free(token->attribute.string);
        // }
//#endif
    }
return 1;
}