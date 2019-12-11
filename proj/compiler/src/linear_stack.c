
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2019
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "linear_stack.h"
#include "preced_analyze.h"

int solved;
int errflg;

void DLError() {
    /*
     ** Vytiskne upozornění na to, že došlo k chybě.
     ** Tato funkce bude volána z některých dále implementovaných operací.
     **/
    printf("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE; /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList(tDLList *L) {
    /*
     ** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
     ** z následujících funkcí nebude volána nad neinicializovaným seznamem).
     ** Tato inicializace se nikdy nebude provádět nad již inicializovaným
     ** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
     ** že neinicializované proměnné mají nedefinovanou hodnotu.
     **/

    L->First = NULL;
    L->Last = NULL;
    L->Act = NULL;

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLDisposeList(tDLList *L) {
    /*
     ** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
     ** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
     ** uvolněny voláním operace free.
     **/

    if (L->First != NULL) {
        tDLElemPtr tmp = L->First;
        while (L->First != NULL) {
            L->First = L->First->rptr;
            free(tmp);
            tmp = L->First;
        }
        L->Act = NULL;
        L->Last = NULL;
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}
void DLInsertFirst(tDLList *L, int val) {
    /*
     ** Vloží nový prvek na začátek seznamu L.
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    tDLElemPtr tmp = (tDLElemPtr)malloc(sizeof(struct tDLElem));
    if (tmp == NULL) {
        DLError();
    }

    tmp->data = val;
    tmp->rptr = L->First;
    tmp->lptr = NULL;

    if (L->First != NULL) {
        // iserting to non empty list
        L->First->lptr = tmp;
    } else {
        // iserting to empty list
        L->Last = tmp;
    }

    L->First = tmp;

    // solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
    /*
     ** Vloží nový prvek na konec seznamu L (symetrická operace k
     *DLInsertFirst).
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/

    tDLElemPtr tmp = (tDLElemPtr)malloc(sizeof(struct tDLElem));
    if (tmp == NULL) {
        DLError();
    }

    tmp->data = val;
    tmp->lptr = L->Last;
    tmp->rptr = NULL;

    if (L->Last != NULL) {
        // iserting to non empty list
        L->Last->rptr = tmp;
    }

    L->Last = tmp;

    // solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

void DLFirst(tDLList *L) {
    /*
     ** Nastaví aktivitu na první prvek seznamu L.
     ** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
     ** aniž byste testovali, zda je seznam L prázdný.
     **/

    L->Act = L->First;
    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLLast(tDLList *L) {
    /*
     ** Nastaví aktivitu na poslední prvek seznamu L.
     ** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
     ** aniž byste testovali, zda je seznam L prázdný.
     **/

    L->Act = L->Last;

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLCopyFirst(tDLList *L, int *val) {
    /*
     ** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
     ** Pokud je seznam L prázdný, volá funkci DLError().
     **/

    if (L->First == NULL) {
        DLError();
        return;
    } else {
        *val = L->First->data;
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLCopyLast(tDLList *L, int *val) {
    /*
     ** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
     ** Pokud je seznam L prázdný, volá funkci DLError().
     **/
    if ((L->First == NULL)) {
        DLError();
        return;
    } else {
        *val = L->Last->data;
    }

    // solved = FALSE;  s                 /* V případě řešení, smažte tento
    // řádek! */
}

void DLDeleteFirst(tDLList *L) {
    /*
     ** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
     ** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
     **/
    if (L->First != NULL) {
        tDLElemPtr tmp;
        tmp = L->First;
        if (L->Act == L->First) {
            L->Act = NULL;
        }

        if (L->Last == L->First) {
            L->First = NULL;
            L->Last = NULL;
        } else {
            L->First = L->First->rptr;
            L->First->lptr = NULL;
        }
        free(tmp);
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLDeleteLast(tDLList *L) {
    /*
     ** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
     ** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
     **/
    if (L->First != NULL) {
        tDLElemPtr tmp;
        tmp = L->Last;
        if (L->Act == L->Last) {
            L->Act = NULL;
        }

        if (L->Last == L->First) {
            L->First = NULL;
            L->Last = NULL;
        } else {
            L->Last = L->Last->lptr;
            L->Last->rptr = NULL;
        }
        free(tmp);
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLPostDelete(tDLList *L) {
    /*
     ** Zruší prvek seznamu L za aktivním prvkem.
     ** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
     ** posledním prvkem seznamu, nic se neděje.
     **/
    if ((L->Act != NULL) && (L->Act != L->Last)) {
        tDLElemPtr tmp;

        // save pointer to element after element we want to delete
        tmp = L->Act->rptr;
        L->Act->rptr = tmp->rptr;
        if (tmp == L->Last) {
            L->Last = L->Act;
        } else {
            tmp->rptr->lptr = L->Act;
        }
        free(tmp);
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLPreDelete(tDLList *L) {
    /*
     ** Zruší prvek před aktivním prvkem seznamu L .
     ** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
     ** prvním prvkem seznamu, nic se neděje.
     **/
    if ((L->Act != NULL) && (L->Act != L->First)) {
        tDLElemPtr tmp;

        // save pointer to element after element we want to delete
        tmp = L->Act->lptr;
        L->Act->lptr = tmp->lptr;
        if (tmp == L->First) {
            L->First = L->Act;
        } else {
            tmp->lptr->rptr = L->Act;
        }
        free(tmp);
    }

    //  solved = FALSE;                   /* V případě řešení, smažte tento
    //  řádek! */
}

void DLPostInsert(tDLList *L, int val) {
    /*
     ** Vloží prvek za aktivní prvek seznamu L.
     ** Pokud nebyl seznam L aktivní, nic se neděje.
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    if (L->Act != NULL) {
        tDLElemPtr new_elem;
        new_elem = (tDLElemPtr)malloc(sizeof(struct tDLElem));
        if (new_elem == NULL) {
            DLError();
        }

        new_elem->data = val;

        // set correct pointers
        new_elem->rptr = L->Act->rptr;
        new_elem->lptr = L->Act;
        L->Act->rptr = new_elem;

        if (L->Act == L->Last) {
            // if active element was first element
            L->Last = new_elem;
        } else {
            new_elem->rptr->lptr = new_elem;
        }
    }
}

void DLPreInsert(tDLList *L, int val) {
    if (L->Act != NULL) {
        tDLElemPtr new_elem;
        new_elem = (tDLElemPtr)malloc(sizeof(struct tDLElem));
        if (new_elem == NULL) {
            DLError();
        }

        new_elem->data = val;

        // set correct pointers
        new_elem->lptr = L->Act->lptr;
        new_elem->rptr = L->Act;
        L->Act->lptr = new_elem;

        if (L->Act == L->First) {
            // if active element was first element
            L->First = new_elem;
        } else {
            new_elem->lptr->rptr = new_elem;
        }
    }
}

void DLCopy(tDLList *L, int *val) {
    if (L->Act == NULL) {
        DLError();
    } else {
        *val = L->Act->data;
    }
}

void get_element(tDLList *L, struct tDLElem *val) {
    (void)val;
    if (L->Act == NULL) {
        DLError();
    } else {
        val = L->Act;
    }
}
void DLActualize(tDLList *L, int val) {
    if (L->Act != NULL) {
        L->Act->data = val;
    }
}

void DLSucc(tDLList *L) {
    if (L->Act) {
        L->Act = L->Act->rptr;
    }
}

void DLPred(tDLList *L) {
    if (L->Act == L->First) {
        L->Act = NULL;
    } else {
        L->Act = L->Act->lptr;
    }
}

int DLActive(tDLList *L) {
    /*
     ** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
     ** Funkci je vhodné implementovat jedním příkazem return.
     **/
    return (L->Act != NULL) ? 1 : 0;
}

void insert_after_term(tDLList *list, int s) {
    DLLast(list);
    struct tDLElem *tmp = (struct tDLElem *)malloc(sizeof(struct tDLElem));
    get_element(list, tmp);
    while (tmp->data >= ID_NT) {
        DLPred(list);
        get_element(list, tmp);
    }
    free(tmp);
    DLPostInsert(list, s);
    DLLast(list);
}