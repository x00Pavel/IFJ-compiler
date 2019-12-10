/**
 * \file ./symtable.h
 * \brief Header of symbol table with hash table
 * 
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 * 
 * \note Ispeared by solution from IAL course (du2)
 * 
 * \date 2019
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scaner.h"


#define MAX_HTSIZE 40

#define ERR -1
#define NEW 0
#define FOUND 1

typedef char* tKey;

typedef struct tHTItem{
	tKey key;				 /*< Key - name of id                 */
	token_t type;			 /*< Token type                       */
	token_t ret_val;		 /*< Type of return value */
	int param_count;         /*< Count of paramters for functions */
	bool id_declared;        /*< Flag for declared identeficators */
	int in_if;
	int in_else;
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

tHTItem *search_everywhere(table_s *ptrht, tKey key);

void htDelete(table_s *ptrht, tKey key);

int htClearAll(table_s *hash_table, bool ok);

void htPrintItem(tHTItem *ptritem);

void htPrintTable(table_s *ptrht);

#endif
