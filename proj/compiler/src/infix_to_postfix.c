#include "infix_to_postfix.h"
#include "dynamic_string.h"

void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen ) {
    
    char top_tmp; // temporary variable 

    while(stackEmpty(s) != 1){

        // take symbol from the top of stack 
        top_tmp = (char)stackTop(s); 

        // remove element from the top of stack
        stackPop(s);

        // if symbol is '(', then just remove it  
        if (top_tmp ==  '('){
            break;
        }
        else
        {
            // insert to propriet place in output expression
            postExpr[*postLen] = top_tmp;
        }
        // increment length of output expression 
        (*postLen) += 1;
        

    }

}

/*
** Pomocná funkce doOperation.
** Zpracuje operátor, který je předán parametrem c po načtení znaku ze
** vstupního pole znaků.
**
** Dle priority předaného operátoru a případně priori   ty operátoru na
** vrcholu zásobníku rozhodneme o dalším postupu. Délka převedeného 
** výrazu a taktéž ukazatel na první volné místo, do kterého se má zapisovat, 
** představuje parametr postLen, výstupním polem znaků je opět postExpr.
*/
void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen ) {

    // if stack is empty 
    if(stackEmpty(s)){
        // insert to the top 
        stackPush(s, c); 
        return;
    }

    char top_tmp = (char)stackTop(s);
    // if on top of stack is '(', then
    if (top_tmp == '('){
        // just insert operator
        stackPush(s, c);
        return;
    }

    // if on the top of stack is operator with lower priority, then
    if (((top_tmp == '+') || (top_tmp == '-')) && 
              ((c == '*') || (c == '/'))){
        // insert operator on the top of stack 
        stackPush(s, c);
        return;
    }

    // insert to propriety place in output expression
    postExpr[*postLen] = top_tmp;
    // increment length of output expression
    (*postLen) += 1;
    // remove inserted operator from stack 
    stackPop(s);

    // recursive call of this function 
    doOperation(s, c, postExpr, postLen);
}


/* 
** Konverzní funkce infix2postfix.
** Čte infixový výraz ze vstupního řetězce infExpr a generuje
** odpovídající postfixový výraz do výstupního řetězce (postup převodu
** hledejte v přednáškách nebo ve studijní opoře). Paměť pro výstupní řetězec
** (o velikosti MAX_LEN) je třeba alokovat. Volající funkce, tedy
** příjemce konvertovaného řetězce, zajistí korektní uvolnění zde alokované
** paměti.
**
** Tvar výrazu:
** 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
**    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
**    násobení má stejnou prioritu jako dělení. Priorita násobení je
**    větší než priorita sčítání. Všechny operátory jsou binární
**    (neuvažujte unární mínus).
**
** 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
**    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
**
** 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
**    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
**    chybné zadání výrazu).
**
** 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen 
**    ukončovacím znakem '='.
**
** 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
**
** Poznámky k implementaci
** -----------------------
** Jako zásobník použijte zásobník znaků tStack implementovaný v příkladu c202. 
** Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
**
** Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
**
** Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
** char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
**
** Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
** nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
** by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
** ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
** řetězce konstantu NULL.
*/
char* infix2postfix (const char* infExpr) {

    // prepair all resources 
    // oupput expression 
    char *outExpr = (char *) malloc(MAX_LEN * sizeof(char));
    if (outExpr == NULL){
        printf("error malloc\n");
        return NULL;
    }
    // and stack
    tStack *stack = (tStack *)malloc(sizeof(tStack));
    if(stack == NULL){
        free(outExpr);
        return NULL;
    }
    stackInit(stack);

    unsigned int postLen = 0; // length of ouput expression 
    char c = *infExpr;
    int count = 1;
    while (c != '\0'){
    // for (char c = *infExpr; c != '\0'; c = *(infExpr)++){
        if(((c >= 'a') && (c <= 'z')) || // a .. z
           ((c >= 'A') && (c <= 'Z')) || // A .. Z
           ((c >= '0') && (c <= '9'))    // 0 .. 9
           ){
            // printf("symbol '%s'\n", &c);
            outExpr[postLen++] = c;
        }
        else if( c == '('){
            // printf("left breket '%s'\n", &c);
            stackPush(stack, c);
        }
        else if (c == ')'){
            // printf("right breket '%s'\n", &c);
            untilLeftPar(stack, outExpr, &postLen);
        }
        else if((c == '+') || 
                (c == '-') || 
                (c == '*') || 
                (c == '/')){
                    // printf("operator '%s'\n", &c);
                    doOperation(stack, c, outExpr, &postLen);
        }
        else if(c == '='){
            while(stackEmpty(stack) != 1){
                stackTop(stack, &(outExpr[postLen++]));
                stackPop(stack);
            }
            outExpr[postLen++] = '='; 
            break;
        }

        // take next sumbol
        c = *(infExpr + count); 
        count++;
    }

    outExpr[postLen++] = '\0'; 
    free(stack);
    return outExpr;                /* V případě řešení můžete smazat tento řádek. */
}

/* Konec c204.c */
