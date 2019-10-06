#include <stdio.h>
#include <assert.h>

#include "errors.h"

int main(int arc, char **argv)
{

    /* Input file */
    FILE *file;
    file = fopen(argv[0], "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }
    /* Lexer */

    fclose(file);
    /* Syntax analyzer MAIN PROCESS */

    /* Semantic analyzer */

    /* Intermediate code generator */

    /* Optimizer */

    /* Code generator */

}