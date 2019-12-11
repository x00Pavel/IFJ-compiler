/**
 * \file ./dynamic_string.c
 * \brief Implimentation of symbol table using hash table
 *
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 *
 * \date 2019
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_string.h"
#include "errors.h"

#ifndef __STDBOOL_H
#include <stdbool.h>
#endif

#define DEF_STR_SIZE 8

void str_clean(dynamic_string_ptr str) {
    assert(str);

    if (str->str != NULL) {
        free(str->str);
    }
    if (str != NULL) {
        free(str);
    }
}

int realloc_string(dynamic_string_ptr *str) {
    assert(str != NULL);

    (*str)->str = (string)realloc((*str)->str, (*str)->size + DEF_STR_SIZE);
    if ((*str)->str == NULL) {
        str_clean(*str);
        return 99;
    }

    (*str)->size += DEF_STR_SIZE;

    return 0;
}

bool add_char_to_str(dynamic_string_ptr dst, int src) {
    assert(src);
    assert(dst);

    if (dst->len + 1 >= dst->size) {
        if (realloc_string(&dst) != 0) {
            return false;
        }
    }

    dst->str[dst->len++] = (char)src;
    dst->str[dst->len] = '\0';

    return true;
}

void str_init(dynamic_string_ptr *str) {
    *str = (dynamic_string_ptr)malloc(sizeof(struct dynamic_string));
    if (!str) {
        return;
    }

    (*str)->str = (string)malloc(DEF_STR_SIZE);
    if (!(*str)->str) {
        return;
    }
    (*str)->size = DEF_STR_SIZE;
    (*str)->len = 0;
}
