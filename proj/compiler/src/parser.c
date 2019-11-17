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

int func_mb_ret(FILE *file, struct token_s *token, tStack *stack){

    switch (token->type){
    case TOKEN_NONE:
        return 1; // we R ok
        break;
    case TOKEN_FNC:
        func_for_FNC(file, token, stack); // free string inside function
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

int func_cond_mb(FILE *file, struct token_s *token, tStack *stack, int count_of_brackets){
    get_token(file, token, stack);
    if(token->type == TOKEN_L_BRACKET){
        count_of_brackets++;
        func_cond_mb(file, token, stack, count_of_brackets);
        }
    if(token->type == TOKEN_FNC){
            func_for_FNC(file, token, stack);
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

int check_next_token(FILE *file, struct token_s *token, tStack *stack, int *count_of_params){
    get_token(file, token, stack);
    if(token->type == TOKEN_COMA){
        get_token(file, token, stack);
        func_for_atributes(file, token, stack, count_of_params);
    }else if(token->type == TOKEN_R_BRACKET){
        return 1; // WE R OK
    }
return -1; // ERROR, dostali jsme neco jineho nez "," nebo ")"
}

int func_for_atributes(FILE *file, struct token_s *token, tStack *stack, int *count_of_params){
    (*count_of_params)++;
    switch (token->type){
    case TOKEN_ID:
        // CHECK HASH
        token_function_body(token, count_of_params);
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params); 
        break;
    case TOKEN_INT:
        token_function_body(token, count_of_params);
        check_next_token(file, token, stack, count_of_params);
        break;
    case TOKEN_FLOAT:
        token_function_body(token, count_of_params);
        check_next_token(file, token, stack, count_of_params);
        break;
    case TOKEN_STRING:
        token_function_body(token, count_of_params);
        free(token->attribute.string);
        check_next_token(file, token, stack, count_of_params);
        break;
        
    default:
        return -1; // neco jineho nez int/string/float/id
        break;
    }
return 1; // WE R OK
}

int func_for_FNC(FILE *file, struct token_s *token, tStack *stack){
    
    // check hash

    int count_of_params = 0;
    
    struct token_s token_for_time; // token_for_time
    
    token_for_time.type=token->type;
    token_for_time.attribute=token->attribute;
    if(token->type == TOKEN_FNC){
        token_for_time.attribute.string = (char *) malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        strcpy(token_for_time.attribute.string, token->attribute.string);
    }

    free(token->attribute.string);    

    get_token(file, token, stack);

    if(token->type == TOKEN_L_BRACKET){
        get_token(file, token, stack);
        if(token->type == TOKEN_R_BRACKET){
            return 1; // nastala ")"
        }else{
            func_for_atributes(file, token, stack, &count_of_params);
            token_function_end(&token_for_time);
            free(token_for_time.attribute.string);
        }
    }else{
        return -1; // ERROR
    }
return 1; // WE R OK
}

int func_for_id(FILE *file, struct token_s *token, tStack *stack){
    // check HASH for ID
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
        case TOKEN_INT:
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
            func_for_FNC(file, token, stack);
            asigment_of_function_with_y(&token_for_time);
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
 // mb need free
return 1; // WE R OK
}

int func_prog(FILE *file, struct token_s *token, tStack *stack, int state, int ret_code){

int count_of_brackets = 0;

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

        case TOKEN_ID:
            // check HASH TABLE
            // generace ciloveho kodu, create ID
            func_for_id(file, token, stack);
        
            get_token(file, token, stack);
            if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                return -1; // ERROR MUST BE EOL or EOF or DEDENT
            break;
        
        case TOKEN_FNC:
            // check HASH TABLE
            func_for_FNC(file, token, stack);
            
            get_token(file, token, stack);
            if(token->type != TOKEN_EOL && token->type != TOKEN_EOF && token->type != TOKEN_DEDEND)
                return -1; // ERROR MUST BE EOL or EOF or DEDENT
                
            break;

        case TOKEN_KEY_WORD:
            switch (token->attribute.key_word){
            case _IF_:
        
                count_of_brackets = 0;
                func_cond_mb(file, token, stack, count_of_brackets);
                get_token(file, token, stack);
                if(token->type != TOKEN_DDOT)
                    return -1; // must be :
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL)
                    return -1; // must be end of line
                get_token(file, token, stack);
                if(token->type != TOKEN_INDEND)
                    return -1; // must be INDENT
                func_prog(file, token, stack, state, ret_code); // inside if
                if(token->type != TOKEN_DEDEND)
                    return -1; // must be DEDENT
                break;
            
            case _WHILE_:
                
                count_of_brackets = 0;
                func_cond_mb(file, token, stack, count_of_brackets);
                get_token(file, token, stack);
                if(token->type != TOKEN_DDOT)
                    return -1; // must be :
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL)
                    return -1; // must be end of line
                get_token(file, token, stack);
                if(token->type != TOKEN_INDEND)
                    return -1; // must be INDENT
                func_prog(file, token, stack, state, ret_code); // inside if
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
                func_prog(file, token, stack, state, ret_code); // inside if
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
                    func_mb_ret(file, token, stack);
                    get_token(file, token, stack);
                    if(token->type != TOKEN_EOL)
                        return -1; // must be EOL
                }
                break;

            case _DEF_:
                get_token(file, token, stack);
                if(token->type != TOKEN_FNC)
                    return -1; // must be name of FUNC

                func_for_FNC(file, token, stack);
                get_token(file, token, stack);
                if(token->type != TOKEN_DDOT)
                    return -1; // must be :
                get_token(file, token, stack);
                if(token->type != TOKEN_EOL)
                    return -1; // must be end of line
                get_token(file, token, stack);
                if(token->type != TOKEN_INDEND)
                    return -1; // must be INDENT
                func_prog(file, token, stack, state, ret_code); // inside ned func
                if(token->type != TOKEN_DEDEND)
                    return -1; // must be DEDENT

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