#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "errors.h"
#include "scaner.h"

// je nutne udelat v headeru prototipy



int main(int arc, char **argv){
	
    /* Input file */
    FILE *file;
    file = fopen(argv[0], "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }

    token_ptr token;
	while(token->type != TOKEN_EOF){
		scanner(file, token);
		printf("\ntoken type: %d\n\n", token->type);
	}
    /* Lexer */
    fclose(file);
    /* Syntax analyzer MAIN PROCESS */

    /* Semantic analyzer */

    /* Intermediate code generator */

    /* Optimizer */

    /* Code generator */

}
