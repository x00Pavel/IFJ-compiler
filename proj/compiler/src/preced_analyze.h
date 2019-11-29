
#ifndef _PRECED_ANALYZE_H
#define _PRECED_ANALYZE_H
#include "scaner.h"
#include "symtable.h"

/**
 * \brief Enumeration of avaliable symbols in table
*/
typedef enum
{
    PLUS = 0,    /*< +  */
    MINUS,   /*< -  */
    MUL,     /*< *  */
    DIV,     /*< /  */
    DIV_INT, /*< // */
    // GT,      /*< >  */
    // LS,      /*< <  */
    // GE,      /*< >= */
    // LE,      /*< <= */
    // NE,      /*< != */
    EQ,      /*<  == */
    LB,      /*<  ( */
    RB,      /*<  ) */
    INT,    /*< Integer number */
    FLT,    /*< Float number   */
    STR,     /*< String         */
    ID,      /*< ID */
    DLR,     /*< $              */
    ID_NT,
    INT_NT,
    FLT_NT,
    STR_NT,
    NT,      /*< Not terminal   */
    END      /*< End symbol     */
} tab_symbol;



/**
 * \brief Enumeration of avaliable rules
*/
typedef enum
{   NT_PLUS_NT,    /*< E -> E +  E */
    NT_MINUS_NT,   /*< E -> E -  E */
    NT_MUL_NT,     /*< E -> E *  E */
    NT_DIV_NT,     /*< E -> E /  E */
    NT_INT_DIV_NT, /*< E -> E // E */
    NT_GT_NT,      /*< E -> E >  E */
    NT_LS_NT,      /*< E -> E <  E */
    NT_GE_NT,      /*< E -> E >= E */
    NT_LE_NT,      /*< E -> E <= E */
    NT_NE_NT,      /*< E -> E != E */
    NT_EQ_NT,      /*< E -> E == E */
    LB_NT_RB,      /*< E -> ( E )  */
    OPERAND,       /*< E ->   i    */
    ERROR,         /*< Rule does not exist */
} rule;

/** \brief Function for precedence analysis
 * 
 * \param[in] token First token of expression
 * \param[in] hash_table Local hash table
 * \param[in] bracket_cnt Count of bracket
 * 
 * \return true if expression is right
 * \return false in case of any error
 * 
*/
int preced_analyze(FILE *file, struct token_s *token, table_s *hash_table, int bracket_cnt);

#endif
