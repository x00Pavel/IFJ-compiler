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
#include "parser.h"
#include "codegenerator.h"
#include "stack.h"

int check_next_token(FILE *file, struct token_s *token, tStack *stack){

    get_token(file, token, stack);
    if(token->type == TOKEN_COMA){
        get_token(file, token, stack);
        func_for_atributes(file, token, stack);
    }else if(token->type == TOKEN_R_BRACKET){
        return 1; // WE R OK
    }
return -1; // ERROR, dostali jsme neco jineho nez "," nebo ")"
}

int func_for_atributes(FILE *file, struct token_s *token, tStack *stack){
        
    switch (token->type){
    case TOKEN_ID:
        // check hash
        // generate attribute
        free(token->attribute.string); 
        check_next_token(file, token, stack); 
        break;
    case TOKEN_INT:
        // generate attribute
        check_next_token(file, token, stack);
        break;
    case TOKEN_FLOAT:
        // generate attribute
        check_next_token(file, token, stack);
        break;
    case TOKEN_STRING:
        // generate attribute
        free(token->attribute.string);
        check_next_token(file, token, stack);
        break;
        
    default:
        return -1; // neco jineho nez int/string/float/id
        break;
    }
return 1; // WE R OK
}

int func_for_FNC(FILE *file, struct token_s *token, tStack *stack){
    
    // check hash
    
    //struct token_s token_for_time;

    //token_for_time.type=(*token)->type;
    //token_for_time.attribute=(*token)->attribute;

    free(token->attribute.string);    

    get_token(file, token, stack);

    if(token->type == TOKEN_L_BRACKET){
        get_token(file, token, stack);
        if(token->type == TOKEN_R_BRACKET){
            return 1; // nastala ")"
        }else{
            func_for_atributes(file, token, stack);
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
        token_for_time.attribute.string = (char *) malloc(sizeof(char) * strlen(token->attribute.string));
        strcpy(token_for_time.attribute.string, token->attribute.string);
    }

    printf("T_type: %d\n", token->type);
    printf("must be a: %s\n", token_for_time.attribute.string);

    free(token->attribute.string);
    printf("must be a: %s\n", token_for_time.attribute.string);
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
            define_variable(&token_for_time);
            id_is_equal_to(&token_for_time ,token);
            free(token_for_time.attribute.string);
            break;
        case TOKEN_STRING:
            // move string to ID
            // precedencni analyza
            // def_and_move(&token_for_time, &(*token));
            define_variable(&token_for_time);
            id_is_equal_to(&token_for_time, token);
            // ADD FREE FOR ALL
            break;
        case TOKEN_FLOAT:
            // move float to ID
            // precedencni analyza
            // def_and_move(&token_for_time, &(*token));
            define_variable(&token_for_time);
            id_is_equal_to(&token_for_time, token);
            break;
        //case TOKEN_NONE:
            // move NONE to ID
            // def_and_move(&token_for_time, &(*token));
            // break;
        case TOKEN_FNC:
            func_for_FNC(file, token, stack);
            break;
        default:
            return -1;
            break;
        }
    }else{
        return -1; // ERROR must be =
    }
return 1; // WE R OK
}