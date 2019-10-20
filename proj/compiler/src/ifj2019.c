#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "scaner.h"

// je nutne udelat v headeru prototipy

int main(int arc, char **argv){
    (void) (arc);
    /* Input file */
    FILE *file;
    file = fopen("./test.txt", "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }

    token_ptr token = (token_ptr) malloc(sizeof(token_t));

        // WE MUST DO IT IN ANOTHER WAY 
        // when we process one token, then call scaner to give us the next token 
    	scanner(file, token);
		printf("\n token type: %d\n\n", token->type);

    free(token);
    fclose(file);
    /* Lexer */
    /* Syntax analyzer MAIN PROCESS */
    /* Semantic analyzer */

    /* Intermediate code generator */

    /* Optimizer */

    /* Code generator */

}
