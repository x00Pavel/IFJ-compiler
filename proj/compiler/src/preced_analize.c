/**
 * \brief Implementation of CONVENTIONAL SYNTAKTIC ANALYSIS
 * 
 * \author Pavel Yadlouski (xyadlo00@stud.fit.vutbr.cz)
 * 
 * \date 2019
*/

#include <string.h>
#include "symtable.h"
#include "codegenerator.h"
#include "preced_analize.h"
#include "stack.h"
#include "errors.h"

typedef enum{
    S, /* <      */
    R, /* >      */
    Q, /*< =     */
    E  /*< Error */
} tab_operator;

int stack_top_term(tStack *stack){
    int top = stackTop(stack);
    if ((top == INT) || (top == FLT) || (top == STR)){
        stackPop(stack);
        stack_top_term(stack);
        stackPush(stack, top);
    }
    else if(top < INT){
        return top;        
    }
    return 0;
}

int prec_table[10][10] = {
/*  |+ |- |* |/ |//|r |( |) |i |$ |  */ 
    {R ,R ,S ,S ,S ,R ,S ,S ,S ,R }, // +
    {R ,R ,S ,S ,S ,R ,S ,S ,S ,R }, // -
    {R ,R ,R ,R ,R ,R ,S ,R ,S ,R }, // *
    {R ,R ,R ,R ,R ,R ,S ,R ,S ,R }, // /
    {R ,R ,R ,R ,R ,R ,S ,R ,S ,R }, // //
    {S ,S ,S ,S ,S ,E ,S ,R ,S ,S }, // r -> <= >= < > = != 
    {S ,S ,S ,S ,S ,S ,S ,Q ,S ,E }, // (
    {R ,R ,R ,R ,R ,R ,E ,R ,E ,R }, // )
    {R ,R ,R ,R ,R ,R ,E ,R ,E ,R }, // i -> INT, FLT, STR
    {S ,S ,S ,S ,S ,S ,S ,E ,S ,E }// $
};

tab_symbol token_to_element(struct token_s *token){
    switch (token->type){
    case TOKEN_INT:
        return INT;    
    case TOKEN_FLOAT:
        return FLT;
    case TOKEN_STRING:
        return STR;
    case TOKEN_MULTIPLY:
        return MUL;
    case TOKEN_SUM:
        return PLUS;
    case TOKEN_MINUS:
        return MINUS;
    case TOKEN_DIVISION:
        return DIV;
    case TOKEN_DIV_INT:
        return DIV_INT;
    case TOKEN_ID:
        return ID;
    case TOKEN_EQUAL:
        return EQ;
    case TOKEN_NOT_EQUAL:
        return NE;
    case TOKEN_GREATER:
        return GT; 
    case TOKEN_LESS:
        return LS;
    case TOKEN_GREATER_EQ:
        return GE;
    case TOKEN_LESS_EQ:
        return LE;
    default:
        return NT;
    }
}

rule check_rule(tab_symbol op3, tab_symbol op2, tab_symbol op1){ 

    switch (op2){
    case PLUS:
        if ((op3 == INT && op1 == INT) || 
            (op3 == FLT && op1 == FLT) || 
            (op3 == STR && op1 == STR))
        {
            return NT_PLUS_NT;
        }
        else if ((op3 == INT && op1 == FLT) || 
                 (op3 == FLT && op1 == INT))
        {
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_PLUS_NT;
        }
        else{
            // error
            return ERROR;
        }

    case MINUS:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_MINUS_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_MINUS_NT;
        }
        else{
            // error
            return ERROR;
        }

    case MUL:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_MUL_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_MUL_NT;
        }
        else{
            // error
            return ERROR;
        }
    case DIV: // 
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_DIV_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_DIV_NT;
        }
        else{
            // error
            return ERROR;
        }
    case DIV_INT:
        if (op3 == INT && op1 == INT){
            return NT_INT_DIV_NT;
        }
        else{
            // error
            return ERROR;
        }
    case GT:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_GT_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression

            return NT_GT_NT;
        }
        else{
            // error
            return ERROR;
        }
    case LS:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_LS_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_LS_NT;
        }
        else{
            // error
            return ERROR;
        }
    case GE:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_GE_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_GE_NT;
        }
        else{
            return ERROR;
        }
    case LE:
        if ((op3 == INT && op1 == INT) || (op3 == FLT && op1 == FLT)){
            return NT_LE_NT;
        }
        else if ((op3 == INT && op1 == FLT) || (op3 == FLT && op1 == INT)){
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_LE_NT;
        }
        else{
            // error
            return ERROR;
        }
    case NE:
        if ((op3 == INT && op1 == INT) || 
            (op3 == FLT && op1 == FLT) || 
            (op3 == STR && op1 == STR))
        {
            return NT_NE_NT;
        }
        else if ((op3 == INT && op1 == FLT) || 
                 (op3 == FLT && op1 == INT))
        {
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_NE_NT;
        }
        else{
            // error
            return ERROR;
        }

    case EQ:
        if ((op3 == INT && op1 == INT) ||
            (op3 == FLT && op1 == FLT) ||
            (op3 == STR && op1 == STR))
        {
            return NT_EQ_NT;
        }
        else if ((op3 == INT && op1 == FLT) ||
                 (op3 == FLT && op1 == INT))
        {
            // check types. in need, call convertion function
            // it would be print out before expression
            return NT_EQ_NT;
        }
        else{
            // error
            return ERROR;
        }

    case RB:
    case LB:
        return LB_NT_RB;
    case ID:
        return OPERAND;
    default:
        break;
    }
    return ERR;
}

