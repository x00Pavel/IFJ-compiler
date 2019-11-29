
/**
 * \file ./symtable.c
 * \brief Implementation of symbol table with hash table
 * 
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 * 
 * \note Ispeared by solution from IAL course (du2)
 * 
 * \date 2019
 */

#include <ctype.h>
#include "symtable.h"
#include "errors.h"

int HTSIZE = MAX_HTSIZE;

#ifdef DEBUG
char *types_[] = {

    "TOKEN_INT",    // integer int
    "TOKEN_FLOAT ", // float
    "TOKEN_STRING", // string

    // Operators
    "TOKEN_SUM ",     // +
    "TOKEN_MINUS",    // -
    "TOKEN_ASSIGN",   // =
    "TOKEN_MULTIPLY", // *
    "TOKEN_DIVISION", // /

    // Relation operators
    "TOKEN_EQUAL",      // ==
    "TOKEN_NOT_EQUAL",  // !=
    "TOKEN_GREATER",    // >
    "TOKEN_LESS",       // <
    "TOKEN_GREATER_EQ", // >=
    "TOKEN_LESS_EQ",    // <=

    // Special tokens
    "TOKEN_EOL",      // end of line \n
    "TOKEN_EOF",      // end of file
    "TOKEN_KEY_WORD", // key_word_t
    "TOKEN_EMPTY",    // "white" symbols

    // Punctuations
    "TOKEN_L_BRACKET", // (
    "TOKEN_R_BRACKET", // )
    "TOKEN_DOT",       // .
    "TOKEN_COMA",      // ,
    "TOKEN_SEMICOLON", // ;
    "TOKEN_DDOT",      // :
    "TOKEN_ID",
    "TOKEN_HEX",
    "TOKEN_INDEND", // indend
    "TOKEN_DEDEND", // dedend
    "TOKEN_FNC",
    "TOKEN_NONE",
    "TOKEN_DIV_INT"};

char *kw_[] = {
    "_DEF_",
    "_ELSE_",
    "_IF_",
    "_NONE_",
    "_PASS_",
    "_RETURN_",
    "_WHILE_"};
#endif


int hashCode ( tKey key ) {
	int retval = 1;
	size_t keylen = strlen(key);
	for (size_t i = 0; i < keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

void htInit (table_s *ptrht) {
    // initialize all elements to NULL
    for(int i = 0; i < HTSIZE; i++){
        ptrht->hash_table[i] = NULL;
    }
    ptrht->prev_hash_table = NULL;

}

tHTItem* htSearch (table_s *ptrht, tKey key ) {

    tHTItem *item = (ptrht->hash_table)[hashCode(key)];

    while(item){
        if (strcmp(key, item->key) == 0){
            return item;
        }
        else{
            item = item->ptrnext;
        }
    }
    return NULL;

}

tHTItem* search_everywhere(table_s *ptrht, tKey key){

    tHTItem *item;

    while (ptrht != NULL){
        item = htSearch(ptrht, key);
        if(item){
            return item;
        }
        ptrht = ptrht->prev_hash_table;
    }
    return NULL;
}

int htInsert(table_s *ptrht, tKey key, token_t type)
{
    tHTItem *item = htSearch(ptrht, key);
    
    if (item != NULL){
        // key already exist in hash table
        return FOUND;
    }
   else{ 
        // create new item to insert 
        tHTItem *new_item = (tHTItem *) malloc(sizeof(tHTItem));
        if(!new_item){
            return ERR; 
        }
        new_item->key = (char*) malloc(sizeof(char) * strlen(key) + 1);
        strcpy(new_item->key, key);
        new_item->type = type;
        new_item->ptrnext = NULL;

        // get index in hash table
        int index = hashCode(key);
        
        item = (ptrht->hash_table)[index];

        // if synonym exist
        if(item != NULL){
            // chain it with new item
            new_item->ptrnext = item;
        }
        // insert to the begining
        (ptrht->hash_table)[index] = new_item;
    }   
    return NEW;
}


void htDelete ( table_s* ptrht, tKey key ) {

    int index = hashCode(key);
    tHTItem *item = (ptrht->hash_table)[index];
    tHTItem *next_item = NULL, *prev_item = NULL;

    // go through synonyms list and check key
    while (item != NULL){
        next_item = item->ptrnext;

        if(strcmp(item->key, key) == 0){
            free(item->key);
            free(item);

            if(prev_item == NULL){
                // item is in the begining of the list
                (ptrht->hash_table)[index] = next_item;
            }
            else{
                // item is in the end or in somewhere else in the list
                prev_item->ptrnext = next_item;                
            }
            return;
        }
        // go to next item to search key
        prev_item = item;
        item = item->ptrnext;
    }
}

int htClearAll(table_s *hash_table, bool ok)
{

    tHTItem *item, *delete_item;

    // go through every index in table 
    for (int i = 0; i < HTSIZE; i++){
        item = hash_table->hash_table[i];
        // go through every item in linked list
        while(item){
            delete_item = item;
            if(ok){
                if(delete_item->type == TOKEN_FNC){
                    if(!delete_item->id_declared){
                        fprintf(stderr,"Function is not decleared\n");
                        return ERR_UNDEF;
                    }
                }
            }
            item = item->ptrnext;
            free(delete_item->key);
            free(delete_item);
        }
        hash_table->hash_table[i] = NULL;
    }
    return OK;
}

#ifdef DEBUG
void htPrintItem(tHTItem *item)
{
    if (item){
        printf("Key: %s -- Type: %s", item->key, types_[item->type]);
    }
    else{
        printf("NULL\n");
    }
}

void htPrintTable(table_s *ptrht)
{
    int sumcnt = 0;

    printf("------------HASH TABLE--------------\n");
    for (int i = 0; i < HTSIZE; i++)
    {
        printf("%i:", i);
        tHTItem *ptr = (ptrht->hash_table)[i];
        while (ptr != NULL)
        {   
            printf("(");
            htPrintItem(ptr);
            ptr = ptr->ptrnext;
            sumcnt++;
            printf(")");
        }
        printf("\n");
    }

    printf("------------------------------------\n");
    printf("Items count %i  \n", sumcnt);
    printf("------------------------------------\n");
}
#endif