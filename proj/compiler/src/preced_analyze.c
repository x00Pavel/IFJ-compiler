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
#include "preced_analyze.h"
#include "stack.h"
#include "linear_stack.h"
#include "errors.h"


char prec_table[18][18] = {
/*    +    -    *    /   //   <=  >=   <   >   =   !=  (     )    i    f    s   id    $    */
    {'>', '>', '<', '<', '<', '>','>','>','>','>','>', '<', '>', '<', '<', '<', '<', '>'}, // +
    {'>', '>', '<', '<', '<', '>','>','>','>','>','>', '<', '>', '<', '<', '<', '<', '>'}, // -
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', '<', '>', '<', '<', '<', '<', '>'}, // *
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', '<', '>', '<', '<', '<', '<', '>'}, // /
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', '<', '>', '<', '<', '<', '<', '>'}, // //
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // <
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // >
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // <=
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // >=
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // !=
    {'<', '<', '<', '<', '<', ' ',' ',' ',' ',' ',' ', '<', '>', '<', '<', '<', '<', '>'}, // ==
    {'<', '<', '<', '<', '<', '<','<','<','<','<','<', '<', '=', '<', '<', '<', '<', ' '}, // (
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // )
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // i
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // f
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // s
    {'>', '>', '>', '>', '>', '>','>','>','>','>','>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // id
    {'<', '<', '<', '<', '<', '<','<','<','<','<','<', '<', ' ', '<', '<', '<', '<', ' '}  // $
};

char *symbols[] = {
    "PLUS",    /*< +  */
    "MINUS",   /*< -  */
    "MUL",     /*< *  */
    "DIV",     /*< /  */
    "DIV_INT", /*< // */
    "GT",      /*< >  */
    "LS",      /*< <  */
    "GE",      /*< >= */
    "LE",      /*< <= */
    "NE",      /*< != */
    "EQ",  /*<  == */
    "RB",  /*<  ( */
    "LB",  /*<  ) */
    "INT", /*< Integer number */
    "FLT", /*< Float number   */
    "STR", /*< String         */
    "ID",  /*< ID */
    "DLR", /*< $              */
    "ID_NT",
    "INT_NT",
    "FLT_NT",
    "STR_NT",
    "NT", /*< Not terminal   */
    "END" /*< End symbol     */
};

typedef enum
{
    S = 100, /* <      */
    R,       /* >      */
    Q,       /*< =     */
    E        /*< Error */
} tab_operator;

tab_symbol token_to_element(struct token_s *token)
{
    switch (token->type)
    {
    case TOKEN_INT:
    case TOKEN_FLOAT:
    case TOKEN_STRING:
    case TOKEN_ID:
        return ID;
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
    // case TOKEN_DDOT:
    case TOKEN_EOL:
        return DLR;
    case TOKEN_EQUAL:
        return EQ;
    case TOKEN_NOT_EQUAL:
        return  NE;
    case TOKEN_GREATER:
        return GT;
    case TOKEN_LESS:
        return LS;
    case TOKEN_GREATER_EQ:
        return GE;
    case TOKEN_LESS_EQ:
        return LE;
    case TOKEN_R_BRACKET:
        return RB;
    case TOKEN_L_BRACKET:
        return LB;
    default:
        return NT;
    }
}

int top_term(tDLList *list){
    int top;
    int i = 0;
    DLCopy(list, &top);
    while (top == ID_NT)
    {
        DLPred(list);
        DLCopy(list, &top);
        i++;
    }
    // } while ((top == ID_NT) || (top == FLT_NT) || (top == INT_NT) || (top == STR_NT));

    DLLast(list);

    return top;
}

bool end = false;
bool end_scan = false;

bool check_operand(tDLList *list){
    int i;
    DLCopyLast(list, &i);
    if(i != ID_NT){
        printf("ERROR. NO OPERANDS\n");
        end_scan = true;
        end = true;
        return false;
    }
    return true;
}

void reduce_rule(tDLList *list, int symbol, int top, struct token_s *prev_token)
{
    if (symbol == DLR){
        end_scan = true;
    }
    // printf("reduce\t");
    int tmp = top_term(list);
    switch (tmp){
    case S:
        DLPostDelete(list);
        printf("rule E->i\n");
        DLActualize(list, ID_NT);
        break;
    case PLUS: // $ < E + E <- top
        if(!check_operand(list)){
            return;
        }
        // printf("rule: E -> E + E\n");
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        // if(token->type == TOKEN_STRING && prev_token->type == TOKEN_STRING){

        // }
        // func_sum(зкум)
            // (token, prev_token);
            // free(prev_token->attribute.string);
            break;
    case MINUS:
        if(!check_operand(list)){
            return;
        }
        // printf("rule: E -> E - E\n");
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        // if(token->type != TOKEN_STRING && prev_token->type != TOKEN_STRING)
        // gen_sub(token, prev_token)
        // else{
        //     printf()
        // }
        break;
    case MUL:
        if (!check_operand(list)){
            return;
        }
        DLPred(list);
        DLPred(list);
        DLPred(list);

        // printf("rule: E -> E * E\n");
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case DIV:
        if(!check_operand(list)){
            return;
        }
        DLPred(list);
        DLPred(list);
        DLPred(list);

        // printf("rule: E -> E / E\n");
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case DIV_INT:
        if (!check_operand(list)){
            return;
        }
        DLPred(list);
        DLPred(list);
        DLPred(list);

        // printf("rule: E -> E // E\n");
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case INT_NT: // E -> ( int|id|flt|str )
    case FLT_NT:
    case STR_NT:
    case ID_NT:
        if (top == RB)
        {
            DLPred(list);
            int type = tmp;
            DLCopy(list, &tmp);
            if (tmp == LB)
            {
                DLPostDelete(list);
                DLPostDelete(list);
                switch (type)
                {
                case INT_NT:
                    DLActualize(list, INT_NT);
                    break;
                case FLT_NT:
                    DLActualize(list, FLT_NT);
                    break;
                case STR_NT:
                    DLActualize(list, STR_NT);
                    break;
                case ID_NT:
                    DLActualize(list, ID_NT);
                    break;
                default:
                    break;
                }
                DLActualize(list, INT_NT);
            }
        }
        break;
    case ID:
        DLPred(list);
        DLCopy(list, &tmp);
        if (tmp == S){
            DLPostDelete(list);
            // printf("rule E->i\n");
            DLActualize(list, ID_NT);
            break;
        }
        else{
            fprintf(stderr,"error. before ID can be only <\n");
            return;
        }
    case RB:
        // #ifdef DEBUG
        // printf("rule: E -> (E)\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case GT:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG
        // printf("rule: E -> E > E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case GE:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG
        // printf("rule: E -> E >= E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case LS:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG 
        // printf("rule: E -> E < E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case LE:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG
        // printf("rule: E -> E <= E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case NE:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG
        //     printf("rule: E -> E != E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case EQ:
        if (!check_operand(list)){
            return;
        }
        // #ifdef DEBUG
        //     printf("rule: E -> E == E\n");
        // #endif
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;

    default:
        printf("error\n");
        break;
    }
    if (symbol == DLR){
        return;
    }
    else
    {

        tmp = top_term(list);
        switch (prec_table[tmp][symbol])
        {
        case '>':
            reduce_rule(list, symbol, top, prev_token);
            break;
        default:
            if (tmp != ID && symbol != RB)
            {
                DLPreInsert(list, S);
            }
            DLInsertLast(list, symbol);
            DLLast(list);
            break;
        }
    }
}

int preced_analyze(struct token_s *token, table_s *hash_table, int bracket_cnt, struct dynamic_string *str)
{
    (void)flag_while;
    (void)str;
    (void)hash_table;
    tDLList *list = (tDLList *)malloc(sizeof(tDLList));
    DLInitList(list);
    DLInsertFirst(list, DLR);
    DLFirst(list);

    tStack *scanner_stack = (tStack *)malloc(sizeof(tStack));
    stackInit(scanner_stack);
    stackPush(scanner_stack, 0);

    int top;
    int symbol;
    struct token_s *prev_token = (struct token_s *)malloc(sizeof(struct token_s));

    // stackstack_operations(t, str);
    do
    {
        symbol = token_to_element(token);
        if(symbol == NT){
            fprintf(stdout, "Invalid operator\n");
            return ERR_SYNTAX;
        }
        top = top_term(list); //in stack
        if (symbol == DLR && top == DLR)
        {
            end = false;
            break;
        }
        // #ifdef DEBUG
        //     printf("top %s -- symbol: %s\t", symbols[top], symbols[symbol]);
        //     printf("operation %c\t", prec_table[top][symbol]);
        // #endif
        int top_nt;
        switch (prec_table[top][symbol]){
        case '=':
            DLPostInsert(list, symbol);
            break;
        case '<':
            DLCopyLast(list, &top_nt);
            if (top_nt == ID_NT)
            {
                DLPreInsert(list, S);
                DLPostInsert(list, symbol);
                DLSucc(list);
            }
            else
            {
                //  #ifdef DEBUG     
                //     printf("insert to the top: %s\n", symbols[symbol]);
                // #endif            
                DLPostInsert(list, S);
                DLSucc(list);
                DLPostInsert(list, symbol);
                DLSucc(list);
            }
            break;
        case '>':
            reduce_rule(list, symbol, top, prev_token);
            break;
        default:
            end_scan = false;
            free(scanner_stack);
            // free(prev_token->attribute.string);
            free(prev_token);
            DLDisposeList(list);
            free(list);
            return ERR;
            break;
        }
        // Save previous important token
        switch (token->type){
        // case TOKEN_ID:
        //     prev_token->type = TOKEN_ID;
        //     prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        //     strcpy(prev_token->attribute.string, token->attribute.string);
        //     break;
        // case TOKEN_STRING:
        //     prev_token->type = TOKEN_STRING;
        //     prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
        //     strcpy(prev_token->attribute.string, token->attribute.string);
        //     break;
        // case TOKEN_INT:
        //     prev_token->type = TOKEN_INT;
        //     prev_token->attribute.int_val = token->attribute.int_val;
        //     break;
        // case TOKEN_FLOAT:
        //     prev_token->type =  TOKEN_FLOAT; 
        //     prev_token->attribute.float_val = token->attribute.float_val;
        //     break;
        case TOKEN_L_BRACKET:
            bracket_cnt++;
            break;
        case TOKEN_R_BRACKET:
            bracket_cnt--;
            break;
        // case TOKEN_EOL:
        case TOKEN_EOF:
            fprintf(stderr, "Error in precedence analyzes\n");
            end = true;
            return ERR_SYNTAX;
        // case TOKEN_FNC:          
        default:
            break;
        }

        if (!end_scan){
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING){
                free(token->attribute.string);
            }
            get_token(token, scanner_stack);
            if(token->type == TOKEN_DDOT){
                get_token(token, scanner_stack);
                if(token->type != TOKEN_EOL){
                    fprintf(stderr, "ERROR AFTER DDOT - NOT EOL\n");
                    end_scan = false;
                    free(scanner_stack);
                    // free(prev_token->attribute.string);
                    free(prev_token);
                    DLDisposeList(list);
                    free(list);
                    end_scan = false;
                    free(scanner_stack);
                    // free(prev_token->attribute.string);
                    free(prev_token);
                    DLDisposeList(list);
                    free(list);
                    return ERR_SYNTAX;
                }
            }
        }
        if(token->type == TOKEN_ID){
            if(!htSearch(hash_table, token->attribute.string)){
                if (!search_everywhere(hash_table, token->attribute.string)){
                    fprintf(stderr, "ID is not in hash table\n");
                    end_scan = false;
                    free(scanner_stack);
                    // free(prev_token->attribute.string);
                    free(prev_token);
                    DLDisposeList(list);
                    free(list);
                    return ERR_PARAM;
                }
            }
        }
    } while (!end);

    end_scan = false;
    free(scanner_stack);
    // free(prev_token->attribute.string);
    free(prev_token);
    DLDisposeList(list);
    free(list);
    return OK;
}
