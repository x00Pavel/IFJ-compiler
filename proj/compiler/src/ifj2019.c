#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "errors.h"
#include "scaner.h"

// je nutne udelat v headeru prototipy

int main(int arc, char **argv){
    (void)arc;
    /* Input file */
    FILE *file;
    file = fopen(argv[1], "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }
    while(1){
        struct token_s *token = (struct token_s *)malloc(sizeof(struct token_s));
        // int ret_code = scanner(file, token);
        
        // printf("%d\n", scanner(file, token));
        
        int ret_code = get_token(file, token);
        if(ret_code != 0){
            return -1;
        }
        printf("token type: %d\n\n", token->type);

        if(token->type == TOKEN_ID){
            free(token->attribute.string);
        }
        free(token);
    }
    fclose(file);

    return 0;
}
