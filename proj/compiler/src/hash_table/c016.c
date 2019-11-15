#include "c016.h"
#include <ctype.h>

int HTSIZE = MAX_HTSIZE;

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

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není,
** vrací se hodnota NULL.
**
*/
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

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {

    tHTItem *item = htSearch(ptrht, key);
    
    if (item != NULL){
        // key already exist in hash table
        item->data = data;
        return;
    }
   else{ 
        // create new item to insert 
        tHTItem *new_item = (tHTItem *) malloc(sizeof(tHTItem));
        if(!new_item){
            return; 
        }
        new_item->key = key;
        new_item->data = data;
        new_item->ptrnext = NULL;

        // get index in hash table
        int index = hashCode(key);
        
        item = (*ptrht)[index];

        // if synonim exist
        if(item != NULL){
            // chain it with new item
            new_item->ptrnext = item;
        }
        // insert to the begining
        (*ptrht)[index] = new_item;
    }
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/
tData* htRead ( tHTable* ptrht, tKey key ) {

    tHTItem *item = htSearch(ptrht, key);
    if(item != NULL){
        return &(item->data); 
    }
    return NULL;
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {

    int index = hashCode(key);
    tHTItem *item = (*ptrht)[index];
    tHTItem *next_item = NULL, *prev_item = NULL;

    // go through synonims list and check key
    while (item != NULL){
        next_item = item->ptrnext;

        if(strcmp(item->key, key) == 0){
            
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

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {

    tHTItem *item, *delet_item;

    // go through every index in table 
    for (int i = 0; i < HTSIZE; i++){
        item = (*ptrht)[i];
        // go through every item in linked list
        while(item){
            delet_item = item;
            item = item->ptrnext;
            free(delet_item);
        }
        (*ptrht)[i] = NULL;
    }
}
