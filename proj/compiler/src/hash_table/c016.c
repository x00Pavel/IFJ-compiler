#include "c016.h"
#include <ctype.h>

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

void htInit ( tHTable* ptrht ) {
    // initialize all elements to NULL
    for(int i = 0; i < HTSIZE; i++){
        (*ptrht)[i] = NULL;
    }
}

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

    tHTItem *item = (*ptrht)[hashCode(key)];

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

int htInsert(tHTable *ptrht, tKey key, token_t type)
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
        
        item = (*ptrht)[index];

        // if synonym exist
        if(item != NULL){
            // chain it with new item
            new_item->ptrnext = item;
        }
        // insert to the begining
        (*ptrht)[index] = new_item;
    }
    return NEW;
}

// tData* htRead ( tHTable* ptrht, tKey key ) {

//     tHTItem *item = htSearch(ptrht, key);
//     if(item != NULL){
//         return item->data; 
//     }
//     return NULL;
// }

void htDelete ( tHTable* ptrht, tKey key ) {

    int index = hashCode(key);
    tHTItem *item = (*ptrht)[index];
    tHTItem *next_item = NULL, *prev_item = NULL;

    // go through synonims list and check key
    while (item != NULL){
        next_item = item->ptrnext;

        if(strcmp(item->key, key) == 0){
            free(item->key);
            free(item);

            if(prev_item == NULL){
                // item is in the begining of the list
                (*ptrht)[index] = next_item;
            }
            else{
                // item is in the end or in somewhere else in the list
                prev_item->ptrnext = next_item;                
            }
            return;
        }
        // go to next item to serch key
        prev_item = item;
        item = item->ptrnext;
    }
}

void htClearAll ( tHTable* ptrht ) {

    tHTItem *item, *delete_item;

    // go through every index in table 
    for (int i = 0; i < HTSIZE; i++){
        item = (*ptrht)[i];
        // go through every item in linked list
        while(item){
            delete_item = item;
            item = item->ptrnext;
            free(delete_item->key);
            free(delete_item);
        }
        (*ptrht)[i] = NULL;
    }
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

void htPrintTable(tHTable *ptrht)
{
    int sumcnt = 0;

    printf("------------HASH TABLE--------------\n");
    for (int i = 0; i < HTSIZE; i++)
    {
        printf("%i:", i);
        tHTItem *ptr = (*ptrht)[i];
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