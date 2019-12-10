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

#define PLUS_OP 1
#define MINUS_OP 2
#define MUL_OP 3
#define GEN_VAR 4
#define DIV_OP 5
#define DIV_INT_OP 6
#define GT_OP 7
#define LS_OP 8

char prec_table[18][18] = {
    /*    +    -    *    /   //   <=  >=   <   >   =   !=  (     )    i    f    s   id    $    */
    {'>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // +
    {'>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // -
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // *
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // /
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '<', '<', '>'}, // //
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // <
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // >
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // <=
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // >=
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // !=
    {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '<', '<', '<', '>'}, // ==
    {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', '<', '<', '<', ' '}, // (
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // )
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // i
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // f
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // s
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', ' ', '>'}, // id
    {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', ' ', '<', '<', '<', '<', ' '}  // $
};
/*
void clean(){
    end_scan = false;
    free(scanner_stack);
    // free(prev_token->attribute.string);
    free(prev_token);
    DLDisposeList(list);
    free(list);
}
*/

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
    "EQ",      /*<  == */
    "RB",      /*<  ( */
    "LB",      /*<  ) */
    "INT",     /*< Integer number */
    "FLT",     /*< Float number   */
    "STR",     /*< String         */
    "ID",      /*< ID */
    "DLR",     /*< $              */
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

struct token_s *prev_token;
int i;
int array_rules[100];

tab_symbol token_to_element(token_t type)
{
    switch (type)
    {
    case TOKEN_INT:
        return INT;
    case TOKEN_FLOAT:
        return FLT;
    case TOKEN_STRING:
        return STR;
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
        return NE;
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

int top_term(tDLList *list)
{
    int top;
    int i = 0;
    DLCopy(list, &top);
    while (top >= ID_NT)
    {
        DLPred(list);
        DLCopy(list, &top);
        i++;
    }

    DLLast(list);

    return top;
}

bool end = false;
bool end_scan = false;

int check_operand(tDLList *list, int operation)
{
    int op_1;
    int op_2;
    DLCopyLast(list, &op_1);
    DLPred(list);
    DLPredCopy(list, op_2);

    switch (operation)
    {
    case PLUS:
        if (op_1 == INT_NT && op_2 == INT_NT)
        {
            return INT_NT;
        }
        else if (op_1 == FLT_NT && op_2 == FLT_NT)
        {
            return FLT_NT;
        }
        else if (op_1 == STR_NT || op_2 == STR_NT)
        {
            if (op_1 != op_2)
            {
                return ERR_INCOMPATIBLE;
            }
            else
            {
                return STR_NT;
            }
        }
        else if ((op_1 == INT_NT && op_2 == FLT_NT) || (op_1 == FLT_NT && op_2 == INT_NT))
        {
            return FLT_NT;
        }
        break;
    case MUL:
    case DIV:
    case MINUS:
        if (op_1 == INT_NT && op_2 == INT_NT)
        {
            return INT_NT;
        }
        else if (op_1 == FLT_NT && op_2 == FLT_NT)
        {
            return FLT_NT;
        }
        else if ((op_1 == INT_NT && op_2 == FLT_NT) || (op_1 == FLT_NT && op_2 == INT_NT))
        {
            return FLT_NT;
        }
        else
        {
            return ERR_INCOMPATIBLE;
        }
    case DIV_INT:
        if (op_1 == INT_NT && op_2 == INT_NT)
        {
            return INT_NT;
        }
        else
        {
            return ERR_INCOMPATIBLE;
        }
    case GT:
    case GE:
    case LS:
    case LE:
    case NE:
    case EQ:
        if (op_1 == STR_NT || op_2 == STR_NT)
        {
            return ERR_INCOMPATIBLE;
        }
        else
        {
            return BOOL_NT;
        }
    default:
        break;
    }

    return true;
}

int reduce_rule(tDLList *list, int symbol, int top, struct token_s *prev_token)
{
    if (symbol == DLR)
    {
        end_scan = true;
    }

    int tmp = top_term(list);
    int rule = 0;

    int output_type = check_operand(list, tmp);
    if (output_type == ERR_INCOMPATIBLE)
    {
        return ERR_INCOMPATIBLE;
    }

    switch (tmp)
    {
    case S:
        DLPostDelete(list);
        DLActualize(list, symbol);
        break;
    case PLUS:
    case MINUS:
    case MUL:
    case DIV:
    case DIV_INT:
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLActualize(list, output_type);
        array_rules[i] = tmp;
        i++;
        break;
    case INT_NT:
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
            }
        }

        break;
    case INT:
    case FLT:
    case STR:
    case ID:
        DLPred(list);
        int tmp_2;
        DLCopy(list, &tmp_2);
        if (tmp_2 == S)
        {
            DLPostDelete(list);
            DLActualize(list, tmp);
        }
        else
        {
            fprintf(stderr, "error. before ID can be only <\n");
            return -1;
        }
        #ifdef DEBUG_PRECED
            array_rules[i] = 'E';
            i++;
        #endif
        prec_an_operand(frame, token, str_for_while);
        // if(token->type == TOKEN_STRING || token->type ==  TOKEN_STRING )
        //     free(token->attribute.string);
        break;
    case RB:
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLActualize(list, ID_NT);
        break;
    case GT:
    case GE:
    case LS:
    case LE:
    case NE:
    case EQ:
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLDeleteLast(list);
        DLActualize(list, output_type);
        array_rules[i] = tmp;
        i++;
        break;
    default:
        printf("error\n");
        break;
    }

    if (symbol == DLR)
    {
        return OK;
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
            if ((tmp != ID) && (tmp != INT) && (tmp != FLT) && (tmp != STR) && (symbol != RB))
            {
                DLPreInsert(list, S);
            }
            DLInsertLast(list, symbol);
            DLLast(list);
            break;
        }
    }
    return 0;
}

int preced_analyze(struct token_s *token, table_s *hash_table, int *count_of_params, struct dynamic_string *str, tStack *stack)
{
    (void)str;
    (void)hash_table;

    i = 0;
    int ret_code = 0;
    tDLList *list = (tDLList *)malloc(sizeof(tDLList));
    DLInitList(list);
    DLInsertFirst(list, DLR);
    DLFirst(list);

    tStack *scanner_stack = (tStack *)malloc(sizeof(tStack));
    stackInit(scanner_stack);
    stackPush(scanner_stack, 0);
    int top;
    int symbol;
    prev_token = (struct token_s *)malloc(sizeof(struct token_s));

    do
    {
        if (token->type == TOKEN_ID)
        {
            tHTItem *tmp = htSearch(hash_table, token->attribute.string);
            symbol = token_to_element(tmp->ret_val);
        }
        else
        {
            symbol = token_to_element(token->type);
        }

        if (symbol == NT)
        {
            return ERR_SYNTAX;
        }
        top = top_term(list); //in stack
        if (symbol == DLR && top == DLR)
        {
            end = false;
            break;
        }
        int top_nt;
        switch (prec_table[top][symbol])
        {
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
        case TOKEN_ID:
            prev_token->type = TOKEN_ID;
            prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
            strcpy(prev_token->attribute.string, token->attribute.string);
            break;
        case TOKEN_STRING:
            prev_token->type = TOKEN_STRING;
            prev_token->attribute.string = (char *)malloc(sizeof(char) * strlen(token->attribute.string) + 1);
            strcpy(prev_token->attribute.string, token->attribute.string);
            break;
        case TOKEN_INT:
            prev_token->type = TOKEN_INT;
            prev_token->attribute.int_val = token->attribute.int_val;
            break;
        case TOKEN_L_BRACKET:
            // bracket_cnt++;
            break;
        case TOKEN_R_BRACKET:
            // bracket_cnt--;
            break;
        // case TOKEN_EOL:
        case TOKEN_EOF:
            fprintf(stderr, "Error in precedence analyzes\n");
            end = true;
            return ERR_SYNTAX;
        default:
            break;
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
                    return ERR_UNDEF;
                }
            }
        }

        if (!end_scan){
            if (token->type == TOKEN_ID || token->type == TOKEN_STRING){
                free(token->attribute.string);
            }
            ret_code = get_token(token, scanner_stack);
            if (ret_code != OK)
            {
                return ret_code;
            }
            if (token->type == TOKEN_DDOT)
            {
                ret_code = get_token(token, scanner_stack);
                if (ret_code != OK)
                {
                    return ret_code;
                }    
                if(token->type != TOKEN_EOL){
                    // fprintf(stderr, "ERROR AFTER DDOT - NOT EOL\n");
                    end_scan = false;
                    free(scanner_stack);
                    // free(prev_token->attribute.string);
                    free(prev_token);
                    DLDisposeList(list);
                    free(list);
                    return ERR_OTHER;
                }
            }
        }
        if(token->type == TOKEN_ID){
            if(!htSearch(hash_table, token->attribute.string)){
                if (!search_everywhere(hash_table, token->attribute.string)){
                    // fprintf(stderr, "ID is not in hash table\n");
                    end_scan = false;
                    free(scanner_stack);
                    // free(prev_token->attribute.string);
                    free(prev_token);
                    DLDisposeList(list);
                    free(list);
                    return ERR_UNDEF;
                }
            }
        }
        else if(token->type == TOKEN_FNC){
            // here would be code from parese for Function call
            tHTItem *item = htSearch(hash_table, token->attribute.string);
            if (item)
            {
                if (item->type == TOKEN_ID)
                {
                    free(token->attribute.string);
                    return ERR_UNDEF; // ERROR, FNC WITH THE SAME NAME AS ID
                }
                else if (item->type == TOKEN_FNC)
                {
                    ret_code = func_for_FNC(token, stack, hash_table, false, count_of_params, str);
                    if (ret_code != OK)
                        return ret_code;
                    if (item->param_count != *count_of_params)
                    {
                        free(token->attribute.string);
                        return ERR_INCOMPATIBLE; // ERROR, no same count of params
                    }
                }
            }
            else
            {
                item = search_everywhere(hash_table, token->attribute.string);
                if (item)
                {
                    if (item->type == TOKEN_ID)
                    {
                        return ERR_UNDEF; // ERROR, FNC WITH THE SAME NAME AS ID
                    }
                    else if (item->type == TOKEN_FNC)
                    {
                        ret_code = func_for_FNC(token, stack, hash_table, false, count_of_params, str);
                        if (ret_code != OK)
                            return ret_code;
                        if (item->param_count != *count_of_params)
                        {
                            return ERR_INCOMPATIBLE; // no same count of params
                        }
                    }
                }
                else
                {
                    table_s *glob_hash_table = hash_table;

                    while (glob_hash_table->prev_hash_table != NULL)
                    {
                        glob_hash_table = glob_hash_table->prev_hash_table;
                    }

                    htInsert(glob_hash_table, token->attribute.string, token->type);
                    item = htSearch(glob_hash_table, token->attribute.string);
                    item->id_declared = false;

                    ret_code = func_for_FNC(token, stack, hash_table, false, count_of_params, str);
                    if (ret_code != OK)
                        return ret_code;
                    item->param_count = *count_of_params;
                }
            }
            *count_of_params = 0;
        
    } while (!end);
    
    #ifdef DEBUG_PRECED
        for(int a = 0; a < i; a++){
            printf("%c --> ", array_rules[a]);
        }
    } while (!end);

    end_scan = false;
    free(scanner_stack);
    // free(prev_token->attribute.string);
    // if (prev_token->type == TOKEN_ID || prev_token->type == TOKEN_STRING)
    // {
    //     free(prev_token->attribute.string);
    // }
    free(prev_token);
    DLDisposeList(list);
    free(list);
    return OK;
}
/*
    TODO 200 int 
        201 float
        202 string 
*/