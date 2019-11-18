#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../scaner.h"


#define MAX_HTSIZE 40

#define ERR -1
#define NEW 0
#define FOUND 1

typedef char* tKey;

typedef struct tHTItem{
	tKey key;				 /*< Key - name of id                 */
	token_t type;			 /*< Token type                       */
	bool id_declared;        /*< Flag for declared identeficators */
	struct tHTItem* ptrnext; /*< Pointer to next node             */
} tHTItem;

typedef tHTItem* tHTable[MAX_HTSIZE];

extern int HTSIZE;

int hashCode ( tKey key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, tKey key );

int htInsert(tHTable *ptrht, tKey key, token_t type);

void htDelete(tHTable *ptrht, tKey key);

void htClearAll ( tHTable* ptrht );

void htPrintItem(tHTItem *ptritem);

void htPrintTable(tHTable *ptrht);

#endif
