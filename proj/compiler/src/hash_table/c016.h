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

typedef struct table{
	tHTItem * hash_table[MAX_HTSIZE];
	struct table *prev_hash_table;
} table_s;

extern int HTSIZE;

int hashCode ( tKey key );

void htInit(table_s *ptrht);

tHTItem *htSearch(table_s *ptrht, tKey key);

int htInsert(table_s *ptrht, tKey key, token_t type);

bool find_key(table_s *ptrht, tKey key);

void htDelete(table_s *ptrht, tKey key);

void htClearAll(tHTItem *ptrht[MAX_HTSIZE]);

void htPrintItem(tHTItem *ptritem);

void htPrintTable(table_s *ptrht);

#endif
