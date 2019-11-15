#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include "../scaner.h"

#define MAX_HTSIZE 40

typedef char* tKey;

typedef struct token_s tData;

typedef struct tHTItem{
	tKey key;				 /*< Key                 */
	tData data;				 /*< Value                */
	struct tHTItem* ptrnext; /*< Pointer to next node*/
} tHTItem;

typedef tHTItem* tHTable[MAX_HTSIZE];

extern int HTSIZE;

int hashCode ( tKey key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, tKey key );

void htInsert ( tHTable* ptrht, tKey key, tData data );

tData* htRead ( tHTable* ptrht, tKey key );

void htDelete ( tHTable* ptrht, tKey key );

void htClearAll ( tHTable* ptrht );

#endif
