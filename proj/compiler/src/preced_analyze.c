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

char prec_table[13][13] = {
/*    +    -    *    /   //   r    (     )    i    f    s   id    $    */
    {'>', '>', '<', '<', '<', '>', '<', '>', '<', '<', '<', '<', '>'}, // +
    {'>', '>', '<', '<', '<', '>', '<', '>', '<', '<', '<', '<', '>'}, // -
    {'>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // *
    {'>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // /
    {'>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // //
    {'<', '<', '<', '<', '<', ' ', '<', '>', '<', '<', '<', '<', '<'}, // r -> <= >= < > = !=
    {'<', '<', '<', '<', '<', '<', '<', '=', '<', '<', '<', '<', ' '}, // (
    {'>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // )
    {'>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // i
    {'>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // f
    {'>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // s
    {'>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // id
    {'<', '<', '<', '<', '<', '<', '<', ' ', '<', '<', '<', '<', ' '}  // $
};

char *symbols[] = {
    "PLUS",    /*< +  */
    "MINUS",   /*< -  */
    "MUL",     /*< *  */
    "DIV",     /*< /  */
    "DIV_INT", /*< // */
    // GT,      /*< >  */
    // LS,      /*< <  */
    // GE,      /*< >= */
    // LE,      /*< <= */
    // NE,      /*< != */
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

typedef enum{
    S = 100, /* <      */
    R , /* >      */
    Q , /*< =     */
    E   /*< Error */
} tab_operator;

tab_symbol token_to_element(struct token_s *token){
    switch (token->type){
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
    case TOKEN_DDOT:
        return DLR;
    // case TOKEN_EQUAL:
    // case TOKEN_NOT_EQUAL:
    // case TOKEN_GREATER:
    // case TOKEN_LESS:
    // case TOKEN_GREATER_EQ:
    // case TOKEN_LESS_EQ:
    //     return R;
    case TOKEN_R_BRACKET:
        return RB;
    case TOKEN_L_BRACKET:
        return LB;
    default:
        printf("not terminal\n");
        return NT;
    }
}

int top_term(tDLList *list){
    int top;
    int i = 0;
    DLCopy(list, &top);
    while (top == ID_NT){
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

void reduce_rule(tDLList *list, int symbol, int top){
    if (symbol == DLR)
    {
        end_scan = true;
    }
    printf("reduce\t");
    int tmp = top_term(list);
    switch (tmp){
    case S:
        DLPostDelete(list);
        printf("rule E->i\n");
        DLActualize(list, ID_NT);
        break;
    case PLUS: // $ < E + E <- top
        printf("rule: E -> E + E\n");
        DLPred(list);
        DLPred(list);
        DLPred(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case MINUS:
        DLPred(list);
        printf("rule: E -> E - E\n");
        DLCopy(list, &tmp);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case MUL:
        DLPred(list);
        DLPred(list);
        DLPred(list);

        printf("rule: E -> E * E\n");
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case DIV:
        DLPred(list);
        DLPred(list);
        DLPred(list);

        printf("rule: E -> E / E\n");
        DLPostDelete(list);
        DLPostDelete(list);
        DLPostDelete(list);
        DLActualize(list, ID_NT);
        break;
    case DIV_INT:
        DLPred(list);
        DLPred(list);
        DLPred(list);

        printf("rule: E -> E // E\n");
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
        if (tmp == S)
        {
            DLPostDelete(list);
            printf("rule E->i\n");
            DLActualize(list, ID_NT);
            break;
        }
        else
        {
            printf("error. before ID can be only <\n");
            return ;
        }   
    // case LB:
    case RB:
        printf("rule: E -> (E)\n");
        // DLPred(list);
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
    else{

        tmp = top_term(list);
        switch (prec_table[tmp][symbol])
        {
        case '>':
            reduce_rule(list, symbol, top);
            break;
        default:
            if (tmp != ID && symbol != RB){
                DLPreInsert(list, S);
            }
            DLInsertLast(list, symbol);
            DLLast(list);
            break;
        }
    }
}

int preced_analyze(struct token_s *token, table_s *hash_table, int bracket_cnt){
    (void)hash_table;
    tDLList *list = (tDLList *) malloc(sizeof(tDLList));
    DLInitList(list);
    DLInsertFirst(list, DLR);
    DLFirst(list);
    
    tStack *scanner_stack = (tStack *)malloc(sizeof(tStack));
    stackInit(scanner_stack);
    stackPush(scanner_stack, 0);

    
    int top;
    int symbol;
    // struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));
    // struct token_s *prev_token = (struct token_s *)malloc(sizeof(struct token_s));
    do{
        symbol = token_to_element(token); 
        top = top_term(list); //in stack 
        if(symbol == DLR && top == DLR){
            end = false;
            break;
        }
        printf("top %s -- symbol: %s\t",symbols[top], symbols[symbol]);
        printf("operation %c\t", prec_table[top][symbol]);

        switch (prec_table[top][symbol]){
        case '=':
            DLPostInsert(list, symbol);
            break;
        case '<': 
            goto Cleanup; 
            Cleanup: ;   
            int top_nt;
            DLCopyLast(list, &top_nt);
            if(top_nt == ID_NT){ 
                DLPreInsert(list, S);
                DLPostInsert(list, symbol);
                DLSucc(list);
            }
            else{ 
                printf("insert to the top: %s\n", symbols[symbol]);
                DLPostInsert(list, S);
                DLSucc(list);
                DLPostInsert(list, symbol);
                DLSucc(list);
            }
            break;
        case '>':
            reduce_rule(list, symbol, top);
            break;
        default:
            return ERR;
            break;
        }

        // Save previous important token
        // switch (token->type){
        // case TOKEN_ID:
        // case TOKEN_STRING:
        //     prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);    
        //     strcpy(prev_token->attribute.string, token->attribute.string);
        //     break;
        // case TOKEN_INT:
        //     prev_token->attribute.int_val = token->attribute.int_val;
        //     break;
        // case TOKEN_FLOAT:
        //     prev_token->attribute.float_val = token->attribute.float_val;
        // default:
        //     break;
        // }
        
        if(!end_scan){
            if(token->type == TOKEN_ID){
                free(token->attribute.string);
            }
            get_token(token, scanner_stack);
        }
        if (token->type == TOKEN_R_BRACKET){
            bracket_cnt++;
        }
        else if(token->type == TOKEN_L_BRACKET){
            bracket_cnt--;
        }

        // check token in hash table
    } while (!end);
    
    free(scanner_stack);
    
    DLDisposeList(list);
    free(list);
    return false;
}
