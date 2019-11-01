
/* ******************************* c202.h *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c202 - Zásobník znaků v poli                                        */
/*  Hlavičkový soubor pro c202.c                                              */
/*  Vytvořil: Václav Topinka, září 2005                                       */
/*  Úpravy: Kamil Jeřábek, září 2019                                         */
/* ************************************************************************** */

/* TENTO SOUBOR, PROSÍME, NEUPRAVUJTE! */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>

#define MAX_STACK 20
extern int STACK_SIZE; 

extern int solved;                     
extern int err_flag;                 

                                        
#define MAX_SERR    3                                   
#define SERR_INIT   1                                 
#define SERR_PUSH   2                                 
#define SERR_TOP    3                                   

                            
typedef struct stack {
	int arr[MAX_STACK];                           
	int top;                                
} tStack;

                                 
void stackError ( int error_code );
void stackInit ( tStack* s );
int stackEmpty ( const tStack* s );
int stackFull ( const tStack* s );
int stackTop ( const tStack* s);
void stackPop ( tStack* s );
void stackPush ( tStack* s, int c );

#endif
