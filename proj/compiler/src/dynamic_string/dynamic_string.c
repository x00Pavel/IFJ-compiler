#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../errors.h"
#include "dynamic_string.h"

#ifndef __STDBOOL_H
    #include <stdbool.h>
#endif

void str_clean(dynamic_string_ptr str){
    assert(str != NULL);

    if(str->str != NULL){
        free(str->str);
    }

    str->len = 0;
    str->size = 0;
}

int realloc_string(dynamic_string_ptr str){
    assert(str != NULL);

    str->str = (string)realloc(str->str, str->size + DEF_STR_SIZE);
    if(str->str == NULL){
        str_clean(str);
        return ERR_INTERNAL;
    }

    str->size += DEF_STR_SIZE;

    return 0;
}

bool add_chat_to_str(dynamic_string_ptr dst, char* src){
    assert(src != NULL);
    assert(dst != NULL);

    if(dst->len + 1 >= dst->size){
        if(realloc_string(dst) != 0){
            return false;
        }
    }

    dst->str[dst->len++] = src;
    dst->str[dst->len] = '\0';

    return true;
}

void string_init(dynamic_string_ptr str){

    str->str = (string)malloc(DEF_STR_SIZE);
    if(!str->str){
        return NULL;
    }

    str->size = DEF_STR_SIZE;
    str->len = 0;

    return str;
}

inline bool str_cmp(string dst, string src){
    if (strcmp(dst, src) == 0){
        return true;
    }
    else{
        return false;
    }
}