void gen_operation(rule _rule, struct token_s *token1, struct token_s *token2){
    (void)token1;
    (void)token2;

    switch(_rule)
    {
    case NT_PLUS_NT:
        // add(token, prev_token);
        break;
    case NT_MINUS_NT:
        // substr(token, token_prev);
        break;
    case NT_MUL_NT:
        // mul(token1, token2);
        break;
    case NT_DIV_NT:
        // div(token1, token2);
        break;
    case NT_INT_DIV_NT:
        // int_div(token1, token2);
        break;
    case NT_EQ_NT:
        // equal(token1, token2);
        break;
    case NT_GE_NT:
        // greater_equal(token1, token2);
        break;
    case NT_GT_NT:
        // greater(token1, token2);
        break;
    case NT_LE_NT:
        // less_equal(token1, token2);
        break;
    case NT_LS_NT:
        // less(token1,token2);
        break;
    case NT_NE_NT:
        // not_equal(token1, token2);
        break;
    
    default:
        break;
    }
}

int preced_analyze(FILE *file, struct token_s *token, table_s *hash_table, int bracket_cnt){
    tStack *stack = (tStack *) malloc(sizeof(tStack)); 
    stackInit(stack);
    stackPush(stack, DLR);

    tStack *scanner_stack = (tStack *)malloc(sizeof(tStack));
    stackInit(stack);
    stackPush(stack, 0);

    int top;
    tab_symbol symbol;
    // struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));
    struct token_s *prev_token = (struct token_s *)malloc(sizeof(struct token_s));
    do{
        symbol = token_to_element(token);
        top = stackTop(stack);

        switch (prec_table[symbol][top]){
        case Q: // =
            stackPush(stack, symbol);
            break;
        case S: // <
            if ((top == INT) || (top == FLT) || (top == STR)){
                stackPop(stack);
                stackPush(stack, S);
                stackPush(stack, top);
                stackPush(stack, symbol);
            }
            else{
                stackPush(stack, S);
                stackPush(stack, symbol);
            }
            break;
        case R: // >
            if((top == INT) || (top == FLT) || (top == STR)){
                stackPop(stack);
                int top_1 = stackTop(stack);
                if(top_1 <= EQ){ // binary operator
                    stackPop(stack);
                    int top_2 = stackTop(stack);
                    if((top_2 == INT) || (top_2 == FLT) || (top_2 == STR)){
                        stackPop(stack);
                        if(stackTop(stack) == S){
                            rule _rule = check_rule(top_2, top_1, top);
                            if (_rule != ERROR){
                                stackPop(stack);
                                if(top == STR || top_2 == STR){
                                    stackPush(stack,STR);
                                }
                                else if((top == INT && top_2 == FLT) || 
                                        (top == FLT && top_2 == INT) ||
                                        (top == FLT && top_2 == FLT)){
                                    stackPush(stack, FLT);
                                }
                                else if(top == INT && top_2 == INT){
                                    stackPush(stack, INT);
                                }
                                else{
                                    return ERR_INCOMPATIBLE;
                                }
                                printf("reduce NT\n");
                            }
                            else{
                                return ERR_INCOMPATIBLE;
                            }
                            // switch with call function for generating 
                            // code based on rule
                            gen_operation(_rule, token, prev_token);
                        }
                    }
                }
            }
            break;
        default:
            return ERR;
            break;
        }

        // Save previous important token
        switch (token->type){
        case TOKEN_ID:
        case TOKEN_STRING:
            prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);    
            strcpy(prev_token->attribute.string, token->attribute.string);
            break;
        case TOKEN_INT:
            prev_token->attribute.int_val = token->attribute.int_val;
            break;
        case TOKEN_FLOAT:
            prev_token->attribute.float_val = token->attribute.float_val;
        default:
            break;
        }

        get_token(file, token, scanner_stack);
        if (token->type == TOKEN_R_BRACKET){
            bracket_cnt++;
        }
        else if(token->type == TOKEN_L_BRACKET){
            bracket_cnt--;
        }
  
        if ((token->type == TOKEN_ID)){
            if(!htSearch(hash_table, token->attribute.string)){
                if (!search_everywhere(hash_table, token->attribute.string)){
                    // ID not found in hash_table -> ERROR 
                    return ERR_PARAM;                   
                }
            }
        }
    } while ((stackTop(stack) != DLR) &&
             (token->type != TOKEN_DDOT) &&
             (bracket_cnt == 0)); //не уверен нужно ли

    // rule rule_ = check_rule(element);
    return false;
}
