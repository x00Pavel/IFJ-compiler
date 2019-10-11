#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include "scaner.h"

void scaner(char *str){
int c;
	for( int i = 0; (c = getchar()) != ' ' || c != '\n' || c != EOF ; i++)
	{
	str[i] = c;
	}
	check(str, &c);
	//scaner(str);
}

void check(char *str, int *c){
for (int i = 0; i < 7; i++){ // analogicke funcke pro ostatni typy atributu
	if( *str == *key_word_arr[i]){
		printf("TOKEN+\n"); // sem pridame funcki pro vytvoreni tokenu
		}
	}
	if(c != EOF){ // kdyz nejsme na konci souboru, tak hledame dalsi slovo
	scaner(str);
	}
}

void create_token(){

}

int main(int arc, char **argv)
{
	char str[50];
    /* Input file */
    FILE *file;
    file = fopen(argv[0], "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }
    /* Lexer */
    	scaner(str);
    fclose(file);
    /* Syntax analyzer MAIN PROCESS */

    /* Semantic analyzer */

    /* Intermediate code generator */

    /* Optimizer */

    /* Code generator */

}
